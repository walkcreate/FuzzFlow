#ifndef FUZZFLOW_OBJECTLITERALNODE_H
#define FUZZFLOW_OBJECTLITERALNODE_H

#include "../../js2graph/Graph.h"

#include "../LiteralNode.h"
#include "PropExprAssignNode.h"
#include "FunctionPropertyNode.h"

/**
 * ObjectLiteral is composed of propertyAssignment.
 *
 * We consider three production rules of propertyAssignment:
 * PropertyExpressionAssignment, ComputedPropertyExpressionAssignment, and FunctionProperty
 */

namespace FuzzFlow {

class ObjectLiteralNode final : public LiteralNode,
                                public DataConsumerNode
{
private:
    static const string label;

    /// PropertyAssignment propertyName
    unsigned int prop_expr_assignments_size = 0;

    /// FunctionPropertyNode
    /// TODO: Is it necessary to separate FunctionProperty from other PropertyAssignments?
    unsigned int function_properties_size = 0;

public:
    /*
     * This map acts like a FunctionPropertyNode
     *
     * save the FunctionProperty's graph
     * FunctionProperty's prop name -> function graph
     */

    ObjectLiteralNode()
    {
        this->node_hash_current = this->label;
    }

    string get_label() override
    {
        return ObjectLiteralNode::label;
    }

    void post_construct(const vector<weak_ptr<PropExprAssignNode>>& prop_expr_assignments,
                        const vector<weak_ptr<FunctionPropertyNode>>& func_properties)
    {
        this->inputs.clear();

        /*
         * PropertyAssignments including FunctionProperty are all data producers
         */
        this->prop_expr_assignments_size = prop_expr_assignments.size();
        this->function_properties_size = func_properties.size(); // TODO: useful?

        /// both normal property assignments and FunctionProperties are all inputs of
        /// ObjectLiteralNode
        for (auto &prop: prop_expr_assignments) {
            this->inputs.push_back(prop);
        }
        for (auto &prop: func_properties) {
            this->inputs.push_back(prop);
        }

        this->DataConsumerNode::post_construct();
    }

    vector<shared_ptr<PropExprAssignNode>> prop_expr_assignments() const
    {
        vector<shared_ptr<PropExprAssignNode>> _prop_expr_assignments;

        for (int i = 0; i < this->prop_expr_assignments_size; i++) {
            _prop_expr_assignments.push_back(
                dynamic_pointer_cast<PropExprAssignNode>(this->inputs[i].lock()));
        }

        return _prop_expr_assignments;
    }

    vector<shared_ptr<FunctionPropertyNode>> function_properties() const
    {
        vector<shared_ptr<FunctionPropertyNode>> _func_properties;

        for (unsigned int i = prop_expr_assignments_size;
             i < this->prop_expr_assignments_size + this->function_properties_size; i++) {
            _func_properties.push_back(
                dynamic_pointer_cast<FunctionPropertyNode>(this->inputs[i].lock()));
        }

        return _func_properties;
    }

    shared_ptr<IRNode> clone() override
    {
        auto new_node = make_shared<ObjectLiteralNode>();

        /// Do not call post-construct on the new node now, as it would incorrectly update
        /// the `uses` of the original property assignment node.
        /// At this point, recording the new object literal node in the original node's
        /// `uses` would be incorrect.
        /// Instead, only update the `inputs` of the new node here.
        /// The `uses` of these inputs will be updated during the repair phase.

        /// PropertyAssignments including FunctionProperty are all FloatingNodes.
        new_node->prop_expr_assignments_size = this->prop_expr_assignments().size();
        new_node->function_properties_size = this->function_properties().size(); // TODO: useful?

        /// both normal property assignments and FunctionProperties are all inputs of
        /// ObjectLiteralNode
        for (auto &prop: this->prop_expr_assignments()) {
            new_node->inputs.push_back(prop);
        }

        for (auto &prop: this->function_properties()) {
            new_node->inputs.push_back(prop);
        }

        return new_node;
    }

    void clone_repair(map<weak_ptr<IRNode>, weak_ptr<IRNode>, std::owner_less<>> &refNode2ownNode) override
    {
        vector<weak_ptr<PropExprAssignNode>> real_prop_expr_assignments;
        vector<weak_ptr<FunctionPropertyNode>> real_func_properties;

        for (auto &node: prop_expr_assignments()) {
            ASSERT_OR_EXIT(refNode2ownNode.contains(node));
            ASSERT_OR_EXIT(! refNode2ownNode[node].expired());

            auto real_node = refNode2ownNode.at(node);
            auto real_prop_node = dynamic_pointer_cast<PropExprAssignNode>(real_node.lock());

            real_prop_expr_assignments.push_back(real_prop_node);

            ASSERT_OR_EXIT(real_prop_node != nullptr);
        }

        for (auto &node: function_properties()) {
            ASSERT_OR_EXIT(refNode2ownNode.contains(node));
            ASSERT_OR_EXIT(! refNode2ownNode[node].expired());

            auto real_node = refNode2ownNode.at(node);
            auto real_prop_node = dynamic_pointer_cast<FunctionPropertyNode>(real_node.lock());

            real_func_properties.push_back(real_prop_node);

            ASSERT_OR_EXIT(real_prop_node != nullptr);
        }

        this->post_construct(real_prop_expr_assignments, real_func_properties);
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<ObjectLiteralNode>(shared_from_this());
        visitor.visit(node);
    }

    string get_producer_expr(JavaScriptLifter &visitor) override;
};

} /// end of namespace

#endif //FUZZFLOW_OBJECTLITERALNODE_H
