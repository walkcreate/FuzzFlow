#ifndef FUZZFLOW_SEQUENTIALOPERATIONNODE_H
#define FUZZFLOW_SEQUENTIALOPERATIONNODE_H

#include "UniSuccessorNode.h"

namespace FuzzFlow {

class SequentialOperationNode : public UniSuccessorNode {
public:
    explicit SequentialOperationNode(const weak_ptr<FixedNode> &next)
        : UniSuccessorNode(next)
    {}

};

} /// end of namespace

#endif //FUZZFLOW_SEQUENTIALOPERATIONNODE_H
