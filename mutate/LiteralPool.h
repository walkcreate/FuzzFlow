#ifndef FUZZFLOW_MUTATE_LITERALPOOL_H
#define FUZZFLOW_MUTATE_LITERALPOOL_H

#include "../utils/common_using.h"
#include "../nodes/AllNodesInclude.h"

namespace FuzzFlow {

class LiteralPool {
public:
    LiteralPool() = default;

    ~LiteralPool() = default;

    set<shared_ptr<LiteralNode>> literals;
};

} // FuzzFlow

#endif //FUZZFLOW_MUTATE_LITERALPOOL_H
