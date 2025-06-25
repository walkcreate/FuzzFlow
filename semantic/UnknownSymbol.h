#ifndef FUZZFLOW_UNKNOWNSYMBOL_H
#define FUZZFLOW_UNKNOWNSYMBOL_H

#include "Symbol.h"
#include "SymKind.h"

namespace FuzzFlow {

class UnknownSymbol final : public Symbol {
public:
    explicit UnknownSymbol(const string& name) : Symbol(name, SymKind::Unknown) {}

    ~UnknownSymbol() override = default;

};

}

#endif //FUZZFLOW_UNKNOWNSYMBOL_H
