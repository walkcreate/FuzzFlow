#ifndef FUZZFLOW_ENTERERROR_H
#define FUZZFLOW_ENTERERROR_H

#include <string>
#include <stdexcept>

namespace FuzzFlow {

using std::string;

/// Error in translate
class EnterError final : public std::runtime_error {
public:
    explicit EnterError(const string &message) : std::runtime_error(message) {}
};

} /// end of namespace

#endif //FUZZFLOW_ENTERERROR_H
