#ifndef FUZZFLOW_IFNODE_H
#define FUZZFLOW_IFNODE_H

#include "IRNode.h"
#include "FixedNode.h"
#include "BeginNode.h"
#include "EndNode.h"
#include "DataProducerNode.h"
#include "DataConsumerNode.h"
#include "MergeNode.h"

namespace FuzzFlow {

class IfNode : public FixedNode,
               public DataConsumerNode
{
private:
    static const string label;
    pair<weak_ptr<FixedNode>, weak_ptr<FixedNode>> successors;

public:
    IfNode(const weak_ptr<DataProducerNode> &condition,
           const weak_ptr<FixedNode> &b_then,
           const weak_ptr<FixedNode> &b_else)
    {
        this->inputs.push_back(condition);
        this->successors = {b_then, b_else};
    }

    string get_label() override
    {
        return IfNode::label;
    }

    void post_construct() override
    {
        this->DataConsumerNode::post_construct();

        const weak_ptr<IfNode> node_self = dynamic_pointer_cast<IfNode>(shared_from_this());

        this->branch_true()->predecessor = node_self;
        this->branch_false()->predecessor = node_self;
    }

    shared_ptr<DataProducerNode> condition() const
    {
        return this->inputs[0].lock();
    }

    shared_ptr<FixedNode> branch_true() const
    {
        /// When we call this function, we are always going to access the node.
        /// So we return a shared ptr
        return this->successors.first.lock();
    }

    shared_ptr<FixedNode> branch_false() const
    {
        return this->successors.second.lock();
    }

    /// todo ?
    shared_ptr<MergeNode> merge() const
    {
        shared_ptr<BeginNode> begin_node = std::dynamic_pointer_cast<BeginNode>(this->branch_true());
        assert((begin_node != nullptr));

        shared_ptr<EndNode> end_node = std::dynamic_pointer_cast<EndNode>(begin_node->next());
        assert((end_node != nullptr));

        shared_ptr<MergeNode> merge_node = std::dynamic_pointer_cast<MergeNode>(end_node->merge_node.lock());
        assert((merge_node != nullptr));

        return merge_node;
    }

    shared_ptr<IRNode> clone() override
    {
        auto new_node = make_shared<IfNode>(this->condition(),
            this->branch_true(),
            this->branch_false());

        return new_node;
    }

    void clone_repair(map<weak_ptr<IRNode>,
                          weak_ptr<IRNode>,
                            std::owner_less<>>& refNode2ownNode) override
    {
        this->DataConsumerNode::clone_repair(refNode2ownNode);

        ASSERT_OR_EXIT(refNode2ownNode.contains(this->successors.first));
        ASSERT_OR_EXIT(! refNode2ownNode[this->successors.first].expired());
        ASSERT_OR_EXIT(refNode2ownNode.contains(this->successors.second));
        ASSERT_OR_EXIT(! refNode2ownNode[this->successors.second].expired());

        this->successors.first = dynamic_pointer_cast<FixedNode>(
            refNode2ownNode[this->successors.first].lock());

        this->successors.second = dynamic_pointer_cast<FixedNode>(
            refNode2ownNode[this->successors.second].lock());

        ASSERT_OR_EXIT(this->successors.first.lock() != nullptr);
        ASSERT_OR_EXIT(this->successors.second.lock() != nullptr);

        this->post_construct();
    }

    void swap_branches()
    {
        const auto tmp = this->successors.first;
        this->successors.first = this->successors.second;
        this->successors.second = tmp;
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<IfNode>(shared_from_this());
        visitor.visit(node);
    }
};

} /// end of namespace

#endif //FUZZFLOW_IFNODE_H

