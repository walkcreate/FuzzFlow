#ifndef FUZZFLOW_TERMINALUI_H
#define FUZZFLOW_TERMINALUI_H

#include <iostream>
#include <memory>
#include <string>

#include "./protobuf/ExportStatistics.h"
#include "../utils/util_time.h"

using std::cout;
using std::shared_ptr;
using std::string;

namespace FuzzFlow {

class TerminalUI {
public:
    /// This function is made static, with low coupling to the Fuzzer class
    static void print_statistics(ExportStatistics const& proto_stats);
};

} /// end of namespace FuzzFlow

#endif //FUZZFLOW_TERMINALUI_H
