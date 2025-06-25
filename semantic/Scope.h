#ifndef FUZZFLOW_SCOPE_H
#define FUZZFLOW_SCOPE_H

#include <utility>
#include "antlr4-runtime.h"

#include "../utils/common_using.h"

#include "Symbol.h"
#include "../thirdparty/antlr4/JavaScriptParser.h"

namespace FuzzFlow {

using namespace antlr4;

class Scope {
public:
    /// All symbols in the current scope have been collected during the Enter phase.
    map<string, shared_ptr<Symbol>> name2symbol;

    /// Upper scope
    /// multi sub scope may correspond to one same upper scope
    shared_ptr<Scope> enclosing_scope = nullptr;

    /// The AST node corresponding to the current scope.
    /// We use raw pointer here. The resource is managed by ANTLR.
    ParserRuleContext *node_ctx = nullptr;

    Scope(antlr4::ParserRuleContext *node_ctx, shared_ptr<Scope> enclosing_scope)
    {
        this->node_ctx = node_ctx;
        this->enclosing_scope = std::move(enclosing_scope);
    }

    ~Scope() = default;

    void enter(const string& name,
               const shared_ptr<Symbol>& symbol)
    {
        this->name2symbol.insert({name, symbol});
    }

    [[nodiscard]] bool has_symbol(const string& name) const
    {
        return this->name2symbol.contains(name);
    }

    shared_ptr<Symbol> get_symbol(const string& name)
    {
        if (has_symbol(name)) {
            auto symbol = this->name2symbol[name];
            return symbol;
        }

        return nullptr;
    }

    shared_ptr<Symbol> get_symbol_cascade(const string& name)
    {
        shared_ptr<Symbol> symbol = get_symbol(name);

        if (symbol != nullptr) {
            return symbol;
        }

        if (this->enclosing_scope != nullptr)
        {
            ParserRuleContext *node = this->enclosing_scope->node_ctx;

            /// If the parent node of the upper scope is a ClassDecl, the lookup fails.
            if (auto *p = dynamic_cast<JavaScriptParser::ClassDeclarationContext *>(node->parent)) {
                return nullptr;
            }

            return this->enclosing_scope->get_symbol_cascade(name);
        }

        return nullptr;
    }
};

} /// end of namespace

#endif //FUZZFLOW_SCOPE_H
