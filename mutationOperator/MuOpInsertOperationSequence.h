#ifndef FUZZFLOW_MUOPINSERTOPERATIONSEQUENCE_H
#define FUZZFLOW_MUOPINSERTOPERATIONSEQUENCE_H
#include <memory>

#include "MuOp.h"
#include "../mutate/OperationSequence.h"

namespace FuzzFlow {

class MuOpInsertOperationSequence final : public MuOp {
public:
    explicit MuOpInsertOperationSequence(const shared_ptr<OperationSequence> &sequence,
                                         const weak_ptr<FixedNode> &init_prev,
                                         const weak_ptr<FixedNode> &init_post)
    {
        _sequence = sequence;
        _init_prev = init_prev;
        _init_post = init_post;
    }

    void undo() override
    {
        auto orig_prev = _sequence->nodes.front()->predecessor;
        auto orig_post = _sequence->nodes.back()->successor;

        auto orig_prev_uni = dynamic_pointer_cast<UniSuccessorNode>(orig_prev.lock());
        ASSERT_OR_EXIT(orig_prev_uni != nullptr);

        orig_prev_uni->successor = orig_post;
        orig_post.lock()->predecessor = orig_prev_uni;

        _sequence->nodes.front()->predecessor = _init_prev;
        _sequence->nodes.back()->successor = _init_post;
    }

private:
    shared_ptr<OperationSequence> _sequence;
    weak_ptr<FixedNode> _init_prev;
    weak_ptr<FixedNode> _init_post;
};

} // FuzzFlow

#endif //FUZZFLOW_MUOPINSERTOPERATIONSEQUENCE_H
