#ifndef FUZZFLOW_FUNCTIONSYMBOL_H
#define FUZZFLOW_FUNCTIONSYMBOL_H

#include <utility>
#include <vector>
#include <memory>

#include "SymKind.h"
#include "FunctionKind.h"
#include "Symbol.h"
#include "VarSymbol.h"

#include "antlr4-runtime.h"

using std::shared_ptr;
using std::vector;

namespace FuzzFlow {

class FunctionSymbol final : public Symbol {

public:
    FunctionSymbol(const string& name,
                   vector<shared_ptr<VarSymbol>> args,
                   const FunctionKind function_kind)
      : Symbol(name, SymKind::Function)
    {
        this->vars = std::move(args);
        this->function_kind = function_kind;
    }

    static int getNumParams() { return 0; }

private:
    std::vector<shared_ptr<VarSymbol>> vars;
    FunctionKind function_kind;

    /// point to function declaration node
    antlr4::ParserRuleContext *decl;

};

} /// end of namespace

#endif //FUZZFLOW_FUNCTIONSYMBOL_H