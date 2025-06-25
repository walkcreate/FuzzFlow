#ifndef FUZZFLOW_EXECUTIONOUTCOME_H
#define FUZZFLOW_EXECUTIONOUTCOME_H

namespace FuzzFlow {

enum class ExecutionOutcome {
    crashed,
    failed,
    succeeded,
    timeout
};

}

#endif //FUZZFLOW_EXECUTIONOUTCOME_H
