#ifndef FUZZFLOW_TRYNODE_H
#define FUZZFLOW_TRYNODE_H

#include "../AbstractBeginNode.h"

#include "CatchNode.h"
#include "FinallyNode.h"

namespace FuzzFlow {

class TryNode final : public AbstractBeginNode {
private:
    static const string label;

public:
    /// Records catch and finally node info in try node for control flow tracking.
    ///
    /// When a throw occurs inside a function call within try (with no other throws),
    /// catch and finally nodes lose their merge inputs, making them unreachable
    /// during control flow traversal. Storing these nodes in try ensures proper
    /// lifting phase operation.
    ///
    /// Note: Catch and finally nodes don't need to reference try in their uses,
    /// as this isn't an input-use relationship.
    ///
    weak_ptr<CatchNode> catch_node;
    weak_ptr<FinallyNode> finally_node;

    TryNode(const weak_ptr<FixedNode>& next,
            const weak_ptr<CatchNode> &catch_node,
            const weak_ptr<FinallyNode> &finally_node)
        : AbstractBeginNode(next)
    {
        if (! catch_node.expired()) {
            this->catch_node = catch_node;
        }

        if (! finally_node.expired()) {
            this->finally_node = finally_node;
        }

        this->node_hash_current = label;
    }

    string get_label() override
    {
        return TryNode::label;
    }

    shared_ptr<IRNode> clone() override {
        return make_shared<TryNode>(this->next(), this->catch_node, this->finally_node);
    }

    void clone_repair(map<weak_ptr<IRNode>, weak_ptr<IRNode>, std::owner_less<>>& refNode2ownNode) override
    {
        this->AbstractBeginNode::clone_repair(refNode2ownNode);

        if (this->catch_node.lock() != nullptr) {
            ASSERT_OR_EXIT(refNode2ownNode.contains(this->catch_node));
            ASSERT_OR_EXIT(! refNode2ownNode[this->catch_node].expired());

            this->catch_node = dynamic_pointer_cast<CatchNode>(
            refNode2ownNode[this->catch_node].lock());

            ASSERT_OR_EXIT(this->catch_node.lock() != nullptr);
        }

        if (this->finally_node.lock() != nullptr) {
            ASSERT_OR_EXIT(refNode2ownNode.contains(this->finally_node));
            ASSERT_OR_EXIT(! refNode2ownNode[this->finally_node].expired());

            this->finally_node = dynamic_pointer_cast<FinallyNode>(
            refNode2ownNode[this->finally_node].lock());

            ASSERT_OR_EXIT(this->finally_node.lock() != nullptr);
        }

        this->post_construct();
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<TryNode>(shared_from_this());
        visitor.visit(node);
    }
};

} /// end of namespace

#endif //FUZZFLOW_TRYNODE_H
