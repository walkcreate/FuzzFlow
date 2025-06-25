#ifndef FUZZFLOW_OPERATIONSEQUENCEPOOL_H
#define FUZZFLOW_OPERATIONSEQUENCEPOOL_H

#include "OperationSequence.h"
#include "ExtractOperationSequence.h"

namespace FuzzFlow {

class OperationSequencePool {
public:
    OperationSequencePool() = default;

    set<shared_ptr<OperationSequence>> sequences;

    void extract(const shared_ptr<Graph> &graph);

    bool verify_sequence(const shared_ptr<OperationSequence>& seq);
};

} // FuzzFlow

#endif //FUZZFLOW_OPERATIONSEQUENCEPOOL_H
