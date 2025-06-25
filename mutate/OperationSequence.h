#ifndef FUZZFLOW_OPERATIONSEQUENCE_H
#define FUZZFLOW_OPERATIONSEQUENCE_H

#include "../utils/common_using.h"

#include "../nodes/AllNodesInclude.h"

namespace FuzzFlow {

class OperationSequence {
public:
    OperationSequence() = default;

    ~OperationSequence() = default;

    vector<shared_ptr<SequentialOperationNode>> nodes;
};

} // FuzzFlow

#endif //FUZZFLOW_OPERATIONSEQUENCE_H
