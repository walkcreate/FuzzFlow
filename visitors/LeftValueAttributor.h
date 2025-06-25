#ifndef FUZZFLOW_LEFTVALUEATTRIBUTOR_H
#define FUZZFLOW_LEFTVALUEATTRIBUTOR_H

#include "../utils/common_using.h"

#include <any>

#include "../thirdparty/antlr4/JavaScriptParserBaseVisitor.h"
#include "../semantic/FunctionSymbol.h"
#include "../semantic/VarSymbol.h"
#include "../semantic/Scope.h"

#include "antlr4-runtime.h"
using antlr4::ParserRuleContext;

class LeftValueAttributor : public JavaScriptParserBaseVisitor {

    bool should_be_left_value = false;

    bool should_be_left_member = false;

    bool searching_root_object_var = false;

    std::any visitPreIncrementExpression(JavaScriptParser::PreIncrementExpressionContext *ctx) override
    {
        ///
        /// The target of the increment operator must always be an l-value.
        /// The expression being incremented can be an identifier or other expressions,
        /// such as MemberDot.
        ///
        if (JavaScriptParser::SingleExpressionContext *expr = ctx->singleExpression();
            dynamic_cast<JavaScriptParser::MemberDotExpressionContext *>(expr) != nullptr
            || dynamic_cast<JavaScriptParser::MemberIndexExpressionContext *>(expr) != nullptr)
        {
            this->should_be_left_member = true;
            visit(expr);
            this->should_be_left_member = false;
        }
        else {
            this->should_be_left_value = true;
            visit(expr);
            this->should_be_left_value = false;
        }

        return nullptr;
    }

    std::any visitPostIncrementExpression(JavaScriptParser::PostIncrementExpressionContext *ctx) override
    {
        if (JavaScriptParser::SingleExpressionContext *expr = ctx->singleExpression();
            dynamic_cast<JavaScriptParser::MemberDotExpressionContext *>(expr) != nullptr
            || dynamic_cast<JavaScriptParser::MemberIndexExpressionContext *>(expr) != nullptr)
        {

            this->should_be_left_member = true;
            visit(expr);
            this->should_be_left_member = false;
        }
        else {
            this->should_be_left_value = true;
            visit(expr);
            this->should_be_left_value = false;
        }

        return nullptr;
    }

    std::any visitPreDecreaseExpression(JavaScriptParser::PreDecreaseExpressionContext *ctx) override
    {
        if (JavaScriptParser::SingleExpressionContext *expr = ctx->singleExpression();
            dynamic_cast<JavaScriptParser::MemberDotExpressionContext *>(expr) != nullptr
            || dynamic_cast<JavaScriptParser::MemberIndexExpressionContext *>(expr) != nullptr)
        {
            this->should_be_left_member = true;
            visit(expr);
            this->should_be_left_member = false;
        }
        else {
            this->should_be_left_value = true;
            visit(expr);
            this->should_be_left_value = false;
        }

        return nullptr;
    }

    std::any visitPostDecreaseExpression(JavaScriptParser::PostDecreaseExpressionContext *ctx) override
    {
        if (JavaScriptParser::SingleExpressionContext *expr = ctx->singleExpression();
            dynamic_cast<JavaScriptParser::MemberDotExpressionContext *>(expr) != nullptr
            || dynamic_cast<JavaScriptParser::MemberIndexExpressionContext *>(expr) != nullptr)
        {
            this->should_be_left_member = true;
            visit(expr);
            this->should_be_left_member = false;
        }
        else {
            this->should_be_left_value = true;
            visit(expr);
            this->should_be_left_value = false;
        }

        return nullptr;
    }

    std::any visitIdentifier(JavaScriptParser::IdentifierContext *ctx) override
    {
        if (this->should_be_left_value){
            ctx->is_left_value = true;
        }
        return this->JavaScriptParserBaseVisitor::visitIdentifier(ctx);
    }

    std::any visitAssignmentExpression(JavaScriptParser::AssignmentExpressionContext *ctx) override
    {
        /// The target of an assignment must always be an l-value.
        if (JavaScriptParser::SingleExpressionContext *single_expr_left = ctx->singleExpression(0);
            dynamic_cast<JavaScriptParser::MemberDotExpressionContext *>(single_expr_left) != nullptr
            || dynamic_cast<JavaScriptParser::MemberIndexExpressionContext *>(single_expr_left) != nullptr)
        {
            this->should_be_left_member = true;
            visit(single_expr_left);
            this->should_be_left_member = false;
        }
        else {
            this->should_be_left_value = true;
            visit(single_expr_left);
            this->should_be_left_value = false;
        }

        /// traverse the right child
        JavaScriptParser::SingleExpressionContext *single_expr_right = ctx->singleExpression(1);
        visit(single_expr_right);

        return nullptr;
    }

    std::any visitAssignmentOperatorExpression(JavaScriptParser::AssignmentOperatorExpressionContext *ctx) override
    {
        /// The target of an AssignmentOperator must always be an l-value.
        /// +=, -=, *=, /=, ...
        ///
        if (JavaScriptParser::SingleExpressionContext *single_expr_left = ctx->singleExpression(0);
            dynamic_cast<JavaScriptParser::MemberDotExpressionContext *>(single_expr_left) != nullptr
            || dynamic_cast<JavaScriptParser::MemberIndexExpressionContext *>(single_expr_left) != nullptr)
        {
            this->should_be_left_member = true;
            visit(single_expr_left);
            this->should_be_left_member = false;
        }
        else {
            this->should_be_left_value = true;
            visit(single_expr_left);
            this->should_be_left_value = false;
        }

        JavaScriptParser::SingleExpressionContext *single_expr_right = ctx->singleExpression(1);
        visit(single_expr_right);

        return nullptr;
    }

    void tag_left_value_for_object_access(JavaScriptParser::SingleExpressionContext * object_field)
    {
        /// In the object part, if the left subtree contains only an Identifier or
        /// MemberDot/MemberIndex, the root object's identifier should be marked as an l-value.
        if (const auto id_node = dynamic_cast<JavaScriptParser::IdentifierExpressionContext *>(object_field))
        {
            /// If the Object of a MemberDot is an Identifier and the search flag is set to true,
            /// the Identifier is marked as an l-value.
            /// This identifies the root object variable being sought.
            /// Only by marking the Identifier as an l-value can the corresponding var symbol object be located.
            if (this->searching_root_object_var) {
                id_node->identifier()->is_left_value = true;
                this->searching_root_object_var = false;
            }
        }
        else if (dynamic_cast<JavaScriptParser::MemberDotExpressionContext *>(object_field) != nullptr
                 || dynamic_cast<JavaScriptParser::MemberIndexExpressionContext *>(object_field) != nullptr) {
            /// If the object part is still a MemberDot or MemberIndex, the search should continue.
            /// At this point, the search flag should remain active,
            /// as there is still a possibility of locating the root object variable(var) .
            this->visit(object_field);
        }
        else {
            /// If the object part is not a MemberDot or MemberIndex,
            /// there is no need to search for the root variable (var) anymore, as the chain of references has been broken.
            /// Even if a Member node is encountered later, it will no longer be used as an l-value.
            this->searching_root_object_var = false;
            this->visit(object_field);
        }
    }

    /**
     * Production rule:
     *   singleExpression '?'? '.' '#'? identifierName
     */
    std::any visitMemberDotExpression(JavaScriptParser::MemberDotExpressionContext *ctx) override
    {
        ///
        /// When visiting a MemberDotExpression, if should_be_left_member is true,
        /// it indicates that the MemberDot node is the direct target of an assignment.
        /// In this case, the node's is_left_value flag is set to distinguish between StoreField and LoadField.
        /// Not all MemberDot nodes on the left side of the assignment operator(=)
        /// need to be marked as l-values.
        /// Only the MemberDot node that is the direct child of the assignment expression's
        /// left side should be marked as an l-value.
        ///
        /// Once a node is marked as an l-value, its lower-level MemberDot nodes do not need to
        /// be assigned the l-value property.
        ///
        /// For example, in a MemberDotExpression like o.a.b.c:
        /// The overall expression is a MemberDot with object as o.a.b and field as c.
        /// o.a.b is a MemberDot with object as o.a and field as b.
        /// o.a is another MemberDot with object as o and field as a.
        /// Among these three MemberDot nodes, only the first one is marked as an l-value.
        ///
        bool has_set_search = false;
        if (this->should_be_left_member) {
            ctx->is_left_value = true;

            /// One assignment produces one MemberX of l-value type.
            /// Once this node is set as an l-value Member,
            /// lower-level Member nodes do not need to be set as l-values.
            this->should_be_left_member = false;

            this->searching_root_object_var = true;
            has_set_search = true;
        }

        const auto object_field = ctx->singleExpression();

        this->tag_left_value_for_object_access(object_field);

        /// todo
        /// The child nodes under the field part do not need to be marked as l-values.
        auto field_ret = this->visit(ctx->identifierName());

        /// Disables the flag to prevent subsequent MemberDot operations from being affected if lookup fails.
        if (has_set_search && this->searching_root_object_var) {
            this->searching_root_object_var = false;
        }

        return nullptr;
    }

    /**
     * Production rule:
     *     singleExpression '[' expressionSequence ']'
     */
    std::any visitMemberIndexExpression(JavaScriptParser::MemberIndexExpressionContext *ctx) override
    {

        bool has_set_search = false;
        if (this->should_be_left_member) {

            ctx->is_left_value = true;
            this->should_be_left_member = false;

            this->searching_root_object_var = true;
            has_set_search = true;
        }

        JavaScriptParser::SingleExpressionContext * object_field = ctx->singleExpression();
        this->tag_left_value_for_object_access(object_field);

        auto field_ret = this->visit(ctx->expressionSequence());

        if (has_set_search && this->searching_root_object_var) {
            this->searching_root_object_var = false;
        }

        return nullptr;
    }
};

#endif //FUZZFLOW_LEFTVALUEATTRIBUTOR_H
