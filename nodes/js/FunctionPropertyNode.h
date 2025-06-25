#ifndef FUZZFLOW_FUNCTIONPROPERTYVALUE_H
#define FUZZFLOW_FUNCTIONPROPERTYVALUE_H

#include "../../js2graph/Graph.h"

#include "../DataProducerNode.h"
#include "../DataConsumerNode.h"

///
/// Although the function property's value is a separate function (which will exist as an independent graph),
/// we still need to represent the function property within the ObjectLiteralNode to maintain complete object
/// property semantics.
/// This ensures proper handling during the graph2js phase.
///
namespace FuzzFlow {

class FunctionPropertyNode final : public DataProducerNode,
                                   public DataConsumerNode
{
private:
    static const string label;

public:
    weak_ptr<Graph> function_graph;

    FunctionPropertyNode(const weak_ptr<DataProducerNode> &property_name,
                         const weak_ptr<Graph> &graph)
    {
        this->inputs.push_back(property_name);
        this->function_graph = graph;
    }

    string get_label() override
    {
        return FunctionPropertyNode::label;
    }

    shared_ptr<DataProducerNode> property_name() const
    {
        if (this->inputs.empty()) {
            return nullptr;
        }

        return this->inputs[0].lock();
    }

    void set_property_name(const weak_ptr<DataProducerNode> &member_index)
    {
        this->inputs.clear();
        this->inputs.push_back(member_index);
    }

    shared_ptr<IRNode> clone() override
    {
        auto new_node = make_shared<FunctionPropertyNode>(this->property_name(), this->function_graph);
        return new_node;
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<FunctionPropertyNode>(shared_from_this());
        visitor.visit(node);
    }
};

} /// end of namespace

#endif //FUZZFLOW_FUNCTIONPROPERTYVALUE_H
