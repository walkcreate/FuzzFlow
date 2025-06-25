#ifndef FUZZFLOW_VARSYMBOL_H
#define FUZZFLOW_VARSYMBOL_H

#include "Symbol.h"
#include "SymKind.h"

namespace FuzzFlow {

class VarSymbol final : public Symbol {
public:
    /**
     * Base class constructors are automatically called for you if they have no argument.
     * If you want to call a superclass constructor with an argument,
     * you must use the subclass's constructor initialization list.
     * Unlike Java, C++ supports multiple inheritance (for better or worse),
     * so the base class must be referred to by name, rather than "super()".
     * @param name
     */
    explicit VarSymbol(const string &name) : Symbol(name, SymKind::Variable) {}

    ~VarSymbol() override = default;
};

} /// end of namespace

#endif //FUZZFLOW_VARSYMBOL_H
