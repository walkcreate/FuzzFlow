#ifndef FUZZFLOW_LOOPEXIT_H
#define FUZZFLOW_LOOPEXIT_H

#include "IRNode.h"
#include "FixedNode.h"
#include "LoopBegin.h"
#include "UniSuccessorNode.h"

namespace FuzzFlow {

class LoopExit final : public UniSuccessorNode {
private:
    static const string label;

public:
    explicit LoopExit(const weak_ptr<FixedNode>& next)
        : UniSuccessorNode(next)
    {
        this->node_hash_current = label;
    }

    string get_label() override
    {
        return label;
    }

    shared_ptr<IRNode> clone() override
    {
        return make_shared<LoopExit>(this->next());
    }

    void clone_repair(map<weak_ptr<IRNode>, weak_ptr<IRNode>, std::owner_less<>> &refNode2ownNode) override
    {
        ASSERT_OR_EXIT(refNode2ownNode.contains(this->successor));
        ASSERT_OR_EXIT(! refNode2ownNode[this->successor].expired());

        this->successor = dynamic_pointer_cast<FixedNode>(
            refNode2ownNode[this->successor].lock());

        ASSERT_OR_EXIT(this->successor.lock() != nullptr);

        this->post_construct();
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<LoopExit>(shared_from_this());
        visitor.visit(node);
    }
};

} /// end of namespace

#endif //FUZZFLOW_LOOPEXIT_H
