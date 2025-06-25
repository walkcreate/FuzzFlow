#ifndef FUZZFLOW_REFRESOLVERERROR_H
#define FUZZFLOW_REFRESOLVERERROR_H

#include <string>
#include <stdexcept>

namespace FuzzFlow {

using std::string;

/// Error in translate
class RefResolverError final : public std::runtime_error {
public:
    explicit RefResolverError(const string &message) : std::runtime_error(message) {}
};

} /// end of namespace

#endif //FUZZFLOW_REFRESOLVERERROR_H
