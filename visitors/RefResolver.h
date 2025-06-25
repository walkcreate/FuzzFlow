#ifndef FUZZFLOW_REFRESOLVER_H
#define FUZZFLOW_REFRESOLVER_H

#include "antlr4-runtime.h"
#include "../thirdparty/antlr4/JavaScriptParserBaseVisitor.h"

#include "../utils/common_using.h"
#include "../utils/assert_or_throw.h"

#include "../semantic/FunctionSymbol.h"
#include "../semantic/VarSymbol.h"
#include "../semantic/UnknownSymbol.h"
#include "../semantic/Scope.h"
#include "../exceptions/RefResolverError.h"

/// Reference resolution attaches var symbols to identifiers
/// (Used later for data flow analysis in IR generation)
/// Scope information is required during this phase
///
namespace FuzzFlow {

using antlr4::ParserRuleContext;

///
/// Processes JS code that must satisfy:
/// 1. Unique declarations: Re-declarations are resolved to single valid definition
/// 2. Babel preprocessor handles undeclared vars (by injecting declarations)
///
class RefResolver final : public JavaScriptParserBaseVisitor
{
public:
    shared_ptr<Scope> current_scope = nullptr;

    /// When an assignment implies variable declaration, the variable's scope is global.
    shared_ptr<Scope> global_scope = nullptr;

    /// scope -> name -> varSymbol
    ///
    /// When multiple variables with the same name are declared (possibly multiple times) in the same scope,
    /// the map cannot maintain multiple copies of them.
    map<shared_ptr<Scope>,
        map<string,
            shared_ptr<VarSymbol>>> declared_vars_map;

    map<shared_ptr<Scope>,
        map<string,
            shared_ptr<UnknownSymbol>>> declared_unknown_map;

    set<shared_ptr<Symbol>> builtin_symbols;

    ///
    /// set<shared_ptr<Symbol>> builtin_symbols are saved in AST ProgramContext
    ///
    void init_builtin_symbols(set<shared_ptr<Symbol>>& builtin_symbols)
    {
        /// doc: https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects
        const set<string> builtin_objects = {
            "console",
            "read", "print", "eval", "WebAssembly",
            "Symbol", "load",
            "RegExp",
            "toFixed", "quit",

            /// Value properties
            "globalThis", "Infinity", "NaN", "undefined",

            /// Fundamental objects
            "Object", "Function", "Boolean", "Symbol",

            /// Error objects
            "Error", "AggregateError", "EvalError", "RangeError", "ReferenceError", "SyntaxError",
            "TypeError", "URIError", "InternalError",

            /// Numbers and dates
            "Number", "BigInt", "Math", "Date",

            /// Text processing
            "String", "RegExp",

            /// Indexed collections
            "Array", "Int8Array", "Uint8Array", "Uint8ClampedArray", "Int16Array", "Uint16Array",
            "Int32Array", "Uint32Array", "BigInt64Array", "BigUint64Array", "Float32Array", "Float64Array",

            /// Keyed collections
            "WeakSet", "Set", "Map", "WeakMap",

            /// Structured data
            "ArrayBuffer", "SharedArrayBuffer", "DataView", "Atomics", "JSON",

            /// Managing memory
            "WeakRef", "FinalizationRegistry",

            /// Control abstraction objects
            "Iterator", "AsyncIterator", "Promise", "GeneratorFunction", "AsyncGeneratorFunction", "Generator",
            "AsyncGenerator", "AsyncFunction",

            /// Reflection
            "Reflect", "Proxy",

            /// Internationalization
            "Intl",

            /// browser
            "document"
        };

        for (auto& name : builtin_objects) {
            auto symbol = make_shared<VarSymbol>(name);
            builtin_symbols.insert(symbol);
        }

        this->builtin_symbols = builtin_symbols;
    }

    shared_ptr<Symbol> find_symbol_cascade(const shared_ptr<Scope>& scope, const string& symbol_name)
    {
        shared_ptr<Symbol> symbol_in_scope = scope->get_symbol(symbol_name);

        if (symbol_in_scope != nullptr) {
            if (this->declared_vars_map.find(scope) != declared_vars_map.end())
            {
                auto& name2symbol = this->declared_vars_map[scope]; // copy constructor for map!

                if (! name2symbol.empty()
                    && (name2symbol.find(symbol_name) != name2symbol.end()))
                {
                    shared_ptr<VarSymbol> var_symbol = name2symbol[symbol_name];
                    return var_symbol;
                }
            }

            if (this->declared_unknown_map.contains(scope)) {
                /// may be function's parameter
                auto& unknown_map = declared_unknown_map[scope];

                if (unknown_map.contains(symbol_name)) {
                    shared_ptr<UnknownSymbol> unk_sym = unknown_map[symbol_name];
                    return unk_sym;
                }
            }

            /// If the symbol isn't found in either declared map but exists in the scope's name2sym, it must be a function symbol.
            ///
            if (dynamic_pointer_cast<VarSymbol>(symbol_in_scope) != nullptr) {
                return symbol_in_scope;
            }

            if (dynamic_pointer_cast<FunctionSymbol>(symbol_in_scope) != nullptr) {
                return symbol_in_scope;
            }

            assert_or_throw_js2graph(false, "Find symbol failed.");
        }
        else {
            if (scope->enclosing_scope != nullptr) {
                ParserRuleContext *node = scope->enclosing_scope->node_ctx;
                if (dynamic_cast<JavaScriptParser::ClassDeclarationContext *>(node->parent) != nullptr) {
                    return nullptr;
                }

                return this->find_symbol_cascade(scope->enclosing_scope, symbol_name);
            }
        }

        return nullptr;
    }

    std::any visitProgram(JavaScriptParser::ProgramContext *ctx) override
    {
        this->init_builtin_symbols(ctx->builtin_symbols);

        this->current_scope = ctx->scope;
        this->global_scope = ctx->scope;

        return this->JavaScriptParserBaseVisitor::visitProgram(ctx);
    }

    ///
    /// Traverse the AST, resolve the corresponding Symbol for each identifier, and annotate it onto the Identifier node.
    /// This function only performs resolution; it does not create symbols.
    /// At the Enter phase, symbols are already annotated on nodes like VariableDecl and FunctionDecl.
    ///
    std::any visitIdentifier(JavaScriptParser::IdentifierContext *ctx) override
    {
        /// to support ObjectLiteral
        if (this->is_property_name) {
            return nullptr;
        }

        const string id_name = ctx->getText();
        shared_ptr<Scope> scope = this->current_scope;

        const shared_ptr<Symbol> symbol = this->find_symbol_cascade(scope, id_name);

        if (shared_ptr<VarSymbol> v_sym = dynamic_pointer_cast<VarSymbol>(symbol)) {
            ctx->symbol = v_sym;
        }
        else if (shared_ptr<FunctionSymbol> f_sym = dynamic_pointer_cast<FunctionSymbol>(symbol)) {
            ctx->symbol = f_sym;
        }
        else if (shared_ptr<UnknownSymbol> u_sym = dynamic_pointer_cast<UnknownSymbol>(symbol)) {
            ctx->symbol = u_sym;
        }
        else {
            bool found_in_builtin = false;

            for (auto& sym : this->builtin_symbols) {
                if (sym->name == id_name) {
                    ctx->symbol = sym;
                    found_in_builtin = true;
                }
            }

            if (! found_in_builtin) {
                const string msg = "Variable: '" + id_name + "' is not resolved.\n";
                cerr << msg;
                throw RefResolverError{msg};
            }
        }

        return nullptr;
    }

    /// function call
    std::any visitArgumentsExpression(JavaScriptParser::ArgumentsExpressionContext *ctx) override
    {
        return this->JavaScriptParserBaseVisitor::visitArgumentsExpression(ctx);
    }

    std::any visitVariableDeclaration(JavaScriptParser::VariableDeclarationContext *ctx) override;

    /// If the assignment target is an undeclared identifier, create a corresponding var symbol.
    ///
    std::any visitAssignmentExpression(JavaScriptParser::AssignmentExpressionContext *ctx) override
    {
        const auto _current_scope = this->current_scope;
        const auto assign_tgt = ctx->singleExpression(0);

        if (auto assign_id_expr = dynamic_cast<JavaScriptParser::IdentifierExpressionContext *>(assign_tgt))
        {
            if (auto assign_id = assign_id_expr->identifier();
                assign_id->symbol == nullptr)
            {
                string id_name = assign_id->getText();
                shared_ptr<Symbol> sym = this->find_symbol_cascade(_current_scope, id_name);

                if (sym == nullptr) {
                    auto var_symbol = make_shared<VarSymbol>(id_name);

                    /// The symbol should be added to the global scope
                    this->global_scope->enter(id_name, var_symbol);

                    map<string, shared_ptr<VarSymbol>> &declared_syms = this->declared_vars_map[this->global_scope];
                    declared_syms.insert({id_name, var_symbol});

                    assign_id->symbol = var_symbol;
                }
            }
        }

        /// The left-hand side may not be an identifier, so it might not trigger the condition branch.
        /// We must ensure execution proceeds.
        this->visit(ctx->singleExpression(0));

        /// Normally traversing the right-hand side.
        this->visit(ctx->singleExpression(1));

        return nullptr;
    }

    /// Function parameters are treated like variable declarations and must be inserted into declared vars map
    /// 
    std::any visitFormalParameterList(JavaScriptParser::FormalParameterListContext *ctx) override
    {
        for (JavaScriptParser::FormalParameterArgContext *arg : ctx->formalParameterArg())
        {
            const auto arg_id = arg->assignable()->identifier();
            string arg_name = arg_id->getText();

            shared_ptr<VarSymbol> unknown_sym = dynamic_pointer_cast<VarSymbol>(arg_id->symbol);
            this->declared_vars_map[this->current_scope].insert({arg_name, unknown_sym});
        }

        return nullptr;
    }

    std::any visitFunctionDeclaration(JavaScriptParser::FunctionDeclarationContext *ctx) override
    {
        const auto last_scope = this->current_scope;
        this->current_scope = ctx->scope;

        map<string, shared_ptr<VarSymbol>> scope_declared_vars {}; // new resource
        this->declared_vars_map.insert({this->current_scope, scope_declared_vars});

        /// traverse the sub tree
        this->JavaScriptParserBaseVisitor::visitFunctionDeclaration(ctx);

        this->current_scope = last_scope;

        return nullptr;
    }

    std::any visitForStatement(JavaScriptParser::ForStatementContext *ctx) override
    {
        const auto last_scope = this->current_scope;
        this->current_scope = ctx->scope;

        map<string, shared_ptr<VarSymbol>> scope_map; // new resource
        this->declared_vars_map.insert({this->current_scope, scope_map});

        this->JavaScriptParserBaseVisitor::visitForStatement(ctx);

        this->current_scope = last_scope;
        return nullptr;
    }

    std::any visitBlock(JavaScriptParser::BlockContext *ctx) override
    {
        const auto last_scope = this->current_scope;
        this->current_scope = ctx->scope;

        map<string, shared_ptr<VarSymbol>> scope_map; // new resource
        this->declared_vars_map.insert({this->current_scope, scope_map});

        this->JavaScriptParserBaseVisitor::visitBlock(ctx);

        this->current_scope = last_scope;
        return nullptr;
    }

    std::any visitIdentifierName(JavaScriptParser::IdentifierNameContext *ctx) override;

    std::any visitForInStatement(JavaScriptParser::ForInStatementContext *ctx) override;

private:
    bool is_property_name = false;
};

} /// end of namespace

#endif //FUZZFLOW_REFRESOLVER_H
