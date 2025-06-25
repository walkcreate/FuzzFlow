#ifndef FUZZFLOW_VARPROXY_H
#define FUZZFLOW_VARPROXY_H

#include "../utils/common_using.h"

#include "../semantic/VarSymbol.h"

namespace FuzzFlow {

///
/// One definition for a variable
/// Every definition for a symbol creates a new var in SSA
///
class VarProxy {
public:
    shared_ptr<VarSymbol> var_symbol;
    unsigned int index;

    VarProxy(const shared_ptr<VarSymbol> &sym, const unsigned int index)
    {
        this->var_symbol = sym;
        this->index = index;
    }

    /// copy constructor?
    VarProxy(const shared_ptr<VarProxy> &proxy,
             map<shared_ptr<VarSymbol>,
                 shared_ptr<VarSymbol>> &oldVarSym2newVarSym)
    {
        shared_ptr<VarSymbol> new_var_sym;

        if (oldVarSym2newVarSym.contains(proxy->var_symbol)) {
            new_var_sym = oldVarSym2newVarSym.at(proxy->var_symbol);
        }
        else {
            new_var_sym = make_shared<VarSymbol>(proxy->var_symbol->name);
            oldVarSym2newVarSym.insert_or_assign(proxy->var_symbol, new_var_sym);
        }

        this->var_symbol = new_var_sym;
        this->index = proxy->index;
    }

    /// return likes a0 x1 y2
    [[nodiscard]] string get_label() const
    {
        return this->var_symbol->name + std::to_string(this->index);
    }
};

} /// end of namespace

#endif //FUZZFLOW_VARPROXY_H
