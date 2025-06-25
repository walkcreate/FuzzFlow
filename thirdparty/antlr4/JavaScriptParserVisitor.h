
    #include "JavaScriptParserBase.h"


// Generated from JavaScriptParser.g4 by ANTLR 4.9.3

#pragma once


#include "antlr4-runtime.h"
#include "JavaScriptParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by JavaScriptParser.
 */
class  JavaScriptParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by JavaScriptParser.
   */
    virtual antlrcpp::Any visitProgram(JavaScriptParser::ProgramContext *context) = 0;

    virtual antlrcpp::Any visitSourceElement(JavaScriptParser::SourceElementContext *context) = 0;

    virtual antlrcpp::Any visitStatement(JavaScriptParser::StatementContext *context) = 0;

    virtual antlrcpp::Any visitBlock(JavaScriptParser::BlockContext *context) = 0;

    virtual antlrcpp::Any visitStatementList(JavaScriptParser::StatementListContext *context) = 0;

    virtual antlrcpp::Any visitImportStatement(JavaScriptParser::ImportStatementContext *context) = 0;

    virtual antlrcpp::Any visitImportFromBlock(JavaScriptParser::ImportFromBlockContext *context) = 0;

    virtual antlrcpp::Any visitModuleItems(JavaScriptParser::ModuleItemsContext *context) = 0;

    virtual antlrcpp::Any visitImportDefault(JavaScriptParser::ImportDefaultContext *context) = 0;

    virtual antlrcpp::Any visitImportNamespace(JavaScriptParser::ImportNamespaceContext *context) = 0;

    virtual antlrcpp::Any visitImportFrom(JavaScriptParser::ImportFromContext *context) = 0;

    virtual antlrcpp::Any visitAliasName(JavaScriptParser::AliasNameContext *context) = 0;

    virtual antlrcpp::Any visitExportDeclaration(JavaScriptParser::ExportDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitExportDefaultDeclaration(JavaScriptParser::ExportDefaultDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitExportFromBlock(JavaScriptParser::ExportFromBlockContext *context) = 0;

    virtual antlrcpp::Any visitDeclaration(JavaScriptParser::DeclarationContext *context) = 0;

    virtual antlrcpp::Any visitVariableStatement(JavaScriptParser::VariableStatementContext *context) = 0;

    virtual antlrcpp::Any visitVariableDeclarationList(JavaScriptParser::VariableDeclarationListContext *context) = 0;

    virtual antlrcpp::Any visitVariableDeclaration(JavaScriptParser::VariableDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitEmptyStatement_(JavaScriptParser::EmptyStatement_Context *context) = 0;

    virtual antlrcpp::Any visitExpressionStatement(JavaScriptParser::ExpressionStatementContext *context) = 0;

    virtual antlrcpp::Any visitIfStatement(JavaScriptParser::IfStatementContext *context) = 0;

    virtual antlrcpp::Any visitDoStatement(JavaScriptParser::DoStatementContext *context) = 0;

    virtual antlrcpp::Any visitWhileStatement(JavaScriptParser::WhileStatementContext *context) = 0;

    virtual antlrcpp::Any visitForStatement(JavaScriptParser::ForStatementContext *context) = 0;

    virtual antlrcpp::Any visitForInStatement(JavaScriptParser::ForInStatementContext *context) = 0;

    virtual antlrcpp::Any visitForOfStatement(JavaScriptParser::ForOfStatementContext *context) = 0;

    virtual antlrcpp::Any visitVarModifier(JavaScriptParser::VarModifierContext *context) = 0;

    virtual antlrcpp::Any visitContinueStatement(JavaScriptParser::ContinueStatementContext *context) = 0;

    virtual antlrcpp::Any visitBreakStatement(JavaScriptParser::BreakStatementContext *context) = 0;

    virtual antlrcpp::Any visitReturnStatement(JavaScriptParser::ReturnStatementContext *context) = 0;

    virtual antlrcpp::Any visitYieldStatement(JavaScriptParser::YieldStatementContext *context) = 0;

    virtual antlrcpp::Any visitWithStatement(JavaScriptParser::WithStatementContext *context) = 0;

    virtual antlrcpp::Any visitSwitchStatement(JavaScriptParser::SwitchStatementContext *context) = 0;

    virtual antlrcpp::Any visitCaseBlock(JavaScriptParser::CaseBlockContext *context) = 0;

    virtual antlrcpp::Any visitCaseClauses(JavaScriptParser::CaseClausesContext *context) = 0;

    virtual antlrcpp::Any visitCaseClause(JavaScriptParser::CaseClauseContext *context) = 0;

    virtual antlrcpp::Any visitDefaultClause(JavaScriptParser::DefaultClauseContext *context) = 0;

    virtual antlrcpp::Any visitLabelledStatement(JavaScriptParser::LabelledStatementContext *context) = 0;

    virtual antlrcpp::Any visitThrowStatement(JavaScriptParser::ThrowStatementContext *context) = 0;

    virtual antlrcpp::Any visitTryStatement(JavaScriptParser::TryStatementContext *context) = 0;

    virtual antlrcpp::Any visitCatchProduction(JavaScriptParser::CatchProductionContext *context) = 0;

    virtual antlrcpp::Any visitFinallyProduction(JavaScriptParser::FinallyProductionContext *context) = 0;

    virtual antlrcpp::Any visitDebuggerStatement(JavaScriptParser::DebuggerStatementContext *context) = 0;

    virtual antlrcpp::Any visitFunctionDeclaration(JavaScriptParser::FunctionDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitClassDeclaration(JavaScriptParser::ClassDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitClassTail(JavaScriptParser::ClassTailContext *context) = 0;

    virtual antlrcpp::Any visitClassElement(JavaScriptParser::ClassElementContext *context) = 0;

    virtual antlrcpp::Any visitMethodDefinition(JavaScriptParser::MethodDefinitionContext *context) = 0;

    virtual antlrcpp::Any visitFormalParameterList(JavaScriptParser::FormalParameterListContext *context) = 0;

    virtual antlrcpp::Any visitFormalParameterArg(JavaScriptParser::FormalParameterArgContext *context) = 0;

    virtual antlrcpp::Any visitLastFormalParameterArg(JavaScriptParser::LastFormalParameterArgContext *context) = 0;

    virtual antlrcpp::Any visitFunctionBody(JavaScriptParser::FunctionBodyContext *context) = 0;

    virtual antlrcpp::Any visitSourceElements(JavaScriptParser::SourceElementsContext *context) = 0;

    virtual antlrcpp::Any visitArrayLiteral(JavaScriptParser::ArrayLiteralContext *context) = 0;

    virtual antlrcpp::Any visitElementList(JavaScriptParser::ElementListContext *context) = 0;

    virtual antlrcpp::Any visitArrayElement(JavaScriptParser::ArrayElementContext *context) = 0;

    virtual antlrcpp::Any visitPropertyExpressionAssignment(JavaScriptParser::PropertyExpressionAssignmentContext *context) = 0;

    virtual antlrcpp::Any visitComputedPropertyExpressionAssignment(JavaScriptParser::ComputedPropertyExpressionAssignmentContext *context) = 0;

    virtual antlrcpp::Any visitFunctionProperty(JavaScriptParser::FunctionPropertyContext *context) = 0;

    virtual antlrcpp::Any visitPropertyGetter(JavaScriptParser::PropertyGetterContext *context) = 0;

    virtual antlrcpp::Any visitPropertySetter(JavaScriptParser::PropertySetterContext *context) = 0;

    virtual antlrcpp::Any visitPropertyShorthand(JavaScriptParser::PropertyShorthandContext *context) = 0;

    virtual antlrcpp::Any visitPropertyName(JavaScriptParser::PropertyNameContext *context) = 0;

    virtual antlrcpp::Any visitArguments(JavaScriptParser::ArgumentsContext *context) = 0;

    virtual antlrcpp::Any visitArgument(JavaScriptParser::ArgumentContext *context) = 0;

    virtual antlrcpp::Any visitExpressionSequence(JavaScriptParser::ExpressionSequenceContext *context) = 0;

    virtual antlrcpp::Any visitTemplateStringExpression(JavaScriptParser::TemplateStringExpressionContext *context) = 0;

    virtual antlrcpp::Any visitTernaryExpression(JavaScriptParser::TernaryExpressionContext *context) = 0;

    virtual antlrcpp::Any visitLogicalAndExpression(JavaScriptParser::LogicalAndExpressionContext *context) = 0;

    virtual antlrcpp::Any visitPowerExpression(JavaScriptParser::PowerExpressionContext *context) = 0;

    virtual antlrcpp::Any visitPreIncrementExpression(JavaScriptParser::PreIncrementExpressionContext *context) = 0;

    virtual antlrcpp::Any visitObjectLiteralExpression(JavaScriptParser::ObjectLiteralExpressionContext *context) = 0;

    virtual antlrcpp::Any visitMetaExpression(JavaScriptParser::MetaExpressionContext *context) = 0;

    virtual antlrcpp::Any visitInExpression(JavaScriptParser::InExpressionContext *context) = 0;

    virtual antlrcpp::Any visitLogicalOrExpression(JavaScriptParser::LogicalOrExpressionContext *context) = 0;

    virtual antlrcpp::Any visitNotExpression(JavaScriptParser::NotExpressionContext *context) = 0;

    virtual antlrcpp::Any visitPreDecreaseExpression(JavaScriptParser::PreDecreaseExpressionContext *context) = 0;

    virtual antlrcpp::Any visitArgumentsExpression(JavaScriptParser::ArgumentsExpressionContext *context) = 0;

    virtual antlrcpp::Any visitAwaitExpression(JavaScriptParser::AwaitExpressionContext *context) = 0;

    virtual antlrcpp::Any visitThisExpression(JavaScriptParser::ThisExpressionContext *context) = 0;

    virtual antlrcpp::Any visitFunctionExpression(JavaScriptParser::FunctionExpressionContext *context) = 0;

    virtual antlrcpp::Any visitUnaryMinusExpression(JavaScriptParser::UnaryMinusExpressionContext *context) = 0;

    virtual antlrcpp::Any visitAssignmentExpression(JavaScriptParser::AssignmentExpressionContext *context) = 0;

    virtual antlrcpp::Any visitPostDecreaseExpression(JavaScriptParser::PostDecreaseExpressionContext *context) = 0;

    virtual antlrcpp::Any visitTypeofExpression(JavaScriptParser::TypeofExpressionContext *context) = 0;

    virtual antlrcpp::Any visitInstanceofExpression(JavaScriptParser::InstanceofExpressionContext *context) = 0;

    virtual antlrcpp::Any visitUnaryPlusExpression(JavaScriptParser::UnaryPlusExpressionContext *context) = 0;

    virtual antlrcpp::Any visitDeleteExpression(JavaScriptParser::DeleteExpressionContext *context) = 0;

    virtual antlrcpp::Any visitImportExpression(JavaScriptParser::ImportExpressionContext *context) = 0;

    virtual antlrcpp::Any visitEqualityExpression(JavaScriptParser::EqualityExpressionContext *context) = 0;

    virtual antlrcpp::Any visitBitXOrExpression(JavaScriptParser::BitXOrExpressionContext *context) = 0;

    virtual antlrcpp::Any visitSuperExpression(JavaScriptParser::SuperExpressionContext *context) = 0;

    virtual antlrcpp::Any visitMultiplicativeExpression(JavaScriptParser::MultiplicativeExpressionContext *context) = 0;

    virtual antlrcpp::Any visitBitShiftExpression(JavaScriptParser::BitShiftExpressionContext *context) = 0;

    virtual antlrcpp::Any visitParenthesizedExpression(JavaScriptParser::ParenthesizedExpressionContext *context) = 0;

    virtual antlrcpp::Any visitAdditiveExpression(JavaScriptParser::AdditiveExpressionContext *context) = 0;

    virtual antlrcpp::Any visitRelationalExpression(JavaScriptParser::RelationalExpressionContext *context) = 0;

    virtual antlrcpp::Any visitPostIncrementExpression(JavaScriptParser::PostIncrementExpressionContext *context) = 0;

    virtual antlrcpp::Any visitYieldExpression(JavaScriptParser::YieldExpressionContext *context) = 0;

    virtual antlrcpp::Any visitBitNotExpression(JavaScriptParser::BitNotExpressionContext *context) = 0;

    virtual antlrcpp::Any visitNewExpression(JavaScriptParser::NewExpressionContext *context) = 0;

    virtual antlrcpp::Any visitLiteralExpression(JavaScriptParser::LiteralExpressionContext *context) = 0;

    virtual antlrcpp::Any visitArrayLiteralExpression(JavaScriptParser::ArrayLiteralExpressionContext *context) = 0;

    virtual antlrcpp::Any visitMemberDotExpression(JavaScriptParser::MemberDotExpressionContext *context) = 0;

    virtual antlrcpp::Any visitClassExpression(JavaScriptParser::ClassExpressionContext *context) = 0;

    virtual antlrcpp::Any visitMemberIndexExpression(JavaScriptParser::MemberIndexExpressionContext *context) = 0;

    virtual antlrcpp::Any visitIdentifierExpression(JavaScriptParser::IdentifierExpressionContext *context) = 0;

    virtual antlrcpp::Any visitBitAndExpression(JavaScriptParser::BitAndExpressionContext *context) = 0;

    virtual antlrcpp::Any visitBitOrExpression(JavaScriptParser::BitOrExpressionContext *context) = 0;

    virtual antlrcpp::Any visitAssignmentOperatorExpression(JavaScriptParser::AssignmentOperatorExpressionContext *context) = 0;

    virtual antlrcpp::Any visitVoidExpression(JavaScriptParser::VoidExpressionContext *context) = 0;

    virtual antlrcpp::Any visitCoalesceExpression(JavaScriptParser::CoalesceExpressionContext *context) = 0;

    virtual antlrcpp::Any visitAssignable(JavaScriptParser::AssignableContext *context) = 0;

    virtual antlrcpp::Any visitObjectLiteral(JavaScriptParser::ObjectLiteralContext *context) = 0;

    virtual antlrcpp::Any visitFunctionDecl(JavaScriptParser::FunctionDeclContext *context) = 0;

    virtual antlrcpp::Any visitAnonymousFunctionDecl(JavaScriptParser::AnonymousFunctionDeclContext *context) = 0;

    virtual antlrcpp::Any visitArrowFunction(JavaScriptParser::ArrowFunctionContext *context) = 0;

    virtual antlrcpp::Any visitArrowFunctionParameters(JavaScriptParser::ArrowFunctionParametersContext *context) = 0;

    virtual antlrcpp::Any visitArrowFunctionBody(JavaScriptParser::ArrowFunctionBodyContext *context) = 0;

    virtual antlrcpp::Any visitAssignmentOperator(JavaScriptParser::AssignmentOperatorContext *context) = 0;

    virtual antlrcpp::Any visitLiteral(JavaScriptParser::LiteralContext *context) = 0;

    virtual antlrcpp::Any visitTemplateStringLiteral(JavaScriptParser::TemplateStringLiteralContext *context) = 0;

    virtual antlrcpp::Any visitTemplateStringAtom(JavaScriptParser::TemplateStringAtomContext *context) = 0;

    virtual antlrcpp::Any visitNumericLiteral(JavaScriptParser::NumericLiteralContext *context) = 0;

    virtual antlrcpp::Any visitBigintLiteral(JavaScriptParser::BigintLiteralContext *context) = 0;

    virtual antlrcpp::Any visitGetter(JavaScriptParser::GetterContext *context) = 0;

    virtual antlrcpp::Any visitSetter(JavaScriptParser::SetterContext *context) = 0;

    virtual antlrcpp::Any visitIdentifierName(JavaScriptParser::IdentifierNameContext *context) = 0;

    virtual antlrcpp::Any visitIdentifier(JavaScriptParser::IdentifierContext *context) = 0;

    virtual antlrcpp::Any visitReservedWord(JavaScriptParser::ReservedWordContext *context) = 0;

    virtual antlrcpp::Any visitKeyword(JavaScriptParser::KeywordContext *context) = 0;

    virtual antlrcpp::Any visitLet_(JavaScriptParser::Let_Context *context) = 0;

    virtual antlrcpp::Any visitEos(JavaScriptParser::EosContext *context) = 0;


};

