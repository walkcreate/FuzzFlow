#ifndef FUZZFLOW_ENTER_H
#define FUZZFLOW_ENTER_H

#include "../thirdparty/antlr4/JavaScriptParserBaseVisitor.h"
#include "antlr4-runtime.h"

#include "../utils/common_using.h"

#include "../semantic/FunctionSymbol.h"
#include "../semantic/VarSymbol.h"
#include "../semantic/Scope.h"

#include "../exceptions/EnterError.h"

///
/// Scope analysis. Create Symbol.
/// Annotate scope and symbol to AST
///
namespace FuzzFlow {

class Enter final : public JavaScriptParserBaseVisitor {
public:
    shared_ptr<Scope> current_scope;

    std::any visitProgram(JavaScriptParser::ProgramContext *ctx) override
    {
        const auto last_scope = this->current_scope;

        this->current_scope = make_shared<Scope>(ctx, this->current_scope);
        ctx->scope = this->current_scope;

        const auto var_symbol = make_shared<VarSymbol>("__main__");
        ctx->function_symbol = var_symbol;

        this->JavaScriptParserBaseVisitor::visitProgram(ctx);

        this->current_scope = last_scope;

        return {};
    }

    std::any visitVariableDeclaration(JavaScriptParser::VariableDeclarationContext *ctx) override
    {
        /// Attach the varSymbol to AST's VariableDeclaration node
        if (JavaScriptParser::AssignableContext *assignable = ctx->assignable();
            assignable->identifier() != nullptr)
        {
            if (string id_name = assignable->identifier()->getText();
                this->current_scope->has_symbol(id_name))
            {
                cout << "Duplicate symbol: " << id_name << std::endl;

                /// A variable with the same name has been redeclared, creating a new var symbol.
                /// The newly declared variable will overwrite the old one.
                /// For subsequent symbol lookups, the scope should be searched from the most recent declaration to the earliest.
                const auto var = make_shared<VarSymbol>(id_name);
                ctx->var_symbol = var;
                this->current_scope->enter(id_name, var);
            }
            else {
                /// Create symbol table item for variable
                const auto var = make_shared<VarSymbol>(id_name);
                ctx->var_symbol = var;

                this->current_scope->enter(id_name, var);
            }
        }

        ///
        /// assignable may be ArrayLiteral or ObjectLiteral
        /// But they can be transformed during preprocess phase.

        /// Call the parent class's method with the same name to traverse the child nodes.
        this->JavaScriptParserBaseVisitor::visitVariableDeclaration(ctx);

        return {};
    }

    std::any visitFunctionDeclaration(JavaScriptParser::FunctionDeclarationContext *ctx) override
    {
        auto last_scope = this->current_scope;

        this->current_scope = make_shared<Scope>(ctx, last_scope);
        ctx->scope = this->current_scope;

        this->JavaScriptParserBaseVisitor::visitFunctionDeclaration(ctx);

        string func_name = ctx->identifier()->getText();
        const auto symbol = make_shared<VarSymbol>(func_name);

        this->current_scope = last_scope;

        if (this->current_scope->has_symbol(func_name)) {
            cout << "Duplicate symbol: " << func_name << std::endl;
        }
        else {
            this->current_scope->enter(func_name, symbol);
        }

        return {};
    }

    std::any visitFormalParameterList(JavaScriptParser::FormalParameterListContext *ctx) override
    {
        for (JavaScriptParser::FormalParameterArgContext *arg : ctx->formalParameterArg())
        {
            /// create VarSymbol for parameter and annotate it to the AST
            const auto arg_id = arg->assignable()->identifier();

            /// Non-function calls may also reach here, so the arg_id could be null.
            /// TODO: WebKit_JSTests_es6_destructuring_in_parameters.js
            ///
            if (arg_id == nullptr) {
                throw EnterError("FormalParameterArgContext arg id is null");
            }

            //if (arg_id->symbol == nullptr) {
            //    continue;
            //}

            string arg_name = arg_id->getText();
            auto var = make_shared<VarSymbol>(arg_name);
            arg_id->symbol = var;

            /// add the symbol of the parameter to the function's scope
            this->current_scope->enter(arg_name, var);
        }

        return {};
    }

    std::any visitBlock(JavaScriptParser::BlockContext *ctx) override
    {
        const auto last_scope = this->current_scope;

        this->current_scope = make_shared<Scope>(ctx, this->current_scope);
        ctx->scope = this->current_scope;

        this->JavaScriptParserBaseVisitor::visitBlock(ctx);

        this->current_scope = last_scope;
        return {};
    }

    std::any visitForStatement(JavaScriptParser::ForStatementContext *ctx) override
    {
        const auto last_scope = this->current_scope;

        this->current_scope = make_shared<Scope>(ctx, this->current_scope);
        ctx->scope = this->current_scope;

        /// traverse the childs
        this->JavaScriptParserBaseVisitor::visitForStatement(ctx);

        this->current_scope = last_scope;
        return {};
    }

    std::any visitForInStatement(JavaScriptParser::ForInStatementContext *ctx) override
    {
        const auto last_scope = this->current_scope;

        this->current_scope = make_shared<Scope>(ctx, this->current_scope);
        ctx->scope = this->current_scope;

        this->JavaScriptParserBaseVisitor::visitForInStatement(ctx);

        this->current_scope = last_scope;
        return {};
    }

    std::any visitForOfStatement(JavaScriptParser::ForOfStatementContext *ctx) override
    {
        const auto last_scope = this->current_scope;

        this->current_scope = make_shared<Scope>(ctx, this->current_scope);
        ctx->scope = this->current_scope;

        this->JavaScriptParserBaseVisitor::visitForOfStatement(ctx);

        this->current_scope = last_scope;
        return {};
    }

    std::any visitClassDeclaration(JavaScriptParser::ClassDeclarationContext *ctx) override
    {
        this->JavaScriptParserBaseVisitor::visitClassDeclaration(ctx);

        return {};
    }

    std::any visitCatchProduction(JavaScriptParser::CatchProductionContext *ctx) override
    {
        const auto current_scope = this->current_scope;

        if (JavaScriptParser::AssignableContext *assignable = ctx->assignable();
            assignable != nullptr && assignable->identifier() != nullptr)
        {
            if (string id_name = assignable->identifier()->getText();
                current_scope->has_symbol(id_name))
            {
                cout << "Duplicate symbol: " << id_name << std::endl;

                /// Declares a new variable with the same name, creating a fresh var symbol
                /// The new declaration shadows the previous variable
                /// When querying the scope, search from most recent to oldest declarations
                ///
                const auto var_symbol = make_shared<VarSymbol>(id_name);
                assignable->identifier()->is_left_value = true;
                this->current_scope->enter(id_name, var_symbol);
            }
            else {
                const auto var_symbol = make_shared<VarSymbol>(id_name);
                assignable->identifier()->is_left_value = true;
                this->current_scope->enter(id_name, var_symbol);
            }
        }

        ///
        this->JavaScriptParserBaseVisitor::visitCatchProduction(ctx);

        return {};
    }
};

} /// end of namespace

#endif //FUZZFLOW_ENTER_H