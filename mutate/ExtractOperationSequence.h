#ifndef FUZZFLOW_EXTRACTOPERATIONSEQUENCE_H
#define FUZZFLOW_EXTRACTOPERATIONSEQUENCE_H

#include "WalkCtrlFlow.h"
#include "OperationSequence.h"

namespace FuzzFlow {

class ExtractOperationSequence final : public WalkCtrlFlow {
public:
    explicit ExtractOperationSequence(const shared_ptr<FixedNode> &walk_start)
        : WalkCtrlFlow(walk_start)
    {}

    /// result
    vector<shared_ptr<OperationSequence>> sequences {};

    shared_ptr<SequentialOperationNode> current_sequence_head;

    set<shared_ptr<DataProducerNode>> valid_producers;

    static bool is_literal_node(const shared_ptr<DataProducerNode> &producer);

    [[nodiscard]] bool is_valid_producer(const shared_ptr<DataProducerNode> &producer) const;

    void handler(const weak_ptr<FixedNode>& current_node) override;

    void add2sequence(const shared_ptr<SequentialOperationNode>& operation_node);

    void finish_sequence();
};

} // FuzzFlow

#endif //FUZZFLOW_EXTRACTOPERATIONSEQUENCE_H
