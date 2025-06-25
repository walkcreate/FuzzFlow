#ifndef FUZZFLOW_SYMBOL_H
#define FUZZFLOW_SYMBOL_H

#include "SymKind.h"

#include <string>
using std::string;

namespace FuzzFlow {

class Symbol {
public:
    string name;
    SymKind kind;

    Symbol(const string &name, SymKind kind)
    {
        this->name = name;
        this->kind = kind;
    }

    virtual ~Symbol() = default;
};

} /// end of namespace

#endif //FUZZFLOW_SYMBOL_H
