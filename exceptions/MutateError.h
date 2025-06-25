#ifndef FUZZFLOW_MUTATEERROR_H
#define FUZZFLOW_MUTATEERROR_H

#include <stdexcept>

#include <string>

namespace FuzzFlow {

using std::string;

/// Error in mutate
class MutateError final : public std::runtime_error {
public:
    explicit MutateError(const string &message) : std::runtime_error(message) {}
};

} /// end of namespace


#endif //FUZZFLOW_MUTATEERROR_H
