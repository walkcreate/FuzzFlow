#ifndef FUZZFLOW_ABSTRACTENDNODE_H
#define FUZZFLOW_ABSTRACTENDNODE_H

#include "../utils/common_using.h"

#include "IRNode.h"
#include "FixedNode.h"

namespace FuzzFlow {

class AbstractEndNode : public FixedNode {
public:
    /// no successors
};

} /// end of namespace

#endif //FUZZFLOW_ABSTRACTENDNODE_H
