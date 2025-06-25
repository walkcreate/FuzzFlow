#ifndef FUZZFLOW_UNISUCCESSORNODE_H
#define FUZZFLOW_UNISUCCESSORNODE_H

#include "IRNode.h"
#include "FixedNode.h"

namespace FuzzFlow {

class UniSuccessorNode : public FixedNode
{
public:
    weak_ptr<FixedNode> successor;

    explicit UniSuccessorNode(const weak_ptr<FixedNode> &next)
    {
        this->successor = next;
    }

    ~UniSuccessorNode() override = default;

    virtual void post_construct()
    {
        if (this->successor.expired()) {
            assert_or_throw_mutate(false, "error");
        }

        this->successor.lock()->predecessor =
            dynamic_pointer_cast<FixedNode>(shared_from_this());
    }

    void clone_repair(map<weak_ptr<IRNode>,
                          weak_ptr<IRNode>,
                            std::owner_less<>> &refNode2ownNode) override
    {
        ASSERT_OR_EXIT(refNode2ownNode.contains(this->successor));
        ASSERT_OR_EXIT(! refNode2ownNode[this->successor].expired());

        const auto real_node = refNode2ownNode[this->successor].lock();
        const auto fixed_real = dynamic_pointer_cast<FixedNode>(real_node);

        this->successor = fixed_real;

        ASSERT_OR_EXIT(this->successor.lock() != nullptr);

        /// Attention:
        this->UniSuccessorNode::post_construct();
    }

    shared_ptr<FixedNode> next() const
    {
        if (this->successor.expired()) {
            assert_or_throw_mutate(false, "error");
            return nullptr;
        }

        if (auto locked = this->successor.lock()) {
            return locked;
        }
        else {
            assert_or_throw_mutate(false, "error");
            return nullptr;
        }
    }

    void set_next(const weak_ptr<FixedNode>& next_node)
    {
        /// "next" and "predecessor" are mutually opposite edges.
        weak_ptr<UniSuccessorNode> node_self = dynamic_pointer_cast<UniSuccessorNode>(shared_from_this());
        this->successor = next_node;

        auto shared_p = next_node.lock();
        shared_p->predecessor = node_self;
    }
};

} /// end of namespace

#endif //FUZZFLOW_UNISUCCESSORNODE_H
