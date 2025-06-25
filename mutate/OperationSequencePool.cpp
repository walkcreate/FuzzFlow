#include "OperationSequencePool.h"

#include "SubGraphPool.h"

namespace FuzzFlow {

bool OperationSequencePool::verify_sequence(const shared_ptr<OperationSequence>& seq)
{
    if (seq->nodes.size() == 1) {
        return true;
    }

    for (int i = 0; i < seq->nodes.size(); i++) {

        if (i > 0) {
            auto prev = seq->nodes[i]->predecessor.lock();
            ASSERT_OR_EXIT(prev != nullptr);

            auto prev_operation = dynamic_pointer_cast<SequentialOperationNode>(prev);
            ASSERT_OR_EXIT(prev_operation != nullptr);

            ASSERT_OR_EXIT(prev_operation == seq->nodes[i - 1]);
        }

        if (i < seq->nodes.size() - 1) {
            auto post = seq->nodes[i]->successor.lock();
            ASSERT_OR_EXIT(post != nullptr);

            auto post_operation = dynamic_pointer_cast<SequentialOperationNode>(post);
            ASSERT_OR_EXIT(post_operation != nullptr);

            ASSERT_OR_EXIT(post_operation == seq->nodes[i + 1]);
        }
    }

    return true;
}

void OperationSequencePool::extract(const shared_ptr<Graph> &graph)
{
    auto function_head = dynamic_pointer_cast<FunctionHeadNode>(graph->nodes[0]);
    ExtractOperationSequence walker(function_head);

    walker.walk();

    for (const auto& seq : walker.sequences) {
        verify_sequence(seq);
        this->sequences.insert(seq);
    }
}

} /// end of namespace