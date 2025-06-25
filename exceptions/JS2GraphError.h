#ifndef FUZZFLOW_JS2SONERROR_H
#define FUZZFLOW_JS2SONERROR_H

#include <string>
#include <stdexcept>

namespace FuzzFlow {

using std::string;

/// Error in translate
class JS2GraphError final : public std::runtime_error {
public:
    explicit JS2GraphError(const string &message) : std::runtime_error(message) {}
};

} /// end of namespace

#endif //FUZZFLOW_JS2SONERROR_H
