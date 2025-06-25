#ifndef TRYEXIT_H
#define TRYEXIT_H

#include "../IRNode.h"
#include "../FixedNode.h"
#include "../LoopBegin.h"
#include "../UniSuccessorNode.h"
#include "CatchNode.h"

namespace FuzzFlow {

class TryExit final : public UniSuccessorNode {
private:
    static const string label;

public:
    explicit TryExit(const weak_ptr<FixedNode>& next)
        : UniSuccessorNode(next)
    {
        this->node_hash_current = label;
        this->node_hash_next = label;
    }

    string get_label() override
    {
        return TryExit::label;
    }

    shared_ptr<IRNode> clone() override
    {
        return make_shared<TryExit>(this->next());
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<TryExit>(shared_from_this());
        visitor.visit(node);
    }
};

} /// end of namespace

#endif //TRYEXIT_H
