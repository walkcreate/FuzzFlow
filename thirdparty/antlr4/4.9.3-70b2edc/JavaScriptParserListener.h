
    #include "JavaScriptParserBase.h"


// Generated from JavaScriptParser.g4 by ANTLR 4.9.3

#pragma once


#include "antlr4-runtime.h"
#include "JavaScriptParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by JavaScriptParser.
 */
class  JavaScriptParserListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(JavaScriptParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(JavaScriptParser::ProgramContext *ctx) = 0;

  virtual void enterSourceElement(JavaScriptParser::SourceElementContext *ctx) = 0;
  virtual void exitSourceElement(JavaScriptParser::SourceElementContext *ctx) = 0;

  virtual void enterStatement(JavaScriptParser::StatementContext *ctx) = 0;
  virtual void exitStatement(JavaScriptParser::StatementContext *ctx) = 0;

  virtual void enterBlock(JavaScriptParser::BlockContext *ctx) = 0;
  virtual void exitBlock(JavaScriptParser::BlockContext *ctx) = 0;

  virtual void enterStatementList(JavaScriptParser::StatementListContext *ctx) = 0;
  virtual void exitStatementList(JavaScriptParser::StatementListContext *ctx) = 0;

  virtual void enterImportStatement(JavaScriptParser::ImportStatementContext *ctx) = 0;
  virtual void exitImportStatement(JavaScriptParser::ImportStatementContext *ctx) = 0;

  virtual void enterImportFromBlock(JavaScriptParser::ImportFromBlockContext *ctx) = 0;
  virtual void exitImportFromBlock(JavaScriptParser::ImportFromBlockContext *ctx) = 0;

  virtual void enterModuleItems(JavaScriptParser::ModuleItemsContext *ctx) = 0;
  virtual void exitModuleItems(JavaScriptParser::ModuleItemsContext *ctx) = 0;

  virtual void enterImportDefault(JavaScriptParser::ImportDefaultContext *ctx) = 0;
  virtual void exitImportDefault(JavaScriptParser::ImportDefaultContext *ctx) = 0;

  virtual void enterImportNamespace(JavaScriptParser::ImportNamespaceContext *ctx) = 0;
  virtual void exitImportNamespace(JavaScriptParser::ImportNamespaceContext *ctx) = 0;

  virtual void enterImportFrom(JavaScriptParser::ImportFromContext *ctx) = 0;
  virtual void exitImportFrom(JavaScriptParser::ImportFromContext *ctx) = 0;

  virtual void enterAliasName(JavaScriptParser::AliasNameContext *ctx) = 0;
  virtual void exitAliasName(JavaScriptParser::AliasNameContext *ctx) = 0;

  virtual void enterExportDeclaration(JavaScriptParser::ExportDeclarationContext *ctx) = 0;
  virtual void exitExportDeclaration(JavaScriptParser::ExportDeclarationContext *ctx) = 0;

  virtual void enterExportDefaultDeclaration(JavaScriptParser::ExportDefaultDeclarationContext *ctx) = 0;
  virtual void exitExportDefaultDeclaration(JavaScriptParser::ExportDefaultDeclarationContext *ctx) = 0;

  virtual void enterExportFromBlock(JavaScriptParser::ExportFromBlockContext *ctx) = 0;
  virtual void exitExportFromBlock(JavaScriptParser::ExportFromBlockContext *ctx) = 0;

  virtual void enterDeclaration(JavaScriptParser::DeclarationContext *ctx) = 0;
  virtual void exitDeclaration(JavaScriptParser::DeclarationContext *ctx) = 0;

  virtual void enterVariableStatement(JavaScriptParser::VariableStatementContext *ctx) = 0;
  virtual void exitVariableStatement(JavaScriptParser::VariableStatementContext *ctx) = 0;

  virtual void enterVariableDeclarationList(JavaScriptParser::VariableDeclarationListContext *ctx) = 0;
  virtual void exitVariableDeclarationList(JavaScriptParser::VariableDeclarationListContext *ctx) = 0;

  virtual void enterVariableDeclaration(JavaScriptParser::VariableDeclarationContext *ctx) = 0;
  virtual void exitVariableDeclaration(JavaScriptParser::VariableDeclarationContext *ctx) = 0;

  virtual void enterEmptyStatement_(JavaScriptParser::EmptyStatement_Context *ctx) = 0;
  virtual void exitEmptyStatement_(JavaScriptParser::EmptyStatement_Context *ctx) = 0;

  virtual void enterExpressionStatement(JavaScriptParser::ExpressionStatementContext *ctx) = 0;
  virtual void exitExpressionStatement(JavaScriptParser::ExpressionStatementContext *ctx) = 0;

  virtual void enterIfStatement(JavaScriptParser::IfStatementContext *ctx) = 0;
  virtual void exitIfStatement(JavaScriptParser::IfStatementContext *ctx) = 0;

  virtual void enterDoStatement(JavaScriptParser::DoStatementContext *ctx) = 0;
  virtual void exitDoStatement(JavaScriptParser::DoStatementContext *ctx) = 0;

  virtual void enterWhileStatement(JavaScriptParser::WhileStatementContext *ctx) = 0;
  virtual void exitWhileStatement(JavaScriptParser::WhileStatementContext *ctx) = 0;

  virtual void enterForStatement(JavaScriptParser::ForStatementContext *ctx) = 0;
  virtual void exitForStatement(JavaScriptParser::ForStatementContext *ctx) = 0;

  virtual void enterForInStatement(JavaScriptParser::ForInStatementContext *ctx) = 0;
  virtual void exitForInStatement(JavaScriptParser::ForInStatementContext *ctx) = 0;

  virtual void enterForOfStatement(JavaScriptParser::ForOfStatementContext *ctx) = 0;
  virtual void exitForOfStatement(JavaScriptParser::ForOfStatementContext *ctx) = 0;

  virtual void enterVarModifier(JavaScriptParser::VarModifierContext *ctx) = 0;
  virtual void exitVarModifier(JavaScriptParser::VarModifierContext *ctx) = 0;

  virtual void enterContinueStatement(JavaScriptParser::ContinueStatementContext *ctx) = 0;
  virtual void exitContinueStatement(JavaScriptParser::ContinueStatementContext *ctx) = 0;

  virtual void enterBreakStatement(JavaScriptParser::BreakStatementContext *ctx) = 0;
  virtual void exitBreakStatement(JavaScriptParser::BreakStatementContext *ctx) = 0;

  virtual void enterReturnStatement(JavaScriptParser::ReturnStatementContext *ctx) = 0;
  virtual void exitReturnStatement(JavaScriptParser::ReturnStatementContext *ctx) = 0;

  virtual void enterYieldStatement(JavaScriptParser::YieldStatementContext *ctx) = 0;
  virtual void exitYieldStatement(JavaScriptParser::YieldStatementContext *ctx) = 0;

  virtual void enterWithStatement(JavaScriptParser::WithStatementContext *ctx) = 0;
  virtual void exitWithStatement(JavaScriptParser::WithStatementContext *ctx) = 0;

  virtual void enterSwitchStatement(JavaScriptParser::SwitchStatementContext *ctx) = 0;
  virtual void exitSwitchStatement(JavaScriptParser::SwitchStatementContext *ctx) = 0;

  virtual void enterCaseBlock(JavaScriptParser::CaseBlockContext *ctx) = 0;
  virtual void exitCaseBlock(JavaScriptParser::CaseBlockContext *ctx) = 0;

  virtual void enterCaseClauses(JavaScriptParser::CaseClausesContext *ctx) = 0;
  virtual void exitCaseClauses(JavaScriptParser::CaseClausesContext *ctx) = 0;

  virtual void enterCaseClause(JavaScriptParser::CaseClauseContext *ctx) = 0;
  virtual void exitCaseClause(JavaScriptParser::CaseClauseContext *ctx) = 0;

  virtual void enterDefaultClause(JavaScriptParser::DefaultClauseContext *ctx) = 0;
  virtual void exitDefaultClause(JavaScriptParser::DefaultClauseContext *ctx) = 0;

  virtual void enterLabelledStatement(JavaScriptParser::LabelledStatementContext *ctx) = 0;
  virtual void exitLabelledStatement(JavaScriptParser::LabelledStatementContext *ctx) = 0;

  virtual void enterThrowStatement(JavaScriptParser::ThrowStatementContext *ctx) = 0;
  virtual void exitThrowStatement(JavaScriptParser::ThrowStatementContext *ctx) = 0;

  virtual void enterTryStatement(JavaScriptParser::TryStatementContext *ctx) = 0;
  virtual void exitTryStatement(JavaScriptParser::TryStatementContext *ctx) = 0;

  virtual void enterCatchProduction(JavaScriptParser::CatchProductionContext *ctx) = 0;
  virtual void exitCatchProduction(JavaScriptParser::CatchProductionContext *ctx) = 0;

  virtual void enterFinallyProduction(JavaScriptParser::FinallyProductionContext *ctx) = 0;
  virtual void exitFinallyProduction(JavaScriptParser::FinallyProductionContext *ctx) = 0;

  virtual void enterDebuggerStatement(JavaScriptParser::DebuggerStatementContext *ctx) = 0;
  virtual void exitDebuggerStatement(JavaScriptParser::DebuggerStatementContext *ctx) = 0;

  virtual void enterFunctionDeclaration(JavaScriptParser::FunctionDeclarationContext *ctx) = 0;
  virtual void exitFunctionDeclaration(JavaScriptParser::FunctionDeclarationContext *ctx) = 0;

  virtual void enterClassDeclaration(JavaScriptParser::ClassDeclarationContext *ctx) = 0;
  virtual void exitClassDeclaration(JavaScriptParser::ClassDeclarationContext *ctx) = 0;

  virtual void enterClassTail(JavaScriptParser::ClassTailContext *ctx) = 0;
  virtual void exitClassTail(JavaScriptParser::ClassTailContext *ctx) = 0;

  virtual void enterClassElement(JavaScriptParser::ClassElementContext *ctx) = 0;
  virtual void exitClassElement(JavaScriptParser::ClassElementContext *ctx) = 0;

  virtual void enterMethodDefinition(JavaScriptParser::MethodDefinitionContext *ctx) = 0;
  virtual void exitMethodDefinition(JavaScriptParser::MethodDefinitionContext *ctx) = 0;

  virtual void enterFormalParameterList(JavaScriptParser::FormalParameterListContext *ctx) = 0;
  virtual void exitFormalParameterList(JavaScriptParser::FormalParameterListContext *ctx) = 0;

  virtual void enterFormalParameterArg(JavaScriptParser::FormalParameterArgContext *ctx) = 0;
  virtual void exitFormalParameterArg(JavaScriptParser::FormalParameterArgContext *ctx) = 0;

  virtual void enterLastFormalParameterArg(JavaScriptParser::LastFormalParameterArgContext *ctx) = 0;
  virtual void exitLastFormalParameterArg(JavaScriptParser::LastFormalParameterArgContext *ctx) = 0;

  virtual void enterFunctionBody(JavaScriptParser::FunctionBodyContext *ctx) = 0;
  virtual void exitFunctionBody(JavaScriptParser::FunctionBodyContext *ctx) = 0;

  virtual void enterSourceElements(JavaScriptParser::SourceElementsContext *ctx) = 0;
  virtual void exitSourceElements(JavaScriptParser::SourceElementsContext *ctx) = 0;

  virtual void enterArrayLiteral(JavaScriptParser::ArrayLiteralContext *ctx) = 0;
  virtual void exitArrayLiteral(JavaScriptParser::ArrayLiteralContext *ctx) = 0;

  virtual void enterElementList(JavaScriptParser::ElementListContext *ctx) = 0;
  virtual void exitElementList(JavaScriptParser::ElementListContext *ctx) = 0;

  virtual void enterArrayElement(JavaScriptParser::ArrayElementContext *ctx) = 0;
  virtual void exitArrayElement(JavaScriptParser::ArrayElementContext *ctx) = 0;

  virtual void enterPropertyExpressionAssignment(JavaScriptParser::PropertyExpressionAssignmentContext *ctx) = 0;
  virtual void exitPropertyExpressionAssignment(JavaScriptParser::PropertyExpressionAssignmentContext *ctx) = 0;

  virtual void enterComputedPropertyExpressionAssignment(JavaScriptParser::ComputedPropertyExpressionAssignmentContext *ctx) = 0;
  virtual void exitComputedPropertyExpressionAssignment(JavaScriptParser::ComputedPropertyExpressionAssignmentContext *ctx) = 0;

  virtual void enterFunctionProperty(JavaScriptParser::FunctionPropertyContext *ctx) = 0;
  virtual void exitFunctionProperty(JavaScriptParser::FunctionPropertyContext *ctx) = 0;

  virtual void enterPropertyGetter(JavaScriptParser::PropertyGetterContext *ctx) = 0;
  virtual void exitPropertyGetter(JavaScriptParser::PropertyGetterContext *ctx) = 0;

  virtual void enterPropertySetter(JavaScriptParser::PropertySetterContext *ctx) = 0;
  virtual void exitPropertySetter(JavaScriptParser::PropertySetterContext *ctx) = 0;

  virtual void enterPropertyShorthand(JavaScriptParser::PropertyShorthandContext *ctx) = 0;
  virtual void exitPropertyShorthand(JavaScriptParser::PropertyShorthandContext *ctx) = 0;

  virtual void enterPropertyName(JavaScriptParser::PropertyNameContext *ctx) = 0;
  virtual void exitPropertyName(JavaScriptParser::PropertyNameContext *ctx) = 0;

  virtual void enterArguments(JavaScriptParser::ArgumentsContext *ctx) = 0;
  virtual void exitArguments(JavaScriptParser::ArgumentsContext *ctx) = 0;

  virtual void enterArgument(JavaScriptParser::ArgumentContext *ctx) = 0;
  virtual void exitArgument(JavaScriptParser::ArgumentContext *ctx) = 0;

  virtual void enterExpressionSequence(JavaScriptParser::ExpressionSequenceContext *ctx) = 0;
  virtual void exitExpressionSequence(JavaScriptParser::ExpressionSequenceContext *ctx) = 0;

  virtual void enterTemplateStringExpression(JavaScriptParser::TemplateStringExpressionContext *ctx) = 0;
  virtual void exitTemplateStringExpression(JavaScriptParser::TemplateStringExpressionContext *ctx) = 0;

  virtual void enterTernaryExpression(JavaScriptParser::TernaryExpressionContext *ctx) = 0;
  virtual void exitTernaryExpression(JavaScriptParser::TernaryExpressionContext *ctx) = 0;

  virtual void enterLogicalAndExpression(JavaScriptParser::LogicalAndExpressionContext *ctx) = 0;
  virtual void exitLogicalAndExpression(JavaScriptParser::LogicalAndExpressionContext *ctx) = 0;

  virtual void enterPowerExpression(JavaScriptParser::PowerExpressionContext *ctx) = 0;
  virtual void exitPowerExpression(JavaScriptParser::PowerExpressionContext *ctx) = 0;

  virtual void enterPreIncrementExpression(JavaScriptParser::PreIncrementExpressionContext *ctx) = 0;
  virtual void exitPreIncrementExpression(JavaScriptParser::PreIncrementExpressionContext *ctx) = 0;

  virtual void enterObjectLiteralExpression(JavaScriptParser::ObjectLiteralExpressionContext *ctx) = 0;
  virtual void exitObjectLiteralExpression(JavaScriptParser::ObjectLiteralExpressionContext *ctx) = 0;

  virtual void enterMetaExpression(JavaScriptParser::MetaExpressionContext *ctx) = 0;
  virtual void exitMetaExpression(JavaScriptParser::MetaExpressionContext *ctx) = 0;

  virtual void enterInExpression(JavaScriptParser::InExpressionContext *ctx) = 0;
  virtual void exitInExpression(JavaScriptParser::InExpressionContext *ctx) = 0;

  virtual void enterLogicalOrExpression(JavaScriptParser::LogicalOrExpressionContext *ctx) = 0;
  virtual void exitLogicalOrExpression(JavaScriptParser::LogicalOrExpressionContext *ctx) = 0;

  virtual void enterNotExpression(JavaScriptParser::NotExpressionContext *ctx) = 0;
  virtual void exitNotExpression(JavaScriptParser::NotExpressionContext *ctx) = 0;

  virtual void enterPreDecreaseExpression(JavaScriptParser::PreDecreaseExpressionContext *ctx) = 0;
  virtual void exitPreDecreaseExpression(JavaScriptParser::PreDecreaseExpressionContext *ctx) = 0;

  virtual void enterArgumentsExpression(JavaScriptParser::ArgumentsExpressionContext *ctx) = 0;
  virtual void exitArgumentsExpression(JavaScriptParser::ArgumentsExpressionContext *ctx) = 0;

  virtual void enterAwaitExpression(JavaScriptParser::AwaitExpressionContext *ctx) = 0;
  virtual void exitAwaitExpression(JavaScriptParser::AwaitExpressionContext *ctx) = 0;

  virtual void enterThisExpression(JavaScriptParser::ThisExpressionContext *ctx) = 0;
  virtual void exitThisExpression(JavaScriptParser::ThisExpressionContext *ctx) = 0;

  virtual void enterFunctionExpression(JavaScriptParser::FunctionExpressionContext *ctx) = 0;
  virtual void exitFunctionExpression(JavaScriptParser::FunctionExpressionContext *ctx) = 0;

  virtual void enterUnaryMinusExpression(JavaScriptParser::UnaryMinusExpressionContext *ctx) = 0;
  virtual void exitUnaryMinusExpression(JavaScriptParser::UnaryMinusExpressionContext *ctx) = 0;

  virtual void enterAssignmentExpression(JavaScriptParser::AssignmentExpressionContext *ctx) = 0;
  virtual void exitAssignmentExpression(JavaScriptParser::AssignmentExpressionContext *ctx) = 0;

  virtual void enterPostDecreaseExpression(JavaScriptParser::PostDecreaseExpressionContext *ctx) = 0;
  virtual void exitPostDecreaseExpression(JavaScriptParser::PostDecreaseExpressionContext *ctx) = 0;

  virtual void enterTypeofExpression(JavaScriptParser::TypeofExpressionContext *ctx) = 0;
  virtual void exitTypeofExpression(JavaScriptParser::TypeofExpressionContext *ctx) = 0;

  virtual void enterInstanceofExpression(JavaScriptParser::InstanceofExpressionContext *ctx) = 0;
  virtual void exitInstanceofExpression(JavaScriptParser::InstanceofExpressionContext *ctx) = 0;

  virtual void enterUnaryPlusExpression(JavaScriptParser::UnaryPlusExpressionContext *ctx) = 0;
  virtual void exitUnaryPlusExpression(JavaScriptParser::UnaryPlusExpressionContext *ctx) = 0;

  virtual void enterDeleteExpression(JavaScriptParser::DeleteExpressionContext *ctx) = 0;
  virtual void exitDeleteExpression(JavaScriptParser::DeleteExpressionContext *ctx) = 0;

  virtual void enterImportExpression(JavaScriptParser::ImportExpressionContext *ctx) = 0;
  virtual void exitImportExpression(JavaScriptParser::ImportExpressionContext *ctx) = 0;

  virtual void enterEqualityExpression(JavaScriptParser::EqualityExpressionContext *ctx) = 0;
  virtual void exitEqualityExpression(JavaScriptParser::EqualityExpressionContext *ctx) = 0;

  virtual void enterBitXOrExpression(JavaScriptParser::BitXOrExpressionContext *ctx) = 0;
  virtual void exitBitXOrExpression(JavaScriptParser::BitXOrExpressionContext *ctx) = 0;

  virtual void enterSuperExpression(JavaScriptParser::SuperExpressionContext *ctx) = 0;
  virtual void exitSuperExpression(JavaScriptParser::SuperExpressionContext *ctx) = 0;

  virtual void enterMultiplicativeExpression(JavaScriptParser::MultiplicativeExpressionContext *ctx) = 0;
  virtual void exitMultiplicativeExpression(JavaScriptParser::MultiplicativeExpressionContext *ctx) = 0;

  virtual void enterBitShiftExpression(JavaScriptParser::BitShiftExpressionContext *ctx) = 0;
  virtual void exitBitShiftExpression(JavaScriptParser::BitShiftExpressionContext *ctx) = 0;

  virtual void enterParenthesizedExpression(JavaScriptParser::ParenthesizedExpressionContext *ctx) = 0;
  virtual void exitParenthesizedExpression(JavaScriptParser::ParenthesizedExpressionContext *ctx) = 0;

  virtual void enterAdditiveExpression(JavaScriptParser::AdditiveExpressionContext *ctx) = 0;
  virtual void exitAdditiveExpression(JavaScriptParser::AdditiveExpressionContext *ctx) = 0;

  virtual void enterRelationalExpression(JavaScriptParser::RelationalExpressionContext *ctx) = 0;
  virtual void exitRelationalExpression(JavaScriptParser::RelationalExpressionContext *ctx) = 0;

  virtual void enterPostIncrementExpression(JavaScriptParser::PostIncrementExpressionContext *ctx) = 0;
  virtual void exitPostIncrementExpression(JavaScriptParser::PostIncrementExpressionContext *ctx) = 0;

  virtual void enterYieldExpression(JavaScriptParser::YieldExpressionContext *ctx) = 0;
  virtual void exitYieldExpression(JavaScriptParser::YieldExpressionContext *ctx) = 0;

  virtual void enterBitNotExpression(JavaScriptParser::BitNotExpressionContext *ctx) = 0;
  virtual void exitBitNotExpression(JavaScriptParser::BitNotExpressionContext *ctx) = 0;

  virtual void enterNewExpression(JavaScriptParser::NewExpressionContext *ctx) = 0;
  virtual void exitNewExpression(JavaScriptParser::NewExpressionContext *ctx) = 0;

  virtual void enterLiteralExpression(JavaScriptParser::LiteralExpressionContext *ctx) = 0;
  virtual void exitLiteralExpression(JavaScriptParser::LiteralExpressionContext *ctx) = 0;

  virtual void enterArrayLiteralExpression(JavaScriptParser::ArrayLiteralExpressionContext *ctx) = 0;
  virtual void exitArrayLiteralExpression(JavaScriptParser::ArrayLiteralExpressionContext *ctx) = 0;

  virtual void enterMemberDotExpression(JavaScriptParser::MemberDotExpressionContext *ctx) = 0;
  virtual void exitMemberDotExpression(JavaScriptParser::MemberDotExpressionContext *ctx) = 0;

  virtual void enterClassExpression(JavaScriptParser::ClassExpressionContext *ctx) = 0;
  virtual void exitClassExpression(JavaScriptParser::ClassExpressionContext *ctx) = 0;

  virtual void enterMemberIndexExpression(JavaScriptParser::MemberIndexExpressionContext *ctx) = 0;
  virtual void exitMemberIndexExpression(JavaScriptParser::MemberIndexExpressionContext *ctx) = 0;

  virtual void enterIdentifierExpression(JavaScriptParser::IdentifierExpressionContext *ctx) = 0;
  virtual void exitIdentifierExpression(JavaScriptParser::IdentifierExpressionContext *ctx) = 0;

  virtual void enterBitAndExpression(JavaScriptParser::BitAndExpressionContext *ctx) = 0;
  virtual void exitBitAndExpression(JavaScriptParser::BitAndExpressionContext *ctx) = 0;

  virtual void enterBitOrExpression(JavaScriptParser::BitOrExpressionContext *ctx) = 0;
  virtual void exitBitOrExpression(JavaScriptParser::BitOrExpressionContext *ctx) = 0;

  virtual void enterAssignmentOperatorExpression(JavaScriptParser::AssignmentOperatorExpressionContext *ctx) = 0;
  virtual void exitAssignmentOperatorExpression(JavaScriptParser::AssignmentOperatorExpressionContext *ctx) = 0;

  virtual void enterVoidExpression(JavaScriptParser::VoidExpressionContext *ctx) = 0;
  virtual void exitVoidExpression(JavaScriptParser::VoidExpressionContext *ctx) = 0;

  virtual void enterCoalesceExpression(JavaScriptParser::CoalesceExpressionContext *ctx) = 0;
  virtual void exitCoalesceExpression(JavaScriptParser::CoalesceExpressionContext *ctx) = 0;

  virtual void enterAssignable(JavaScriptParser::AssignableContext *ctx) = 0;
  virtual void exitAssignable(JavaScriptParser::AssignableContext *ctx) = 0;

  virtual void enterObjectLiteral(JavaScriptParser::ObjectLiteralContext *ctx) = 0;
  virtual void exitObjectLiteral(JavaScriptParser::ObjectLiteralContext *ctx) = 0;

  virtual void enterFunctionDecl(JavaScriptParser::FunctionDeclContext *ctx) = 0;
  virtual void exitFunctionDecl(JavaScriptParser::FunctionDeclContext *ctx) = 0;

  virtual void enterAnonymousFunctionDecl(JavaScriptParser::AnonymousFunctionDeclContext *ctx) = 0;
  virtual void exitAnonymousFunctionDecl(JavaScriptParser::AnonymousFunctionDeclContext *ctx) = 0;

  virtual void enterArrowFunction(JavaScriptParser::ArrowFunctionContext *ctx) = 0;
  virtual void exitArrowFunction(JavaScriptParser::ArrowFunctionContext *ctx) = 0;

  virtual void enterArrowFunctionParameters(JavaScriptParser::ArrowFunctionParametersContext *ctx) = 0;
  virtual void exitArrowFunctionParameters(JavaScriptParser::ArrowFunctionParametersContext *ctx) = 0;

  virtual void enterArrowFunctionBody(JavaScriptParser::ArrowFunctionBodyContext *ctx) = 0;
  virtual void exitArrowFunctionBody(JavaScriptParser::ArrowFunctionBodyContext *ctx) = 0;

  virtual void enterAssignmentOperator(JavaScriptParser::AssignmentOperatorContext *ctx) = 0;
  virtual void exitAssignmentOperator(JavaScriptParser::AssignmentOperatorContext *ctx) = 0;

  virtual void enterLiteral(JavaScriptParser::LiteralContext *ctx) = 0;
  virtual void exitLiteral(JavaScriptParser::LiteralContext *ctx) = 0;

  virtual void enterTemplateStringLiteral(JavaScriptParser::TemplateStringLiteralContext *ctx) = 0;
  virtual void exitTemplateStringLiteral(JavaScriptParser::TemplateStringLiteralContext *ctx) = 0;

  virtual void enterTemplateStringAtom(JavaScriptParser::TemplateStringAtomContext *ctx) = 0;
  virtual void exitTemplateStringAtom(JavaScriptParser::TemplateStringAtomContext *ctx) = 0;

  virtual void enterNumericLiteral(JavaScriptParser::NumericLiteralContext *ctx) = 0;
  virtual void exitNumericLiteral(JavaScriptParser::NumericLiteralContext *ctx) = 0;

  virtual void enterBigintLiteral(JavaScriptParser::BigintLiteralContext *ctx) = 0;
  virtual void exitBigintLiteral(JavaScriptParser::BigintLiteralContext *ctx) = 0;

  virtual void enterGetter(JavaScriptParser::GetterContext *ctx) = 0;
  virtual void exitGetter(JavaScriptParser::GetterContext *ctx) = 0;

  virtual void enterSetter(JavaScriptParser::SetterContext *ctx) = 0;
  virtual void exitSetter(JavaScriptParser::SetterContext *ctx) = 0;

  virtual void enterIdentifierName(JavaScriptParser::IdentifierNameContext *ctx) = 0;
  virtual void exitIdentifierName(JavaScriptParser::IdentifierNameContext *ctx) = 0;

  virtual void enterIdentifier(JavaScriptParser::IdentifierContext *ctx) = 0;
  virtual void exitIdentifier(JavaScriptParser::IdentifierContext *ctx) = 0;

  virtual void enterReservedWord(JavaScriptParser::ReservedWordContext *ctx) = 0;
  virtual void exitReservedWord(JavaScriptParser::ReservedWordContext *ctx) = 0;

  virtual void enterKeyword(JavaScriptParser::KeywordContext *ctx) = 0;
  virtual void exitKeyword(JavaScriptParser::KeywordContext *ctx) = 0;

  virtual void enterLet_(JavaScriptParser::Let_Context *ctx) = 0;
  virtual void exitLet_(JavaScriptParser::Let_Context *ctx) = 0;

  virtual void enterEos(JavaScriptParser::EosContext *ctx) = 0;
  virtual void exitEos(JavaScriptParser::EosContext *ctx) = 0;


};

