#ifndef FUZZFLOW_MUOPMOVECTRLGROUP_H
#define FUZZFLOW_MUOPMOVECTRLGROUP_H

#include "../nodes/FixedNode.h"
#include "../nodes/UniSuccessorNode.h"

#include "MuOp.h"

namespace FuzzFlow {

class MuOpMoveCtrlGroup final : public MuOp {
public:
    MuOpMoveCtrlGroup(const weak_ptr<FixedNode> &head_node,
                      const weak_ptr<UniSuccessorNode> &tail_node,
                      const weak_ptr<UniSuccessorNode> &_orig_prev,
                      const weak_ptr<UniSuccessorNode> &_new_prev)
    {
        /// The head node may be an EndNode or IfNode, so we use the common base class FixedNode to represent it.
        /// We only need to extract its predecessors, without checking whether it's a uni node.
        this->head_node = head_node;

        this->tail_node = tail_node;
        this->orig_prev = _orig_prev;
        this->new_prev = _new_prev;
    }

    void undo() override
    {
        const auto tail_uni = tail_node.lock();

        const auto old_post = orig_prev.lock()->next();
        const auto new_post = tail_uni->next();

        orig_prev.lock()->successor = head_node;
        head_node.lock()->predecessor = orig_prev;

        old_post->predecessor = tail_node;
        tail_uni->successor = old_post;

        new_prev.lock()->successor = new_post;
        new_post->predecessor = new_prev;
    }

private:
    weak_ptr<FixedNode> head_node;
    weak_ptr<UniSuccessorNode> tail_node;
    weak_ptr<UniSuccessorNode> orig_prev;
    weak_ptr<UniSuccessorNode> new_prev;
};

} /// end of namespace

#endif //FUZZFLOW_MUOPMOVECTRLGROUP_H
