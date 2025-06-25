#include "GraphPainter.h"

namespace FuzzFlow {

string GraphPainter::to_dot(shared_ptr<Graph> graph, bool rescheduling_index)
{
    string dot_code = "digraph{\n";

    /// The node index is only used in painting.
    /// So we generate the indexes when painting.
    map<weak_ptr<IRNode>,
        unsigned int,
        std::owner_less<>> node2index;

    if (rescheduling_index) {
        unsigned int index = 1;
        for (auto& node : graph->nodes) {
            node2index[node] = index ++;
        }
    }
    else {
        for (auto& node : graph->nodes) {
            node2index[node] = node->index;
        }
    }

    for (auto& node : graph->nodes) {
        /// Draw the node
        string fill_color = "lightgray";

        bool is_producer = false;
        if (auto float_node = dynamic_pointer_cast<DataProducerNode>(node)){
            is_producer = true;
        }

        if (dynamic_pointer_cast<FixedNode>(node)){
            if (dynamic_pointer_cast<FunctionHeadNode>(node)){
                fill_color = "lightgreen";
            }
            else {
                fill_color = "lightblue";
            }
        }
        else if (auto float_node = dynamic_pointer_cast<DataProducerNode>(node)){
            if (dynamic_pointer_cast<BuiltinNode>(float_node)) {
                fill_color = "Turquoise";
            }
            else {
                fill_color = "orange";
            }
        }

        bool is_object_access = false;
        if (dynamic_pointer_cast<AccessObjectNode>(node)) {
            fill_color = "pink";
            is_object_access = true;
        }

        string attached_var_names;
        if (is_producer) {
            auto float_node = dynamic_pointer_cast<DataProducerNode>(node);
            for (auto& [_proxy, _node] : graph->varProxy2node){

                shared_ptr<DataProducerNode> _float_node = dynamic_pointer_cast<DataProducerNode>(_node.lock());
                //if ((_float_node != nullptr) && _float_node->equals(float_node)) {
                if (_float_node == float_node) {
                    if (!attached_var_names.empty()){
                        attached_var_names += ", ";
                    }
                    attached_var_names += _proxy->get_label();
                }
            }
        }

        if (! attached_var_names.empty()) {
            attached_var_names = "(" + attached_var_names + ")";
        }

        string node_label = std::to_string(node2index[node]) + " ";
        node_label += node->get_label() + attached_var_names;
        node_label += "\\n";

        string uses_label;
        if (is_producer) {
            auto producer = dynamic_pointer_cast<DataProducerNode>(node);
            uses_label = " u:" + std::to_string(producer->uses.size());
        }

        string inputs_label;
        if (auto consumer = dynamic_pointer_cast<DataConsumerNode>(node)) {
            inputs_label = " i:" + std::to_string(consumer->inputs.size());
        }

        node_label += uses_label;
        node_label += inputs_label;

        dot_code += "\tnode";
        dot_code += std::to_string(node2index[node]);
        dot_code += R"( [ shape="box", style="filled", color="black", label=")";
        dot_code += node_label + "\"";
        dot_code += ", fillcolor=\"" + fill_color + "\"";
        dot_code += "]\n";
    }

    dot_code += "\n";

    /// Draw the edges
     
    string line_style_data = R"( [color="orange"])";
    string line_style_control = R"( [color="blue"])";

    for (auto& node : graph->nodes) {
        string node_name = "node" + std::to_string(node2index[node]);

        if (auto uni_node = dynamic_pointer_cast<UniSuccessorNode>(node); uni_node != nullptr) {
            dot_code += "\t" + node_name;
            dot_code += " -> node" + std::to_string(node2index[uni_node->next()]);
            dot_code += line_style_control + "\n";

            if (auto merge_node = dynamic_pointer_cast<AbstractMergeNode>(node)){
                for (auto& _merged_end : merge_node->merged_flows){
                    dot_code += "\t" + node_name + " -> node" + std::to_string(node2index[_merged_end]) + "\n";
                }
            }
            else if (auto relay_node = dynamic_pointer_cast<CtrlRelayNode>(node)){
                dot_code += "\t" + node_name + " -> node" + std::to_string(node2index[relay_node->merged_flows[0].lock()]) + "\n";
            }
            else if (auto try_node = dynamic_pointer_cast<TryNode>(node)) {
                if (! try_node->catch_node.expired()) {
                    dot_code += "\t" + node_name + " -> node" + std::to_string(node2index[try_node->catch_node.lock()]) + "\n";
                }

                if (! try_node->finally_node.expired()) {
                    dot_code += "\t" + node_name + " -> node" + std::to_string(node2index[try_node->finally_node.lock()]) + "\n";
                }
            }
        }
        else if (auto ret_node = dynamic_pointer_cast<ReturnNode>(node)){
            if (ret_node->return_value().has_value()){
                dot_code += "\t" + node_name + " -> node" + std::to_string(node2index[ret_node->return_value().value()]) + "\n";
            }
        }
        else if(auto node_unwind = dynamic_pointer_cast<UnwindNode>(node)) {
            if (node_unwind->exception_node() != nullptr) {
                dot_code += "\t" + node_name + " -> node";
                dot_code += std::to_string(node2index[node_unwind->exception_node()]);
                dot_code += "\n";
            }
        }
        else if (auto if_node = dynamic_pointer_cast<IfNode>(node)){
            dot_code += "\t" + node_name + " -> node";
            dot_code += std::to_string(node2index[if_node->condition()]) + "\n";

            dot_code += "\t" + node_name + " -> node";
            dot_code += std::to_string(node2index[if_node->branch_true()]) + line_style_control + "\n";

            dot_code += "\t" + node_name + " -> node";
            dot_code += std::to_string(node2index[if_node->branch_false()]) + line_style_control + "\n";
        }
        else if (auto for_in_enum = dynamic_pointer_cast<ForInEnum>(node)){
            dot_code += "\t" + node_name + " -> node";
            dot_code += std::to_string(node2index[for_in_enum->enumPropName()]) + "\n";

            dot_code += "\t" + node_name + " -> node";
            dot_code += std::to_string(node2index[for_in_enum->enumObject()]) + "\n";

            dot_code += "\t" + node_name + " -> node";
            dot_code += std::to_string(node2index[for_in_enum->branch_true()]) + line_style_control + "\n";

            dot_code += "\t" + node_name + " -> node";
            dot_code += std::to_string(node2index[for_in_enum->branch_false()]) + line_style_control + "\n";
        }
        else if (auto loop_end_node = dynamic_pointer_cast<LoopEnd>(node)){
            int begin_index = node2index[loop_end_node->loop_begin()];
            dot_code += "\t" + node_name + " -> node" + std::to_string(begin_index) + "\n";
        }

        if (auto consumer = dynamic_pointer_cast<DataConsumerNode>(node)) {
            for (auto& _input : consumer->inputs){
                dot_code += "\t" + node_name + " -> node";
                dot_code += std::to_string(node2index[_input]) + line_style_data + "\n";
            }

            if (auto phi_node = dynamic_pointer_cast<PhiNode>(consumer)){
                dot_code += "\t" + node_name + " -> node" + std::to_string(node2index[phi_node->merge_node]) + "\n";
            }
        }
    }

    dot_code += "}\n";
    return dot_code;
}

} /// end of namespace