#ifndef FUZZFLOW_PROGRAMASPECTS_H
#define FUZZFLOW_PROGRAMASPECTS_H

#include "../execution/ExecutionOutcome.h"

namespace FuzzFlow {

class ProgramAspects {
public:
    virtual ~ProgramAspects() = default;

    ExecutionOutcome outcome;

    ProgramAspects(ExecutionOutcome outcome) {
        this->outcome = outcome;
    }

    virtual uint64_t count() {
        return 0;
    }
};

} /// end of namespace

#endif //FUZZFLOW_PROGRAMASPECTS_H
