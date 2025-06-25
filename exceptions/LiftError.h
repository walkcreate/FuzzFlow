#ifndef FUZZFLOW_LIFTERROR_H
#define FUZZFLOW_LIFTERROR_H

#include <string>
#include <stdexcept>

namespace FuzzFlow {

using std::string;

/// Error in graph2js
class LiftError final : public std::runtime_error {
public:
    explicit LiftError(const string &message) : std::runtime_error(message) {}
};

} /// end of namespace

#endif //FUZZFLOW_LIFTERROR_H
