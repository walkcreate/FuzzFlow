#ifndef FUZZFLOW_FORINENUM_H
#define FUZZFLOW_FORINENUM_H

#include "../FixedNode.h"
#include "../MergeNode.h"

#include "ForInPropName.h"

#include "../DataProducerNode.h"
#include "../DataConsumerNode.h"

namespace FuzzFlow
{
class ForInEnum final : public FixedNode,
                        public DataConsumerNode
{
private:
    static const string label;
    std::pair<weak_ptr<FixedNode>, weak_ptr<FixedNode>> successors;

public:
    ForInEnum(const weak_ptr<ForInPropName>& prop_name_node,
              const weak_ptr<DataProducerNode>& object_node,
              const weak_ptr<FixedNode> &b_then,
              const weak_ptr<FixedNode> &b_false)
    {
        this->inputs.push_back(prop_name_node);
        this->inputs.push_back(object_node);
        this->successors = {b_then, b_false};

        this->node_hash_current = this->label;
    }

    string get_label() override
    {
        return ForInEnum::label;
    }

    shared_ptr<ForInPropName> enumPropName() const
    {
        return dynamic_pointer_cast<ForInPropName>(
            this->inputs[0].lock());
    }

    shared_ptr<DataProducerNode> enumObject() const
    {
        return this->inputs[1].lock();
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

    void post_construct() override
    {
        this->DataConsumerNode::post_construct();

        const weak_ptr<FixedNode> node_self = dynamic_pointer_cast<FixedNode>(shared_from_this());

        this->branch_true()->predecessor = node_self;
        this->branch_false()->predecessor = node_self;
    }

    shared_ptr<IRNode> clone() override
    {
        auto new_node = make_shared<ForInEnum>(this->enumPropName(),
                                                                this->enumObject(),
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

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<ForInEnum>(shared_from_this());
        visitor.visit(node);
    }
};

}

#endif //FUZZFLOW_FORINENUM_H
