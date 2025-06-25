#ifndef FUZZFLOW_MUOPSPLICE_H
#define FUZZFLOW_MUOPSPLICE_H

#include "../utils/common_using.h"
#include "../nodes/AllNodesInclude.h"
#include "MuOp.h"

namespace FuzzFlow {

class MuOpSplice final : public MuOp {
public:
    MuOpSplice(const shared_ptr<FixedNode> &graph_b_head,
               const shared_ptr<UniSuccessorNode> &graph_b_head_prev,
               const shared_ptr<UniSuccessorNode> &graph_b_tail,
               const shared_ptr<FixedNode> &graph_b_tail_post)
    {
        this->graph_b_head = graph_b_head;
        this->graph_b_head_prev = graph_b_head_prev;
        this->graph_b_tail = graph_b_tail;
        this->graph_b_tail_post = graph_b_tail_post;
    }

    ~MuOpSplice() override = default;

    void undo() override
    {
        const auto splice_current_prev = graph_b_head->predecessor.lock();
        const auto splice_current_prev_uni = dynamic_pointer_cast<UniSuccessorNode>(splice_current_prev);
        const auto splice_current_post = graph_b_tail->successor.lock();

        ASSERT_OR_EXIT(splice_current_prev_uni != nullptr);
        ASSERT_OR_EXIT(splice_current_post != nullptr);

        splice_current_prev_uni->successor = splice_current_post;
        splice_current_post->predecessor = splice_current_prev;

        graph_b_head->predecessor = graph_b_head_prev;
        graph_b_head_prev->successor = graph_b_head;

        graph_b_tail->successor = graph_b_tail_post;
        graph_b_tail_post->predecessor = graph_b_tail;
    }

private:
    shared_ptr<FixedNode>        graph_b_head;
    shared_ptr<UniSuccessorNode> graph_b_head_prev;
    shared_ptr<UniSuccessorNode> graph_b_tail;
    shared_ptr<FixedNode>        graph_b_tail_post;
};

} /// end of namespace

#endif //FUZZFLOW_MUOPSPLICE_H
