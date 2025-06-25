#ifndef FUZZFLOW_ABSTRACTBEGINNODE_H
#define FUZZFLOW_ABSTRACTBEGINNODE_H

#include "../utils/common_using.h"

#include "FixedNode.h"
#include "UniSuccessorNode.h"

namespace FuzzFlow {

class AbstractBeginNode : public UniSuccessorNode {
public:
    explicit AbstractBeginNode(const weak_ptr<FixedNode>& next)
        : UniSuccessorNode(next)
    {}
};

}

#endif //FUZZFLOW_ABSTRACTBEGINNODE_H
