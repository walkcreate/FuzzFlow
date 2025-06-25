#ifndef FUZZFLOW_MUOPMOVESEQUENTIALOPERATION_H
#define FUZZFLOW_MUOPMOVESEQUENTIALOPERATION_H

#include "MuOp.h"
#include "../nodes/FixedNode.h"
#include "../nodes/IfNode.h"
#include "../nodes/UniSuccessorNode.h"

namespace FuzzFlow {

class MuOpMoveSequentialOperation final : public MuOp {
public:
    MuOpMoveSequentialOperation(const weak_ptr<UniSuccessorNode> &node_to_move,
                    const weak_ptr<UniSuccessorNode> &last_prev_node,
                    const weak_ptr<UniSuccessorNode> &new_prev_node)
    {
        this->node_to_move = node_to_move;
        this->orig_prev_node = last_prev_node;
        this->new_prev_node = new_prev_node;
    }

    void undo() override
    {
        const auto orig_post = this->orig_prev_node.lock()->next();

        /// Setup the edges in the original context.
        this->orig_prev_node.lock()->successor = node_to_move;
        orig_post->predecessor = node_to_move;

        /// Restore the edges in the new context.
        const auto new_post = node_to_move.lock()->next();
        this->new_prev_node.lock()->successor = new_post;
        new_post->predecessor = this->new_prev_node;

        /// Restore the original connections of the moved node.
        node_to_move.lock()->predecessor = orig_prev_node;
        node_to_move.lock()->successor = orig_post;
    }

private:
    weak_ptr<UniSuccessorNode> node_to_move;
    weak_ptr<UniSuccessorNode> orig_prev_node;
    weak_ptr<UniSuccessorNode> new_prev_node;
};

} /// end of namespace

#endif //FUZZFLOW_MUOPMOVESEQUENTIALOPERATION_H
