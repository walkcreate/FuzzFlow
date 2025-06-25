#ifndef FUZZFLOW_EXECUTION_H
#define FUZZFLOW_EXECUTION_H

#include <string>
using std::string;

#include "ExecutionOutcome.h"

namespace FuzzFlow {

class Execution {
public:
    // The execution outcome
    ExecutionOutcome outcome;

    // The program's stdout
    string stdout;

    // The program's stderr
    string stderr;

    // Execution time in microseconds
    double exec_time;
};

} /// end of namespace FuzzFlow

#endif //FUZZFLOW_EXECUTION_H
