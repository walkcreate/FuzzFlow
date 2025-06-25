#include "RefResolver.h"

namespace FuzzFlow {

std::any RefResolver::visitVariableDeclaration(JavaScriptParser::VariableDeclarationContext *ctx)
{
    if (ctx->assignable()->identifier() != nullptr) {
        string id_name = ctx->assignable()->identifier()->getText();

        auto _current_scope = this->current_scope;

        /// `this->declared_vars_map[_current_scope]` is a map
        /// Since assignment typically performs a copy (not modifying the original),
        /// we must use a reference to avoid unnecessary duplication.
        ///
        map<string, shared_ptr<VarSymbol>> &declared_syms = this->declared_vars_map[_current_scope];
        auto sym = _current_scope->get_symbol(id_name);

        if (sym != nullptr) {
            if (shared_ptr<VarSymbol> v_sym = std::dynamic_pointer_cast<VarSymbol>(sym)) {
                declared_syms.insert({id_name, v_sym});
            }
            else {
                std::cout << "Error symbol type\n";
                assert(false);
            }
        }
    }

    return this->JavaScriptParserBaseVisitor::visitVariableDeclaration(ctx);
}

std::any RefResolver::visitIdentifierName(JavaScriptParser::IdentifierNameContext *ctx)
{
    /// Identifiers used as property names do not require reference resolution.
    ///
    /// We use IdentifierName rather than PropertyName as the control point because:
    /// - PropertyName may expand to `[ singleExpression ]` production, where inner
    ///   identifiers (e.g., `apple` in `[apple + "le"]`) still need reference resolution.
    /// - IdentifierName provides a clear boundary for this optimization.
    ///
    bool turn_off_resolve = false;
    if (dynamic_cast<JavaScriptParser::PropertyNameContext *>(ctx->parent) != nullptr
        || dynamic_cast<JavaScriptParser::MemberDotExpressionContext *>(ctx->parent) != nullptr) {

        this->is_property_name = true;
        turn_off_resolve = true;
        }

    /// Delegates to parent class traversal method.
    /// Note: Found identifiers will skip reference resolution during this pass.
    ///
    auto visit_ret = this->JavaScriptParserBaseVisitor::visitIdentifierName(ctx);

    if (turn_off_resolve) {
        this->is_property_name = false;
    }

    return visit_ret;
}

std::any RefResolver::visitForInStatement(JavaScriptParser::ForInStatementContext *ctx)
{
    /// enter new scope
    auto old_scope = this->current_scope;
    this->current_scope = ctx->scope;

    map<string, shared_ptr<VarSymbol>> scope_map; // new resource
    this->declared_vars_map.insert({this->current_scope, scope_map});

    /// traversing the child tree
    this->JavaScriptParserBaseVisitor::visitForInStatement(ctx);

    /// restore scope
    this->current_scope = old_scope;

    return nullptr;
}

} /// end of namespace