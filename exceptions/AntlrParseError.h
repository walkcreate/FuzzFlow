#ifndef FUZZFLOW_ANTLRPARSEERROR_H
#define FUZZFLOW_ANTLRPARSEERROR_H

#include <string>
#include <stdexcept>

namespace FuzzFlow {

using std::string;

/// Error in antlr parsing
class AntlrParseError final : public std::runtime_error {
public:
    explicit AntlrParseError(const string &message) : std::runtime_error(message) {}
};

}

#endif //FUZZFLOW_ANTLRPARSEERROR_H
