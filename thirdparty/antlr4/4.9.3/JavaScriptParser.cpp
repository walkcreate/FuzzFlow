
    #include "JavaScriptParserBase.h"


// Generated from JavaScriptParser.g4 by ANTLR 4.9.3


#include "JavaScriptParserListener.h"
#include "JavaScriptParserVisitor.h"

#include "JavaScriptParser.h"


using namespace antlrcpp;
using namespace antlr4;

JavaScriptParser::JavaScriptParser(TokenStream *input) : JavaScriptParserBase(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

JavaScriptParser::~JavaScriptParser() {
  delete _interpreter;
}

std::string JavaScriptParser::getGrammarFileName() const {
  return "JavaScriptParser.g4";
}

const std::vector<std::string>& JavaScriptParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& JavaScriptParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgramContext ------------------------------------------------------------------

JavaScriptParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ProgramContext::EOF() {
  return getToken(JavaScriptParser::EOF, 0);
}

tree::TerminalNode* JavaScriptParser::ProgramContext::HashBangLine() {
  return getToken(JavaScriptParser::HashBangLine, 0);
}

JavaScriptParser::SourceElementsContext* JavaScriptParser::ProgramContext::sourceElements() {
  return getRuleContext<JavaScriptParser::SourceElementsContext>(0);
}


size_t JavaScriptParser::ProgramContext::getRuleIndex() const {
  return JavaScriptParser::RuleProgram;
}

void JavaScriptParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void JavaScriptParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}


antlrcpp::Any JavaScriptParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ProgramContext* JavaScriptParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, JavaScriptParser::RuleProgram);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(155);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      setState(154);
      match(JavaScriptParser::HashBangLine);
      break;
    }

    default:
      break;
    }
    setState(158);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      setState(157);
      sourceElements();
      break;
    }

    default:
      break;
    }
    setState(160);
    match(JavaScriptParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SourceElementContext ------------------------------------------------------------------

JavaScriptParser::SourceElementContext::SourceElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::StatementContext* JavaScriptParser::SourceElementContext::statement() {
  return getRuleContext<JavaScriptParser::StatementContext>(0);
}


size_t JavaScriptParser::SourceElementContext::getRuleIndex() const {
  return JavaScriptParser::RuleSourceElement;
}

void JavaScriptParser::SourceElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSourceElement(this);
}

void JavaScriptParser::SourceElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSourceElement(this);
}


antlrcpp::Any JavaScriptParser::SourceElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitSourceElement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::SourceElementContext* JavaScriptParser::sourceElement() {
  SourceElementContext *_localctx = _tracker.createInstance<SourceElementContext>(_ctx, getState());
  enterRule(_localctx, 2, JavaScriptParser::RuleSourceElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(162);
    statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

JavaScriptParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::BlockContext* JavaScriptParser::StatementContext::block() {
  return getRuleContext<JavaScriptParser::BlockContext>(0);
}

JavaScriptParser::VariableStatementContext* JavaScriptParser::StatementContext::variableStatement() {
  return getRuleContext<JavaScriptParser::VariableStatementContext>(0);
}

JavaScriptParser::ImportStatementContext* JavaScriptParser::StatementContext::importStatement() {
  return getRuleContext<JavaScriptParser::ImportStatementContext>(0);
}

JavaScriptParser::ExportStatementContext* JavaScriptParser::StatementContext::exportStatement() {
  return getRuleContext<JavaScriptParser::ExportStatementContext>(0);
}

JavaScriptParser::EmptyStatement_Context* JavaScriptParser::StatementContext::emptyStatement_() {
  return getRuleContext<JavaScriptParser::EmptyStatement_Context>(0);
}

JavaScriptParser::ClassDeclarationContext* JavaScriptParser::StatementContext::classDeclaration() {
  return getRuleContext<JavaScriptParser::ClassDeclarationContext>(0);
}

JavaScriptParser::ExpressionStatementContext* JavaScriptParser::StatementContext::expressionStatement() {
  return getRuleContext<JavaScriptParser::ExpressionStatementContext>(0);
}

JavaScriptParser::IfStatementContext* JavaScriptParser::StatementContext::ifStatement() {
  return getRuleContext<JavaScriptParser::IfStatementContext>(0);
}

JavaScriptParser::IterationStatementContext* JavaScriptParser::StatementContext::iterationStatement() {
  return getRuleContext<JavaScriptParser::IterationStatementContext>(0);
}

JavaScriptParser::ContinueStatementContext* JavaScriptParser::StatementContext::continueStatement() {
  return getRuleContext<JavaScriptParser::ContinueStatementContext>(0);
}

JavaScriptParser::BreakStatementContext* JavaScriptParser::StatementContext::breakStatement() {
  return getRuleContext<JavaScriptParser::BreakStatementContext>(0);
}

JavaScriptParser::ReturnStatementContext* JavaScriptParser::StatementContext::returnStatement() {
  return getRuleContext<JavaScriptParser::ReturnStatementContext>(0);
}

JavaScriptParser::YieldStatementContext* JavaScriptParser::StatementContext::yieldStatement() {
  return getRuleContext<JavaScriptParser::YieldStatementContext>(0);
}

JavaScriptParser::WithStatementContext* JavaScriptParser::StatementContext::withStatement() {
  return getRuleContext<JavaScriptParser::WithStatementContext>(0);
}

JavaScriptParser::LabelledStatementContext* JavaScriptParser::StatementContext::labelledStatement() {
  return getRuleContext<JavaScriptParser::LabelledStatementContext>(0);
}

JavaScriptParser::SwitchStatementContext* JavaScriptParser::StatementContext::switchStatement() {
  return getRuleContext<JavaScriptParser::SwitchStatementContext>(0);
}

JavaScriptParser::ThrowStatementContext* JavaScriptParser::StatementContext::throwStatement() {
  return getRuleContext<JavaScriptParser::ThrowStatementContext>(0);
}

JavaScriptParser::TryStatementContext* JavaScriptParser::StatementContext::tryStatement() {
  return getRuleContext<JavaScriptParser::TryStatementContext>(0);
}

JavaScriptParser::DebuggerStatementContext* JavaScriptParser::StatementContext::debuggerStatement() {
  return getRuleContext<JavaScriptParser::DebuggerStatementContext>(0);
}

JavaScriptParser::FunctionDeclarationContext* JavaScriptParser::StatementContext::functionDeclaration() {
  return getRuleContext<JavaScriptParser::FunctionDeclarationContext>(0);
}


size_t JavaScriptParser::StatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleStatement;
}

void JavaScriptParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void JavaScriptParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}


antlrcpp::Any JavaScriptParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::StatementContext* JavaScriptParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 4, JavaScriptParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(184);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(164);
      block();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(165);
      variableStatement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(166);
      importStatement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(167);
      exportStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(168);
      emptyStatement_();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(169);
      classDeclaration();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(170);
      expressionStatement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(171);
      ifStatement();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(172);
      iterationStatement();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(173);
      continueStatement();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(174);
      breakStatement();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(175);
      returnStatement();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(176);
      yieldStatement();
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(177);
      withStatement();
      break;
    }

    case 15: {
      enterOuterAlt(_localctx, 15);
      setState(178);
      labelledStatement();
      break;
    }

    case 16: {
      enterOuterAlt(_localctx, 16);
      setState(179);
      switchStatement();
      break;
    }

    case 17: {
      enterOuterAlt(_localctx, 17);
      setState(180);
      throwStatement();
      break;
    }

    case 18: {
      enterOuterAlt(_localctx, 18);
      setState(181);
      tryStatement();
      break;
    }

    case 19: {
      enterOuterAlt(_localctx, 19);
      setState(182);
      debuggerStatement();
      break;
    }

    case 20: {
      enterOuterAlt(_localctx, 20);
      setState(183);
      functionDeclaration();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

JavaScriptParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::BlockContext::OpenBrace() {
  return getToken(JavaScriptParser::OpenBrace, 0);
}

tree::TerminalNode* JavaScriptParser::BlockContext::CloseBrace() {
  return getToken(JavaScriptParser::CloseBrace, 0);
}

JavaScriptParser::StatementListContext* JavaScriptParser::BlockContext::statementList() {
  return getRuleContext<JavaScriptParser::StatementListContext>(0);
}


size_t JavaScriptParser::BlockContext::getRuleIndex() const {
  return JavaScriptParser::RuleBlock;
}

void JavaScriptParser::BlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlock(this);
}

void JavaScriptParser::BlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlock(this);
}


antlrcpp::Any JavaScriptParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::BlockContext* JavaScriptParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 6, JavaScriptParser::RuleBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(186);
    match(JavaScriptParser::OpenBrace);
    setState(188);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      setState(187);
      statementList();
      break;
    }

    default:
      break;
    }
    setState(190);
    match(JavaScriptParser::CloseBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementListContext ------------------------------------------------------------------

JavaScriptParser::StatementListContext::StatementListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::StatementContext *> JavaScriptParser::StatementListContext::statement() {
  return getRuleContexts<JavaScriptParser::StatementContext>();
}

JavaScriptParser::StatementContext* JavaScriptParser::StatementListContext::statement(size_t i) {
  return getRuleContext<JavaScriptParser::StatementContext>(i);
}


size_t JavaScriptParser::StatementListContext::getRuleIndex() const {
  return JavaScriptParser::RuleStatementList;
}

void JavaScriptParser::StatementListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatementList(this);
}

void JavaScriptParser::StatementListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatementList(this);
}


antlrcpp::Any JavaScriptParser::StatementListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitStatementList(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::StatementListContext* JavaScriptParser::statementList() {
  StatementListContext *_localctx = _tracker.createInstance<StatementListContext>(_ctx, getState());
  enterRule(_localctx, 8, JavaScriptParser::RuleStatementList);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(193); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(192);
              statement();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(195); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportStatementContext ------------------------------------------------------------------

JavaScriptParser::ImportStatementContext::ImportStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ImportStatementContext::Import() {
  return getToken(JavaScriptParser::Import, 0);
}

JavaScriptParser::ImportFromBlockContext* JavaScriptParser::ImportStatementContext::importFromBlock() {
  return getRuleContext<JavaScriptParser::ImportFromBlockContext>(0);
}


size_t JavaScriptParser::ImportStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleImportStatement;
}

void JavaScriptParser::ImportStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImportStatement(this);
}

void JavaScriptParser::ImportStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImportStatement(this);
}


antlrcpp::Any JavaScriptParser::ImportStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitImportStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ImportStatementContext* JavaScriptParser::importStatement() {
  ImportStatementContext *_localctx = _tracker.createInstance<ImportStatementContext>(_ctx, getState());
  enterRule(_localctx, 10, JavaScriptParser::RuleImportStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(197);
    match(JavaScriptParser::Import);
    setState(198);
    importFromBlock();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportFromBlockContext ------------------------------------------------------------------

JavaScriptParser::ImportFromBlockContext::ImportFromBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::ImportFromContext* JavaScriptParser::ImportFromBlockContext::importFrom() {
  return getRuleContext<JavaScriptParser::ImportFromContext>(0);
}

JavaScriptParser::EosContext* JavaScriptParser::ImportFromBlockContext::eos() {
  return getRuleContext<JavaScriptParser::EosContext>(0);
}

JavaScriptParser::ImportNamespaceContext* JavaScriptParser::ImportFromBlockContext::importNamespace() {
  return getRuleContext<JavaScriptParser::ImportNamespaceContext>(0);
}

JavaScriptParser::ModuleItemsContext* JavaScriptParser::ImportFromBlockContext::moduleItems() {
  return getRuleContext<JavaScriptParser::ModuleItemsContext>(0);
}

JavaScriptParser::ImportDefaultContext* JavaScriptParser::ImportFromBlockContext::importDefault() {
  return getRuleContext<JavaScriptParser::ImportDefaultContext>(0);
}

tree::TerminalNode* JavaScriptParser::ImportFromBlockContext::StringLiteral() {
  return getToken(JavaScriptParser::StringLiteral, 0);
}


size_t JavaScriptParser::ImportFromBlockContext::getRuleIndex() const {
  return JavaScriptParser::RuleImportFromBlock;
}

void JavaScriptParser::ImportFromBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImportFromBlock(this);
}

void JavaScriptParser::ImportFromBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImportFromBlock(this);
}


antlrcpp::Any JavaScriptParser::ImportFromBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitImportFromBlock(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ImportFromBlockContext* JavaScriptParser::importFromBlock() {
  ImportFromBlockContext *_localctx = _tracker.createInstance<ImportFromBlockContext>(_ctx, getState());
  enterRule(_localctx, 12, JavaScriptParser::RuleImportFromBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(212);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::OpenBrace:
      case JavaScriptParser::Multiply:
      case JavaScriptParser::NullLiteral:
      case JavaScriptParser::BooleanLiteral:
      case JavaScriptParser::Break:
      case JavaScriptParser::Do:
      case JavaScriptParser::Instanceof:
      case JavaScriptParser::Typeof:
      case JavaScriptParser::Case:
      case JavaScriptParser::Else:
      case JavaScriptParser::New:
      case JavaScriptParser::Var:
      case JavaScriptParser::Catch:
      case JavaScriptParser::Finally:
      case JavaScriptParser::Return:
      case JavaScriptParser::Void:
      case JavaScriptParser::Continue:
      case JavaScriptParser::For:
      case JavaScriptParser::Switch:
      case JavaScriptParser::While:
      case JavaScriptParser::Debugger:
      case JavaScriptParser::Function_:
      case JavaScriptParser::This:
      case JavaScriptParser::With:
      case JavaScriptParser::Default:
      case JavaScriptParser::If:
      case JavaScriptParser::Throw:
      case JavaScriptParser::Delete:
      case JavaScriptParser::In:
      case JavaScriptParser::Try:
      case JavaScriptParser::As:
      case JavaScriptParser::From:
      case JavaScriptParser::Class:
      case JavaScriptParser::Enum:
      case JavaScriptParser::Extends:
      case JavaScriptParser::Super:
      case JavaScriptParser::Const:
      case JavaScriptParser::Export:
      case JavaScriptParser::Import:
      case JavaScriptParser::Async:
      case JavaScriptParser::Await:
      case JavaScriptParser::Yield:
      case JavaScriptParser::Implements:
      case JavaScriptParser::StrictLet:
      case JavaScriptParser::NonStrictLet:
      case JavaScriptParser::Private:
      case JavaScriptParser::Public:
      case JavaScriptParser::Interface:
      case JavaScriptParser::Package:
      case JavaScriptParser::Protected:
      case JavaScriptParser::Static:
      case JavaScriptParser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(201);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
        case 1: {
          setState(200);
          importDefault();
          break;
        }

        default:
          break;
        }
        setState(205);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case JavaScriptParser::Multiply:
          case JavaScriptParser::NullLiteral:
          case JavaScriptParser::BooleanLiteral:
          case JavaScriptParser::Break:
          case JavaScriptParser::Do:
          case JavaScriptParser::Instanceof:
          case JavaScriptParser::Typeof:
          case JavaScriptParser::Case:
          case JavaScriptParser::Else:
          case JavaScriptParser::New:
          case JavaScriptParser::Var:
          case JavaScriptParser::Catch:
          case JavaScriptParser::Finally:
          case JavaScriptParser::Return:
          case JavaScriptParser::Void:
          case JavaScriptParser::Continue:
          case JavaScriptParser::For:
          case JavaScriptParser::Switch:
          case JavaScriptParser::While:
          case JavaScriptParser::Debugger:
          case JavaScriptParser::Function_:
          case JavaScriptParser::This:
          case JavaScriptParser::With:
          case JavaScriptParser::Default:
          case JavaScriptParser::If:
          case JavaScriptParser::Throw:
          case JavaScriptParser::Delete:
          case JavaScriptParser::In:
          case JavaScriptParser::Try:
          case JavaScriptParser::As:
          case JavaScriptParser::From:
          case JavaScriptParser::Class:
          case JavaScriptParser::Enum:
          case JavaScriptParser::Extends:
          case JavaScriptParser::Super:
          case JavaScriptParser::Const:
          case JavaScriptParser::Export:
          case JavaScriptParser::Import:
          case JavaScriptParser::Async:
          case JavaScriptParser::Await:
          case JavaScriptParser::Yield:
          case JavaScriptParser::Implements:
          case JavaScriptParser::StrictLet:
          case JavaScriptParser::NonStrictLet:
          case JavaScriptParser::Private:
          case JavaScriptParser::Public:
          case JavaScriptParser::Interface:
          case JavaScriptParser::Package:
          case JavaScriptParser::Protected:
          case JavaScriptParser::Static:
          case JavaScriptParser::Identifier: {
            setState(203);
            importNamespace();
            break;
          }

          case JavaScriptParser::OpenBrace: {
            setState(204);
            moduleItems();
            break;
          }

        default:
          throw NoViableAltException(this);
        }
        setState(207);
        importFrom();
        setState(208);
        eos();
        break;
      }

      case JavaScriptParser::StringLiteral: {
        enterOuterAlt(_localctx, 2);
        setState(210);
        match(JavaScriptParser::StringLiteral);
        setState(211);
        eos();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ModuleItemsContext ------------------------------------------------------------------

JavaScriptParser::ModuleItemsContext::ModuleItemsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ModuleItemsContext::OpenBrace() {
  return getToken(JavaScriptParser::OpenBrace, 0);
}

tree::TerminalNode* JavaScriptParser::ModuleItemsContext::CloseBrace() {
  return getToken(JavaScriptParser::CloseBrace, 0);
}

std::vector<JavaScriptParser::AliasNameContext *> JavaScriptParser::ModuleItemsContext::aliasName() {
  return getRuleContexts<JavaScriptParser::AliasNameContext>();
}

JavaScriptParser::AliasNameContext* JavaScriptParser::ModuleItemsContext::aliasName(size_t i) {
  return getRuleContext<JavaScriptParser::AliasNameContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::ModuleItemsContext::Comma() {
  return getTokens(JavaScriptParser::Comma);
}

tree::TerminalNode* JavaScriptParser::ModuleItemsContext::Comma(size_t i) {
  return getToken(JavaScriptParser::Comma, i);
}


size_t JavaScriptParser::ModuleItemsContext::getRuleIndex() const {
  return JavaScriptParser::RuleModuleItems;
}

void JavaScriptParser::ModuleItemsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterModuleItems(this);
}

void JavaScriptParser::ModuleItemsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitModuleItems(this);
}


antlrcpp::Any JavaScriptParser::ModuleItemsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitModuleItems(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ModuleItemsContext* JavaScriptParser::moduleItems() {
  ModuleItemsContext *_localctx = _tracker.createInstance<ModuleItemsContext>(_ctx, getState());
  enterRule(_localctx, 14, JavaScriptParser::RuleModuleItems);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(214);
    match(JavaScriptParser::OpenBrace);
    setState(220);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(215);
        aliasName();
        setState(216);
        match(JavaScriptParser::Comma); 
      }
      setState(222);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    }
    setState(227);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 60) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 60)) & ((1ULL << (JavaScriptParser::NullLiteral - 60))
      | (1ULL << (JavaScriptParser::BooleanLiteral - 60))
      | (1ULL << (JavaScriptParser::Break - 60))
      | (1ULL << (JavaScriptParser::Do - 60))
      | (1ULL << (JavaScriptParser::Instanceof - 60))
      | (1ULL << (JavaScriptParser::Typeof - 60))
      | (1ULL << (JavaScriptParser::Case - 60))
      | (1ULL << (JavaScriptParser::Else - 60))
      | (1ULL << (JavaScriptParser::New - 60))
      | (1ULL << (JavaScriptParser::Var - 60))
      | (1ULL << (JavaScriptParser::Catch - 60))
      | (1ULL << (JavaScriptParser::Finally - 60))
      | (1ULL << (JavaScriptParser::Return - 60))
      | (1ULL << (JavaScriptParser::Void - 60))
      | (1ULL << (JavaScriptParser::Continue - 60))
      | (1ULL << (JavaScriptParser::For - 60))
      | (1ULL << (JavaScriptParser::Switch - 60))
      | (1ULL << (JavaScriptParser::While - 60))
      | (1ULL << (JavaScriptParser::Debugger - 60))
      | (1ULL << (JavaScriptParser::Function_ - 60))
      | (1ULL << (JavaScriptParser::This - 60))
      | (1ULL << (JavaScriptParser::With - 60))
      | (1ULL << (JavaScriptParser::Default - 60))
      | (1ULL << (JavaScriptParser::If - 60))
      | (1ULL << (JavaScriptParser::Throw - 60))
      | (1ULL << (JavaScriptParser::Delete - 60))
      | (1ULL << (JavaScriptParser::In - 60))
      | (1ULL << (JavaScriptParser::Try - 60))
      | (1ULL << (JavaScriptParser::As - 60))
      | (1ULL << (JavaScriptParser::From - 60))
      | (1ULL << (JavaScriptParser::Class - 60))
      | (1ULL << (JavaScriptParser::Enum - 60))
      | (1ULL << (JavaScriptParser::Extends - 60))
      | (1ULL << (JavaScriptParser::Super - 60))
      | (1ULL << (JavaScriptParser::Const - 60))
      | (1ULL << (JavaScriptParser::Export - 60))
      | (1ULL << (JavaScriptParser::Import - 60))
      | (1ULL << (JavaScriptParser::Async - 60))
      | (1ULL << (JavaScriptParser::Await - 60))
      | (1ULL << (JavaScriptParser::Yield - 60))
      | (1ULL << (JavaScriptParser::Implements - 60))
      | (1ULL << (JavaScriptParser::StrictLet - 60))
      | (1ULL << (JavaScriptParser::NonStrictLet - 60))
      | (1ULL << (JavaScriptParser::Private - 60))
      | (1ULL << (JavaScriptParser::Public - 60))
      | (1ULL << (JavaScriptParser::Interface - 60))
      | (1ULL << (JavaScriptParser::Package - 60))
      | (1ULL << (JavaScriptParser::Protected - 60))
      | (1ULL << (JavaScriptParser::Static - 60))
      | (1ULL << (JavaScriptParser::Identifier - 60)))) != 0)) {
      setState(223);
      aliasName();
      setState(225);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == JavaScriptParser::Comma) {
        setState(224);
        match(JavaScriptParser::Comma);
      }
    }
    setState(229);
    match(JavaScriptParser::CloseBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportDefaultContext ------------------------------------------------------------------

JavaScriptParser::ImportDefaultContext::ImportDefaultContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::AliasNameContext* JavaScriptParser::ImportDefaultContext::aliasName() {
  return getRuleContext<JavaScriptParser::AliasNameContext>(0);
}

tree::TerminalNode* JavaScriptParser::ImportDefaultContext::Comma() {
  return getToken(JavaScriptParser::Comma, 0);
}


size_t JavaScriptParser::ImportDefaultContext::getRuleIndex() const {
  return JavaScriptParser::RuleImportDefault;
}

void JavaScriptParser::ImportDefaultContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImportDefault(this);
}

void JavaScriptParser::ImportDefaultContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImportDefault(this);
}


antlrcpp::Any JavaScriptParser::ImportDefaultContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitImportDefault(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ImportDefaultContext* JavaScriptParser::importDefault() {
  ImportDefaultContext *_localctx = _tracker.createInstance<ImportDefaultContext>(_ctx, getState());
  enterRule(_localctx, 16, JavaScriptParser::RuleImportDefault);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(231);
    aliasName();
    setState(232);
    match(JavaScriptParser::Comma);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportNamespaceContext ------------------------------------------------------------------

JavaScriptParser::ImportNamespaceContext::ImportNamespaceContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ImportNamespaceContext::Multiply() {
  return getToken(JavaScriptParser::Multiply, 0);
}

std::vector<JavaScriptParser::IdentifierNameContext *> JavaScriptParser::ImportNamespaceContext::identifierName() {
  return getRuleContexts<JavaScriptParser::IdentifierNameContext>();
}

JavaScriptParser::IdentifierNameContext* JavaScriptParser::ImportNamespaceContext::identifierName(size_t i) {
  return getRuleContext<JavaScriptParser::IdentifierNameContext>(i);
}

tree::TerminalNode* JavaScriptParser::ImportNamespaceContext::As() {
  return getToken(JavaScriptParser::As, 0);
}


size_t JavaScriptParser::ImportNamespaceContext::getRuleIndex() const {
  return JavaScriptParser::RuleImportNamespace;
}

void JavaScriptParser::ImportNamespaceContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImportNamespace(this);
}

void JavaScriptParser::ImportNamespaceContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImportNamespace(this);
}


antlrcpp::Any JavaScriptParser::ImportNamespaceContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitImportNamespace(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ImportNamespaceContext* JavaScriptParser::importNamespace() {
  ImportNamespaceContext *_localctx = _tracker.createInstance<ImportNamespaceContext>(_ctx, getState());
  enterRule(_localctx, 18, JavaScriptParser::RuleImportNamespace);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(236);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::Multiply: {
        setState(234);
        match(JavaScriptParser::Multiply);
        break;
      }

      case JavaScriptParser::NullLiteral:
      case JavaScriptParser::BooleanLiteral:
      case JavaScriptParser::Break:
      case JavaScriptParser::Do:
      case JavaScriptParser::Instanceof:
      case JavaScriptParser::Typeof:
      case JavaScriptParser::Case:
      case JavaScriptParser::Else:
      case JavaScriptParser::New:
      case JavaScriptParser::Var:
      case JavaScriptParser::Catch:
      case JavaScriptParser::Finally:
      case JavaScriptParser::Return:
      case JavaScriptParser::Void:
      case JavaScriptParser::Continue:
      case JavaScriptParser::For:
      case JavaScriptParser::Switch:
      case JavaScriptParser::While:
      case JavaScriptParser::Debugger:
      case JavaScriptParser::Function_:
      case JavaScriptParser::This:
      case JavaScriptParser::With:
      case JavaScriptParser::Default:
      case JavaScriptParser::If:
      case JavaScriptParser::Throw:
      case JavaScriptParser::Delete:
      case JavaScriptParser::In:
      case JavaScriptParser::Try:
      case JavaScriptParser::As:
      case JavaScriptParser::From:
      case JavaScriptParser::Class:
      case JavaScriptParser::Enum:
      case JavaScriptParser::Extends:
      case JavaScriptParser::Super:
      case JavaScriptParser::Const:
      case JavaScriptParser::Export:
      case JavaScriptParser::Import:
      case JavaScriptParser::Async:
      case JavaScriptParser::Await:
      case JavaScriptParser::Yield:
      case JavaScriptParser::Implements:
      case JavaScriptParser::StrictLet:
      case JavaScriptParser::NonStrictLet:
      case JavaScriptParser::Private:
      case JavaScriptParser::Public:
      case JavaScriptParser::Interface:
      case JavaScriptParser::Package:
      case JavaScriptParser::Protected:
      case JavaScriptParser::Static:
      case JavaScriptParser::Identifier: {
        setState(235);
        identifierName();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(240);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::As) {
      setState(238);
      match(JavaScriptParser::As);
      setState(239);
      identifierName();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportFromContext ------------------------------------------------------------------

JavaScriptParser::ImportFromContext::ImportFromContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ImportFromContext::From() {
  return getToken(JavaScriptParser::From, 0);
}

tree::TerminalNode* JavaScriptParser::ImportFromContext::StringLiteral() {
  return getToken(JavaScriptParser::StringLiteral, 0);
}


size_t JavaScriptParser::ImportFromContext::getRuleIndex() const {
  return JavaScriptParser::RuleImportFrom;
}

void JavaScriptParser::ImportFromContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImportFrom(this);
}

void JavaScriptParser::ImportFromContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImportFrom(this);
}


antlrcpp::Any JavaScriptParser::ImportFromContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitImportFrom(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ImportFromContext* JavaScriptParser::importFrom() {
  ImportFromContext *_localctx = _tracker.createInstance<ImportFromContext>(_ctx, getState());
  enterRule(_localctx, 20, JavaScriptParser::RuleImportFrom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(242);
    match(JavaScriptParser::From);
    setState(243);
    match(JavaScriptParser::StringLiteral);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AliasNameContext ------------------------------------------------------------------

JavaScriptParser::AliasNameContext::AliasNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::IdentifierNameContext *> JavaScriptParser::AliasNameContext::identifierName() {
  return getRuleContexts<JavaScriptParser::IdentifierNameContext>();
}

JavaScriptParser::IdentifierNameContext* JavaScriptParser::AliasNameContext::identifierName(size_t i) {
  return getRuleContext<JavaScriptParser::IdentifierNameContext>(i);
}

tree::TerminalNode* JavaScriptParser::AliasNameContext::As() {
  return getToken(JavaScriptParser::As, 0);
}


size_t JavaScriptParser::AliasNameContext::getRuleIndex() const {
  return JavaScriptParser::RuleAliasName;
}

void JavaScriptParser::AliasNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAliasName(this);
}

void JavaScriptParser::AliasNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAliasName(this);
}


antlrcpp::Any JavaScriptParser::AliasNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitAliasName(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::AliasNameContext* JavaScriptParser::aliasName() {
  AliasNameContext *_localctx = _tracker.createInstance<AliasNameContext>(_ctx, getState());
  enterRule(_localctx, 22, JavaScriptParser::RuleAliasName);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(245);
    identifierName();
    setState(248);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::As) {
      setState(246);
      match(JavaScriptParser::As);
      setState(247);
      identifierName();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExportStatementContext ------------------------------------------------------------------

JavaScriptParser::ExportStatementContext::ExportStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t JavaScriptParser::ExportStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleExportStatement;
}

void JavaScriptParser::ExportStatementContext::copyFrom(ExportStatementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ExportDefaultDeclarationContext ------------------------------------------------------------------

tree::TerminalNode* JavaScriptParser::ExportDefaultDeclarationContext::Export() {
  return getToken(JavaScriptParser::Export, 0);
}

tree::TerminalNode* JavaScriptParser::ExportDefaultDeclarationContext::Default() {
  return getToken(JavaScriptParser::Default, 0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::ExportDefaultDeclarationContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

JavaScriptParser::EosContext* JavaScriptParser::ExportDefaultDeclarationContext::eos() {
  return getRuleContext<JavaScriptParser::EosContext>(0);
}

JavaScriptParser::ExportDefaultDeclarationContext::ExportDefaultDeclarationContext(ExportStatementContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::ExportDefaultDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExportDefaultDeclaration(this);
}
void JavaScriptParser::ExportDefaultDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExportDefaultDeclaration(this);
}

antlrcpp::Any JavaScriptParser::ExportDefaultDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitExportDefaultDeclaration(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExportDeclarationContext ------------------------------------------------------------------

tree::TerminalNode* JavaScriptParser::ExportDeclarationContext::Export() {
  return getToken(JavaScriptParser::Export, 0);
}

JavaScriptParser::EosContext* JavaScriptParser::ExportDeclarationContext::eos() {
  return getRuleContext<JavaScriptParser::EosContext>(0);
}

JavaScriptParser::ExportFromBlockContext* JavaScriptParser::ExportDeclarationContext::exportFromBlock() {
  return getRuleContext<JavaScriptParser::ExportFromBlockContext>(0);
}

JavaScriptParser::DeclarationContext* JavaScriptParser::ExportDeclarationContext::declaration() {
  return getRuleContext<JavaScriptParser::DeclarationContext>(0);
}

JavaScriptParser::ExportDeclarationContext::ExportDeclarationContext(ExportStatementContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::ExportDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExportDeclaration(this);
}
void JavaScriptParser::ExportDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExportDeclaration(this);
}

antlrcpp::Any JavaScriptParser::ExportDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitExportDeclaration(this);
  else
    return visitor->visitChildren(this);
}
JavaScriptParser::ExportStatementContext* JavaScriptParser::exportStatement() {
  ExportStatementContext *_localctx = _tracker.createInstance<ExportStatementContext>(_ctx, getState());
  enterRule(_localctx, 24, JavaScriptParser::RuleExportStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(262);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<JavaScriptParser::ExportDeclarationContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(250);
      match(JavaScriptParser::Export);
      setState(253);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
      case 1: {
        setState(251);
        exportFromBlock();
        break;
      }

      case 2: {
        setState(252);
        declaration();
        break;
      }

      default:
        break;
      }
      setState(255);
      eos();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<JavaScriptParser::ExportDefaultDeclarationContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(257);
      match(JavaScriptParser::Export);
      setState(258);
      match(JavaScriptParser::Default);
      setState(259);
      singleExpression(0);
      setState(260);
      eos();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExportFromBlockContext ------------------------------------------------------------------

JavaScriptParser::ExportFromBlockContext::ExportFromBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::ImportNamespaceContext* JavaScriptParser::ExportFromBlockContext::importNamespace() {
  return getRuleContext<JavaScriptParser::ImportNamespaceContext>(0);
}

JavaScriptParser::ImportFromContext* JavaScriptParser::ExportFromBlockContext::importFrom() {
  return getRuleContext<JavaScriptParser::ImportFromContext>(0);
}

JavaScriptParser::EosContext* JavaScriptParser::ExportFromBlockContext::eos() {
  return getRuleContext<JavaScriptParser::EosContext>(0);
}

JavaScriptParser::ModuleItemsContext* JavaScriptParser::ExportFromBlockContext::moduleItems() {
  return getRuleContext<JavaScriptParser::ModuleItemsContext>(0);
}


size_t JavaScriptParser::ExportFromBlockContext::getRuleIndex() const {
  return JavaScriptParser::RuleExportFromBlock;
}

void JavaScriptParser::ExportFromBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExportFromBlock(this);
}

void JavaScriptParser::ExportFromBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExportFromBlock(this);
}


antlrcpp::Any JavaScriptParser::ExportFromBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitExportFromBlock(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ExportFromBlockContext* JavaScriptParser::exportFromBlock() {
  ExportFromBlockContext *_localctx = _tracker.createInstance<ExportFromBlockContext>(_ctx, getState());
  enterRule(_localctx, 26, JavaScriptParser::RuleExportFromBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(274);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::Multiply:
      case JavaScriptParser::NullLiteral:
      case JavaScriptParser::BooleanLiteral:
      case JavaScriptParser::Break:
      case JavaScriptParser::Do:
      case JavaScriptParser::Instanceof:
      case JavaScriptParser::Typeof:
      case JavaScriptParser::Case:
      case JavaScriptParser::Else:
      case JavaScriptParser::New:
      case JavaScriptParser::Var:
      case JavaScriptParser::Catch:
      case JavaScriptParser::Finally:
      case JavaScriptParser::Return:
      case JavaScriptParser::Void:
      case JavaScriptParser::Continue:
      case JavaScriptParser::For:
      case JavaScriptParser::Switch:
      case JavaScriptParser::While:
      case JavaScriptParser::Debugger:
      case JavaScriptParser::Function_:
      case JavaScriptParser::This:
      case JavaScriptParser::With:
      case JavaScriptParser::Default:
      case JavaScriptParser::If:
      case JavaScriptParser::Throw:
      case JavaScriptParser::Delete:
      case JavaScriptParser::In:
      case JavaScriptParser::Try:
      case JavaScriptParser::As:
      case JavaScriptParser::From:
      case JavaScriptParser::Class:
      case JavaScriptParser::Enum:
      case JavaScriptParser::Extends:
      case JavaScriptParser::Super:
      case JavaScriptParser::Const:
      case JavaScriptParser::Export:
      case JavaScriptParser::Import:
      case JavaScriptParser::Async:
      case JavaScriptParser::Await:
      case JavaScriptParser::Yield:
      case JavaScriptParser::Implements:
      case JavaScriptParser::StrictLet:
      case JavaScriptParser::NonStrictLet:
      case JavaScriptParser::Private:
      case JavaScriptParser::Public:
      case JavaScriptParser::Interface:
      case JavaScriptParser::Package:
      case JavaScriptParser::Protected:
      case JavaScriptParser::Static:
      case JavaScriptParser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(264);
        importNamespace();
        setState(265);
        importFrom();
        setState(266);
        eos();
        break;
      }

      case JavaScriptParser::OpenBrace: {
        enterOuterAlt(_localctx, 2);
        setState(268);
        moduleItems();
        setState(270);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
        case 1: {
          setState(269);
          importFrom();
          break;
        }

        default:
          break;
        }
        setState(272);
        eos();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationContext ------------------------------------------------------------------

JavaScriptParser::DeclarationContext::DeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::VariableStatementContext* JavaScriptParser::DeclarationContext::variableStatement() {
  return getRuleContext<JavaScriptParser::VariableStatementContext>(0);
}

JavaScriptParser::ClassDeclarationContext* JavaScriptParser::DeclarationContext::classDeclaration() {
  return getRuleContext<JavaScriptParser::ClassDeclarationContext>(0);
}

JavaScriptParser::FunctionDeclarationContext* JavaScriptParser::DeclarationContext::functionDeclaration() {
  return getRuleContext<JavaScriptParser::FunctionDeclarationContext>(0);
}


size_t JavaScriptParser::DeclarationContext::getRuleIndex() const {
  return JavaScriptParser::RuleDeclaration;
}

void JavaScriptParser::DeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeclaration(this);
}

void JavaScriptParser::DeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeclaration(this);
}


antlrcpp::Any JavaScriptParser::DeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitDeclaration(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::DeclarationContext* JavaScriptParser::declaration() {
  DeclarationContext *_localctx = _tracker.createInstance<DeclarationContext>(_ctx, getState());
  enterRule(_localctx, 28, JavaScriptParser::RuleDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(279);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::Var:
      case JavaScriptParser::Const:
      case JavaScriptParser::StrictLet:
      case JavaScriptParser::NonStrictLet: {
        enterOuterAlt(_localctx, 1);
        setState(276);
        variableStatement();
        break;
      }

      case JavaScriptParser::Class: {
        enterOuterAlt(_localctx, 2);
        setState(277);
        classDeclaration();
        break;
      }

      case JavaScriptParser::Function_:
      case JavaScriptParser::Async: {
        enterOuterAlt(_localctx, 3);
        setState(278);
        functionDeclaration();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableStatementContext ------------------------------------------------------------------

JavaScriptParser::VariableStatementContext::VariableStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::VariableDeclarationListContext* JavaScriptParser::VariableStatementContext::variableDeclarationList() {
  return getRuleContext<JavaScriptParser::VariableDeclarationListContext>(0);
}

JavaScriptParser::EosContext* JavaScriptParser::VariableStatementContext::eos() {
  return getRuleContext<JavaScriptParser::EosContext>(0);
}


size_t JavaScriptParser::VariableStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleVariableStatement;
}

void JavaScriptParser::VariableStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableStatement(this);
}

void JavaScriptParser::VariableStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableStatement(this);
}


antlrcpp::Any JavaScriptParser::VariableStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitVariableStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::VariableStatementContext* JavaScriptParser::variableStatement() {
  VariableStatementContext *_localctx = _tracker.createInstance<VariableStatementContext>(_ctx, getState());
  enterRule(_localctx, 30, JavaScriptParser::RuleVariableStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(281);
    variableDeclarationList();
    setState(282);
    eos();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDeclarationListContext ------------------------------------------------------------------

JavaScriptParser::VariableDeclarationListContext::VariableDeclarationListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::VarModifierContext* JavaScriptParser::VariableDeclarationListContext::varModifier() {
  return getRuleContext<JavaScriptParser::VarModifierContext>(0);
}

std::vector<JavaScriptParser::VariableDeclarationContext *> JavaScriptParser::VariableDeclarationListContext::variableDeclaration() {
  return getRuleContexts<JavaScriptParser::VariableDeclarationContext>();
}

JavaScriptParser::VariableDeclarationContext* JavaScriptParser::VariableDeclarationListContext::variableDeclaration(size_t i) {
  return getRuleContext<JavaScriptParser::VariableDeclarationContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::VariableDeclarationListContext::Comma() {
  return getTokens(JavaScriptParser::Comma);
}

tree::TerminalNode* JavaScriptParser::VariableDeclarationListContext::Comma(size_t i) {
  return getToken(JavaScriptParser::Comma, i);
}


size_t JavaScriptParser::VariableDeclarationListContext::getRuleIndex() const {
  return JavaScriptParser::RuleVariableDeclarationList;
}

void JavaScriptParser::VariableDeclarationListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableDeclarationList(this);
}

void JavaScriptParser::VariableDeclarationListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableDeclarationList(this);
}


antlrcpp::Any JavaScriptParser::VariableDeclarationListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitVariableDeclarationList(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::VariableDeclarationListContext* JavaScriptParser::variableDeclarationList() {
  VariableDeclarationListContext *_localctx = _tracker.createInstance<VariableDeclarationListContext>(_ctx, getState());
  enterRule(_localctx, 32, JavaScriptParser::RuleVariableDeclarationList);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(284);
    varModifier();
    setState(285);
    variableDeclaration();
    setState(290);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(286);
        match(JavaScriptParser::Comma);
        setState(287);
        variableDeclaration(); 
      }
      setState(292);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDeclarationContext ------------------------------------------------------------------

JavaScriptParser::VariableDeclarationContext::VariableDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::AssignableContext* JavaScriptParser::VariableDeclarationContext::assignable() {
  return getRuleContext<JavaScriptParser::AssignableContext>(0);
}

tree::TerminalNode* JavaScriptParser::VariableDeclarationContext::Assign() {
  return getToken(JavaScriptParser::Assign, 0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::VariableDeclarationContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}


size_t JavaScriptParser::VariableDeclarationContext::getRuleIndex() const {
  return JavaScriptParser::RuleVariableDeclaration;
}

void JavaScriptParser::VariableDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableDeclaration(this);
}

void JavaScriptParser::VariableDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableDeclaration(this);
}


antlrcpp::Any JavaScriptParser::VariableDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitVariableDeclaration(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::VariableDeclarationContext* JavaScriptParser::variableDeclaration() {
  VariableDeclarationContext *_localctx = _tracker.createInstance<VariableDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 34, JavaScriptParser::RuleVariableDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(293);
    assignable();
    setState(296);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      setState(294);
      match(JavaScriptParser::Assign);
      setState(295);
      singleExpression(0);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EmptyStatement_Context ------------------------------------------------------------------

JavaScriptParser::EmptyStatement_Context::EmptyStatement_Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::EmptyStatement_Context::SemiColon() {
  return getToken(JavaScriptParser::SemiColon, 0);
}


size_t JavaScriptParser::EmptyStatement_Context::getRuleIndex() const {
  return JavaScriptParser::RuleEmptyStatement_;
}

void JavaScriptParser::EmptyStatement_Context::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEmptyStatement_(this);
}

void JavaScriptParser::EmptyStatement_Context::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEmptyStatement_(this);
}


antlrcpp::Any JavaScriptParser::EmptyStatement_Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitEmptyStatement_(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::EmptyStatement_Context* JavaScriptParser::emptyStatement_() {
  EmptyStatement_Context *_localctx = _tracker.createInstance<EmptyStatement_Context>(_ctx, getState());
  enterRule(_localctx, 36, JavaScriptParser::RuleEmptyStatement_);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(298);
    match(JavaScriptParser::SemiColon);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionStatementContext ------------------------------------------------------------------

JavaScriptParser::ExpressionStatementContext::ExpressionStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::ExpressionSequenceContext* JavaScriptParser::ExpressionStatementContext::expressionSequence() {
  return getRuleContext<JavaScriptParser::ExpressionSequenceContext>(0);
}

JavaScriptParser::EosContext* JavaScriptParser::ExpressionStatementContext::eos() {
  return getRuleContext<JavaScriptParser::EosContext>(0);
}


size_t JavaScriptParser::ExpressionStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleExpressionStatement;
}

void JavaScriptParser::ExpressionStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpressionStatement(this);
}

void JavaScriptParser::ExpressionStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpressionStatement(this);
}


antlrcpp::Any JavaScriptParser::ExpressionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitExpressionStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ExpressionStatementContext* JavaScriptParser::expressionStatement() {
  ExpressionStatementContext *_localctx = _tracker.createInstance<ExpressionStatementContext>(_ctx, getState());
  enterRule(_localctx, 38, JavaScriptParser::RuleExpressionStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(300);

    if (!(this->notOpenBraceAndNotFunction())) throw FailedPredicateException(this, "this->notOpenBraceAndNotFunction()");
    setState(301);
    expressionSequence();
    setState(302);
    eos();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfStatementContext ------------------------------------------------------------------

JavaScriptParser::IfStatementContext::IfStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::IfStatementContext::If() {
  return getToken(JavaScriptParser::If, 0);
}

tree::TerminalNode* JavaScriptParser::IfStatementContext::OpenParen() {
  return getToken(JavaScriptParser::OpenParen, 0);
}

JavaScriptParser::ExpressionSequenceContext* JavaScriptParser::IfStatementContext::expressionSequence() {
  return getRuleContext<JavaScriptParser::ExpressionSequenceContext>(0);
}

tree::TerminalNode* JavaScriptParser::IfStatementContext::CloseParen() {
  return getToken(JavaScriptParser::CloseParen, 0);
}

std::vector<JavaScriptParser::StatementContext *> JavaScriptParser::IfStatementContext::statement() {
  return getRuleContexts<JavaScriptParser::StatementContext>();
}

JavaScriptParser::StatementContext* JavaScriptParser::IfStatementContext::statement(size_t i) {
  return getRuleContext<JavaScriptParser::StatementContext>(i);
}

tree::TerminalNode* JavaScriptParser::IfStatementContext::Else() {
  return getToken(JavaScriptParser::Else, 0);
}


size_t JavaScriptParser::IfStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleIfStatement;
}

void JavaScriptParser::IfStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfStatement(this);
}

void JavaScriptParser::IfStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfStatement(this);
}


antlrcpp::Any JavaScriptParser::IfStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitIfStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::IfStatementContext* JavaScriptParser::ifStatement() {
  IfStatementContext *_localctx = _tracker.createInstance<IfStatementContext>(_ctx, getState());
  enterRule(_localctx, 40, JavaScriptParser::RuleIfStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(304);
    match(JavaScriptParser::If);
    setState(305);
    match(JavaScriptParser::OpenParen);
    setState(306);
    expressionSequence();
    setState(307);
    match(JavaScriptParser::CloseParen);
    setState(308);
    statement();
    setState(311);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      setState(309);
      match(JavaScriptParser::Else);
      setState(310);
      statement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IterationStatementContext ------------------------------------------------------------------

JavaScriptParser::IterationStatementContext::IterationStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t JavaScriptParser::IterationStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleIterationStatement;
}

void JavaScriptParser::IterationStatementContext::copyFrom(IterationStatementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- DoStatementContext ------------------------------------------------------------------

tree::TerminalNode* JavaScriptParser::DoStatementContext::Do() {
  return getToken(JavaScriptParser::Do, 0);
}

JavaScriptParser::StatementContext* JavaScriptParser::DoStatementContext::statement() {
  return getRuleContext<JavaScriptParser::StatementContext>(0);
}

tree::TerminalNode* JavaScriptParser::DoStatementContext::While() {
  return getToken(JavaScriptParser::While, 0);
}

tree::TerminalNode* JavaScriptParser::DoStatementContext::OpenParen() {
  return getToken(JavaScriptParser::OpenParen, 0);
}

JavaScriptParser::ExpressionSequenceContext* JavaScriptParser::DoStatementContext::expressionSequence() {
  return getRuleContext<JavaScriptParser::ExpressionSequenceContext>(0);
}

tree::TerminalNode* JavaScriptParser::DoStatementContext::CloseParen() {
  return getToken(JavaScriptParser::CloseParen, 0);
}

JavaScriptParser::EosContext* JavaScriptParser::DoStatementContext::eos() {
  return getRuleContext<JavaScriptParser::EosContext>(0);
}

JavaScriptParser::DoStatementContext::DoStatementContext(IterationStatementContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::DoStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDoStatement(this);
}
void JavaScriptParser::DoStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDoStatement(this);
}

antlrcpp::Any JavaScriptParser::DoStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitDoStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- WhileStatementContext ------------------------------------------------------------------

tree::TerminalNode* JavaScriptParser::WhileStatementContext::While() {
  return getToken(JavaScriptParser::While, 0);
}

tree::TerminalNode* JavaScriptParser::WhileStatementContext::OpenParen() {
  return getToken(JavaScriptParser::OpenParen, 0);
}

JavaScriptParser::ExpressionSequenceContext* JavaScriptParser::WhileStatementContext::expressionSequence() {
  return getRuleContext<JavaScriptParser::ExpressionSequenceContext>(0);
}

tree::TerminalNode* JavaScriptParser::WhileStatementContext::CloseParen() {
  return getToken(JavaScriptParser::CloseParen, 0);
}

JavaScriptParser::StatementContext* JavaScriptParser::WhileStatementContext::statement() {
  return getRuleContext<JavaScriptParser::StatementContext>(0);
}

JavaScriptParser::WhileStatementContext::WhileStatementContext(IterationStatementContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::WhileStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhileStatement(this);
}
void JavaScriptParser::WhileStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhileStatement(this);
}

antlrcpp::Any JavaScriptParser::WhileStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitWhileStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ForStatementContext ------------------------------------------------------------------

tree::TerminalNode* JavaScriptParser::ForStatementContext::For() {
  return getToken(JavaScriptParser::For, 0);
}

tree::TerminalNode* JavaScriptParser::ForStatementContext::OpenParen() {
  return getToken(JavaScriptParser::OpenParen, 0);
}

std::vector<tree::TerminalNode *> JavaScriptParser::ForStatementContext::SemiColon() {
  return getTokens(JavaScriptParser::SemiColon);
}

tree::TerminalNode* JavaScriptParser::ForStatementContext::SemiColon(size_t i) {
  return getToken(JavaScriptParser::SemiColon, i);
}

tree::TerminalNode* JavaScriptParser::ForStatementContext::CloseParen() {
  return getToken(JavaScriptParser::CloseParen, 0);
}

JavaScriptParser::StatementContext* JavaScriptParser::ForStatementContext::statement() {
  return getRuleContext<JavaScriptParser::StatementContext>(0);
}

std::vector<JavaScriptParser::ExpressionSequenceContext *> JavaScriptParser::ForStatementContext::expressionSequence() {
  return getRuleContexts<JavaScriptParser::ExpressionSequenceContext>();
}

JavaScriptParser::ExpressionSequenceContext* JavaScriptParser::ForStatementContext::expressionSequence(size_t i) {
  return getRuleContext<JavaScriptParser::ExpressionSequenceContext>(i);
}

JavaScriptParser::VariableDeclarationListContext* JavaScriptParser::ForStatementContext::variableDeclarationList() {
  return getRuleContext<JavaScriptParser::VariableDeclarationListContext>(0);
}

JavaScriptParser::ForStatementContext::ForStatementContext(IterationStatementContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::ForStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForStatement(this);
}
void JavaScriptParser::ForStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForStatement(this);
}

antlrcpp::Any JavaScriptParser::ForStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitForStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ForInStatementContext ------------------------------------------------------------------

tree::TerminalNode* JavaScriptParser::ForInStatementContext::For() {
  return getToken(JavaScriptParser::For, 0);
}

tree::TerminalNode* JavaScriptParser::ForInStatementContext::OpenParen() {
  return getToken(JavaScriptParser::OpenParen, 0);
}

tree::TerminalNode* JavaScriptParser::ForInStatementContext::In() {
  return getToken(JavaScriptParser::In, 0);
}

JavaScriptParser::ExpressionSequenceContext* JavaScriptParser::ForInStatementContext::expressionSequence() {
  return getRuleContext<JavaScriptParser::ExpressionSequenceContext>(0);
}

tree::TerminalNode* JavaScriptParser::ForInStatementContext::CloseParen() {
  return getToken(JavaScriptParser::CloseParen, 0);
}

JavaScriptParser::StatementContext* JavaScriptParser::ForInStatementContext::statement() {
  return getRuleContext<JavaScriptParser::StatementContext>(0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::ForInStatementContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

JavaScriptParser::VariableDeclarationListContext* JavaScriptParser::ForInStatementContext::variableDeclarationList() {
  return getRuleContext<JavaScriptParser::VariableDeclarationListContext>(0);
}

JavaScriptParser::ForInStatementContext::ForInStatementContext(IterationStatementContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::ForInStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForInStatement(this);
}
void JavaScriptParser::ForInStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForInStatement(this);
}

antlrcpp::Any JavaScriptParser::ForInStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitForInStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ForOfStatementContext ------------------------------------------------------------------

tree::TerminalNode* JavaScriptParser::ForOfStatementContext::For() {
  return getToken(JavaScriptParser::For, 0);
}

tree::TerminalNode* JavaScriptParser::ForOfStatementContext::OpenParen() {
  return getToken(JavaScriptParser::OpenParen, 0);
}

JavaScriptParser::IdentifierContext* JavaScriptParser::ForOfStatementContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}

JavaScriptParser::ExpressionSequenceContext* JavaScriptParser::ForOfStatementContext::expressionSequence() {
  return getRuleContext<JavaScriptParser::ExpressionSequenceContext>(0);
}

tree::TerminalNode* JavaScriptParser::ForOfStatementContext::CloseParen() {
  return getToken(JavaScriptParser::CloseParen, 0);
}

JavaScriptParser::StatementContext* JavaScriptParser::ForOfStatementContext::statement() {
  return getRuleContext<JavaScriptParser::StatementContext>(0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::ForOfStatementContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

JavaScriptParser::VariableDeclarationListContext* JavaScriptParser::ForOfStatementContext::variableDeclarationList() {
  return getRuleContext<JavaScriptParser::VariableDeclarationListContext>(0);
}

tree::TerminalNode* JavaScriptParser::ForOfStatementContext::Await() {
  return getToken(JavaScriptParser::Await, 0);
}

JavaScriptParser::ForOfStatementContext::ForOfStatementContext(IterationStatementContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::ForOfStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForOfStatement(this);
}
void JavaScriptParser::ForOfStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForOfStatement(this);
}

antlrcpp::Any JavaScriptParser::ForOfStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitForOfStatement(this);
  else
    return visitor->visitChildren(this);
}
JavaScriptParser::IterationStatementContext* JavaScriptParser::iterationStatement() {
  IterationStatementContext *_localctx = _tracker.createInstance<IterationStatementContext>(_ctx, getState());
  enterRule(_localctx, 42, JavaScriptParser::RuleIterationStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(369);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<JavaScriptParser::DoStatementContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(313);
      match(JavaScriptParser::Do);
      setState(314);
      statement();
      setState(315);
      match(JavaScriptParser::While);
      setState(316);
      match(JavaScriptParser::OpenParen);
      setState(317);
      expressionSequence();
      setState(318);
      match(JavaScriptParser::CloseParen);
      setState(319);
      eos();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<JavaScriptParser::WhileStatementContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(321);
      match(JavaScriptParser::While);
      setState(322);
      match(JavaScriptParser::OpenParen);
      setState(323);
      expressionSequence();
      setState(324);
      match(JavaScriptParser::CloseParen);
      setState(325);
      statement();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<JavaScriptParser::ForStatementContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(327);
      match(JavaScriptParser::For);
      setState(328);
      match(JavaScriptParser::OpenParen);
      setState(331);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
      case 1: {
        setState(329);
        expressionSequence();
        break;
      }

      case 2: {
        setState(330);
        variableDeclarationList();
        break;
      }

      default:
        break;
      }
      setState(333);
      match(JavaScriptParser::SemiColon);
      setState(335);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << JavaScriptParser::RegularExpressionLiteral)
        | (1ULL << JavaScriptParser::OpenBracket)
        | (1ULL << JavaScriptParser::OpenParen)
        | (1ULL << JavaScriptParser::OpenBrace)
        | (1ULL << JavaScriptParser::PlusPlus)
        | (1ULL << JavaScriptParser::MinusMinus)
        | (1ULL << JavaScriptParser::Plus)
        | (1ULL << JavaScriptParser::Minus)
        | (1ULL << JavaScriptParser::BitNot)
        | (1ULL << JavaScriptParser::Not)
        | (1ULL << JavaScriptParser::NullLiteral)
        | (1ULL << JavaScriptParser::BooleanLiteral)
        | (1ULL << JavaScriptParser::DecimalLiteral)
        | (1ULL << JavaScriptParser::HexIntegerLiteral))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 64)) & ((1ULL << (JavaScriptParser::OctalIntegerLiteral - 64))
        | (1ULL << (JavaScriptParser::OctalIntegerLiteral2 - 64))
        | (1ULL << (JavaScriptParser::BinaryIntegerLiteral - 64))
        | (1ULL << (JavaScriptParser::BigHexIntegerLiteral - 64))
        | (1ULL << (JavaScriptParser::BigOctalIntegerLiteral - 64))
        | (1ULL << (JavaScriptParser::BigBinaryIntegerLiteral - 64))
        | (1ULL << (JavaScriptParser::BigDecimalIntegerLiteral - 64))
        | (1ULL << (JavaScriptParser::Typeof - 64))
        | (1ULL << (JavaScriptParser::New - 64))
        | (1ULL << (JavaScriptParser::Void - 64))
        | (1ULL << (JavaScriptParser::Function_ - 64))
        | (1ULL << (JavaScriptParser::This - 64))
        | (1ULL << (JavaScriptParser::Delete - 64))
        | (1ULL << (JavaScriptParser::Class - 64))
        | (1ULL << (JavaScriptParser::Super - 64))
        | (1ULL << (JavaScriptParser::Import - 64))
        | (1ULL << (JavaScriptParser::Async - 64))
        | (1ULL << (JavaScriptParser::Await - 64))
        | (1ULL << (JavaScriptParser::Yield - 64))
        | (1ULL << (JavaScriptParser::NonStrictLet - 64))
        | (1ULL << (JavaScriptParser::Identifier - 64))
        | (1ULL << (JavaScriptParser::StringLiteral - 64))
        | (1ULL << (JavaScriptParser::BackTick - 64)))) != 0)) {
        setState(334);
        expressionSequence();
      }
      setState(337);
      match(JavaScriptParser::SemiColon);
      setState(339);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << JavaScriptParser::RegularExpressionLiteral)
        | (1ULL << JavaScriptParser::OpenBracket)
        | (1ULL << JavaScriptParser::OpenParen)
        | (1ULL << JavaScriptParser::OpenBrace)
        | (1ULL << JavaScriptParser::PlusPlus)
        | (1ULL << JavaScriptParser::MinusMinus)
        | (1ULL << JavaScriptParser::Plus)
        | (1ULL << JavaScriptParser::Minus)
        | (1ULL << JavaScriptParser::BitNot)
        | (1ULL << JavaScriptParser::Not)
        | (1ULL << JavaScriptParser::NullLiteral)
        | (1ULL << JavaScriptParser::BooleanLiteral)
        | (1ULL << JavaScriptParser::DecimalLiteral)
        | (1ULL << JavaScriptParser::HexIntegerLiteral))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 64)) & ((1ULL << (JavaScriptParser::OctalIntegerLiteral - 64))
        | (1ULL << (JavaScriptParser::OctalIntegerLiteral2 - 64))
        | (1ULL << (JavaScriptParser::BinaryIntegerLiteral - 64))
        | (1ULL << (JavaScriptParser::BigHexIntegerLiteral - 64))
        | (1ULL << (JavaScriptParser::BigOctalIntegerLiteral - 64))
        | (1ULL << (JavaScriptParser::BigBinaryIntegerLiteral - 64))
        | (1ULL << (JavaScriptParser::BigDecimalIntegerLiteral - 64))
        | (1ULL << (JavaScriptParser::Typeof - 64))
        | (1ULL << (JavaScriptParser::New - 64))
        | (1ULL << (JavaScriptParser::Void - 64))
        | (1ULL << (JavaScriptParser::Function_ - 64))
        | (1ULL << (JavaScriptParser::This - 64))
        | (1ULL << (JavaScriptParser::Delete - 64))
        | (1ULL << (JavaScriptParser::Class - 64))
        | (1ULL << (JavaScriptParser::Super - 64))
        | (1ULL << (JavaScriptParser::Import - 64))
        | (1ULL << (JavaScriptParser::Async - 64))
        | (1ULL << (JavaScriptParser::Await - 64))
        | (1ULL << (JavaScriptParser::Yield - 64))
        | (1ULL << (JavaScriptParser::NonStrictLet - 64))
        | (1ULL << (JavaScriptParser::Identifier - 64))
        | (1ULL << (JavaScriptParser::StringLiteral - 64))
        | (1ULL << (JavaScriptParser::BackTick - 64)))) != 0)) {
        setState(338);
        expressionSequence();
      }
      setState(341);
      match(JavaScriptParser::CloseParen);
      setState(342);
      statement();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<JavaScriptParser::ForInStatementContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(343);
      match(JavaScriptParser::For);
      setState(344);
      match(JavaScriptParser::OpenParen);
      setState(347);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
      case 1: {
        setState(345);
        singleExpression(0);
        break;
      }

      case 2: {
        setState(346);
        variableDeclarationList();
        break;
      }

      default:
        break;
      }
      setState(349);
      match(JavaScriptParser::In);
      setState(350);
      expressionSequence();
      setState(351);
      match(JavaScriptParser::CloseParen);
      setState(352);
      statement();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<JavaScriptParser::ForOfStatementContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(354);
      match(JavaScriptParser::For);
      setState(356);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == JavaScriptParser::Await) {
        setState(355);
        match(JavaScriptParser::Await);
      }
      setState(358);
      match(JavaScriptParser::OpenParen);
      setState(361);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
      case 1: {
        setState(359);
        singleExpression(0);
        break;
      }

      case 2: {
        setState(360);
        variableDeclarationList();
        break;
      }

      default:
        break;
      }
      setState(363);
      identifier();
      setState(364);

      if (!(this->p("of"))) throw FailedPredicateException(this, "this->p(\"of\")");
      setState(365);
      expressionSequence();
      setState(366);
      match(JavaScriptParser::CloseParen);
      setState(367);
      statement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarModifierContext ------------------------------------------------------------------

JavaScriptParser::VarModifierContext::VarModifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::VarModifierContext::Var() {
  return getToken(JavaScriptParser::Var, 0);
}

JavaScriptParser::Let_Context* JavaScriptParser::VarModifierContext::let_() {
  return getRuleContext<JavaScriptParser::Let_Context>(0);
}

tree::TerminalNode* JavaScriptParser::VarModifierContext::Const() {
  return getToken(JavaScriptParser::Const, 0);
}


size_t JavaScriptParser::VarModifierContext::getRuleIndex() const {
  return JavaScriptParser::RuleVarModifier;
}

void JavaScriptParser::VarModifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarModifier(this);
}

void JavaScriptParser::VarModifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarModifier(this);
}


antlrcpp::Any JavaScriptParser::VarModifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitVarModifier(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::VarModifierContext* JavaScriptParser::varModifier() {
  VarModifierContext *_localctx = _tracker.createInstance<VarModifierContext>(_ctx, getState());
  enterRule(_localctx, 44, JavaScriptParser::RuleVarModifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(374);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::Var: {
        enterOuterAlt(_localctx, 1);
        setState(371);
        match(JavaScriptParser::Var);
        break;
      }

      case JavaScriptParser::StrictLet:
      case JavaScriptParser::NonStrictLet: {
        enterOuterAlt(_localctx, 2);
        setState(372);
        let_();
        break;
      }

      case JavaScriptParser::Const: {
        enterOuterAlt(_localctx, 3);
        setState(373);
        match(JavaScriptParser::Const);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ContinueStatementContext ------------------------------------------------------------------

JavaScriptParser::ContinueStatementContext::ContinueStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ContinueStatementContext::Continue() {
  return getToken(JavaScriptParser::Continue, 0);
}

JavaScriptParser::EosContext* JavaScriptParser::ContinueStatementContext::eos() {
  return getRuleContext<JavaScriptParser::EosContext>(0);
}

JavaScriptParser::IdentifierContext* JavaScriptParser::ContinueStatementContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}


size_t JavaScriptParser::ContinueStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleContinueStatement;
}

void JavaScriptParser::ContinueStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterContinueStatement(this);
}

void JavaScriptParser::ContinueStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitContinueStatement(this);
}


antlrcpp::Any JavaScriptParser::ContinueStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitContinueStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ContinueStatementContext* JavaScriptParser::continueStatement() {
  ContinueStatementContext *_localctx = _tracker.createInstance<ContinueStatementContext>(_ctx, getState());
  enterRule(_localctx, 46, JavaScriptParser::RuleContinueStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(376);
    match(JavaScriptParser::Continue);
    setState(379);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
    case 1: {
      setState(377);

      if (!(this->notLineTerminator())) throw FailedPredicateException(this, "this->notLineTerminator()");
      setState(378);
      identifier();
      break;
    }

    default:
      break;
    }
    setState(381);
    eos();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BreakStatementContext ------------------------------------------------------------------

JavaScriptParser::BreakStatementContext::BreakStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::BreakStatementContext::Break() {
  return getToken(JavaScriptParser::Break, 0);
}

JavaScriptParser::EosContext* JavaScriptParser::BreakStatementContext::eos() {
  return getRuleContext<JavaScriptParser::EosContext>(0);
}

JavaScriptParser::IdentifierContext* JavaScriptParser::BreakStatementContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}


size_t JavaScriptParser::BreakStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleBreakStatement;
}

void JavaScriptParser::BreakStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBreakStatement(this);
}

void JavaScriptParser::BreakStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBreakStatement(this);
}


antlrcpp::Any JavaScriptParser::BreakStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitBreakStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::BreakStatementContext* JavaScriptParser::breakStatement() {
  BreakStatementContext *_localctx = _tracker.createInstance<BreakStatementContext>(_ctx, getState());
  enterRule(_localctx, 48, JavaScriptParser::RuleBreakStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(383);
    match(JavaScriptParser::Break);
    setState(386);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
    case 1: {
      setState(384);

      if (!(this->notLineTerminator())) throw FailedPredicateException(this, "this->notLineTerminator()");
      setState(385);
      identifier();
      break;
    }

    default:
      break;
    }
    setState(388);
    eos();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturnStatementContext ------------------------------------------------------------------

JavaScriptParser::ReturnStatementContext::ReturnStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ReturnStatementContext::Return() {
  return getToken(JavaScriptParser::Return, 0);
}

JavaScriptParser::EosContext* JavaScriptParser::ReturnStatementContext::eos() {
  return getRuleContext<JavaScriptParser::EosContext>(0);
}

JavaScriptParser::ExpressionSequenceContext* JavaScriptParser::ReturnStatementContext::expressionSequence() {
  return getRuleContext<JavaScriptParser::ExpressionSequenceContext>(0);
}


size_t JavaScriptParser::ReturnStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleReturnStatement;
}

void JavaScriptParser::ReturnStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturnStatement(this);
}

void JavaScriptParser::ReturnStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturnStatement(this);
}


antlrcpp::Any JavaScriptParser::ReturnStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitReturnStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ReturnStatementContext* JavaScriptParser::returnStatement() {
  ReturnStatementContext *_localctx = _tracker.createInstance<ReturnStatementContext>(_ctx, getState());
  enterRule(_localctx, 50, JavaScriptParser::RuleReturnStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(390);
    match(JavaScriptParser::Return);
    setState(393);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
    case 1: {
      setState(391);

      if (!(this->notLineTerminator())) throw FailedPredicateException(this, "this->notLineTerminator()");
      setState(392);
      expressionSequence();
      break;
    }

    default:
      break;
    }
    setState(395);
    eos();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- YieldStatementContext ------------------------------------------------------------------

JavaScriptParser::YieldStatementContext::YieldStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::YieldStatementContext::Yield() {
  return getToken(JavaScriptParser::Yield, 0);
}

JavaScriptParser::EosContext* JavaScriptParser::YieldStatementContext::eos() {
  return getRuleContext<JavaScriptParser::EosContext>(0);
}

JavaScriptParser::ExpressionSequenceContext* JavaScriptParser::YieldStatementContext::expressionSequence() {
  return getRuleContext<JavaScriptParser::ExpressionSequenceContext>(0);
}


size_t JavaScriptParser::YieldStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleYieldStatement;
}

void JavaScriptParser::YieldStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterYieldStatement(this);
}

void JavaScriptParser::YieldStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitYieldStatement(this);
}


antlrcpp::Any JavaScriptParser::YieldStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitYieldStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::YieldStatementContext* JavaScriptParser::yieldStatement() {
  YieldStatementContext *_localctx = _tracker.createInstance<YieldStatementContext>(_ctx, getState());
  enterRule(_localctx, 52, JavaScriptParser::RuleYieldStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(397);
    match(JavaScriptParser::Yield);
    setState(400);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
    case 1: {
      setState(398);

      if (!(this->notLineTerminator())) throw FailedPredicateException(this, "this->notLineTerminator()");
      setState(399);
      expressionSequence();
      break;
    }

    default:
      break;
    }
    setState(402);
    eos();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WithStatementContext ------------------------------------------------------------------

JavaScriptParser::WithStatementContext::WithStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::WithStatementContext::With() {
  return getToken(JavaScriptParser::With, 0);
}

tree::TerminalNode* JavaScriptParser::WithStatementContext::OpenParen() {
  return getToken(JavaScriptParser::OpenParen, 0);
}

JavaScriptParser::ExpressionSequenceContext* JavaScriptParser::WithStatementContext::expressionSequence() {
  return getRuleContext<JavaScriptParser::ExpressionSequenceContext>(0);
}

tree::TerminalNode* JavaScriptParser::WithStatementContext::CloseParen() {
  return getToken(JavaScriptParser::CloseParen, 0);
}

JavaScriptParser::StatementContext* JavaScriptParser::WithStatementContext::statement() {
  return getRuleContext<JavaScriptParser::StatementContext>(0);
}


size_t JavaScriptParser::WithStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleWithStatement;
}

void JavaScriptParser::WithStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWithStatement(this);
}

void JavaScriptParser::WithStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWithStatement(this);
}


antlrcpp::Any JavaScriptParser::WithStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitWithStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::WithStatementContext* JavaScriptParser::withStatement() {
  WithStatementContext *_localctx = _tracker.createInstance<WithStatementContext>(_ctx, getState());
  enterRule(_localctx, 54, JavaScriptParser::RuleWithStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(404);
    match(JavaScriptParser::With);
    setState(405);
    match(JavaScriptParser::OpenParen);
    setState(406);
    expressionSequence();
    setState(407);
    match(JavaScriptParser::CloseParen);
    setState(408);
    statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SwitchStatementContext ------------------------------------------------------------------

JavaScriptParser::SwitchStatementContext::SwitchStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::SwitchStatementContext::Switch() {
  return getToken(JavaScriptParser::Switch, 0);
}

tree::TerminalNode* JavaScriptParser::SwitchStatementContext::OpenParen() {
  return getToken(JavaScriptParser::OpenParen, 0);
}

JavaScriptParser::ExpressionSequenceContext* JavaScriptParser::SwitchStatementContext::expressionSequence() {
  return getRuleContext<JavaScriptParser::ExpressionSequenceContext>(0);
}

tree::TerminalNode* JavaScriptParser::SwitchStatementContext::CloseParen() {
  return getToken(JavaScriptParser::CloseParen, 0);
}

JavaScriptParser::CaseBlockContext* JavaScriptParser::SwitchStatementContext::caseBlock() {
  return getRuleContext<JavaScriptParser::CaseBlockContext>(0);
}


size_t JavaScriptParser::SwitchStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleSwitchStatement;
}

void JavaScriptParser::SwitchStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSwitchStatement(this);
}

void JavaScriptParser::SwitchStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSwitchStatement(this);
}


antlrcpp::Any JavaScriptParser::SwitchStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitSwitchStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::SwitchStatementContext* JavaScriptParser::switchStatement() {
  SwitchStatementContext *_localctx = _tracker.createInstance<SwitchStatementContext>(_ctx, getState());
  enterRule(_localctx, 56, JavaScriptParser::RuleSwitchStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(410);
    match(JavaScriptParser::Switch);
    setState(411);
    match(JavaScriptParser::OpenParen);
    setState(412);
    expressionSequence();
    setState(413);
    match(JavaScriptParser::CloseParen);
    setState(414);
    caseBlock();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CaseBlockContext ------------------------------------------------------------------

JavaScriptParser::CaseBlockContext::CaseBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::CaseBlockContext::OpenBrace() {
  return getToken(JavaScriptParser::OpenBrace, 0);
}

tree::TerminalNode* JavaScriptParser::CaseBlockContext::CloseBrace() {
  return getToken(JavaScriptParser::CloseBrace, 0);
}

std::vector<JavaScriptParser::CaseClausesContext *> JavaScriptParser::CaseBlockContext::caseClauses() {
  return getRuleContexts<JavaScriptParser::CaseClausesContext>();
}

JavaScriptParser::CaseClausesContext* JavaScriptParser::CaseBlockContext::caseClauses(size_t i) {
  return getRuleContext<JavaScriptParser::CaseClausesContext>(i);
}

JavaScriptParser::DefaultClauseContext* JavaScriptParser::CaseBlockContext::defaultClause() {
  return getRuleContext<JavaScriptParser::DefaultClauseContext>(0);
}


size_t JavaScriptParser::CaseBlockContext::getRuleIndex() const {
  return JavaScriptParser::RuleCaseBlock;
}

void JavaScriptParser::CaseBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCaseBlock(this);
}

void JavaScriptParser::CaseBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCaseBlock(this);
}


antlrcpp::Any JavaScriptParser::CaseBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitCaseBlock(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::CaseBlockContext* JavaScriptParser::caseBlock() {
  CaseBlockContext *_localctx = _tracker.createInstance<CaseBlockContext>(_ctx, getState());
  enterRule(_localctx, 58, JavaScriptParser::RuleCaseBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(416);
    match(JavaScriptParser::OpenBrace);
    setState(418);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::Case) {
      setState(417);
      caseClauses();
    }
    setState(424);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::Default) {
      setState(420);
      defaultClause();
      setState(422);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == JavaScriptParser::Case) {
        setState(421);
        caseClauses();
      }
    }
    setState(426);
    match(JavaScriptParser::CloseBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CaseClausesContext ------------------------------------------------------------------

JavaScriptParser::CaseClausesContext::CaseClausesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::CaseClauseContext *> JavaScriptParser::CaseClausesContext::caseClause() {
  return getRuleContexts<JavaScriptParser::CaseClauseContext>();
}

JavaScriptParser::CaseClauseContext* JavaScriptParser::CaseClausesContext::caseClause(size_t i) {
  return getRuleContext<JavaScriptParser::CaseClauseContext>(i);
}


size_t JavaScriptParser::CaseClausesContext::getRuleIndex() const {
  return JavaScriptParser::RuleCaseClauses;
}

void JavaScriptParser::CaseClausesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCaseClauses(this);
}

void JavaScriptParser::CaseClausesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCaseClauses(this);
}


antlrcpp::Any JavaScriptParser::CaseClausesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitCaseClauses(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::CaseClausesContext* JavaScriptParser::caseClauses() {
  CaseClausesContext *_localctx = _tracker.createInstance<CaseClausesContext>(_ctx, getState());
  enterRule(_localctx, 60, JavaScriptParser::RuleCaseClauses);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(429); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(428);
      caseClause();
      setState(431); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == JavaScriptParser::Case);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CaseClauseContext ------------------------------------------------------------------

JavaScriptParser::CaseClauseContext::CaseClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::CaseClauseContext::Case() {
  return getToken(JavaScriptParser::Case, 0);
}

JavaScriptParser::ExpressionSequenceContext* JavaScriptParser::CaseClauseContext::expressionSequence() {
  return getRuleContext<JavaScriptParser::ExpressionSequenceContext>(0);
}

tree::TerminalNode* JavaScriptParser::CaseClauseContext::Colon() {
  return getToken(JavaScriptParser::Colon, 0);
}

JavaScriptParser::StatementListContext* JavaScriptParser::CaseClauseContext::statementList() {
  return getRuleContext<JavaScriptParser::StatementListContext>(0);
}


size_t JavaScriptParser::CaseClauseContext::getRuleIndex() const {
  return JavaScriptParser::RuleCaseClause;
}

void JavaScriptParser::CaseClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCaseClause(this);
}

void JavaScriptParser::CaseClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCaseClause(this);
}


antlrcpp::Any JavaScriptParser::CaseClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitCaseClause(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::CaseClauseContext* JavaScriptParser::caseClause() {
  CaseClauseContext *_localctx = _tracker.createInstance<CaseClauseContext>(_ctx, getState());
  enterRule(_localctx, 62, JavaScriptParser::RuleCaseClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(433);
    match(JavaScriptParser::Case);
    setState(434);
    expressionSequence();
    setState(435);
    match(JavaScriptParser::Colon);
    setState(437);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx)) {
    case 1: {
      setState(436);
      statementList();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DefaultClauseContext ------------------------------------------------------------------

JavaScriptParser::DefaultClauseContext::DefaultClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::DefaultClauseContext::Default() {
  return getToken(JavaScriptParser::Default, 0);
}

tree::TerminalNode* JavaScriptParser::DefaultClauseContext::Colon() {
  return getToken(JavaScriptParser::Colon, 0);
}

JavaScriptParser::StatementListContext* JavaScriptParser::DefaultClauseContext::statementList() {
  return getRuleContext<JavaScriptParser::StatementListContext>(0);
}


size_t JavaScriptParser::DefaultClauseContext::getRuleIndex() const {
  return JavaScriptParser::RuleDefaultClause;
}

void JavaScriptParser::DefaultClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDefaultClause(this);
}

void JavaScriptParser::DefaultClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDefaultClause(this);
}


antlrcpp::Any JavaScriptParser::DefaultClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitDefaultClause(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::DefaultClauseContext* JavaScriptParser::defaultClause() {
  DefaultClauseContext *_localctx = _tracker.createInstance<DefaultClauseContext>(_ctx, getState());
  enterRule(_localctx, 64, JavaScriptParser::RuleDefaultClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(439);
    match(JavaScriptParser::Default);
    setState(440);
    match(JavaScriptParser::Colon);
    setState(442);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx)) {
    case 1: {
      setState(441);
      statementList();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LabelledStatementContext ------------------------------------------------------------------

JavaScriptParser::LabelledStatementContext::LabelledStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::IdentifierContext* JavaScriptParser::LabelledStatementContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}

tree::TerminalNode* JavaScriptParser::LabelledStatementContext::Colon() {
  return getToken(JavaScriptParser::Colon, 0);
}

JavaScriptParser::StatementContext* JavaScriptParser::LabelledStatementContext::statement() {
  return getRuleContext<JavaScriptParser::StatementContext>(0);
}


size_t JavaScriptParser::LabelledStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleLabelledStatement;
}

void JavaScriptParser::LabelledStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLabelledStatement(this);
}

void JavaScriptParser::LabelledStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLabelledStatement(this);
}


antlrcpp::Any JavaScriptParser::LabelledStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitLabelledStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::LabelledStatementContext* JavaScriptParser::labelledStatement() {
  LabelledStatementContext *_localctx = _tracker.createInstance<LabelledStatementContext>(_ctx, getState());
  enterRule(_localctx, 66, JavaScriptParser::RuleLabelledStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(444);
    identifier();
    setState(445);
    match(JavaScriptParser::Colon);
    setState(446);
    statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ThrowStatementContext ------------------------------------------------------------------

JavaScriptParser::ThrowStatementContext::ThrowStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ThrowStatementContext::Throw() {
  return getToken(JavaScriptParser::Throw, 0);
}

JavaScriptParser::ExpressionSequenceContext* JavaScriptParser::ThrowStatementContext::expressionSequence() {
  return getRuleContext<JavaScriptParser::ExpressionSequenceContext>(0);
}

JavaScriptParser::EosContext* JavaScriptParser::ThrowStatementContext::eos() {
  return getRuleContext<JavaScriptParser::EosContext>(0);
}


size_t JavaScriptParser::ThrowStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleThrowStatement;
}

void JavaScriptParser::ThrowStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterThrowStatement(this);
}

void JavaScriptParser::ThrowStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitThrowStatement(this);
}


antlrcpp::Any JavaScriptParser::ThrowStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitThrowStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ThrowStatementContext* JavaScriptParser::throwStatement() {
  ThrowStatementContext *_localctx = _tracker.createInstance<ThrowStatementContext>(_ctx, getState());
  enterRule(_localctx, 68, JavaScriptParser::RuleThrowStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(448);
    match(JavaScriptParser::Throw);
    setState(449);

    if (!(this->notLineTerminator())) throw FailedPredicateException(this, "this->notLineTerminator()");
    setState(450);
    expressionSequence();
    setState(451);
    eos();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TryStatementContext ------------------------------------------------------------------

JavaScriptParser::TryStatementContext::TryStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::TryStatementContext::Try() {
  return getToken(JavaScriptParser::Try, 0);
}

JavaScriptParser::BlockContext* JavaScriptParser::TryStatementContext::block() {
  return getRuleContext<JavaScriptParser::BlockContext>(0);
}

JavaScriptParser::CatchProductionContext* JavaScriptParser::TryStatementContext::catchProduction() {
  return getRuleContext<JavaScriptParser::CatchProductionContext>(0);
}

JavaScriptParser::FinallyProductionContext* JavaScriptParser::TryStatementContext::finallyProduction() {
  return getRuleContext<JavaScriptParser::FinallyProductionContext>(0);
}


size_t JavaScriptParser::TryStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleTryStatement;
}

void JavaScriptParser::TryStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTryStatement(this);
}

void JavaScriptParser::TryStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTryStatement(this);
}


antlrcpp::Any JavaScriptParser::TryStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitTryStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::TryStatementContext* JavaScriptParser::tryStatement() {
  TryStatementContext *_localctx = _tracker.createInstance<TryStatementContext>(_ctx, getState());
  enterRule(_localctx, 70, JavaScriptParser::RuleTryStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(453);
    match(JavaScriptParser::Try);
    setState(454);
    block();
    setState(460);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::Catch: {
        setState(455);
        catchProduction();
        setState(457);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx)) {
        case 1: {
          setState(456);
          finallyProduction();
          break;
        }

        default:
          break;
        }
        break;
      }

      case JavaScriptParser::Finally: {
        setState(459);
        finallyProduction();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CatchProductionContext ------------------------------------------------------------------

JavaScriptParser::CatchProductionContext::CatchProductionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::CatchProductionContext::Catch() {
  return getToken(JavaScriptParser::Catch, 0);
}

JavaScriptParser::BlockContext* JavaScriptParser::CatchProductionContext::block() {
  return getRuleContext<JavaScriptParser::BlockContext>(0);
}

tree::TerminalNode* JavaScriptParser::CatchProductionContext::OpenParen() {
  return getToken(JavaScriptParser::OpenParen, 0);
}

tree::TerminalNode* JavaScriptParser::CatchProductionContext::CloseParen() {
  return getToken(JavaScriptParser::CloseParen, 0);
}

JavaScriptParser::AssignableContext* JavaScriptParser::CatchProductionContext::assignable() {
  return getRuleContext<JavaScriptParser::AssignableContext>(0);
}


size_t JavaScriptParser::CatchProductionContext::getRuleIndex() const {
  return JavaScriptParser::RuleCatchProduction;
}

void JavaScriptParser::CatchProductionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCatchProduction(this);
}

void JavaScriptParser::CatchProductionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCatchProduction(this);
}


antlrcpp::Any JavaScriptParser::CatchProductionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitCatchProduction(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::CatchProductionContext* JavaScriptParser::catchProduction() {
  CatchProductionContext *_localctx = _tracker.createInstance<CatchProductionContext>(_ctx, getState());
  enterRule(_localctx, 72, JavaScriptParser::RuleCatchProduction);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(462);
    match(JavaScriptParser::Catch);
    setState(468);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::OpenParen) {
      setState(463);
      match(JavaScriptParser::OpenParen);
      setState(465);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == JavaScriptParser::OpenBracket

      || _la == JavaScriptParser::OpenBrace || ((((_la - 106) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 106)) & ((1ULL << (JavaScriptParser::Async - 106))
        | (1ULL << (JavaScriptParser::NonStrictLet - 106))
        | (1ULL << (JavaScriptParser::Identifier - 106)))) != 0)) {
        setState(464);
        assignable();
      }
      setState(467);
      match(JavaScriptParser::CloseParen);
    }
    setState(470);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FinallyProductionContext ------------------------------------------------------------------

JavaScriptParser::FinallyProductionContext::FinallyProductionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::FinallyProductionContext::Finally() {
  return getToken(JavaScriptParser::Finally, 0);
}

JavaScriptParser::BlockContext* JavaScriptParser::FinallyProductionContext::block() {
  return getRuleContext<JavaScriptParser::BlockContext>(0);
}


size_t JavaScriptParser::FinallyProductionContext::getRuleIndex() const {
  return JavaScriptParser::RuleFinallyProduction;
}

void JavaScriptParser::FinallyProductionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFinallyProduction(this);
}

void JavaScriptParser::FinallyProductionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFinallyProduction(this);
}


antlrcpp::Any JavaScriptParser::FinallyProductionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitFinallyProduction(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::FinallyProductionContext* JavaScriptParser::finallyProduction() {
  FinallyProductionContext *_localctx = _tracker.createInstance<FinallyProductionContext>(_ctx, getState());
  enterRule(_localctx, 74, JavaScriptParser::RuleFinallyProduction);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(472);
    match(JavaScriptParser::Finally);
    setState(473);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DebuggerStatementContext ------------------------------------------------------------------

JavaScriptParser::DebuggerStatementContext::DebuggerStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::DebuggerStatementContext::Debugger() {
  return getToken(JavaScriptParser::Debugger, 0);
}

JavaScriptParser::EosContext* JavaScriptParser::DebuggerStatementContext::eos() {
  return getRuleContext<JavaScriptParser::EosContext>(0);
}


size_t JavaScriptParser::DebuggerStatementContext::getRuleIndex() const {
  return JavaScriptParser::RuleDebuggerStatement;
}

void JavaScriptParser::DebuggerStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDebuggerStatement(this);
}

void JavaScriptParser::DebuggerStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDebuggerStatement(this);
}


antlrcpp::Any JavaScriptParser::DebuggerStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitDebuggerStatement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::DebuggerStatementContext* JavaScriptParser::debuggerStatement() {
  DebuggerStatementContext *_localctx = _tracker.createInstance<DebuggerStatementContext>(_ctx, getState());
  enterRule(_localctx, 76, JavaScriptParser::RuleDebuggerStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(475);
    match(JavaScriptParser::Debugger);
    setState(476);
    eos();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDeclarationContext ------------------------------------------------------------------

JavaScriptParser::FunctionDeclarationContext::FunctionDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::FunctionDeclarationContext::Function_() {
  return getToken(JavaScriptParser::Function_, 0);
}

JavaScriptParser::IdentifierContext* JavaScriptParser::FunctionDeclarationContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}

tree::TerminalNode* JavaScriptParser::FunctionDeclarationContext::OpenParen() {
  return getToken(JavaScriptParser::OpenParen, 0);
}

tree::TerminalNode* JavaScriptParser::FunctionDeclarationContext::CloseParen() {
  return getToken(JavaScriptParser::CloseParen, 0);
}

JavaScriptParser::FunctionBodyContext* JavaScriptParser::FunctionDeclarationContext::functionBody() {
  return getRuleContext<JavaScriptParser::FunctionBodyContext>(0);
}

tree::TerminalNode* JavaScriptParser::FunctionDeclarationContext::Async() {
  return getToken(JavaScriptParser::Async, 0);
}

tree::TerminalNode* JavaScriptParser::FunctionDeclarationContext::Multiply() {
  return getToken(JavaScriptParser::Multiply, 0);
}

JavaScriptParser::FormalParameterListContext* JavaScriptParser::FunctionDeclarationContext::formalParameterList() {
  return getRuleContext<JavaScriptParser::FormalParameterListContext>(0);
}


size_t JavaScriptParser::FunctionDeclarationContext::getRuleIndex() const {
  return JavaScriptParser::RuleFunctionDeclaration;
}

void JavaScriptParser::FunctionDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionDeclaration(this);
}

void JavaScriptParser::FunctionDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionDeclaration(this);
}


antlrcpp::Any JavaScriptParser::FunctionDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitFunctionDeclaration(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::FunctionDeclarationContext* JavaScriptParser::functionDeclaration() {
  FunctionDeclarationContext *_localctx = _tracker.createInstance<FunctionDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 78, JavaScriptParser::RuleFunctionDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(479);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::Async) {
      setState(478);
      match(JavaScriptParser::Async);
    }
    setState(481);
    match(JavaScriptParser::Function_);
    setState(483);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::Multiply) {
      setState(482);
      match(JavaScriptParser::Multiply);
    }
    setState(485);
    identifier();
    setState(486);
    match(JavaScriptParser::OpenParen);
    setState(488);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::OpenBracket)
      | (1ULL << JavaScriptParser::OpenBrace)
      | (1ULL << JavaScriptParser::Ellipsis))) != 0) || ((((_la - 106) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 106)) & ((1ULL << (JavaScriptParser::Async - 106))
      | (1ULL << (JavaScriptParser::NonStrictLet - 106))
      | (1ULL << (JavaScriptParser::Identifier - 106)))) != 0)) {
      setState(487);
      formalParameterList();
    }
    setState(490);
    match(JavaScriptParser::CloseParen);
    setState(491);
    functionBody();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassDeclarationContext ------------------------------------------------------------------

JavaScriptParser::ClassDeclarationContext::ClassDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ClassDeclarationContext::Class() {
  return getToken(JavaScriptParser::Class, 0);
}

JavaScriptParser::IdentifierContext* JavaScriptParser::ClassDeclarationContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}

JavaScriptParser::ClassTailContext* JavaScriptParser::ClassDeclarationContext::classTail() {
  return getRuleContext<JavaScriptParser::ClassTailContext>(0);
}


size_t JavaScriptParser::ClassDeclarationContext::getRuleIndex() const {
  return JavaScriptParser::RuleClassDeclaration;
}

void JavaScriptParser::ClassDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassDeclaration(this);
}

void JavaScriptParser::ClassDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassDeclaration(this);
}


antlrcpp::Any JavaScriptParser::ClassDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitClassDeclaration(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ClassDeclarationContext* JavaScriptParser::classDeclaration() {
  ClassDeclarationContext *_localctx = _tracker.createInstance<ClassDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 80, JavaScriptParser::RuleClassDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(493);
    match(JavaScriptParser::Class);
    setState(494);
    identifier();
    setState(495);
    classTail();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassTailContext ------------------------------------------------------------------

JavaScriptParser::ClassTailContext::ClassTailContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ClassTailContext::OpenBrace() {
  return getToken(JavaScriptParser::OpenBrace, 0);
}

tree::TerminalNode* JavaScriptParser::ClassTailContext::CloseBrace() {
  return getToken(JavaScriptParser::CloseBrace, 0);
}

tree::TerminalNode* JavaScriptParser::ClassTailContext::Extends() {
  return getToken(JavaScriptParser::Extends, 0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::ClassTailContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

std::vector<JavaScriptParser::ClassElementContext *> JavaScriptParser::ClassTailContext::classElement() {
  return getRuleContexts<JavaScriptParser::ClassElementContext>();
}

JavaScriptParser::ClassElementContext* JavaScriptParser::ClassTailContext::classElement(size_t i) {
  return getRuleContext<JavaScriptParser::ClassElementContext>(i);
}


size_t JavaScriptParser::ClassTailContext::getRuleIndex() const {
  return JavaScriptParser::RuleClassTail;
}

void JavaScriptParser::ClassTailContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassTail(this);
}

void JavaScriptParser::ClassTailContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassTail(this);
}


antlrcpp::Any JavaScriptParser::ClassTailContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitClassTail(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ClassTailContext* JavaScriptParser::classTail() {
  ClassTailContext *_localctx = _tracker.createInstance<ClassTailContext>(_ctx, getState());
  enterRule(_localctx, 82, JavaScriptParser::RuleClassTail);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(499);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::Extends) {
      setState(497);
      match(JavaScriptParser::Extends);
      setState(498);
      singleExpression(0);
    }
    setState(501);
    match(JavaScriptParser::OpenBrace);
    setState(505);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(502);
        classElement(); 
      }
      setState(507);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx);
    }
    setState(508);
    match(JavaScriptParser::CloseBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassElementContext ------------------------------------------------------------------

JavaScriptParser::ClassElementContext::ClassElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::MethodDefinitionContext* JavaScriptParser::ClassElementContext::methodDefinition() {
  return getRuleContext<JavaScriptParser::MethodDefinitionContext>(0);
}

JavaScriptParser::AssignableContext* JavaScriptParser::ClassElementContext::assignable() {
  return getRuleContext<JavaScriptParser::AssignableContext>(0);
}

tree::TerminalNode* JavaScriptParser::ClassElementContext::Assign() {
  return getToken(JavaScriptParser::Assign, 0);
}

JavaScriptParser::ObjectLiteralContext* JavaScriptParser::ClassElementContext::objectLiteral() {
  return getRuleContext<JavaScriptParser::ObjectLiteralContext>(0);
}

tree::TerminalNode* JavaScriptParser::ClassElementContext::SemiColon() {
  return getToken(JavaScriptParser::SemiColon, 0);
}

std::vector<tree::TerminalNode *> JavaScriptParser::ClassElementContext::Static() {
  return getTokens(JavaScriptParser::Static);
}

tree::TerminalNode* JavaScriptParser::ClassElementContext::Static(size_t i) {
  return getToken(JavaScriptParser::Static, i);
}

std::vector<JavaScriptParser::IdentifierContext *> JavaScriptParser::ClassElementContext::identifier() {
  return getRuleContexts<JavaScriptParser::IdentifierContext>();
}

JavaScriptParser::IdentifierContext* JavaScriptParser::ClassElementContext::identifier(size_t i) {
  return getRuleContext<JavaScriptParser::IdentifierContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::ClassElementContext::Async() {
  return getTokens(JavaScriptParser::Async);
}

tree::TerminalNode* JavaScriptParser::ClassElementContext::Async(size_t i) {
  return getToken(JavaScriptParser::Async, i);
}

JavaScriptParser::EmptyStatement_Context* JavaScriptParser::ClassElementContext::emptyStatement_() {
  return getRuleContext<JavaScriptParser::EmptyStatement_Context>(0);
}

JavaScriptParser::PropertyNameContext* JavaScriptParser::ClassElementContext::propertyName() {
  return getRuleContext<JavaScriptParser::PropertyNameContext>(0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::ClassElementContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::ClassElementContext::Hashtag() {
  return getToken(JavaScriptParser::Hashtag, 0);
}


size_t JavaScriptParser::ClassElementContext::getRuleIndex() const {
  return JavaScriptParser::RuleClassElement;
}

void JavaScriptParser::ClassElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassElement(this);
}

void JavaScriptParser::ClassElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassElement(this);
}


antlrcpp::Any JavaScriptParser::ClassElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitClassElement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ClassElementContext* JavaScriptParser::classElement() {
  ClassElementContext *_localctx = _tracker.createInstance<ClassElementContext>(_ctx, getState());
  enterRule(_localctx, 84, JavaScriptParser::RuleClassElement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    setState(535);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(516);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(514);
          _errHandler->sync(this);
          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx)) {
          case 1: {
            setState(510);
            match(JavaScriptParser::Static);
            break;
          }

          case 2: {
            setState(511);

            if (!(this->n("static"))) throw FailedPredicateException(this, "this->n(\"static\")");
            setState(512);
            identifier();
            break;
          }

          case 3: {
            setState(513);
            match(JavaScriptParser::Async);
            break;
          }

          default:
            break;
          } 
        }
        setState(518);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx);
      }
      setState(525);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx)) {
      case 1: {
        setState(519);
        methodDefinition();
        break;
      }

      case 2: {
        setState(520);
        assignable();
        setState(521);
        match(JavaScriptParser::Assign);
        setState(522);
        objectLiteral();
        setState(523);
        match(JavaScriptParser::SemiColon);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(527);
      emptyStatement_();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(529);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == JavaScriptParser::Hashtag) {
        setState(528);
        match(JavaScriptParser::Hashtag);
      }
      setState(531);
      propertyName();
      setState(532);
      match(JavaScriptParser::Assign);
      setState(533);
      singleExpression(0);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MethodDefinitionContext ------------------------------------------------------------------

JavaScriptParser::MethodDefinitionContext::MethodDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::PropertyNameContext* JavaScriptParser::MethodDefinitionContext::propertyName() {
  return getRuleContext<JavaScriptParser::PropertyNameContext>(0);
}

tree::TerminalNode* JavaScriptParser::MethodDefinitionContext::OpenParen() {
  return getToken(JavaScriptParser::OpenParen, 0);
}

tree::TerminalNode* JavaScriptParser::MethodDefinitionContext::CloseParen() {
  return getToken(JavaScriptParser::CloseParen, 0);
}

JavaScriptParser::FunctionBodyContext* JavaScriptParser::MethodDefinitionContext::functionBody() {
  return getRuleContext<JavaScriptParser::FunctionBodyContext>(0);
}

tree::TerminalNode* JavaScriptParser::MethodDefinitionContext::Multiply() {
  return getToken(JavaScriptParser::Multiply, 0);
}

tree::TerminalNode* JavaScriptParser::MethodDefinitionContext::Hashtag() {
  return getToken(JavaScriptParser::Hashtag, 0);
}

JavaScriptParser::FormalParameterListContext* JavaScriptParser::MethodDefinitionContext::formalParameterList() {
  return getRuleContext<JavaScriptParser::FormalParameterListContext>(0);
}

JavaScriptParser::GetterContext* JavaScriptParser::MethodDefinitionContext::getter() {
  return getRuleContext<JavaScriptParser::GetterContext>(0);
}

JavaScriptParser::SetterContext* JavaScriptParser::MethodDefinitionContext::setter() {
  return getRuleContext<JavaScriptParser::SetterContext>(0);
}


size_t JavaScriptParser::MethodDefinitionContext::getRuleIndex() const {
  return JavaScriptParser::RuleMethodDefinition;
}

void JavaScriptParser::MethodDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMethodDefinition(this);
}

void JavaScriptParser::MethodDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMethodDefinition(this);
}


antlrcpp::Any JavaScriptParser::MethodDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitMethodDefinition(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::MethodDefinitionContext* JavaScriptParser::methodDefinition() {
  MethodDefinitionContext *_localctx = _tracker.createInstance<MethodDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 86, JavaScriptParser::RuleMethodDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(576);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 62, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(538);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == JavaScriptParser::Multiply) {
        setState(537);
        match(JavaScriptParser::Multiply);
      }
      setState(541);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == JavaScriptParser::Hashtag) {
        setState(540);
        match(JavaScriptParser::Hashtag);
      }
      setState(543);
      propertyName();
      setState(544);
      match(JavaScriptParser::OpenParen);
      setState(546);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << JavaScriptParser::OpenBracket)
        | (1ULL << JavaScriptParser::OpenBrace)
        | (1ULL << JavaScriptParser::Ellipsis))) != 0) || ((((_la - 106) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 106)) & ((1ULL << (JavaScriptParser::Async - 106))
        | (1ULL << (JavaScriptParser::NonStrictLet - 106))
        | (1ULL << (JavaScriptParser::Identifier - 106)))) != 0)) {
        setState(545);
        formalParameterList();
      }
      setState(548);
      match(JavaScriptParser::CloseParen);
      setState(549);
      functionBody();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(552);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx)) {
      case 1: {
        setState(551);
        match(JavaScriptParser::Multiply);
        break;
      }

      default:
        break;
      }
      setState(555);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx)) {
      case 1: {
        setState(554);
        match(JavaScriptParser::Hashtag);
        break;
      }

      default:
        break;
      }
      setState(557);
      getter();
      setState(558);
      match(JavaScriptParser::OpenParen);
      setState(559);
      match(JavaScriptParser::CloseParen);
      setState(560);
      functionBody();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(563);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx)) {
      case 1: {
        setState(562);
        match(JavaScriptParser::Multiply);
        break;
      }

      default:
        break;
      }
      setState(566);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 60, _ctx)) {
      case 1: {
        setState(565);
        match(JavaScriptParser::Hashtag);
        break;
      }

      default:
        break;
      }
      setState(568);
      setter();
      setState(569);
      match(JavaScriptParser::OpenParen);
      setState(571);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << JavaScriptParser::OpenBracket)
        | (1ULL << JavaScriptParser::OpenBrace)
        | (1ULL << JavaScriptParser::Ellipsis))) != 0) || ((((_la - 106) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 106)) & ((1ULL << (JavaScriptParser::Async - 106))
        | (1ULL << (JavaScriptParser::NonStrictLet - 106))
        | (1ULL << (JavaScriptParser::Identifier - 106)))) != 0)) {
        setState(570);
        formalParameterList();
      }
      setState(573);
      match(JavaScriptParser::CloseParen);
      setState(574);
      functionBody();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FormalParameterListContext ------------------------------------------------------------------

JavaScriptParser::FormalParameterListContext::FormalParameterListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::FormalParameterArgContext *> JavaScriptParser::FormalParameterListContext::formalParameterArg() {
  return getRuleContexts<JavaScriptParser::FormalParameterArgContext>();
}

JavaScriptParser::FormalParameterArgContext* JavaScriptParser::FormalParameterListContext::formalParameterArg(size_t i) {
  return getRuleContext<JavaScriptParser::FormalParameterArgContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::FormalParameterListContext::Comma() {
  return getTokens(JavaScriptParser::Comma);
}

tree::TerminalNode* JavaScriptParser::FormalParameterListContext::Comma(size_t i) {
  return getToken(JavaScriptParser::Comma, i);
}

JavaScriptParser::LastFormalParameterArgContext* JavaScriptParser::FormalParameterListContext::lastFormalParameterArg() {
  return getRuleContext<JavaScriptParser::LastFormalParameterArgContext>(0);
}


size_t JavaScriptParser::FormalParameterListContext::getRuleIndex() const {
  return JavaScriptParser::RuleFormalParameterList;
}

void JavaScriptParser::FormalParameterListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFormalParameterList(this);
}

void JavaScriptParser::FormalParameterListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFormalParameterList(this);
}


antlrcpp::Any JavaScriptParser::FormalParameterListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitFormalParameterList(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::FormalParameterListContext* JavaScriptParser::formalParameterList() {
  FormalParameterListContext *_localctx = _tracker.createInstance<FormalParameterListContext>(_ctx, getState());
  enterRule(_localctx, 88, JavaScriptParser::RuleFormalParameterList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    setState(591);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::OpenBracket:
      case JavaScriptParser::OpenBrace:
      case JavaScriptParser::Async:
      case JavaScriptParser::NonStrictLet:
      case JavaScriptParser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(578);
        formalParameterArg();
        setState(583);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 63, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(579);
            match(JavaScriptParser::Comma);
            setState(580);
            formalParameterArg(); 
          }
          setState(585);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 63, _ctx);
        }
        setState(588);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == JavaScriptParser::Comma) {
          setState(586);
          match(JavaScriptParser::Comma);
          setState(587);
          lastFormalParameterArg();
        }
        break;
      }

      case JavaScriptParser::Ellipsis: {
        enterOuterAlt(_localctx, 2);
        setState(590);
        lastFormalParameterArg();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FormalParameterArgContext ------------------------------------------------------------------

JavaScriptParser::FormalParameterArgContext::FormalParameterArgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::AssignableContext* JavaScriptParser::FormalParameterArgContext::assignable() {
  return getRuleContext<JavaScriptParser::AssignableContext>(0);
}

tree::TerminalNode* JavaScriptParser::FormalParameterArgContext::Assign() {
  return getToken(JavaScriptParser::Assign, 0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::FormalParameterArgContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}


size_t JavaScriptParser::FormalParameterArgContext::getRuleIndex() const {
  return JavaScriptParser::RuleFormalParameterArg;
}

void JavaScriptParser::FormalParameterArgContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFormalParameterArg(this);
}

void JavaScriptParser::FormalParameterArgContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFormalParameterArg(this);
}


antlrcpp::Any JavaScriptParser::FormalParameterArgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitFormalParameterArg(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::FormalParameterArgContext* JavaScriptParser::formalParameterArg() {
  FormalParameterArgContext *_localctx = _tracker.createInstance<FormalParameterArgContext>(_ctx, getState());
  enterRule(_localctx, 90, JavaScriptParser::RuleFormalParameterArg);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(593);
    assignable();
    setState(596);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::Assign) {
      setState(594);
      match(JavaScriptParser::Assign);
      setState(595);
      singleExpression(0);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LastFormalParameterArgContext ------------------------------------------------------------------

JavaScriptParser::LastFormalParameterArgContext::LastFormalParameterArgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::LastFormalParameterArgContext::Ellipsis() {
  return getToken(JavaScriptParser::Ellipsis, 0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::LastFormalParameterArgContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}


size_t JavaScriptParser::LastFormalParameterArgContext::getRuleIndex() const {
  return JavaScriptParser::RuleLastFormalParameterArg;
}

void JavaScriptParser::LastFormalParameterArgContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLastFormalParameterArg(this);
}

void JavaScriptParser::LastFormalParameterArgContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLastFormalParameterArg(this);
}


antlrcpp::Any JavaScriptParser::LastFormalParameterArgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitLastFormalParameterArg(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::LastFormalParameterArgContext* JavaScriptParser::lastFormalParameterArg() {
  LastFormalParameterArgContext *_localctx = _tracker.createInstance<LastFormalParameterArgContext>(_ctx, getState());
  enterRule(_localctx, 92, JavaScriptParser::RuleLastFormalParameterArg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(598);
    match(JavaScriptParser::Ellipsis);
    setState(599);
    singleExpression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionBodyContext ------------------------------------------------------------------

JavaScriptParser::FunctionBodyContext::FunctionBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::FunctionBodyContext::OpenBrace() {
  return getToken(JavaScriptParser::OpenBrace, 0);
}

tree::TerminalNode* JavaScriptParser::FunctionBodyContext::CloseBrace() {
  return getToken(JavaScriptParser::CloseBrace, 0);
}

JavaScriptParser::SourceElementsContext* JavaScriptParser::FunctionBodyContext::sourceElements() {
  return getRuleContext<JavaScriptParser::SourceElementsContext>(0);
}


size_t JavaScriptParser::FunctionBodyContext::getRuleIndex() const {
  return JavaScriptParser::RuleFunctionBody;
}

void JavaScriptParser::FunctionBodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionBody(this);
}

void JavaScriptParser::FunctionBodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionBody(this);
}


antlrcpp::Any JavaScriptParser::FunctionBodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitFunctionBody(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::FunctionBodyContext* JavaScriptParser::functionBody() {
  FunctionBodyContext *_localctx = _tracker.createInstance<FunctionBodyContext>(_ctx, getState());
  enterRule(_localctx, 94, JavaScriptParser::RuleFunctionBody);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(601);
    match(JavaScriptParser::OpenBrace);
    setState(603);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 67, _ctx)) {
    case 1: {
      setState(602);
      sourceElements();
      break;
    }

    default:
      break;
    }
    setState(605);
    match(JavaScriptParser::CloseBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SourceElementsContext ------------------------------------------------------------------

JavaScriptParser::SourceElementsContext::SourceElementsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::SourceElementContext *> JavaScriptParser::SourceElementsContext::sourceElement() {
  return getRuleContexts<JavaScriptParser::SourceElementContext>();
}

JavaScriptParser::SourceElementContext* JavaScriptParser::SourceElementsContext::sourceElement(size_t i) {
  return getRuleContext<JavaScriptParser::SourceElementContext>(i);
}


size_t JavaScriptParser::SourceElementsContext::getRuleIndex() const {
  return JavaScriptParser::RuleSourceElements;
}

void JavaScriptParser::SourceElementsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSourceElements(this);
}

void JavaScriptParser::SourceElementsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSourceElements(this);
}


antlrcpp::Any JavaScriptParser::SourceElementsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitSourceElements(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::SourceElementsContext* JavaScriptParser::sourceElements() {
  SourceElementsContext *_localctx = _tracker.createInstance<SourceElementsContext>(_ctx, getState());
  enterRule(_localctx, 96, JavaScriptParser::RuleSourceElements);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(608); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(607);
              sourceElement();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(610); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 68, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayLiteralContext ------------------------------------------------------------------

JavaScriptParser::ArrayLiteralContext::ArrayLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ArrayLiteralContext::OpenBracket() {
  return getToken(JavaScriptParser::OpenBracket, 0);
}

JavaScriptParser::ElementListContext* JavaScriptParser::ArrayLiteralContext::elementList() {
  return getRuleContext<JavaScriptParser::ElementListContext>(0);
}

tree::TerminalNode* JavaScriptParser::ArrayLiteralContext::CloseBracket() {
  return getToken(JavaScriptParser::CloseBracket, 0);
}


size_t JavaScriptParser::ArrayLiteralContext::getRuleIndex() const {
  return JavaScriptParser::RuleArrayLiteral;
}

void JavaScriptParser::ArrayLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayLiteral(this);
}

void JavaScriptParser::ArrayLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayLiteral(this);
}


antlrcpp::Any JavaScriptParser::ArrayLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitArrayLiteral(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ArrayLiteralContext* JavaScriptParser::arrayLiteral() {
  ArrayLiteralContext *_localctx = _tracker.createInstance<ArrayLiteralContext>(_ctx, getState());
  enterRule(_localctx, 98, JavaScriptParser::RuleArrayLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(612);
    match(JavaScriptParser::OpenBracket);
    setState(613);
    elementList();
    setState(614);
    match(JavaScriptParser::CloseBracket);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementListContext ------------------------------------------------------------------

JavaScriptParser::ElementListContext::ElementListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> JavaScriptParser::ElementListContext::Comma() {
  return getTokens(JavaScriptParser::Comma);
}

tree::TerminalNode* JavaScriptParser::ElementListContext::Comma(size_t i) {
  return getToken(JavaScriptParser::Comma, i);
}

std::vector<JavaScriptParser::ArrayElementContext *> JavaScriptParser::ElementListContext::arrayElement() {
  return getRuleContexts<JavaScriptParser::ArrayElementContext>();
}

JavaScriptParser::ArrayElementContext* JavaScriptParser::ElementListContext::arrayElement(size_t i) {
  return getRuleContext<JavaScriptParser::ArrayElementContext>(i);
}


size_t JavaScriptParser::ElementListContext::getRuleIndex() const {
  return JavaScriptParser::RuleElementList;
}

void JavaScriptParser::ElementListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementList(this);
}

void JavaScriptParser::ElementListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementList(this);
}


antlrcpp::Any JavaScriptParser::ElementListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitElementList(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ElementListContext* JavaScriptParser::elementList() {
  ElementListContext *_localctx = _tracker.createInstance<ElementListContext>(_ctx, getState());
  enterRule(_localctx, 100, JavaScriptParser::RuleElementList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(619);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 69, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(616);
        match(JavaScriptParser::Comma); 
      }
      setState(621);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 69, _ctx);
    }
    setState(623);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::RegularExpressionLiteral)
      | (1ULL << JavaScriptParser::OpenBracket)
      | (1ULL << JavaScriptParser::OpenParen)
      | (1ULL << JavaScriptParser::OpenBrace)
      | (1ULL << JavaScriptParser::Ellipsis)
      | (1ULL << JavaScriptParser::PlusPlus)
      | (1ULL << JavaScriptParser::MinusMinus)
      | (1ULL << JavaScriptParser::Plus)
      | (1ULL << JavaScriptParser::Minus)
      | (1ULL << JavaScriptParser::BitNot)
      | (1ULL << JavaScriptParser::Not)
      | (1ULL << JavaScriptParser::NullLiteral)
      | (1ULL << JavaScriptParser::BooleanLiteral)
      | (1ULL << JavaScriptParser::DecimalLiteral)
      | (1ULL << JavaScriptParser::HexIntegerLiteral))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (JavaScriptParser::OctalIntegerLiteral - 64))
      | (1ULL << (JavaScriptParser::OctalIntegerLiteral2 - 64))
      | (1ULL << (JavaScriptParser::BinaryIntegerLiteral - 64))
      | (1ULL << (JavaScriptParser::BigHexIntegerLiteral - 64))
      | (1ULL << (JavaScriptParser::BigOctalIntegerLiteral - 64))
      | (1ULL << (JavaScriptParser::BigBinaryIntegerLiteral - 64))
      | (1ULL << (JavaScriptParser::BigDecimalIntegerLiteral - 64))
      | (1ULL << (JavaScriptParser::Typeof - 64))
      | (1ULL << (JavaScriptParser::New - 64))
      | (1ULL << (JavaScriptParser::Void - 64))
      | (1ULL << (JavaScriptParser::Function_ - 64))
      | (1ULL << (JavaScriptParser::This - 64))
      | (1ULL << (JavaScriptParser::Delete - 64))
      | (1ULL << (JavaScriptParser::Class - 64))
      | (1ULL << (JavaScriptParser::Super - 64))
      | (1ULL << (JavaScriptParser::Import - 64))
      | (1ULL << (JavaScriptParser::Async - 64))
      | (1ULL << (JavaScriptParser::Await - 64))
      | (1ULL << (JavaScriptParser::Yield - 64))
      | (1ULL << (JavaScriptParser::NonStrictLet - 64))
      | (1ULL << (JavaScriptParser::Identifier - 64))
      | (1ULL << (JavaScriptParser::StringLiteral - 64))
      | (1ULL << (JavaScriptParser::BackTick - 64)))) != 0)) {
      setState(622);
      arrayElement();
    }
    setState(633);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 72, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(626); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(625);
          match(JavaScriptParser::Comma);
          setState(628); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == JavaScriptParser::Comma);
        setState(630);
        arrayElement(); 
      }
      setState(635);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 72, _ctx);
    }
    setState(639);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaScriptParser::Comma) {
      setState(636);
      match(JavaScriptParser::Comma);
      setState(641);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayElementContext ------------------------------------------------------------------

JavaScriptParser::ArrayElementContext::ArrayElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::ArrayElementContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::ArrayElementContext::Ellipsis() {
  return getToken(JavaScriptParser::Ellipsis, 0);
}


size_t JavaScriptParser::ArrayElementContext::getRuleIndex() const {
  return JavaScriptParser::RuleArrayElement;
}

void JavaScriptParser::ArrayElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayElement(this);
}

void JavaScriptParser::ArrayElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayElement(this);
}


antlrcpp::Any JavaScriptParser::ArrayElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitArrayElement(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ArrayElementContext* JavaScriptParser::arrayElement() {
  ArrayElementContext *_localctx = _tracker.createInstance<ArrayElementContext>(_ctx, getState());
  enterRule(_localctx, 102, JavaScriptParser::RuleArrayElement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(643);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::Ellipsis) {
      setState(642);
      match(JavaScriptParser::Ellipsis);
    }
    setState(645);
    singleExpression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PropertyAssignmentContext ------------------------------------------------------------------

JavaScriptParser::PropertyAssignmentContext::PropertyAssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t JavaScriptParser::PropertyAssignmentContext::getRuleIndex() const {
  return JavaScriptParser::RulePropertyAssignment;
}

void JavaScriptParser::PropertyAssignmentContext::copyFrom(PropertyAssignmentContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- PropertyExpressionAssignmentContext ------------------------------------------------------------------

JavaScriptParser::PropertyNameContext* JavaScriptParser::PropertyExpressionAssignmentContext::propertyName() {
  return getRuleContext<JavaScriptParser::PropertyNameContext>(0);
}

tree::TerminalNode* JavaScriptParser::PropertyExpressionAssignmentContext::Colon() {
  return getToken(JavaScriptParser::Colon, 0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::PropertyExpressionAssignmentContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

JavaScriptParser::PropertyExpressionAssignmentContext::PropertyExpressionAssignmentContext(PropertyAssignmentContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::PropertyExpressionAssignmentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPropertyExpressionAssignment(this);
}
void JavaScriptParser::PropertyExpressionAssignmentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPropertyExpressionAssignment(this);
}

antlrcpp::Any JavaScriptParser::PropertyExpressionAssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitPropertyExpressionAssignment(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ComputedPropertyExpressionAssignmentContext ------------------------------------------------------------------

tree::TerminalNode* JavaScriptParser::ComputedPropertyExpressionAssignmentContext::OpenBracket() {
  return getToken(JavaScriptParser::OpenBracket, 0);
}

std::vector<JavaScriptParser::SingleExpressionContext *> JavaScriptParser::ComputedPropertyExpressionAssignmentContext::singleExpression() {
  return getRuleContexts<JavaScriptParser::SingleExpressionContext>();
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::ComputedPropertyExpressionAssignmentContext::singleExpression(size_t i) {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(i);
}

tree::TerminalNode* JavaScriptParser::ComputedPropertyExpressionAssignmentContext::CloseBracket() {
  return getToken(JavaScriptParser::CloseBracket, 0);
}

tree::TerminalNode* JavaScriptParser::ComputedPropertyExpressionAssignmentContext::Colon() {
  return getToken(JavaScriptParser::Colon, 0);
}

JavaScriptParser::ComputedPropertyExpressionAssignmentContext::ComputedPropertyExpressionAssignmentContext(PropertyAssignmentContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::ComputedPropertyExpressionAssignmentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComputedPropertyExpressionAssignment(this);
}
void JavaScriptParser::ComputedPropertyExpressionAssignmentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComputedPropertyExpressionAssignment(this);
}

antlrcpp::Any JavaScriptParser::ComputedPropertyExpressionAssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitComputedPropertyExpressionAssignment(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PropertyShorthandContext ------------------------------------------------------------------

JavaScriptParser::SingleExpressionContext* JavaScriptParser::PropertyShorthandContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::PropertyShorthandContext::Ellipsis() {
  return getToken(JavaScriptParser::Ellipsis, 0);
}

JavaScriptParser::PropertyShorthandContext::PropertyShorthandContext(PropertyAssignmentContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::PropertyShorthandContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPropertyShorthand(this);
}
void JavaScriptParser::PropertyShorthandContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPropertyShorthand(this);
}

antlrcpp::Any JavaScriptParser::PropertyShorthandContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitPropertyShorthand(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PropertySetterContext ------------------------------------------------------------------

JavaScriptParser::SetterContext* JavaScriptParser::PropertySetterContext::setter() {
  return getRuleContext<JavaScriptParser::SetterContext>(0);
}

tree::TerminalNode* JavaScriptParser::PropertySetterContext::OpenParen() {
  return getToken(JavaScriptParser::OpenParen, 0);
}

JavaScriptParser::FormalParameterArgContext* JavaScriptParser::PropertySetterContext::formalParameterArg() {
  return getRuleContext<JavaScriptParser::FormalParameterArgContext>(0);
}

tree::TerminalNode* JavaScriptParser::PropertySetterContext::CloseParen() {
  return getToken(JavaScriptParser::CloseParen, 0);
}

JavaScriptParser::FunctionBodyContext* JavaScriptParser::PropertySetterContext::functionBody() {
  return getRuleContext<JavaScriptParser::FunctionBodyContext>(0);
}

JavaScriptParser::PropertySetterContext::PropertySetterContext(PropertyAssignmentContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::PropertySetterContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPropertySetter(this);
}
void JavaScriptParser::PropertySetterContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPropertySetter(this);
}

antlrcpp::Any JavaScriptParser::PropertySetterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitPropertySetter(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PropertyGetterContext ------------------------------------------------------------------

JavaScriptParser::GetterContext* JavaScriptParser::PropertyGetterContext::getter() {
  return getRuleContext<JavaScriptParser::GetterContext>(0);
}

tree::TerminalNode* JavaScriptParser::PropertyGetterContext::OpenParen() {
  return getToken(JavaScriptParser::OpenParen, 0);
}

tree::TerminalNode* JavaScriptParser::PropertyGetterContext::CloseParen() {
  return getToken(JavaScriptParser::CloseParen, 0);
}

JavaScriptParser::FunctionBodyContext* JavaScriptParser::PropertyGetterContext::functionBody() {
  return getRuleContext<JavaScriptParser::FunctionBodyContext>(0);
}

JavaScriptParser::PropertyGetterContext::PropertyGetterContext(PropertyAssignmentContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::PropertyGetterContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPropertyGetter(this);
}
void JavaScriptParser::PropertyGetterContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPropertyGetter(this);
}

antlrcpp::Any JavaScriptParser::PropertyGetterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitPropertyGetter(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FunctionPropertyContext ------------------------------------------------------------------

JavaScriptParser::PropertyNameContext* JavaScriptParser::FunctionPropertyContext::propertyName() {
  return getRuleContext<JavaScriptParser::PropertyNameContext>(0);
}

tree::TerminalNode* JavaScriptParser::FunctionPropertyContext::OpenParen() {
  return getToken(JavaScriptParser::OpenParen, 0);
}

tree::TerminalNode* JavaScriptParser::FunctionPropertyContext::CloseParen() {
  return getToken(JavaScriptParser::CloseParen, 0);
}

JavaScriptParser::FunctionBodyContext* JavaScriptParser::FunctionPropertyContext::functionBody() {
  return getRuleContext<JavaScriptParser::FunctionBodyContext>(0);
}

tree::TerminalNode* JavaScriptParser::FunctionPropertyContext::Async() {
  return getToken(JavaScriptParser::Async, 0);
}

tree::TerminalNode* JavaScriptParser::FunctionPropertyContext::Multiply() {
  return getToken(JavaScriptParser::Multiply, 0);
}

JavaScriptParser::FormalParameterListContext* JavaScriptParser::FunctionPropertyContext::formalParameterList() {
  return getRuleContext<JavaScriptParser::FormalParameterListContext>(0);
}

JavaScriptParser::FunctionPropertyContext::FunctionPropertyContext(PropertyAssignmentContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::FunctionPropertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionProperty(this);
}
void JavaScriptParser::FunctionPropertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionProperty(this);
}

antlrcpp::Any JavaScriptParser::FunctionPropertyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitFunctionProperty(this);
  else
    return visitor->visitChildren(this);
}
JavaScriptParser::PropertyAssignmentContext* JavaScriptParser::propertyAssignment() {
  PropertyAssignmentContext *_localctx = _tracker.createInstance<PropertyAssignmentContext>(_ctx, getState());
  enterRule(_localctx, 104, JavaScriptParser::RulePropertyAssignment);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(686);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 79, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<JavaScriptParser::PropertyExpressionAssignmentContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(647);
      propertyName();
      setState(648);
      match(JavaScriptParser::Colon);
      setState(649);
      singleExpression(0);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<JavaScriptParser::ComputedPropertyExpressionAssignmentContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(651);
      match(JavaScriptParser::OpenBracket);
      setState(652);
      singleExpression(0);
      setState(653);
      match(JavaScriptParser::CloseBracket);
      setState(654);
      match(JavaScriptParser::Colon);
      setState(655);
      singleExpression(0);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<JavaScriptParser::FunctionPropertyContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(658);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 75, _ctx)) {
      case 1: {
        setState(657);
        match(JavaScriptParser::Async);
        break;
      }

      default:
        break;
      }
      setState(661);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == JavaScriptParser::Multiply) {
        setState(660);
        match(JavaScriptParser::Multiply);
      }
      setState(663);
      propertyName();
      setState(664);
      match(JavaScriptParser::OpenParen);
      setState(666);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << JavaScriptParser::OpenBracket)
        | (1ULL << JavaScriptParser::OpenBrace)
        | (1ULL << JavaScriptParser::Ellipsis))) != 0) || ((((_la - 106) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 106)) & ((1ULL << (JavaScriptParser::Async - 106))
        | (1ULL << (JavaScriptParser::NonStrictLet - 106))
        | (1ULL << (JavaScriptParser::Identifier - 106)))) != 0)) {
        setState(665);
        formalParameterList();
      }
      setState(668);
      match(JavaScriptParser::CloseParen);
      setState(669);
      functionBody();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<JavaScriptParser::PropertyGetterContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(671);
      getter();
      setState(672);
      match(JavaScriptParser::OpenParen);
      setState(673);
      match(JavaScriptParser::CloseParen);
      setState(674);
      functionBody();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<JavaScriptParser::PropertySetterContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(676);
      setter();
      setState(677);
      match(JavaScriptParser::OpenParen);
      setState(678);
      formalParameterArg();
      setState(679);
      match(JavaScriptParser::CloseParen);
      setState(680);
      functionBody();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<JavaScriptParser::PropertyShorthandContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(683);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == JavaScriptParser::Ellipsis) {
        setState(682);
        match(JavaScriptParser::Ellipsis);
      }
      setState(685);
      singleExpression(0);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PropertyNameContext ------------------------------------------------------------------

JavaScriptParser::PropertyNameContext::PropertyNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::IdentifierNameContext* JavaScriptParser::PropertyNameContext::identifierName() {
  return getRuleContext<JavaScriptParser::IdentifierNameContext>(0);
}

tree::TerminalNode* JavaScriptParser::PropertyNameContext::StringLiteral() {
  return getToken(JavaScriptParser::StringLiteral, 0);
}

JavaScriptParser::NumericLiteralContext* JavaScriptParser::PropertyNameContext::numericLiteral() {
  return getRuleContext<JavaScriptParser::NumericLiteralContext>(0);
}

tree::TerminalNode* JavaScriptParser::PropertyNameContext::OpenBracket() {
  return getToken(JavaScriptParser::OpenBracket, 0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::PropertyNameContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::PropertyNameContext::CloseBracket() {
  return getToken(JavaScriptParser::CloseBracket, 0);
}


size_t JavaScriptParser::PropertyNameContext::getRuleIndex() const {
  return JavaScriptParser::RulePropertyName;
}

void JavaScriptParser::PropertyNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPropertyName(this);
}

void JavaScriptParser::PropertyNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPropertyName(this);
}


antlrcpp::Any JavaScriptParser::PropertyNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitPropertyName(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::PropertyNameContext* JavaScriptParser::propertyName() {
  PropertyNameContext *_localctx = _tracker.createInstance<PropertyNameContext>(_ctx, getState());
  enterRule(_localctx, 106, JavaScriptParser::RulePropertyName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(695);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::NullLiteral:
      case JavaScriptParser::BooleanLiteral:
      case JavaScriptParser::Break:
      case JavaScriptParser::Do:
      case JavaScriptParser::Instanceof:
      case JavaScriptParser::Typeof:
      case JavaScriptParser::Case:
      case JavaScriptParser::Else:
      case JavaScriptParser::New:
      case JavaScriptParser::Var:
      case JavaScriptParser::Catch:
      case JavaScriptParser::Finally:
      case JavaScriptParser::Return:
      case JavaScriptParser::Void:
      case JavaScriptParser::Continue:
      case JavaScriptParser::For:
      case JavaScriptParser::Switch:
      case JavaScriptParser::While:
      case JavaScriptParser::Debugger:
      case JavaScriptParser::Function_:
      case JavaScriptParser::This:
      case JavaScriptParser::With:
      case JavaScriptParser::Default:
      case JavaScriptParser::If:
      case JavaScriptParser::Throw:
      case JavaScriptParser::Delete:
      case JavaScriptParser::In:
      case JavaScriptParser::Try:
      case JavaScriptParser::As:
      case JavaScriptParser::From:
      case JavaScriptParser::Class:
      case JavaScriptParser::Enum:
      case JavaScriptParser::Extends:
      case JavaScriptParser::Super:
      case JavaScriptParser::Const:
      case JavaScriptParser::Export:
      case JavaScriptParser::Import:
      case JavaScriptParser::Async:
      case JavaScriptParser::Await:
      case JavaScriptParser::Yield:
      case JavaScriptParser::Implements:
      case JavaScriptParser::StrictLet:
      case JavaScriptParser::NonStrictLet:
      case JavaScriptParser::Private:
      case JavaScriptParser::Public:
      case JavaScriptParser::Interface:
      case JavaScriptParser::Package:
      case JavaScriptParser::Protected:
      case JavaScriptParser::Static:
      case JavaScriptParser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(688);
        identifierName();
        break;
      }

      case JavaScriptParser::StringLiteral: {
        enterOuterAlt(_localctx, 2);
        setState(689);
        match(JavaScriptParser::StringLiteral);
        break;
      }

      case JavaScriptParser::DecimalLiteral:
      case JavaScriptParser::HexIntegerLiteral:
      case JavaScriptParser::OctalIntegerLiteral:
      case JavaScriptParser::OctalIntegerLiteral2:
      case JavaScriptParser::BinaryIntegerLiteral: {
        enterOuterAlt(_localctx, 3);
        setState(690);
        numericLiteral();
        break;
      }

      case JavaScriptParser::OpenBracket: {
        enterOuterAlt(_localctx, 4);
        setState(691);
        match(JavaScriptParser::OpenBracket);
        setState(692);
        singleExpression(0);
        setState(693);
        match(JavaScriptParser::CloseBracket);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentsContext ------------------------------------------------------------------

JavaScriptParser::ArgumentsContext::ArgumentsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ArgumentsContext::OpenParen() {
  return getToken(JavaScriptParser::OpenParen, 0);
}

tree::TerminalNode* JavaScriptParser::ArgumentsContext::CloseParen() {
  return getToken(JavaScriptParser::CloseParen, 0);
}

std::vector<JavaScriptParser::ArgumentContext *> JavaScriptParser::ArgumentsContext::argument() {
  return getRuleContexts<JavaScriptParser::ArgumentContext>();
}

JavaScriptParser::ArgumentContext* JavaScriptParser::ArgumentsContext::argument(size_t i) {
  return getRuleContext<JavaScriptParser::ArgumentContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::ArgumentsContext::Comma() {
  return getTokens(JavaScriptParser::Comma);
}

tree::TerminalNode* JavaScriptParser::ArgumentsContext::Comma(size_t i) {
  return getToken(JavaScriptParser::Comma, i);
}


size_t JavaScriptParser::ArgumentsContext::getRuleIndex() const {
  return JavaScriptParser::RuleArguments;
}

void JavaScriptParser::ArgumentsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArguments(this);
}

void JavaScriptParser::ArgumentsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArguments(this);
}


antlrcpp::Any JavaScriptParser::ArgumentsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitArguments(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ArgumentsContext* JavaScriptParser::arguments() {
  ArgumentsContext *_localctx = _tracker.createInstance<ArgumentsContext>(_ctx, getState());
  enterRule(_localctx, 108, JavaScriptParser::RuleArguments);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(697);
    match(JavaScriptParser::OpenParen);
    setState(709);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::RegularExpressionLiteral)
      | (1ULL << JavaScriptParser::OpenBracket)
      | (1ULL << JavaScriptParser::OpenParen)
      | (1ULL << JavaScriptParser::OpenBrace)
      | (1ULL << JavaScriptParser::Ellipsis)
      | (1ULL << JavaScriptParser::PlusPlus)
      | (1ULL << JavaScriptParser::MinusMinus)
      | (1ULL << JavaScriptParser::Plus)
      | (1ULL << JavaScriptParser::Minus)
      | (1ULL << JavaScriptParser::BitNot)
      | (1ULL << JavaScriptParser::Not)
      | (1ULL << JavaScriptParser::NullLiteral)
      | (1ULL << JavaScriptParser::BooleanLiteral)
      | (1ULL << JavaScriptParser::DecimalLiteral)
      | (1ULL << JavaScriptParser::HexIntegerLiteral))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (JavaScriptParser::OctalIntegerLiteral - 64))
      | (1ULL << (JavaScriptParser::OctalIntegerLiteral2 - 64))
      | (1ULL << (JavaScriptParser::BinaryIntegerLiteral - 64))
      | (1ULL << (JavaScriptParser::BigHexIntegerLiteral - 64))
      | (1ULL << (JavaScriptParser::BigOctalIntegerLiteral - 64))
      | (1ULL << (JavaScriptParser::BigBinaryIntegerLiteral - 64))
      | (1ULL << (JavaScriptParser::BigDecimalIntegerLiteral - 64))
      | (1ULL << (JavaScriptParser::Typeof - 64))
      | (1ULL << (JavaScriptParser::New - 64))
      | (1ULL << (JavaScriptParser::Void - 64))
      | (1ULL << (JavaScriptParser::Function_ - 64))
      | (1ULL << (JavaScriptParser::This - 64))
      | (1ULL << (JavaScriptParser::Delete - 64))
      | (1ULL << (JavaScriptParser::Class - 64))
      | (1ULL << (JavaScriptParser::Super - 64))
      | (1ULL << (JavaScriptParser::Import - 64))
      | (1ULL << (JavaScriptParser::Async - 64))
      | (1ULL << (JavaScriptParser::Await - 64))
      | (1ULL << (JavaScriptParser::Yield - 64))
      | (1ULL << (JavaScriptParser::NonStrictLet - 64))
      | (1ULL << (JavaScriptParser::Identifier - 64))
      | (1ULL << (JavaScriptParser::StringLiteral - 64))
      | (1ULL << (JavaScriptParser::BackTick - 64)))) != 0)) {
      setState(698);
      argument();
      setState(703);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 81, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(699);
          match(JavaScriptParser::Comma);
          setState(700);
          argument(); 
        }
        setState(705);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 81, _ctx);
      }
      setState(707);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == JavaScriptParser::Comma) {
        setState(706);
        match(JavaScriptParser::Comma);
      }
    }
    setState(711);
    match(JavaScriptParser::CloseParen);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentContext ------------------------------------------------------------------

JavaScriptParser::ArgumentContext::ArgumentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::ArgumentContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

JavaScriptParser::IdentifierContext* JavaScriptParser::ArgumentContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}

tree::TerminalNode* JavaScriptParser::ArgumentContext::Ellipsis() {
  return getToken(JavaScriptParser::Ellipsis, 0);
}


size_t JavaScriptParser::ArgumentContext::getRuleIndex() const {
  return JavaScriptParser::RuleArgument;
}

void JavaScriptParser::ArgumentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgument(this);
}

void JavaScriptParser::ArgumentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgument(this);
}


antlrcpp::Any JavaScriptParser::ArgumentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitArgument(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ArgumentContext* JavaScriptParser::argument() {
  ArgumentContext *_localctx = _tracker.createInstance<ArgumentContext>(_ctx, getState());
  enterRule(_localctx, 110, JavaScriptParser::RuleArgument);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(714);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == JavaScriptParser::Ellipsis) {
      setState(713);
      match(JavaScriptParser::Ellipsis);
    }
    setState(718);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 85, _ctx)) {
    case 1: {
      setState(716);
      singleExpression(0);
      break;
    }

    case 2: {
      setState(717);
      identifier();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionSequenceContext ------------------------------------------------------------------

JavaScriptParser::ExpressionSequenceContext::ExpressionSequenceContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<JavaScriptParser::SingleExpressionContext *> JavaScriptParser::ExpressionSequenceContext::singleExpression() {
  return getRuleContexts<JavaScriptParser::SingleExpressionContext>();
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::ExpressionSequenceContext::singleExpression(size_t i) {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::ExpressionSequenceContext::Comma() {
  return getTokens(JavaScriptParser::Comma);
}

tree::TerminalNode* JavaScriptParser::ExpressionSequenceContext::Comma(size_t i) {
  return getToken(JavaScriptParser::Comma, i);
}


size_t JavaScriptParser::ExpressionSequenceContext::getRuleIndex() const {
  return JavaScriptParser::RuleExpressionSequence;
}

void JavaScriptParser::ExpressionSequenceContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpressionSequence(this);
}

void JavaScriptParser::ExpressionSequenceContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpressionSequence(this);
}


antlrcpp::Any JavaScriptParser::ExpressionSequenceContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitExpressionSequence(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ExpressionSequenceContext* JavaScriptParser::expressionSequence() {
  ExpressionSequenceContext *_localctx = _tracker.createInstance<ExpressionSequenceContext>(_ctx, getState());
  enterRule(_localctx, 112, JavaScriptParser::RuleExpressionSequence);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(720);
    singleExpression(0);
    setState(725);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 86, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(721);
        match(JavaScriptParser::Comma);
        setState(722);
        singleExpression(0); 
      }
      setState(727);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 86, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SingleExpressionContext ------------------------------------------------------------------

JavaScriptParser::SingleExpressionContext::SingleExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t JavaScriptParser::SingleExpressionContext::getRuleIndex() const {
  return JavaScriptParser::RuleSingleExpression;
}

void JavaScriptParser::SingleExpressionContext::copyFrom(SingleExpressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- TemplateStringExpressionContext ------------------------------------------------------------------

JavaScriptParser::SingleExpressionContext* JavaScriptParser::TemplateStringExpressionContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

JavaScriptParser::TemplateStringLiteralContext* JavaScriptParser::TemplateStringExpressionContext::templateStringLiteral() {
  return getRuleContext<JavaScriptParser::TemplateStringLiteralContext>(0);
}

JavaScriptParser::TemplateStringExpressionContext::TemplateStringExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::TemplateStringExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTemplateStringExpression(this);
}
void JavaScriptParser::TemplateStringExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTemplateStringExpression(this);
}

antlrcpp::Any JavaScriptParser::TemplateStringExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitTemplateStringExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TernaryExpressionContext ------------------------------------------------------------------

std::vector<JavaScriptParser::SingleExpressionContext *> JavaScriptParser::TernaryExpressionContext::singleExpression() {
  return getRuleContexts<JavaScriptParser::SingleExpressionContext>();
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::TernaryExpressionContext::singleExpression(size_t i) {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(i);
}

tree::TerminalNode* JavaScriptParser::TernaryExpressionContext::QuestionMark() {
  return getToken(JavaScriptParser::QuestionMark, 0);
}

tree::TerminalNode* JavaScriptParser::TernaryExpressionContext::Colon() {
  return getToken(JavaScriptParser::Colon, 0);
}

JavaScriptParser::TernaryExpressionContext::TernaryExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::TernaryExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTernaryExpression(this);
}
void JavaScriptParser::TernaryExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTernaryExpression(this);
}

antlrcpp::Any JavaScriptParser::TernaryExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitTernaryExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LogicalAndExpressionContext ------------------------------------------------------------------

std::vector<JavaScriptParser::SingleExpressionContext *> JavaScriptParser::LogicalAndExpressionContext::singleExpression() {
  return getRuleContexts<JavaScriptParser::SingleExpressionContext>();
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::LogicalAndExpressionContext::singleExpression(size_t i) {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(i);
}

tree::TerminalNode* JavaScriptParser::LogicalAndExpressionContext::And() {
  return getToken(JavaScriptParser::And, 0);
}

JavaScriptParser::LogicalAndExpressionContext::LogicalAndExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::LogicalAndExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalAndExpression(this);
}
void JavaScriptParser::LogicalAndExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalAndExpression(this);
}

antlrcpp::Any JavaScriptParser::LogicalAndExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitLogicalAndExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PowerExpressionContext ------------------------------------------------------------------

std::vector<JavaScriptParser::SingleExpressionContext *> JavaScriptParser::PowerExpressionContext::singleExpression() {
  return getRuleContexts<JavaScriptParser::SingleExpressionContext>();
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::PowerExpressionContext::singleExpression(size_t i) {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(i);
}

tree::TerminalNode* JavaScriptParser::PowerExpressionContext::Power() {
  return getToken(JavaScriptParser::Power, 0);
}

JavaScriptParser::PowerExpressionContext::PowerExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::PowerExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPowerExpression(this);
}
void JavaScriptParser::PowerExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPowerExpression(this);
}

antlrcpp::Any JavaScriptParser::PowerExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitPowerExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PreIncrementExpressionContext ------------------------------------------------------------------

tree::TerminalNode* JavaScriptParser::PreIncrementExpressionContext::PlusPlus() {
  return getToken(JavaScriptParser::PlusPlus, 0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::PreIncrementExpressionContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

JavaScriptParser::PreIncrementExpressionContext::PreIncrementExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::PreIncrementExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPreIncrementExpression(this);
}
void JavaScriptParser::PreIncrementExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPreIncrementExpression(this);
}

antlrcpp::Any JavaScriptParser::PreIncrementExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitPreIncrementExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ObjectLiteralExpressionContext ------------------------------------------------------------------

JavaScriptParser::ObjectLiteralContext* JavaScriptParser::ObjectLiteralExpressionContext::objectLiteral() {
  return getRuleContext<JavaScriptParser::ObjectLiteralContext>(0);
}

JavaScriptParser::ObjectLiteralExpressionContext::ObjectLiteralExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::ObjectLiteralExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterObjectLiteralExpression(this);
}
void JavaScriptParser::ObjectLiteralExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitObjectLiteralExpression(this);
}

antlrcpp::Any JavaScriptParser::ObjectLiteralExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitObjectLiteralExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MetaExpressionContext ------------------------------------------------------------------

tree::TerminalNode* JavaScriptParser::MetaExpressionContext::New() {
  return getToken(JavaScriptParser::New, 0);
}

tree::TerminalNode* JavaScriptParser::MetaExpressionContext::Dot() {
  return getToken(JavaScriptParser::Dot, 0);
}

JavaScriptParser::IdentifierContext* JavaScriptParser::MetaExpressionContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}

JavaScriptParser::MetaExpressionContext::MetaExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::MetaExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMetaExpression(this);
}
void JavaScriptParser::MetaExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMetaExpression(this);
}

antlrcpp::Any JavaScriptParser::MetaExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitMetaExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- InExpressionContext ------------------------------------------------------------------

std::vector<JavaScriptParser::SingleExpressionContext *> JavaScriptParser::InExpressionContext::singleExpression() {
  return getRuleContexts<JavaScriptParser::SingleExpressionContext>();
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::InExpressionContext::singleExpression(size_t i) {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(i);
}

tree::TerminalNode* JavaScriptParser::InExpressionContext::In() {
  return getToken(JavaScriptParser::In, 0);
}

JavaScriptParser::InExpressionContext::InExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::InExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInExpression(this);
}
void JavaScriptParser::InExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInExpression(this);
}

antlrcpp::Any JavaScriptParser::InExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitInExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LogicalOrExpressionContext ------------------------------------------------------------------

std::vector<JavaScriptParser::SingleExpressionContext *> JavaScriptParser::LogicalOrExpressionContext::singleExpression() {
  return getRuleContexts<JavaScriptParser::SingleExpressionContext>();
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::LogicalOrExpressionContext::singleExpression(size_t i) {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(i);
}

tree::TerminalNode* JavaScriptParser::LogicalOrExpressionContext::Or() {
  return getToken(JavaScriptParser::Or, 0);
}

JavaScriptParser::LogicalOrExpressionContext::LogicalOrExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::LogicalOrExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalOrExpression(this);
}
void JavaScriptParser::LogicalOrExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalOrExpression(this);
}

antlrcpp::Any JavaScriptParser::LogicalOrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitLogicalOrExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NotExpressionContext ------------------------------------------------------------------

tree::TerminalNode* JavaScriptParser::NotExpressionContext::Not() {
  return getToken(JavaScriptParser::Not, 0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::NotExpressionContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

JavaScriptParser::NotExpressionContext::NotExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::NotExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNotExpression(this);
}
void JavaScriptParser::NotExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNotExpression(this);
}

antlrcpp::Any JavaScriptParser::NotExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitNotExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PreDecreaseExpressionContext ------------------------------------------------------------------

tree::TerminalNode* JavaScriptParser::PreDecreaseExpressionContext::MinusMinus() {
  return getToken(JavaScriptParser::MinusMinus, 0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::PreDecreaseExpressionContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

JavaScriptParser::PreDecreaseExpressionContext::PreDecreaseExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::PreDecreaseExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPreDecreaseExpression(this);
}
void JavaScriptParser::PreDecreaseExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPreDecreaseExpression(this);
}

antlrcpp::Any JavaScriptParser::PreDecreaseExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitPreDecreaseExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArgumentsExpressionContext ------------------------------------------------------------------

JavaScriptParser::SingleExpressionContext* JavaScriptParser::ArgumentsExpressionContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

JavaScriptParser::ArgumentsContext* JavaScriptParser::ArgumentsExpressionContext::arguments() {
  return getRuleContext<JavaScriptParser::ArgumentsContext>(0);
}

JavaScriptParser::ArgumentsExpressionContext::ArgumentsExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::ArgumentsExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgumentsExpression(this);
}
void JavaScriptParser::ArgumentsExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgumentsExpression(this);
}

antlrcpp::Any JavaScriptParser::ArgumentsExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitArgumentsExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AwaitExpressionContext ------------------------------------------------------------------

tree::TerminalNode* JavaScriptParser::AwaitExpressionContext::Await() {
  return getToken(JavaScriptParser::Await, 0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::AwaitExpressionContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

JavaScriptParser::AwaitExpressionContext::AwaitExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::AwaitExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAwaitExpression(this);
}
void JavaScriptParser::AwaitExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAwaitExpression(this);
}

antlrcpp::Any JavaScriptParser::AwaitExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitAwaitExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ThisExpressionContext ------------------------------------------------------------------

tree::TerminalNode* JavaScriptParser::ThisExpressionContext::This() {
  return getToken(JavaScriptParser::This, 0);
}

JavaScriptParser::ThisExpressionContext::ThisExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::ThisExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterThisExpression(this);
}
void JavaScriptParser::ThisExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitThisExpression(this);
}

antlrcpp::Any JavaScriptParser::ThisExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitThisExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FunctionExpressionContext ------------------------------------------------------------------

JavaScriptParser::AnonymousFunctionContext* JavaScriptParser::FunctionExpressionContext::anonymousFunction() {
  return getRuleContext<JavaScriptParser::AnonymousFunctionContext>(0);
}

JavaScriptParser::FunctionExpressionContext::FunctionExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::FunctionExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionExpression(this);
}
void JavaScriptParser::FunctionExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionExpression(this);
}

antlrcpp::Any JavaScriptParser::FunctionExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitFunctionExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryMinusExpressionContext ------------------------------------------------------------------

tree::TerminalNode* JavaScriptParser::UnaryMinusExpressionContext::Minus() {
  return getToken(JavaScriptParser::Minus, 0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::UnaryMinusExpressionContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

JavaScriptParser::UnaryMinusExpressionContext::UnaryMinusExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::UnaryMinusExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryMinusExpression(this);
}
void JavaScriptParser::UnaryMinusExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryMinusExpression(this);
}

antlrcpp::Any JavaScriptParser::UnaryMinusExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitUnaryMinusExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignmentExpressionContext ------------------------------------------------------------------

std::vector<JavaScriptParser::SingleExpressionContext *> JavaScriptParser::AssignmentExpressionContext::singleExpression() {
  return getRuleContexts<JavaScriptParser::SingleExpressionContext>();
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::AssignmentExpressionContext::singleExpression(size_t i) {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(i);
}

tree::TerminalNode* JavaScriptParser::AssignmentExpressionContext::Assign() {
  return getToken(JavaScriptParser::Assign, 0);
}

JavaScriptParser::AssignmentExpressionContext::AssignmentExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::AssignmentExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignmentExpression(this);
}
void JavaScriptParser::AssignmentExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignmentExpression(this);
}

antlrcpp::Any JavaScriptParser::AssignmentExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitAssignmentExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PostDecreaseExpressionContext ------------------------------------------------------------------

JavaScriptParser::SingleExpressionContext* JavaScriptParser::PostDecreaseExpressionContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::PostDecreaseExpressionContext::MinusMinus() {
  return getToken(JavaScriptParser::MinusMinus, 0);
}

JavaScriptParser::PostDecreaseExpressionContext::PostDecreaseExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::PostDecreaseExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPostDecreaseExpression(this);
}
void JavaScriptParser::PostDecreaseExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPostDecreaseExpression(this);
}

antlrcpp::Any JavaScriptParser::PostDecreaseExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitPostDecreaseExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TypeofExpressionContext ------------------------------------------------------------------

tree::TerminalNode* JavaScriptParser::TypeofExpressionContext::Typeof() {
  return getToken(JavaScriptParser::Typeof, 0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::TypeofExpressionContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

JavaScriptParser::TypeofExpressionContext::TypeofExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::TypeofExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeofExpression(this);
}
void JavaScriptParser::TypeofExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeofExpression(this);
}

antlrcpp::Any JavaScriptParser::TypeofExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitTypeofExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- InstanceofExpressionContext ------------------------------------------------------------------

std::vector<JavaScriptParser::SingleExpressionContext *> JavaScriptParser::InstanceofExpressionContext::singleExpression() {
  return getRuleContexts<JavaScriptParser::SingleExpressionContext>();
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::InstanceofExpressionContext::singleExpression(size_t i) {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(i);
}

tree::TerminalNode* JavaScriptParser::InstanceofExpressionContext::Instanceof() {
  return getToken(JavaScriptParser::Instanceof, 0);
}

JavaScriptParser::InstanceofExpressionContext::InstanceofExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::InstanceofExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInstanceofExpression(this);
}
void JavaScriptParser::InstanceofExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInstanceofExpression(this);
}

antlrcpp::Any JavaScriptParser::InstanceofExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitInstanceofExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryPlusExpressionContext ------------------------------------------------------------------

tree::TerminalNode* JavaScriptParser::UnaryPlusExpressionContext::Plus() {
  return getToken(JavaScriptParser::Plus, 0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::UnaryPlusExpressionContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

JavaScriptParser::UnaryPlusExpressionContext::UnaryPlusExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::UnaryPlusExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryPlusExpression(this);
}
void JavaScriptParser::UnaryPlusExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryPlusExpression(this);
}

antlrcpp::Any JavaScriptParser::UnaryPlusExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitUnaryPlusExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DeleteExpressionContext ------------------------------------------------------------------

tree::TerminalNode* JavaScriptParser::DeleteExpressionContext::Delete() {
  return getToken(JavaScriptParser::Delete, 0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::DeleteExpressionContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

JavaScriptParser::DeleteExpressionContext::DeleteExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::DeleteExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeleteExpression(this);
}
void JavaScriptParser::DeleteExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeleteExpression(this);
}

antlrcpp::Any JavaScriptParser::DeleteExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitDeleteExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ImportExpressionContext ------------------------------------------------------------------

tree::TerminalNode* JavaScriptParser::ImportExpressionContext::Import() {
  return getToken(JavaScriptParser::Import, 0);
}

tree::TerminalNode* JavaScriptParser::ImportExpressionContext::OpenParen() {
  return getToken(JavaScriptParser::OpenParen, 0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::ImportExpressionContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::ImportExpressionContext::CloseParen() {
  return getToken(JavaScriptParser::CloseParen, 0);
}

JavaScriptParser::ImportExpressionContext::ImportExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::ImportExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImportExpression(this);
}
void JavaScriptParser::ImportExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImportExpression(this);
}

antlrcpp::Any JavaScriptParser::ImportExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitImportExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EqualityExpressionContext ------------------------------------------------------------------

std::vector<JavaScriptParser::SingleExpressionContext *> JavaScriptParser::EqualityExpressionContext::singleExpression() {
  return getRuleContexts<JavaScriptParser::SingleExpressionContext>();
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::EqualityExpressionContext::singleExpression(size_t i) {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(i);
}

tree::TerminalNode* JavaScriptParser::EqualityExpressionContext::Equals_() {
  return getToken(JavaScriptParser::Equals_, 0);
}

tree::TerminalNode* JavaScriptParser::EqualityExpressionContext::NotEquals() {
  return getToken(JavaScriptParser::NotEquals, 0);
}

tree::TerminalNode* JavaScriptParser::EqualityExpressionContext::IdentityEquals() {
  return getToken(JavaScriptParser::IdentityEquals, 0);
}

tree::TerminalNode* JavaScriptParser::EqualityExpressionContext::IdentityNotEquals() {
  return getToken(JavaScriptParser::IdentityNotEquals, 0);
}

JavaScriptParser::EqualityExpressionContext::EqualityExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::EqualityExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEqualityExpression(this);
}
void JavaScriptParser::EqualityExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEqualityExpression(this);
}

antlrcpp::Any JavaScriptParser::EqualityExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitEqualityExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BitXOrExpressionContext ------------------------------------------------------------------

std::vector<JavaScriptParser::SingleExpressionContext *> JavaScriptParser::BitXOrExpressionContext::singleExpression() {
  return getRuleContexts<JavaScriptParser::SingleExpressionContext>();
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::BitXOrExpressionContext::singleExpression(size_t i) {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(i);
}

tree::TerminalNode* JavaScriptParser::BitXOrExpressionContext::BitXOr() {
  return getToken(JavaScriptParser::BitXOr, 0);
}

JavaScriptParser::BitXOrExpressionContext::BitXOrExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::BitXOrExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitXOrExpression(this);
}
void JavaScriptParser::BitXOrExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitXOrExpression(this);
}

antlrcpp::Any JavaScriptParser::BitXOrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitBitXOrExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SuperExpressionContext ------------------------------------------------------------------

tree::TerminalNode* JavaScriptParser::SuperExpressionContext::Super() {
  return getToken(JavaScriptParser::Super, 0);
}

JavaScriptParser::SuperExpressionContext::SuperExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::SuperExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSuperExpression(this);
}
void JavaScriptParser::SuperExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSuperExpression(this);
}

antlrcpp::Any JavaScriptParser::SuperExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitSuperExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MultiplicativeExpressionContext ------------------------------------------------------------------

std::vector<JavaScriptParser::SingleExpressionContext *> JavaScriptParser::MultiplicativeExpressionContext::singleExpression() {
  return getRuleContexts<JavaScriptParser::SingleExpressionContext>();
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::MultiplicativeExpressionContext::singleExpression(size_t i) {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(i);
}

tree::TerminalNode* JavaScriptParser::MultiplicativeExpressionContext::Multiply() {
  return getToken(JavaScriptParser::Multiply, 0);
}

tree::TerminalNode* JavaScriptParser::MultiplicativeExpressionContext::Divide() {
  return getToken(JavaScriptParser::Divide, 0);
}

tree::TerminalNode* JavaScriptParser::MultiplicativeExpressionContext::Modulus() {
  return getToken(JavaScriptParser::Modulus, 0);
}

JavaScriptParser::MultiplicativeExpressionContext::MultiplicativeExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::MultiplicativeExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMultiplicativeExpression(this);
}
void JavaScriptParser::MultiplicativeExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMultiplicativeExpression(this);
}

antlrcpp::Any JavaScriptParser::MultiplicativeExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitMultiplicativeExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BitShiftExpressionContext ------------------------------------------------------------------

std::vector<JavaScriptParser::SingleExpressionContext *> JavaScriptParser::BitShiftExpressionContext::singleExpression() {
  return getRuleContexts<JavaScriptParser::SingleExpressionContext>();
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::BitShiftExpressionContext::singleExpression(size_t i) {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(i);
}

tree::TerminalNode* JavaScriptParser::BitShiftExpressionContext::LeftShiftArithmetic() {
  return getToken(JavaScriptParser::LeftShiftArithmetic, 0);
}

tree::TerminalNode* JavaScriptParser::BitShiftExpressionContext::RightShiftArithmetic() {
  return getToken(JavaScriptParser::RightShiftArithmetic, 0);
}

tree::TerminalNode* JavaScriptParser::BitShiftExpressionContext::RightShiftLogical() {
  return getToken(JavaScriptParser::RightShiftLogical, 0);
}

JavaScriptParser::BitShiftExpressionContext::BitShiftExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::BitShiftExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitShiftExpression(this);
}
void JavaScriptParser::BitShiftExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitShiftExpression(this);
}

antlrcpp::Any JavaScriptParser::BitShiftExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitBitShiftExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParenthesizedExpressionContext ------------------------------------------------------------------

tree::TerminalNode* JavaScriptParser::ParenthesizedExpressionContext::OpenParen() {
  return getToken(JavaScriptParser::OpenParen, 0);
}

JavaScriptParser::ExpressionSequenceContext* JavaScriptParser::ParenthesizedExpressionContext::expressionSequence() {
  return getRuleContext<JavaScriptParser::ExpressionSequenceContext>(0);
}

tree::TerminalNode* JavaScriptParser::ParenthesizedExpressionContext::CloseParen() {
  return getToken(JavaScriptParser::CloseParen, 0);
}

JavaScriptParser::ParenthesizedExpressionContext::ParenthesizedExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::ParenthesizedExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParenthesizedExpression(this);
}
void JavaScriptParser::ParenthesizedExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParenthesizedExpression(this);
}

antlrcpp::Any JavaScriptParser::ParenthesizedExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitParenthesizedExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AdditiveExpressionContext ------------------------------------------------------------------

std::vector<JavaScriptParser::SingleExpressionContext *> JavaScriptParser::AdditiveExpressionContext::singleExpression() {
  return getRuleContexts<JavaScriptParser::SingleExpressionContext>();
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::AdditiveExpressionContext::singleExpression(size_t i) {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(i);
}

tree::TerminalNode* JavaScriptParser::AdditiveExpressionContext::Plus() {
  return getToken(JavaScriptParser::Plus, 0);
}

tree::TerminalNode* JavaScriptParser::AdditiveExpressionContext::Minus() {
  return getToken(JavaScriptParser::Minus, 0);
}

JavaScriptParser::AdditiveExpressionContext::AdditiveExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::AdditiveExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAdditiveExpression(this);
}
void JavaScriptParser::AdditiveExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAdditiveExpression(this);
}

antlrcpp::Any JavaScriptParser::AdditiveExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitAdditiveExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- RelationalExpressionContext ------------------------------------------------------------------

std::vector<JavaScriptParser::SingleExpressionContext *> JavaScriptParser::RelationalExpressionContext::singleExpression() {
  return getRuleContexts<JavaScriptParser::SingleExpressionContext>();
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::RelationalExpressionContext::singleExpression(size_t i) {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(i);
}

tree::TerminalNode* JavaScriptParser::RelationalExpressionContext::LessThan() {
  return getToken(JavaScriptParser::LessThan, 0);
}

tree::TerminalNode* JavaScriptParser::RelationalExpressionContext::MoreThan() {
  return getToken(JavaScriptParser::MoreThan, 0);
}

tree::TerminalNode* JavaScriptParser::RelationalExpressionContext::LessThanEquals() {
  return getToken(JavaScriptParser::LessThanEquals, 0);
}

tree::TerminalNode* JavaScriptParser::RelationalExpressionContext::GreaterThanEquals() {
  return getToken(JavaScriptParser::GreaterThanEquals, 0);
}

JavaScriptParser::RelationalExpressionContext::RelationalExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::RelationalExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelationalExpression(this);
}
void JavaScriptParser::RelationalExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelationalExpression(this);
}

antlrcpp::Any JavaScriptParser::RelationalExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitRelationalExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PostIncrementExpressionContext ------------------------------------------------------------------

JavaScriptParser::SingleExpressionContext* JavaScriptParser::PostIncrementExpressionContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::PostIncrementExpressionContext::PlusPlus() {
  return getToken(JavaScriptParser::PlusPlus, 0);
}

JavaScriptParser::PostIncrementExpressionContext::PostIncrementExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::PostIncrementExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPostIncrementExpression(this);
}
void JavaScriptParser::PostIncrementExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPostIncrementExpression(this);
}

antlrcpp::Any JavaScriptParser::PostIncrementExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitPostIncrementExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- YieldExpressionContext ------------------------------------------------------------------

JavaScriptParser::YieldStatementContext* JavaScriptParser::YieldExpressionContext::yieldStatement() {
  return getRuleContext<JavaScriptParser::YieldStatementContext>(0);
}

JavaScriptParser::YieldExpressionContext::YieldExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::YieldExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterYieldExpression(this);
}
void JavaScriptParser::YieldExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitYieldExpression(this);
}

antlrcpp::Any JavaScriptParser::YieldExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitYieldExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BitNotExpressionContext ------------------------------------------------------------------

tree::TerminalNode* JavaScriptParser::BitNotExpressionContext::BitNot() {
  return getToken(JavaScriptParser::BitNot, 0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::BitNotExpressionContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

JavaScriptParser::BitNotExpressionContext::BitNotExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::BitNotExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitNotExpression(this);
}
void JavaScriptParser::BitNotExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitNotExpression(this);
}

antlrcpp::Any JavaScriptParser::BitNotExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitBitNotExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NewExpressionContext ------------------------------------------------------------------

tree::TerminalNode* JavaScriptParser::NewExpressionContext::New() {
  return getToken(JavaScriptParser::New, 0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::NewExpressionContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

JavaScriptParser::ArgumentsContext* JavaScriptParser::NewExpressionContext::arguments() {
  return getRuleContext<JavaScriptParser::ArgumentsContext>(0);
}

JavaScriptParser::NewExpressionContext::NewExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::NewExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNewExpression(this);
}
void JavaScriptParser::NewExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNewExpression(this);
}

antlrcpp::Any JavaScriptParser::NewExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitNewExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LiteralExpressionContext ------------------------------------------------------------------

JavaScriptParser::LiteralContext* JavaScriptParser::LiteralExpressionContext::literal() {
  return getRuleContext<JavaScriptParser::LiteralContext>(0);
}

JavaScriptParser::LiteralExpressionContext::LiteralExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::LiteralExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLiteralExpression(this);
}
void JavaScriptParser::LiteralExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLiteralExpression(this);
}

antlrcpp::Any JavaScriptParser::LiteralExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitLiteralExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArrayLiteralExpressionContext ------------------------------------------------------------------

JavaScriptParser::ArrayLiteralContext* JavaScriptParser::ArrayLiteralExpressionContext::arrayLiteral() {
  return getRuleContext<JavaScriptParser::ArrayLiteralContext>(0);
}

JavaScriptParser::ArrayLiteralExpressionContext::ArrayLiteralExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::ArrayLiteralExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayLiteralExpression(this);
}
void JavaScriptParser::ArrayLiteralExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayLiteralExpression(this);
}

antlrcpp::Any JavaScriptParser::ArrayLiteralExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitArrayLiteralExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MemberDotExpressionContext ------------------------------------------------------------------

JavaScriptParser::SingleExpressionContext* JavaScriptParser::MemberDotExpressionContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::MemberDotExpressionContext::Dot() {
  return getToken(JavaScriptParser::Dot, 0);
}

JavaScriptParser::IdentifierNameContext* JavaScriptParser::MemberDotExpressionContext::identifierName() {
  return getRuleContext<JavaScriptParser::IdentifierNameContext>(0);
}

tree::TerminalNode* JavaScriptParser::MemberDotExpressionContext::QuestionMark() {
  return getToken(JavaScriptParser::QuestionMark, 0);
}

tree::TerminalNode* JavaScriptParser::MemberDotExpressionContext::Hashtag() {
  return getToken(JavaScriptParser::Hashtag, 0);
}

JavaScriptParser::MemberDotExpressionContext::MemberDotExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::MemberDotExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMemberDotExpression(this);
}
void JavaScriptParser::MemberDotExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMemberDotExpression(this);
}

antlrcpp::Any JavaScriptParser::MemberDotExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitMemberDotExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ClassExpressionContext ------------------------------------------------------------------

tree::TerminalNode* JavaScriptParser::ClassExpressionContext::Class() {
  return getToken(JavaScriptParser::Class, 0);
}

JavaScriptParser::ClassTailContext* JavaScriptParser::ClassExpressionContext::classTail() {
  return getRuleContext<JavaScriptParser::ClassTailContext>(0);
}

JavaScriptParser::IdentifierContext* JavaScriptParser::ClassExpressionContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}

JavaScriptParser::ClassExpressionContext::ClassExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::ClassExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassExpression(this);
}
void JavaScriptParser::ClassExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassExpression(this);
}

antlrcpp::Any JavaScriptParser::ClassExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitClassExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MemberIndexExpressionContext ------------------------------------------------------------------

JavaScriptParser::SingleExpressionContext* JavaScriptParser::MemberIndexExpressionContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::MemberIndexExpressionContext::OpenBracket() {
  return getToken(JavaScriptParser::OpenBracket, 0);
}

JavaScriptParser::ExpressionSequenceContext* JavaScriptParser::MemberIndexExpressionContext::expressionSequence() {
  return getRuleContext<JavaScriptParser::ExpressionSequenceContext>(0);
}

tree::TerminalNode* JavaScriptParser::MemberIndexExpressionContext::CloseBracket() {
  return getToken(JavaScriptParser::CloseBracket, 0);
}

JavaScriptParser::MemberIndexExpressionContext::MemberIndexExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::MemberIndexExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMemberIndexExpression(this);
}
void JavaScriptParser::MemberIndexExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMemberIndexExpression(this);
}

antlrcpp::Any JavaScriptParser::MemberIndexExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitMemberIndexExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IdentifierExpressionContext ------------------------------------------------------------------

JavaScriptParser::IdentifierContext* JavaScriptParser::IdentifierExpressionContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}

JavaScriptParser::IdentifierExpressionContext::IdentifierExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::IdentifierExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifierExpression(this);
}
void JavaScriptParser::IdentifierExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifierExpression(this);
}

antlrcpp::Any JavaScriptParser::IdentifierExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitIdentifierExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BitAndExpressionContext ------------------------------------------------------------------

std::vector<JavaScriptParser::SingleExpressionContext *> JavaScriptParser::BitAndExpressionContext::singleExpression() {
  return getRuleContexts<JavaScriptParser::SingleExpressionContext>();
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::BitAndExpressionContext::singleExpression(size_t i) {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(i);
}

tree::TerminalNode* JavaScriptParser::BitAndExpressionContext::BitAnd() {
  return getToken(JavaScriptParser::BitAnd, 0);
}

JavaScriptParser::BitAndExpressionContext::BitAndExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::BitAndExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitAndExpression(this);
}
void JavaScriptParser::BitAndExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitAndExpression(this);
}

antlrcpp::Any JavaScriptParser::BitAndExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitBitAndExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BitOrExpressionContext ------------------------------------------------------------------

std::vector<JavaScriptParser::SingleExpressionContext *> JavaScriptParser::BitOrExpressionContext::singleExpression() {
  return getRuleContexts<JavaScriptParser::SingleExpressionContext>();
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::BitOrExpressionContext::singleExpression(size_t i) {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(i);
}

tree::TerminalNode* JavaScriptParser::BitOrExpressionContext::BitOr() {
  return getToken(JavaScriptParser::BitOr, 0);
}

JavaScriptParser::BitOrExpressionContext::BitOrExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::BitOrExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitOrExpression(this);
}
void JavaScriptParser::BitOrExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitOrExpression(this);
}

antlrcpp::Any JavaScriptParser::BitOrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitBitOrExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignmentOperatorExpressionContext ------------------------------------------------------------------

std::vector<JavaScriptParser::SingleExpressionContext *> JavaScriptParser::AssignmentOperatorExpressionContext::singleExpression() {
  return getRuleContexts<JavaScriptParser::SingleExpressionContext>();
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::AssignmentOperatorExpressionContext::singleExpression(size_t i) {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(i);
}

JavaScriptParser::AssignmentOperatorContext* JavaScriptParser::AssignmentOperatorExpressionContext::assignmentOperator() {
  return getRuleContext<JavaScriptParser::AssignmentOperatorContext>(0);
}

JavaScriptParser::AssignmentOperatorExpressionContext::AssignmentOperatorExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::AssignmentOperatorExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignmentOperatorExpression(this);
}
void JavaScriptParser::AssignmentOperatorExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignmentOperatorExpression(this);
}

antlrcpp::Any JavaScriptParser::AssignmentOperatorExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitAssignmentOperatorExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VoidExpressionContext ------------------------------------------------------------------

tree::TerminalNode* JavaScriptParser::VoidExpressionContext::Void() {
  return getToken(JavaScriptParser::Void, 0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::VoidExpressionContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

JavaScriptParser::VoidExpressionContext::VoidExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::VoidExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVoidExpression(this);
}
void JavaScriptParser::VoidExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVoidExpression(this);
}

antlrcpp::Any JavaScriptParser::VoidExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitVoidExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CoalesceExpressionContext ------------------------------------------------------------------

std::vector<JavaScriptParser::SingleExpressionContext *> JavaScriptParser::CoalesceExpressionContext::singleExpression() {
  return getRuleContexts<JavaScriptParser::SingleExpressionContext>();
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::CoalesceExpressionContext::singleExpression(size_t i) {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(i);
}

tree::TerminalNode* JavaScriptParser::CoalesceExpressionContext::NullCoalesce() {
  return getToken(JavaScriptParser::NullCoalesce, 0);
}

JavaScriptParser::CoalesceExpressionContext::CoalesceExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::CoalesceExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCoalesceExpression(this);
}
void JavaScriptParser::CoalesceExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCoalesceExpression(this);
}

antlrcpp::Any JavaScriptParser::CoalesceExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitCoalesceExpression(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::singleExpression() {
   return singleExpression(0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::singleExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  JavaScriptParser::SingleExpressionContext *_localctx = _tracker.createInstance<SingleExpressionContext>(_ctx, parentState);
  JavaScriptParser::SingleExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 114;
  enterRecursionRule(_localctx, 114, JavaScriptParser::RuleSingleExpression, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(780);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 88, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<FunctionExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(729);
      anonymousFunction();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ClassExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(730);
      match(JavaScriptParser::Class);
      setState(732);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 106) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 106)) & ((1ULL << (JavaScriptParser::Async - 106))
        | (1ULL << (JavaScriptParser::NonStrictLet - 106))
        | (1ULL << (JavaScriptParser::Identifier - 106)))) != 0)) {
        setState(731);
        identifier();
      }
      setState(734);
      classTail();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<NewExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(735);
      match(JavaScriptParser::New);
      setState(736);
      singleExpression(0);
      setState(737);
      arguments();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<NewExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(739);
      match(JavaScriptParser::New);
      setState(740);
      singleExpression(42);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<MetaExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(741);
      match(JavaScriptParser::New);
      setState(742);
      match(JavaScriptParser::Dot);
      setState(743);
      identifier();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<DeleteExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(744);
      match(JavaScriptParser::Delete);
      setState(745);
      singleExpression(37);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<VoidExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(746);
      match(JavaScriptParser::Void);
      setState(747);
      singleExpression(36);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<TypeofExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(748);
      match(JavaScriptParser::Typeof);
      setState(749);
      singleExpression(35);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<PreIncrementExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(750);
      match(JavaScriptParser::PlusPlus);
      setState(751);
      singleExpression(34);
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<PreDecreaseExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(752);
      match(JavaScriptParser::MinusMinus);
      setState(753);
      singleExpression(33);
      break;
    }

    case 11: {
      _localctx = _tracker.createInstance<UnaryPlusExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(754);
      match(JavaScriptParser::Plus);
      setState(755);
      singleExpression(32);
      break;
    }

    case 12: {
      _localctx = _tracker.createInstance<UnaryMinusExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(756);
      match(JavaScriptParser::Minus);
      setState(757);
      singleExpression(31);
      break;
    }

    case 13: {
      _localctx = _tracker.createInstance<BitNotExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(758);
      match(JavaScriptParser::BitNot);
      setState(759);
      singleExpression(30);
      break;
    }

    case 14: {
      _localctx = _tracker.createInstance<NotExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(760);
      match(JavaScriptParser::Not);
      setState(761);
      singleExpression(29);
      break;
    }

    case 15: {
      _localctx = _tracker.createInstance<AwaitExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(762);
      match(JavaScriptParser::Await);
      setState(763);
      singleExpression(28);
      break;
    }

    case 16: {
      _localctx = _tracker.createInstance<ImportExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(764);
      match(JavaScriptParser::Import);
      setState(765);
      match(JavaScriptParser::OpenParen);
      setState(766);
      singleExpression(0);
      setState(767);
      match(JavaScriptParser::CloseParen);
      break;
    }

    case 17: {
      _localctx = _tracker.createInstance<YieldExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(769);
      yieldStatement();
      break;
    }

    case 18: {
      _localctx = _tracker.createInstance<ThisExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(770);
      match(JavaScriptParser::This);
      break;
    }

    case 19: {
      _localctx = _tracker.createInstance<IdentifierExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(771);
      identifier();
      break;
    }

    case 20: {
      _localctx = _tracker.createInstance<SuperExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(772);
      match(JavaScriptParser::Super);
      break;
    }

    case 21: {
      _localctx = _tracker.createInstance<LiteralExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(773);
      literal();
      break;
    }

    case 22: {
      _localctx = _tracker.createInstance<ArrayLiteralExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(774);
      arrayLiteral();
      break;
    }

    case 23: {
      _localctx = _tracker.createInstance<ObjectLiteralExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(775);
      objectLiteral();
      break;
    }

    case 24: {
      _localctx = _tracker.createInstance<ParenthesizedExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(776);
      match(JavaScriptParser::OpenParen);
      setState(777);
      expressionSequence();
      setState(778);
      match(JavaScriptParser::CloseParen);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(863);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 92, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(861);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 91, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<PowerExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(782);

          if (!(precpred(_ctx, 27))) throw FailedPredicateException(this, "precpred(_ctx, 27)");
          setState(783);
          match(JavaScriptParser::Power);
          setState(784);
          singleExpression(27);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<MultiplicativeExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(785);

          if (!(precpred(_ctx, 26))) throw FailedPredicateException(this, "precpred(_ctx, 26)");
          setState(786);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << JavaScriptParser::Multiply)
            | (1ULL << JavaScriptParser::Divide)
            | (1ULL << JavaScriptParser::Modulus))) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(787);
          singleExpression(27);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<AdditiveExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(788);

          if (!(precpred(_ctx, 25))) throw FailedPredicateException(this, "precpred(_ctx, 25)");
          setState(789);
          _la = _input->LA(1);
          if (!(_la == JavaScriptParser::Plus

          || _la == JavaScriptParser::Minus)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(790);
          singleExpression(26);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<CoalesceExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(791);

          if (!(precpred(_ctx, 24))) throw FailedPredicateException(this, "precpred(_ctx, 24)");
          setState(792);
          match(JavaScriptParser::NullCoalesce);
          setState(793);
          singleExpression(25);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<BitShiftExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(794);

          if (!(precpred(_ctx, 23))) throw FailedPredicateException(this, "precpred(_ctx, 23)");
          setState(795);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << JavaScriptParser::RightShiftArithmetic)
            | (1ULL << JavaScriptParser::LeftShiftArithmetic)
            | (1ULL << JavaScriptParser::RightShiftLogical))) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(796);
          singleExpression(24);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<RelationalExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(797);

          if (!(precpred(_ctx, 22))) throw FailedPredicateException(this, "precpred(_ctx, 22)");
          setState(798);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << JavaScriptParser::LessThan)
            | (1ULL << JavaScriptParser::MoreThan)
            | (1ULL << JavaScriptParser::LessThanEquals)
            | (1ULL << JavaScriptParser::GreaterThanEquals))) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(799);
          singleExpression(23);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<InstanceofExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(800);

          if (!(precpred(_ctx, 21))) throw FailedPredicateException(this, "precpred(_ctx, 21)");
          setState(801);
          match(JavaScriptParser::Instanceof);
          setState(802);
          singleExpression(22);
          break;
        }

        case 8: {
          auto newContext = _tracker.createInstance<InExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(803);

          if (!(precpred(_ctx, 20))) throw FailedPredicateException(this, "precpred(_ctx, 20)");
          setState(804);
          match(JavaScriptParser::In);
          setState(805);
          singleExpression(21);
          break;
        }

        case 9: {
          auto newContext = _tracker.createInstance<EqualityExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(806);

          if (!(precpred(_ctx, 19))) throw FailedPredicateException(this, "precpred(_ctx, 19)");
          setState(807);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << JavaScriptParser::Equals_)
            | (1ULL << JavaScriptParser::NotEquals)
            | (1ULL << JavaScriptParser::IdentityEquals)
            | (1ULL << JavaScriptParser::IdentityNotEquals))) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(808);
          singleExpression(20);
          break;
        }

        case 10: {
          auto newContext = _tracker.createInstance<BitAndExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(809);

          if (!(precpred(_ctx, 18))) throw FailedPredicateException(this, "precpred(_ctx, 18)");
          setState(810);
          match(JavaScriptParser::BitAnd);
          setState(811);
          singleExpression(19);
          break;
        }

        case 11: {
          auto newContext = _tracker.createInstance<BitXOrExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(812);

          if (!(precpred(_ctx, 17))) throw FailedPredicateException(this, "precpred(_ctx, 17)");
          setState(813);
          match(JavaScriptParser::BitXOr);
          setState(814);
          singleExpression(18);
          break;
        }

        case 12: {
          auto newContext = _tracker.createInstance<BitOrExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(815);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(816);
          match(JavaScriptParser::BitOr);
          setState(817);
          singleExpression(17);
          break;
        }

        case 13: {
          auto newContext = _tracker.createInstance<LogicalAndExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(818);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(819);
          match(JavaScriptParser::And);
          setState(820);
          singleExpression(16);
          break;
        }

        case 14: {
          auto newContext = _tracker.createInstance<LogicalOrExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(821);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(822);
          match(JavaScriptParser::Or);
          setState(823);
          singleExpression(15);
          break;
        }

        case 15: {
          auto newContext = _tracker.createInstance<TernaryExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(824);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(825);
          match(JavaScriptParser::QuestionMark);
          setState(826);
          singleExpression(0);
          setState(827);
          match(JavaScriptParser::Colon);
          setState(828);
          singleExpression(14);
          break;
        }

        case 16: {
          auto newContext = _tracker.createInstance<AssignmentExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(830);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(831);
          match(JavaScriptParser::Assign);
          setState(832);
          singleExpression(12);
          break;
        }

        case 17: {
          auto newContext = _tracker.createInstance<AssignmentOperatorExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(833);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(834);
          assignmentOperator();
          setState(835);
          singleExpression(11);
          break;
        }

        case 18: {
          auto newContext = _tracker.createInstance<MemberIndexExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(837);

          if (!(precpred(_ctx, 45))) throw FailedPredicateException(this, "precpred(_ctx, 45)");
          setState(838);
          match(JavaScriptParser::OpenBracket);
          setState(839);
          expressionSequence();
          setState(840);
          match(JavaScriptParser::CloseBracket);
          break;
        }

        case 19: {
          auto newContext = _tracker.createInstance<MemberDotExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(842);

          if (!(precpred(_ctx, 44))) throw FailedPredicateException(this, "precpred(_ctx, 44)");
          setState(844);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == JavaScriptParser::QuestionMark) {
            setState(843);
            match(JavaScriptParser::QuestionMark);
          }
          setState(846);
          match(JavaScriptParser::Dot);
          setState(848);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == JavaScriptParser::Hashtag) {
            setState(847);
            match(JavaScriptParser::Hashtag);
          }
          setState(850);
          identifierName();
          break;
        }

        case 20: {
          auto newContext = _tracker.createInstance<ArgumentsExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(851);

          if (!(precpred(_ctx, 41))) throw FailedPredicateException(this, "precpred(_ctx, 41)");
          setState(852);
          arguments();
          break;
        }

        case 21: {
          auto newContext = _tracker.createInstance<PostIncrementExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(853);

          if (!(precpred(_ctx, 39))) throw FailedPredicateException(this, "precpred(_ctx, 39)");
          setState(854);

          if (!(this->notLineTerminator())) throw FailedPredicateException(this, "this->notLineTerminator()");
          setState(855);
          match(JavaScriptParser::PlusPlus);
          break;
        }

        case 22: {
          auto newContext = _tracker.createInstance<PostDecreaseExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(856);

          if (!(precpred(_ctx, 38))) throw FailedPredicateException(this, "precpred(_ctx, 38)");
          setState(857);

          if (!(this->notLineTerminator())) throw FailedPredicateException(this, "this->notLineTerminator()");
          setState(858);
          match(JavaScriptParser::MinusMinus);
          break;
        }

        case 23: {
          auto newContext = _tracker.createInstance<TemplateStringExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(859);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(860);
          templateStringLiteral();
          break;
        }

        default:
          break;
        } 
      }
      setState(865);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 92, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- AssignableContext ------------------------------------------------------------------

JavaScriptParser::AssignableContext::AssignableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::IdentifierContext* JavaScriptParser::AssignableContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}

JavaScriptParser::ArrayLiteralContext* JavaScriptParser::AssignableContext::arrayLiteral() {
  return getRuleContext<JavaScriptParser::ArrayLiteralContext>(0);
}

JavaScriptParser::ObjectLiteralContext* JavaScriptParser::AssignableContext::objectLiteral() {
  return getRuleContext<JavaScriptParser::ObjectLiteralContext>(0);
}


size_t JavaScriptParser::AssignableContext::getRuleIndex() const {
  return JavaScriptParser::RuleAssignable;
}

void JavaScriptParser::AssignableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignable(this);
}

void JavaScriptParser::AssignableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignable(this);
}


antlrcpp::Any JavaScriptParser::AssignableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitAssignable(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::AssignableContext* JavaScriptParser::assignable() {
  AssignableContext *_localctx = _tracker.createInstance<AssignableContext>(_ctx, getState());
  enterRule(_localctx, 116, JavaScriptParser::RuleAssignable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(869);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::Async:
      case JavaScriptParser::NonStrictLet:
      case JavaScriptParser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(866);
        identifier();
        break;
      }

      case JavaScriptParser::OpenBracket: {
        enterOuterAlt(_localctx, 2);
        setState(867);
        arrayLiteral();
        break;
      }

      case JavaScriptParser::OpenBrace: {
        enterOuterAlt(_localctx, 3);
        setState(868);
        objectLiteral();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ObjectLiteralContext ------------------------------------------------------------------

JavaScriptParser::ObjectLiteralContext::ObjectLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::ObjectLiteralContext::OpenBrace() {
  return getToken(JavaScriptParser::OpenBrace, 0);
}

tree::TerminalNode* JavaScriptParser::ObjectLiteralContext::CloseBrace() {
  return getToken(JavaScriptParser::CloseBrace, 0);
}

std::vector<JavaScriptParser::PropertyAssignmentContext *> JavaScriptParser::ObjectLiteralContext::propertyAssignment() {
  return getRuleContexts<JavaScriptParser::PropertyAssignmentContext>();
}

JavaScriptParser::PropertyAssignmentContext* JavaScriptParser::ObjectLiteralContext::propertyAssignment(size_t i) {
  return getRuleContext<JavaScriptParser::PropertyAssignmentContext>(i);
}

std::vector<tree::TerminalNode *> JavaScriptParser::ObjectLiteralContext::Comma() {
  return getTokens(JavaScriptParser::Comma);
}

tree::TerminalNode* JavaScriptParser::ObjectLiteralContext::Comma(size_t i) {
  return getToken(JavaScriptParser::Comma, i);
}


size_t JavaScriptParser::ObjectLiteralContext::getRuleIndex() const {
  return JavaScriptParser::RuleObjectLiteral;
}

void JavaScriptParser::ObjectLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterObjectLiteral(this);
}

void JavaScriptParser::ObjectLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitObjectLiteral(this);
}


antlrcpp::Any JavaScriptParser::ObjectLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitObjectLiteral(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ObjectLiteralContext* JavaScriptParser::objectLiteral() {
  ObjectLiteralContext *_localctx = _tracker.createInstance<ObjectLiteralContext>(_ctx, getState());
  enterRule(_localctx, 118, JavaScriptParser::RuleObjectLiteral);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(871);
    match(JavaScriptParser::OpenBrace);
    setState(883);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 96, _ctx)) {
    case 1: {
      setState(872);
      propertyAssignment();
      setState(877);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 94, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(873);
          match(JavaScriptParser::Comma);
          setState(874);
          propertyAssignment(); 
        }
        setState(879);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 94, _ctx);
      }
      setState(881);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == JavaScriptParser::Comma) {
        setState(880);
        match(JavaScriptParser::Comma);
      }
      break;
    }

    default:
      break;
    }
    setState(885);
    match(JavaScriptParser::CloseBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AnonymousFunctionContext ------------------------------------------------------------------

JavaScriptParser::AnonymousFunctionContext::AnonymousFunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t JavaScriptParser::AnonymousFunctionContext::getRuleIndex() const {
  return JavaScriptParser::RuleAnonymousFunction;
}

void JavaScriptParser::AnonymousFunctionContext::copyFrom(AnonymousFunctionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- AnonymousFunctionDeclContext ------------------------------------------------------------------

tree::TerminalNode* JavaScriptParser::AnonymousFunctionDeclContext::Function_() {
  return getToken(JavaScriptParser::Function_, 0);
}

tree::TerminalNode* JavaScriptParser::AnonymousFunctionDeclContext::OpenParen() {
  return getToken(JavaScriptParser::OpenParen, 0);
}

tree::TerminalNode* JavaScriptParser::AnonymousFunctionDeclContext::CloseParen() {
  return getToken(JavaScriptParser::CloseParen, 0);
}

JavaScriptParser::FunctionBodyContext* JavaScriptParser::AnonymousFunctionDeclContext::functionBody() {
  return getRuleContext<JavaScriptParser::FunctionBodyContext>(0);
}

tree::TerminalNode* JavaScriptParser::AnonymousFunctionDeclContext::Async() {
  return getToken(JavaScriptParser::Async, 0);
}

tree::TerminalNode* JavaScriptParser::AnonymousFunctionDeclContext::Multiply() {
  return getToken(JavaScriptParser::Multiply, 0);
}

JavaScriptParser::FormalParameterListContext* JavaScriptParser::AnonymousFunctionDeclContext::formalParameterList() {
  return getRuleContext<JavaScriptParser::FormalParameterListContext>(0);
}

JavaScriptParser::AnonymousFunctionDeclContext::AnonymousFunctionDeclContext(AnonymousFunctionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::AnonymousFunctionDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAnonymousFunctionDecl(this);
}
void JavaScriptParser::AnonymousFunctionDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAnonymousFunctionDecl(this);
}

antlrcpp::Any JavaScriptParser::AnonymousFunctionDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitAnonymousFunctionDecl(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArrowFunctionContext ------------------------------------------------------------------

JavaScriptParser::ArrowFunctionParametersContext* JavaScriptParser::ArrowFunctionContext::arrowFunctionParameters() {
  return getRuleContext<JavaScriptParser::ArrowFunctionParametersContext>(0);
}

tree::TerminalNode* JavaScriptParser::ArrowFunctionContext::ARROW() {
  return getToken(JavaScriptParser::ARROW, 0);
}

JavaScriptParser::ArrowFunctionBodyContext* JavaScriptParser::ArrowFunctionContext::arrowFunctionBody() {
  return getRuleContext<JavaScriptParser::ArrowFunctionBodyContext>(0);
}

tree::TerminalNode* JavaScriptParser::ArrowFunctionContext::Async() {
  return getToken(JavaScriptParser::Async, 0);
}

JavaScriptParser::ArrowFunctionContext::ArrowFunctionContext(AnonymousFunctionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::ArrowFunctionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrowFunction(this);
}
void JavaScriptParser::ArrowFunctionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrowFunction(this);
}

antlrcpp::Any JavaScriptParser::ArrowFunctionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitArrowFunction(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FunctionDeclContext ------------------------------------------------------------------

JavaScriptParser::FunctionDeclarationContext* JavaScriptParser::FunctionDeclContext::functionDeclaration() {
  return getRuleContext<JavaScriptParser::FunctionDeclarationContext>(0);
}

JavaScriptParser::FunctionDeclContext::FunctionDeclContext(AnonymousFunctionContext *ctx) { copyFrom(ctx); }

void JavaScriptParser::FunctionDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionDecl(this);
}
void JavaScriptParser::FunctionDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionDecl(this);
}

antlrcpp::Any JavaScriptParser::FunctionDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitFunctionDecl(this);
  else
    return visitor->visitChildren(this);
}
JavaScriptParser::AnonymousFunctionContext* JavaScriptParser::anonymousFunction() {
  AnonymousFunctionContext *_localctx = _tracker.createInstance<AnonymousFunctionContext>(_ctx, getState());
  enterRule(_localctx, 120, JavaScriptParser::RuleAnonymousFunction);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(908);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 101, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<JavaScriptParser::FunctionDeclContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(887);
      functionDeclaration();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<JavaScriptParser::AnonymousFunctionDeclContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(889);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == JavaScriptParser::Async) {
        setState(888);
        match(JavaScriptParser::Async);
      }
      setState(891);
      match(JavaScriptParser::Function_);
      setState(893);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == JavaScriptParser::Multiply) {
        setState(892);
        match(JavaScriptParser::Multiply);
      }
      setState(895);
      match(JavaScriptParser::OpenParen);
      setState(897);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << JavaScriptParser::OpenBracket)
        | (1ULL << JavaScriptParser::OpenBrace)
        | (1ULL << JavaScriptParser::Ellipsis))) != 0) || ((((_la - 106) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 106)) & ((1ULL << (JavaScriptParser::Async - 106))
        | (1ULL << (JavaScriptParser::NonStrictLet - 106))
        | (1ULL << (JavaScriptParser::Identifier - 106)))) != 0)) {
        setState(896);
        formalParameterList();
      }
      setState(899);
      match(JavaScriptParser::CloseParen);
      setState(900);
      functionBody();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<JavaScriptParser::ArrowFunctionContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(902);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 100, _ctx)) {
      case 1: {
        setState(901);
        match(JavaScriptParser::Async);
        break;
      }

      default:
        break;
      }
      setState(904);
      arrowFunctionParameters();
      setState(905);
      match(JavaScriptParser::ARROW);
      setState(906);
      arrowFunctionBody();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrowFunctionParametersContext ------------------------------------------------------------------

JavaScriptParser::ArrowFunctionParametersContext::ArrowFunctionParametersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::IdentifierContext* JavaScriptParser::ArrowFunctionParametersContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}

tree::TerminalNode* JavaScriptParser::ArrowFunctionParametersContext::OpenParen() {
  return getToken(JavaScriptParser::OpenParen, 0);
}

tree::TerminalNode* JavaScriptParser::ArrowFunctionParametersContext::CloseParen() {
  return getToken(JavaScriptParser::CloseParen, 0);
}

JavaScriptParser::FormalParameterListContext* JavaScriptParser::ArrowFunctionParametersContext::formalParameterList() {
  return getRuleContext<JavaScriptParser::FormalParameterListContext>(0);
}


size_t JavaScriptParser::ArrowFunctionParametersContext::getRuleIndex() const {
  return JavaScriptParser::RuleArrowFunctionParameters;
}

void JavaScriptParser::ArrowFunctionParametersContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrowFunctionParameters(this);
}

void JavaScriptParser::ArrowFunctionParametersContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrowFunctionParameters(this);
}


antlrcpp::Any JavaScriptParser::ArrowFunctionParametersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitArrowFunctionParameters(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ArrowFunctionParametersContext* JavaScriptParser::arrowFunctionParameters() {
  ArrowFunctionParametersContext *_localctx = _tracker.createInstance<ArrowFunctionParametersContext>(_ctx, getState());
  enterRule(_localctx, 122, JavaScriptParser::RuleArrowFunctionParameters);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(916);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::Async:
      case JavaScriptParser::NonStrictLet:
      case JavaScriptParser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(910);
        identifier();
        break;
      }

      case JavaScriptParser::OpenParen: {
        enterOuterAlt(_localctx, 2);
        setState(911);
        match(JavaScriptParser::OpenParen);
        setState(913);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << JavaScriptParser::OpenBracket)
          | (1ULL << JavaScriptParser::OpenBrace)
          | (1ULL << JavaScriptParser::Ellipsis))) != 0) || ((((_la - 106) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 106)) & ((1ULL << (JavaScriptParser::Async - 106))
          | (1ULL << (JavaScriptParser::NonStrictLet - 106))
          | (1ULL << (JavaScriptParser::Identifier - 106)))) != 0)) {
          setState(912);
          formalParameterList();
        }
        setState(915);
        match(JavaScriptParser::CloseParen);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrowFunctionBodyContext ------------------------------------------------------------------

JavaScriptParser::ArrowFunctionBodyContext::ArrowFunctionBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::ArrowFunctionBodyContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

JavaScriptParser::FunctionBodyContext* JavaScriptParser::ArrowFunctionBodyContext::functionBody() {
  return getRuleContext<JavaScriptParser::FunctionBodyContext>(0);
}


size_t JavaScriptParser::ArrowFunctionBodyContext::getRuleIndex() const {
  return JavaScriptParser::RuleArrowFunctionBody;
}

void JavaScriptParser::ArrowFunctionBodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrowFunctionBody(this);
}

void JavaScriptParser::ArrowFunctionBodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrowFunctionBody(this);
}


antlrcpp::Any JavaScriptParser::ArrowFunctionBodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitArrowFunctionBody(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ArrowFunctionBodyContext* JavaScriptParser::arrowFunctionBody() {
  ArrowFunctionBodyContext *_localctx = _tracker.createInstance<ArrowFunctionBodyContext>(_ctx, getState());
  enterRule(_localctx, 124, JavaScriptParser::RuleArrowFunctionBody);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(920);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 104, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(918);
      singleExpression(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(919);
      functionBody();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentOperatorContext ------------------------------------------------------------------

JavaScriptParser::AssignmentOperatorContext::AssignmentOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::MultiplyAssign() {
  return getToken(JavaScriptParser::MultiplyAssign, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::DivideAssign() {
  return getToken(JavaScriptParser::DivideAssign, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::ModulusAssign() {
  return getToken(JavaScriptParser::ModulusAssign, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::PlusAssign() {
  return getToken(JavaScriptParser::PlusAssign, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::MinusAssign() {
  return getToken(JavaScriptParser::MinusAssign, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::LeftShiftArithmeticAssign() {
  return getToken(JavaScriptParser::LeftShiftArithmeticAssign, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::RightShiftArithmeticAssign() {
  return getToken(JavaScriptParser::RightShiftArithmeticAssign, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::RightShiftLogicalAssign() {
  return getToken(JavaScriptParser::RightShiftLogicalAssign, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::BitAndAssign() {
  return getToken(JavaScriptParser::BitAndAssign, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::BitXorAssign() {
  return getToken(JavaScriptParser::BitXorAssign, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::BitOrAssign() {
  return getToken(JavaScriptParser::BitOrAssign, 0);
}

tree::TerminalNode* JavaScriptParser::AssignmentOperatorContext::PowerAssign() {
  return getToken(JavaScriptParser::PowerAssign, 0);
}


size_t JavaScriptParser::AssignmentOperatorContext::getRuleIndex() const {
  return JavaScriptParser::RuleAssignmentOperator;
}

void JavaScriptParser::AssignmentOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignmentOperator(this);
}

void JavaScriptParser::AssignmentOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignmentOperator(this);
}


antlrcpp::Any JavaScriptParser::AssignmentOperatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitAssignmentOperator(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::AssignmentOperatorContext* JavaScriptParser::assignmentOperator() {
  AssignmentOperatorContext *_localctx = _tracker.createInstance<AssignmentOperatorContext>(_ctx, getState());
  enterRule(_localctx, 126, JavaScriptParser::RuleAssignmentOperator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(922);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << JavaScriptParser::MultiplyAssign)
      | (1ULL << JavaScriptParser::DivideAssign)
      | (1ULL << JavaScriptParser::ModulusAssign)
      | (1ULL << JavaScriptParser::PlusAssign)
      | (1ULL << JavaScriptParser::MinusAssign)
      | (1ULL << JavaScriptParser::LeftShiftArithmeticAssign)
      | (1ULL << JavaScriptParser::RightShiftArithmeticAssign)
      | (1ULL << JavaScriptParser::RightShiftLogicalAssign)
      | (1ULL << JavaScriptParser::BitAndAssign)
      | (1ULL << JavaScriptParser::BitXorAssign)
      | (1ULL << JavaScriptParser::BitOrAssign)
      | (1ULL << JavaScriptParser::PowerAssign))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralContext ------------------------------------------------------------------

JavaScriptParser::LiteralContext::LiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::LiteralContext::NullLiteral() {
  return getToken(JavaScriptParser::NullLiteral, 0);
}

tree::TerminalNode* JavaScriptParser::LiteralContext::BooleanLiteral() {
  return getToken(JavaScriptParser::BooleanLiteral, 0);
}

tree::TerminalNode* JavaScriptParser::LiteralContext::StringLiteral() {
  return getToken(JavaScriptParser::StringLiteral, 0);
}

JavaScriptParser::TemplateStringLiteralContext* JavaScriptParser::LiteralContext::templateStringLiteral() {
  return getRuleContext<JavaScriptParser::TemplateStringLiteralContext>(0);
}

tree::TerminalNode* JavaScriptParser::LiteralContext::RegularExpressionLiteral() {
  return getToken(JavaScriptParser::RegularExpressionLiteral, 0);
}

JavaScriptParser::NumericLiteralContext* JavaScriptParser::LiteralContext::numericLiteral() {
  return getRuleContext<JavaScriptParser::NumericLiteralContext>(0);
}

JavaScriptParser::BigintLiteralContext* JavaScriptParser::LiteralContext::bigintLiteral() {
  return getRuleContext<JavaScriptParser::BigintLiteralContext>(0);
}


size_t JavaScriptParser::LiteralContext::getRuleIndex() const {
  return JavaScriptParser::RuleLiteral;
}

void JavaScriptParser::LiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLiteral(this);
}

void JavaScriptParser::LiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLiteral(this);
}


antlrcpp::Any JavaScriptParser::LiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitLiteral(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::LiteralContext* JavaScriptParser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 128, JavaScriptParser::RuleLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(931);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::NullLiteral: {
        enterOuterAlt(_localctx, 1);
        setState(924);
        match(JavaScriptParser::NullLiteral);
        break;
      }

      case JavaScriptParser::BooleanLiteral: {
        enterOuterAlt(_localctx, 2);
        setState(925);
        match(JavaScriptParser::BooleanLiteral);
        break;
      }

      case JavaScriptParser::StringLiteral: {
        enterOuterAlt(_localctx, 3);
        setState(926);
        match(JavaScriptParser::StringLiteral);
        break;
      }

      case JavaScriptParser::BackTick: {
        enterOuterAlt(_localctx, 4);
        setState(927);
        templateStringLiteral();
        break;
      }

      case JavaScriptParser::RegularExpressionLiteral: {
        enterOuterAlt(_localctx, 5);
        setState(928);
        match(JavaScriptParser::RegularExpressionLiteral);
        break;
      }

      case JavaScriptParser::DecimalLiteral:
      case JavaScriptParser::HexIntegerLiteral:
      case JavaScriptParser::OctalIntegerLiteral:
      case JavaScriptParser::OctalIntegerLiteral2:
      case JavaScriptParser::BinaryIntegerLiteral: {
        enterOuterAlt(_localctx, 6);
        setState(929);
        numericLiteral();
        break;
      }

      case JavaScriptParser::BigHexIntegerLiteral:
      case JavaScriptParser::BigOctalIntegerLiteral:
      case JavaScriptParser::BigBinaryIntegerLiteral:
      case JavaScriptParser::BigDecimalIntegerLiteral: {
        enterOuterAlt(_localctx, 7);
        setState(930);
        bigintLiteral();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TemplateStringLiteralContext ------------------------------------------------------------------

JavaScriptParser::TemplateStringLiteralContext::TemplateStringLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> JavaScriptParser::TemplateStringLiteralContext::BackTick() {
  return getTokens(JavaScriptParser::BackTick);
}

tree::TerminalNode* JavaScriptParser::TemplateStringLiteralContext::BackTick(size_t i) {
  return getToken(JavaScriptParser::BackTick, i);
}

std::vector<JavaScriptParser::TemplateStringAtomContext *> JavaScriptParser::TemplateStringLiteralContext::templateStringAtom() {
  return getRuleContexts<JavaScriptParser::TemplateStringAtomContext>();
}

JavaScriptParser::TemplateStringAtomContext* JavaScriptParser::TemplateStringLiteralContext::templateStringAtom(size_t i) {
  return getRuleContext<JavaScriptParser::TemplateStringAtomContext>(i);
}


size_t JavaScriptParser::TemplateStringLiteralContext::getRuleIndex() const {
  return JavaScriptParser::RuleTemplateStringLiteral;
}

void JavaScriptParser::TemplateStringLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTemplateStringLiteral(this);
}

void JavaScriptParser::TemplateStringLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTemplateStringLiteral(this);
}


antlrcpp::Any JavaScriptParser::TemplateStringLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitTemplateStringLiteral(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::TemplateStringLiteralContext* JavaScriptParser::templateStringLiteral() {
  TemplateStringLiteralContext *_localctx = _tracker.createInstance<TemplateStringLiteralContext>(_ctx, getState());
  enterRule(_localctx, 130, JavaScriptParser::RuleTemplateStringLiteral);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(933);
    match(JavaScriptParser::BackTick);
    setState(937);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == JavaScriptParser::TemplateStringStartExpression

    || _la == JavaScriptParser::TemplateStringAtom) {
      setState(934);
      templateStringAtom();
      setState(939);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(940);
    match(JavaScriptParser::BackTick);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TemplateStringAtomContext ------------------------------------------------------------------

JavaScriptParser::TemplateStringAtomContext::TemplateStringAtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::TemplateStringAtomContext::TemplateStringAtom() {
  return getToken(JavaScriptParser::TemplateStringAtom, 0);
}

tree::TerminalNode* JavaScriptParser::TemplateStringAtomContext::TemplateStringStartExpression() {
  return getToken(JavaScriptParser::TemplateStringStartExpression, 0);
}

JavaScriptParser::SingleExpressionContext* JavaScriptParser::TemplateStringAtomContext::singleExpression() {
  return getRuleContext<JavaScriptParser::SingleExpressionContext>(0);
}

tree::TerminalNode* JavaScriptParser::TemplateStringAtomContext::TemplateCloseBrace() {
  return getToken(JavaScriptParser::TemplateCloseBrace, 0);
}


size_t JavaScriptParser::TemplateStringAtomContext::getRuleIndex() const {
  return JavaScriptParser::RuleTemplateStringAtom;
}

void JavaScriptParser::TemplateStringAtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTemplateStringAtom(this);
}

void JavaScriptParser::TemplateStringAtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTemplateStringAtom(this);
}


antlrcpp::Any JavaScriptParser::TemplateStringAtomContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitTemplateStringAtom(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::TemplateStringAtomContext* JavaScriptParser::templateStringAtom() {
  TemplateStringAtomContext *_localctx = _tracker.createInstance<TemplateStringAtomContext>(_ctx, getState());
  enterRule(_localctx, 132, JavaScriptParser::RuleTemplateStringAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(947);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::TemplateStringAtom: {
        enterOuterAlt(_localctx, 1);
        setState(942);
        match(JavaScriptParser::TemplateStringAtom);
        break;
      }

      case JavaScriptParser::TemplateStringStartExpression: {
        enterOuterAlt(_localctx, 2);
        setState(943);
        match(JavaScriptParser::TemplateStringStartExpression);
        setState(944);
        singleExpression(0);
        setState(945);
        match(JavaScriptParser::TemplateCloseBrace);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumericLiteralContext ------------------------------------------------------------------

JavaScriptParser::NumericLiteralContext::NumericLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::NumericLiteralContext::DecimalLiteral() {
  return getToken(JavaScriptParser::DecimalLiteral, 0);
}

tree::TerminalNode* JavaScriptParser::NumericLiteralContext::HexIntegerLiteral() {
  return getToken(JavaScriptParser::HexIntegerLiteral, 0);
}

tree::TerminalNode* JavaScriptParser::NumericLiteralContext::OctalIntegerLiteral() {
  return getToken(JavaScriptParser::OctalIntegerLiteral, 0);
}

tree::TerminalNode* JavaScriptParser::NumericLiteralContext::OctalIntegerLiteral2() {
  return getToken(JavaScriptParser::OctalIntegerLiteral2, 0);
}

tree::TerminalNode* JavaScriptParser::NumericLiteralContext::BinaryIntegerLiteral() {
  return getToken(JavaScriptParser::BinaryIntegerLiteral, 0);
}


size_t JavaScriptParser::NumericLiteralContext::getRuleIndex() const {
  return JavaScriptParser::RuleNumericLiteral;
}

void JavaScriptParser::NumericLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumericLiteral(this);
}

void JavaScriptParser::NumericLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumericLiteral(this);
}


antlrcpp::Any JavaScriptParser::NumericLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitNumericLiteral(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::NumericLiteralContext* JavaScriptParser::numericLiteral() {
  NumericLiteralContext *_localctx = _tracker.createInstance<NumericLiteralContext>(_ctx, getState());
  enterRule(_localctx, 134, JavaScriptParser::RuleNumericLiteral);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(949);
    _la = _input->LA(1);
    if (!(((((_la - 62) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 62)) & ((1ULL << (JavaScriptParser::DecimalLiteral - 62))
      | (1ULL << (JavaScriptParser::HexIntegerLiteral - 62))
      | (1ULL << (JavaScriptParser::OctalIntegerLiteral - 62))
      | (1ULL << (JavaScriptParser::OctalIntegerLiteral2 - 62))
      | (1ULL << (JavaScriptParser::BinaryIntegerLiteral - 62)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BigintLiteralContext ------------------------------------------------------------------

JavaScriptParser::BigintLiteralContext::BigintLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::BigintLiteralContext::BigDecimalIntegerLiteral() {
  return getToken(JavaScriptParser::BigDecimalIntegerLiteral, 0);
}

tree::TerminalNode* JavaScriptParser::BigintLiteralContext::BigHexIntegerLiteral() {
  return getToken(JavaScriptParser::BigHexIntegerLiteral, 0);
}

tree::TerminalNode* JavaScriptParser::BigintLiteralContext::BigOctalIntegerLiteral() {
  return getToken(JavaScriptParser::BigOctalIntegerLiteral, 0);
}

tree::TerminalNode* JavaScriptParser::BigintLiteralContext::BigBinaryIntegerLiteral() {
  return getToken(JavaScriptParser::BigBinaryIntegerLiteral, 0);
}


size_t JavaScriptParser::BigintLiteralContext::getRuleIndex() const {
  return JavaScriptParser::RuleBigintLiteral;
}

void JavaScriptParser::BigintLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBigintLiteral(this);
}

void JavaScriptParser::BigintLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBigintLiteral(this);
}


antlrcpp::Any JavaScriptParser::BigintLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitBigintLiteral(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::BigintLiteralContext* JavaScriptParser::bigintLiteral() {
  BigintLiteralContext *_localctx = _tracker.createInstance<BigintLiteralContext>(_ctx, getState());
  enterRule(_localctx, 136, JavaScriptParser::RuleBigintLiteral);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(951);
    _la = _input->LA(1);
    if (!(((((_la - 67) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 67)) & ((1ULL << (JavaScriptParser::BigHexIntegerLiteral - 67))
      | (1ULL << (JavaScriptParser::BigOctalIntegerLiteral - 67))
      | (1ULL << (JavaScriptParser::BigBinaryIntegerLiteral - 67))
      | (1ULL << (JavaScriptParser::BigDecimalIntegerLiteral - 67)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GetterContext ------------------------------------------------------------------

JavaScriptParser::GetterContext::GetterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::IdentifierContext* JavaScriptParser::GetterContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}

JavaScriptParser::PropertyNameContext* JavaScriptParser::GetterContext::propertyName() {
  return getRuleContext<JavaScriptParser::PropertyNameContext>(0);
}


size_t JavaScriptParser::GetterContext::getRuleIndex() const {
  return JavaScriptParser::RuleGetter;
}

void JavaScriptParser::GetterContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGetter(this);
}

void JavaScriptParser::GetterContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGetter(this);
}


antlrcpp::Any JavaScriptParser::GetterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitGetter(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::GetterContext* JavaScriptParser::getter() {
  GetterContext *_localctx = _tracker.createInstance<GetterContext>(_ctx, getState());
  enterRule(_localctx, 138, JavaScriptParser::RuleGetter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(953);

    if (!(this->n("get"))) throw FailedPredicateException(this, "this->n(\"get\")");
    setState(954);
    identifier();
    setState(955);
    propertyName();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SetterContext ------------------------------------------------------------------

JavaScriptParser::SetterContext::SetterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::IdentifierContext* JavaScriptParser::SetterContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}

JavaScriptParser::PropertyNameContext* JavaScriptParser::SetterContext::propertyName() {
  return getRuleContext<JavaScriptParser::PropertyNameContext>(0);
}


size_t JavaScriptParser::SetterContext::getRuleIndex() const {
  return JavaScriptParser::RuleSetter;
}

void JavaScriptParser::SetterContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSetter(this);
}

void JavaScriptParser::SetterContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSetter(this);
}


antlrcpp::Any JavaScriptParser::SetterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitSetter(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::SetterContext* JavaScriptParser::setter() {
  SetterContext *_localctx = _tracker.createInstance<SetterContext>(_ctx, getState());
  enterRule(_localctx, 140, JavaScriptParser::RuleSetter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(957);

    if (!(this->n("set"))) throw FailedPredicateException(this, "this->n(\"set\")");
    setState(958);
    identifier();
    setState(959);
    propertyName();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentifierNameContext ------------------------------------------------------------------

JavaScriptParser::IdentifierNameContext::IdentifierNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::IdentifierContext* JavaScriptParser::IdentifierNameContext::identifier() {
  return getRuleContext<JavaScriptParser::IdentifierContext>(0);
}

JavaScriptParser::ReservedWordContext* JavaScriptParser::IdentifierNameContext::reservedWord() {
  return getRuleContext<JavaScriptParser::ReservedWordContext>(0);
}


size_t JavaScriptParser::IdentifierNameContext::getRuleIndex() const {
  return JavaScriptParser::RuleIdentifierName;
}

void JavaScriptParser::IdentifierNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifierName(this);
}

void JavaScriptParser::IdentifierNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifierName(this);
}


antlrcpp::Any JavaScriptParser::IdentifierNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitIdentifierName(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::IdentifierNameContext* JavaScriptParser::identifierName() {
  IdentifierNameContext *_localctx = _tracker.createInstance<IdentifierNameContext>(_ctx, getState());
  enterRule(_localctx, 142, JavaScriptParser::RuleIdentifierName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(963);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 108, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(961);
      identifier();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(962);
      reservedWord();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentifierContext ------------------------------------------------------------------

JavaScriptParser::IdentifierContext::IdentifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::IdentifierContext::Identifier() {
  return getToken(JavaScriptParser::Identifier, 0);
}

tree::TerminalNode* JavaScriptParser::IdentifierContext::NonStrictLet() {
  return getToken(JavaScriptParser::NonStrictLet, 0);
}

tree::TerminalNode* JavaScriptParser::IdentifierContext::Async() {
  return getToken(JavaScriptParser::Async, 0);
}


size_t JavaScriptParser::IdentifierContext::getRuleIndex() const {
  return JavaScriptParser::RuleIdentifier;
}

void JavaScriptParser::IdentifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifier(this);
}

void JavaScriptParser::IdentifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifier(this);
}


antlrcpp::Any JavaScriptParser::IdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitIdentifier(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::IdentifierContext* JavaScriptParser::identifier() {
  IdentifierContext *_localctx = _tracker.createInstance<IdentifierContext>(_ctx, getState());
  enterRule(_localctx, 144, JavaScriptParser::RuleIdentifier);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(965);
    _la = _input->LA(1);
    if (!(((((_la - 106) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 106)) & ((1ULL << (JavaScriptParser::Async - 106))
      | (1ULL << (JavaScriptParser::NonStrictLet - 106))
      | (1ULL << (JavaScriptParser::Identifier - 106)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReservedWordContext ------------------------------------------------------------------

JavaScriptParser::ReservedWordContext::ReservedWordContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

JavaScriptParser::KeywordContext* JavaScriptParser::ReservedWordContext::keyword() {
  return getRuleContext<JavaScriptParser::KeywordContext>(0);
}

tree::TerminalNode* JavaScriptParser::ReservedWordContext::NullLiteral() {
  return getToken(JavaScriptParser::NullLiteral, 0);
}

tree::TerminalNode* JavaScriptParser::ReservedWordContext::BooleanLiteral() {
  return getToken(JavaScriptParser::BooleanLiteral, 0);
}


size_t JavaScriptParser::ReservedWordContext::getRuleIndex() const {
  return JavaScriptParser::RuleReservedWord;
}

void JavaScriptParser::ReservedWordContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReservedWord(this);
}

void JavaScriptParser::ReservedWordContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReservedWord(this);
}


antlrcpp::Any JavaScriptParser::ReservedWordContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitReservedWord(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::ReservedWordContext* JavaScriptParser::reservedWord() {
  ReservedWordContext *_localctx = _tracker.createInstance<ReservedWordContext>(_ctx, getState());
  enterRule(_localctx, 146, JavaScriptParser::RuleReservedWord);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(970);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::Break:
      case JavaScriptParser::Do:
      case JavaScriptParser::Instanceof:
      case JavaScriptParser::Typeof:
      case JavaScriptParser::Case:
      case JavaScriptParser::Else:
      case JavaScriptParser::New:
      case JavaScriptParser::Var:
      case JavaScriptParser::Catch:
      case JavaScriptParser::Finally:
      case JavaScriptParser::Return:
      case JavaScriptParser::Void:
      case JavaScriptParser::Continue:
      case JavaScriptParser::For:
      case JavaScriptParser::Switch:
      case JavaScriptParser::While:
      case JavaScriptParser::Debugger:
      case JavaScriptParser::Function_:
      case JavaScriptParser::This:
      case JavaScriptParser::With:
      case JavaScriptParser::Default:
      case JavaScriptParser::If:
      case JavaScriptParser::Throw:
      case JavaScriptParser::Delete:
      case JavaScriptParser::In:
      case JavaScriptParser::Try:
      case JavaScriptParser::As:
      case JavaScriptParser::From:
      case JavaScriptParser::Class:
      case JavaScriptParser::Enum:
      case JavaScriptParser::Extends:
      case JavaScriptParser::Super:
      case JavaScriptParser::Const:
      case JavaScriptParser::Export:
      case JavaScriptParser::Import:
      case JavaScriptParser::Async:
      case JavaScriptParser::Await:
      case JavaScriptParser::Yield:
      case JavaScriptParser::Implements:
      case JavaScriptParser::StrictLet:
      case JavaScriptParser::NonStrictLet:
      case JavaScriptParser::Private:
      case JavaScriptParser::Public:
      case JavaScriptParser::Interface:
      case JavaScriptParser::Package:
      case JavaScriptParser::Protected:
      case JavaScriptParser::Static: {
        enterOuterAlt(_localctx, 1);
        setState(967);
        keyword();
        break;
      }

      case JavaScriptParser::NullLiteral: {
        enterOuterAlt(_localctx, 2);
        setState(968);
        match(JavaScriptParser::NullLiteral);
        break;
      }

      case JavaScriptParser::BooleanLiteral: {
        enterOuterAlt(_localctx, 3);
        setState(969);
        match(JavaScriptParser::BooleanLiteral);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- KeywordContext ------------------------------------------------------------------

JavaScriptParser::KeywordContext::KeywordContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Break() {
  return getToken(JavaScriptParser::Break, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Do() {
  return getToken(JavaScriptParser::Do, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Instanceof() {
  return getToken(JavaScriptParser::Instanceof, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Typeof() {
  return getToken(JavaScriptParser::Typeof, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Case() {
  return getToken(JavaScriptParser::Case, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Else() {
  return getToken(JavaScriptParser::Else, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::New() {
  return getToken(JavaScriptParser::New, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Var() {
  return getToken(JavaScriptParser::Var, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Catch() {
  return getToken(JavaScriptParser::Catch, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Finally() {
  return getToken(JavaScriptParser::Finally, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Return() {
  return getToken(JavaScriptParser::Return, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Void() {
  return getToken(JavaScriptParser::Void, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Continue() {
  return getToken(JavaScriptParser::Continue, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::For() {
  return getToken(JavaScriptParser::For, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Switch() {
  return getToken(JavaScriptParser::Switch, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::While() {
  return getToken(JavaScriptParser::While, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Debugger() {
  return getToken(JavaScriptParser::Debugger, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Function_() {
  return getToken(JavaScriptParser::Function_, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::This() {
  return getToken(JavaScriptParser::This, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::With() {
  return getToken(JavaScriptParser::With, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Default() {
  return getToken(JavaScriptParser::Default, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::If() {
  return getToken(JavaScriptParser::If, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Throw() {
  return getToken(JavaScriptParser::Throw, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Delete() {
  return getToken(JavaScriptParser::Delete, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::In() {
  return getToken(JavaScriptParser::In, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Try() {
  return getToken(JavaScriptParser::Try, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Class() {
  return getToken(JavaScriptParser::Class, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Enum() {
  return getToken(JavaScriptParser::Enum, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Extends() {
  return getToken(JavaScriptParser::Extends, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Super() {
  return getToken(JavaScriptParser::Super, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Const() {
  return getToken(JavaScriptParser::Const, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Export() {
  return getToken(JavaScriptParser::Export, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Import() {
  return getToken(JavaScriptParser::Import, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Implements() {
  return getToken(JavaScriptParser::Implements, 0);
}

JavaScriptParser::Let_Context* JavaScriptParser::KeywordContext::let_() {
  return getRuleContext<JavaScriptParser::Let_Context>(0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Private() {
  return getToken(JavaScriptParser::Private, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Public() {
  return getToken(JavaScriptParser::Public, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Interface() {
  return getToken(JavaScriptParser::Interface, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Package() {
  return getToken(JavaScriptParser::Package, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Protected() {
  return getToken(JavaScriptParser::Protected, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Static() {
  return getToken(JavaScriptParser::Static, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Yield() {
  return getToken(JavaScriptParser::Yield, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Async() {
  return getToken(JavaScriptParser::Async, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::Await() {
  return getToken(JavaScriptParser::Await, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::From() {
  return getToken(JavaScriptParser::From, 0);
}

tree::TerminalNode* JavaScriptParser::KeywordContext::As() {
  return getToken(JavaScriptParser::As, 0);
}


size_t JavaScriptParser::KeywordContext::getRuleIndex() const {
  return JavaScriptParser::RuleKeyword;
}

void JavaScriptParser::KeywordContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterKeyword(this);
}

void JavaScriptParser::KeywordContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitKeyword(this);
}


antlrcpp::Any JavaScriptParser::KeywordContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitKeyword(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::KeywordContext* JavaScriptParser::keyword() {
  KeywordContext *_localctx = _tracker.createInstance<KeywordContext>(_ctx, getState());
  enterRule(_localctx, 148, JavaScriptParser::RuleKeyword);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1018);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case JavaScriptParser::Break: {
        enterOuterAlt(_localctx, 1);
        setState(972);
        match(JavaScriptParser::Break);
        break;
      }

      case JavaScriptParser::Do: {
        enterOuterAlt(_localctx, 2);
        setState(973);
        match(JavaScriptParser::Do);
        break;
      }

      case JavaScriptParser::Instanceof: {
        enterOuterAlt(_localctx, 3);
        setState(974);
        match(JavaScriptParser::Instanceof);
        break;
      }

      case JavaScriptParser::Typeof: {
        enterOuterAlt(_localctx, 4);
        setState(975);
        match(JavaScriptParser::Typeof);
        break;
      }

      case JavaScriptParser::Case: {
        enterOuterAlt(_localctx, 5);
        setState(976);
        match(JavaScriptParser::Case);
        break;
      }

      case JavaScriptParser::Else: {
        enterOuterAlt(_localctx, 6);
        setState(977);
        match(JavaScriptParser::Else);
        break;
      }

      case JavaScriptParser::New: {
        enterOuterAlt(_localctx, 7);
        setState(978);
        match(JavaScriptParser::New);
        break;
      }

      case JavaScriptParser::Var: {
        enterOuterAlt(_localctx, 8);
        setState(979);
        match(JavaScriptParser::Var);
        break;
      }

      case JavaScriptParser::Catch: {
        enterOuterAlt(_localctx, 9);
        setState(980);
        match(JavaScriptParser::Catch);
        break;
      }

      case JavaScriptParser::Finally: {
        enterOuterAlt(_localctx, 10);
        setState(981);
        match(JavaScriptParser::Finally);
        break;
      }

      case JavaScriptParser::Return: {
        enterOuterAlt(_localctx, 11);
        setState(982);
        match(JavaScriptParser::Return);
        break;
      }

      case JavaScriptParser::Void: {
        enterOuterAlt(_localctx, 12);
        setState(983);
        match(JavaScriptParser::Void);
        break;
      }

      case JavaScriptParser::Continue: {
        enterOuterAlt(_localctx, 13);
        setState(984);
        match(JavaScriptParser::Continue);
        break;
      }

      case JavaScriptParser::For: {
        enterOuterAlt(_localctx, 14);
        setState(985);
        match(JavaScriptParser::For);
        break;
      }

      case JavaScriptParser::Switch: {
        enterOuterAlt(_localctx, 15);
        setState(986);
        match(JavaScriptParser::Switch);
        break;
      }

      case JavaScriptParser::While: {
        enterOuterAlt(_localctx, 16);
        setState(987);
        match(JavaScriptParser::While);
        break;
      }

      case JavaScriptParser::Debugger: {
        enterOuterAlt(_localctx, 17);
        setState(988);
        match(JavaScriptParser::Debugger);
        break;
      }

      case JavaScriptParser::Function_: {
        enterOuterAlt(_localctx, 18);
        setState(989);
        match(JavaScriptParser::Function_);
        break;
      }

      case JavaScriptParser::This: {
        enterOuterAlt(_localctx, 19);
        setState(990);
        match(JavaScriptParser::This);
        break;
      }

      case JavaScriptParser::With: {
        enterOuterAlt(_localctx, 20);
        setState(991);
        match(JavaScriptParser::With);
        break;
      }

      case JavaScriptParser::Default: {
        enterOuterAlt(_localctx, 21);
        setState(992);
        match(JavaScriptParser::Default);
        break;
      }

      case JavaScriptParser::If: {
        enterOuterAlt(_localctx, 22);
        setState(993);
        match(JavaScriptParser::If);
        break;
      }

      case JavaScriptParser::Throw: {
        enterOuterAlt(_localctx, 23);
        setState(994);
        match(JavaScriptParser::Throw);
        break;
      }

      case JavaScriptParser::Delete: {
        enterOuterAlt(_localctx, 24);
        setState(995);
        match(JavaScriptParser::Delete);
        break;
      }

      case JavaScriptParser::In: {
        enterOuterAlt(_localctx, 25);
        setState(996);
        match(JavaScriptParser::In);
        break;
      }

      case JavaScriptParser::Try: {
        enterOuterAlt(_localctx, 26);
        setState(997);
        match(JavaScriptParser::Try);
        break;
      }

      case JavaScriptParser::Class: {
        enterOuterAlt(_localctx, 27);
        setState(998);
        match(JavaScriptParser::Class);
        break;
      }

      case JavaScriptParser::Enum: {
        enterOuterAlt(_localctx, 28);
        setState(999);
        match(JavaScriptParser::Enum);
        break;
      }

      case JavaScriptParser::Extends: {
        enterOuterAlt(_localctx, 29);
        setState(1000);
        match(JavaScriptParser::Extends);
        break;
      }

      case JavaScriptParser::Super: {
        enterOuterAlt(_localctx, 30);
        setState(1001);
        match(JavaScriptParser::Super);
        break;
      }

      case JavaScriptParser::Const: {
        enterOuterAlt(_localctx, 31);
        setState(1002);
        match(JavaScriptParser::Const);
        break;
      }

      case JavaScriptParser::Export: {
        enterOuterAlt(_localctx, 32);
        setState(1003);
        match(JavaScriptParser::Export);
        break;
      }

      case JavaScriptParser::Import: {
        enterOuterAlt(_localctx, 33);
        setState(1004);
        match(JavaScriptParser::Import);
        break;
      }

      case JavaScriptParser::Implements: {
        enterOuterAlt(_localctx, 34);
        setState(1005);
        match(JavaScriptParser::Implements);
        break;
      }

      case JavaScriptParser::StrictLet:
      case JavaScriptParser::NonStrictLet: {
        enterOuterAlt(_localctx, 35);
        setState(1006);
        let_();
        break;
      }

      case JavaScriptParser::Private: {
        enterOuterAlt(_localctx, 36);
        setState(1007);
        match(JavaScriptParser::Private);
        break;
      }

      case JavaScriptParser::Public: {
        enterOuterAlt(_localctx, 37);
        setState(1008);
        match(JavaScriptParser::Public);
        break;
      }

      case JavaScriptParser::Interface: {
        enterOuterAlt(_localctx, 38);
        setState(1009);
        match(JavaScriptParser::Interface);
        break;
      }

      case JavaScriptParser::Package: {
        enterOuterAlt(_localctx, 39);
        setState(1010);
        match(JavaScriptParser::Package);
        break;
      }

      case JavaScriptParser::Protected: {
        enterOuterAlt(_localctx, 40);
        setState(1011);
        match(JavaScriptParser::Protected);
        break;
      }

      case JavaScriptParser::Static: {
        enterOuterAlt(_localctx, 41);
        setState(1012);
        match(JavaScriptParser::Static);
        break;
      }

      case JavaScriptParser::Yield: {
        enterOuterAlt(_localctx, 42);
        setState(1013);
        match(JavaScriptParser::Yield);
        break;
      }

      case JavaScriptParser::Async: {
        enterOuterAlt(_localctx, 43);
        setState(1014);
        match(JavaScriptParser::Async);
        break;
      }

      case JavaScriptParser::Await: {
        enterOuterAlt(_localctx, 44);
        setState(1015);
        match(JavaScriptParser::Await);
        break;
      }

      case JavaScriptParser::From: {
        enterOuterAlt(_localctx, 45);
        setState(1016);
        match(JavaScriptParser::From);
        break;
      }

      case JavaScriptParser::As: {
        enterOuterAlt(_localctx, 46);
        setState(1017);
        match(JavaScriptParser::As);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Let_Context ------------------------------------------------------------------

JavaScriptParser::Let_Context::Let_Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::Let_Context::NonStrictLet() {
  return getToken(JavaScriptParser::NonStrictLet, 0);
}

tree::TerminalNode* JavaScriptParser::Let_Context::StrictLet() {
  return getToken(JavaScriptParser::StrictLet, 0);
}


size_t JavaScriptParser::Let_Context::getRuleIndex() const {
  return JavaScriptParser::RuleLet_;
}

void JavaScriptParser::Let_Context::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLet_(this);
}

void JavaScriptParser::Let_Context::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLet_(this);
}


antlrcpp::Any JavaScriptParser::Let_Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitLet_(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::Let_Context* JavaScriptParser::let_() {
  Let_Context *_localctx = _tracker.createInstance<Let_Context>(_ctx, getState());
  enterRule(_localctx, 150, JavaScriptParser::RuleLet_);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1020);
    _la = _input->LA(1);
    if (!(_la == JavaScriptParser::StrictLet

    || _la == JavaScriptParser::NonStrictLet)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EosContext ------------------------------------------------------------------

JavaScriptParser::EosContext::EosContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* JavaScriptParser::EosContext::SemiColon() {
  return getToken(JavaScriptParser::SemiColon, 0);
}

tree::TerminalNode* JavaScriptParser::EosContext::EOF() {
  return getToken(JavaScriptParser::EOF, 0);
}


size_t JavaScriptParser::EosContext::getRuleIndex() const {
  return JavaScriptParser::RuleEos;
}

void JavaScriptParser::EosContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEos(this);
}

void JavaScriptParser::EosContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<JavaScriptParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEos(this);
}


antlrcpp::Any JavaScriptParser::EosContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<JavaScriptParserVisitor*>(visitor))
    return parserVisitor->visitEos(this);
  else
    return visitor->visitChildren(this);
}

JavaScriptParser::EosContext* JavaScriptParser::eos() {
  EosContext *_localctx = _tracker.createInstance<EosContext>(_ctx, getState());
  enterRule(_localctx, 152, JavaScriptParser::RuleEos);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1026);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 111, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(1022);
      match(JavaScriptParser::SemiColon);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(1023);
      match(JavaScriptParser::EOF);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(1024);

      if (!(this->lineTerminatorAhead())) throw FailedPredicateException(this, "this->lineTerminatorAhead()");
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(1025);

      if (!(this->closeBrace())) throw FailedPredicateException(this, "this->closeBrace()");
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool JavaScriptParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 19: return expressionStatementSempred(antlrcpp::downCast<ExpressionStatementContext *>(context), predicateIndex);
    case 21: return iterationStatementSempred(antlrcpp::downCast<IterationStatementContext *>(context), predicateIndex);
    case 23: return continueStatementSempred(antlrcpp::downCast<ContinueStatementContext *>(context), predicateIndex);
    case 24: return breakStatementSempred(antlrcpp::downCast<BreakStatementContext *>(context), predicateIndex);
    case 25: return returnStatementSempred(antlrcpp::downCast<ReturnStatementContext *>(context), predicateIndex);
    case 26: return yieldStatementSempred(antlrcpp::downCast<YieldStatementContext *>(context), predicateIndex);
    case 34: return throwStatementSempred(antlrcpp::downCast<ThrowStatementContext *>(context), predicateIndex);
    case 42: return classElementSempred(antlrcpp::downCast<ClassElementContext *>(context), predicateIndex);
    case 57: return singleExpressionSempred(antlrcpp::downCast<SingleExpressionContext *>(context), predicateIndex);
    case 69: return getterSempred(antlrcpp::downCast<GetterContext *>(context), predicateIndex);
    case 70: return setterSempred(antlrcpp::downCast<SetterContext *>(context), predicateIndex);
    case 76: return eosSempred(antlrcpp::downCast<EosContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool JavaScriptParser::expressionStatementSempred(ExpressionStatementContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return this->notOpenBraceAndNotFunction();

  default:
    break;
  }
  return true;
}

bool JavaScriptParser::iterationStatementSempred(IterationStatementContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return this->p("of");

  default:
    break;
  }
  return true;
}

bool JavaScriptParser::continueStatementSempred(ContinueStatementContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return this->notLineTerminator();

  default:
    break;
  }
  return true;
}

bool JavaScriptParser::breakStatementSempred(BreakStatementContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 3: return this->notLineTerminator();

  default:
    break;
  }
  return true;
}

bool JavaScriptParser::returnStatementSempred(ReturnStatementContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 4: return this->notLineTerminator();

  default:
    break;
  }
  return true;
}

bool JavaScriptParser::yieldStatementSempred(YieldStatementContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 5: return this->notLineTerminator();

  default:
    break;
  }
  return true;
}

bool JavaScriptParser::throwStatementSempred(ThrowStatementContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 6: return this->notLineTerminator();

  default:
    break;
  }
  return true;
}

bool JavaScriptParser::classElementSempred(ClassElementContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 7: return this->n("static");

  default:
    break;
  }
  return true;
}

bool JavaScriptParser::singleExpressionSempred(SingleExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 8: return precpred(_ctx, 27);
    case 9: return precpred(_ctx, 26);
    case 10: return precpred(_ctx, 25);
    case 11: return precpred(_ctx, 24);
    case 12: return precpred(_ctx, 23);
    case 13: return precpred(_ctx, 22);
    case 14: return precpred(_ctx, 21);
    case 15: return precpred(_ctx, 20);
    case 16: return precpred(_ctx, 19);
    case 17: return precpred(_ctx, 18);
    case 18: return precpred(_ctx, 17);
    case 19: return precpred(_ctx, 16);
    case 20: return precpred(_ctx, 15);
    case 21: return precpred(_ctx, 14);
    case 22: return precpred(_ctx, 13);
    case 23: return precpred(_ctx, 12);
    case 24: return precpred(_ctx, 11);
    case 25: return precpred(_ctx, 45);
    case 26: return precpred(_ctx, 44);
    case 27: return precpred(_ctx, 41);
    case 28: return precpred(_ctx, 39);
    case 29: return this->notLineTerminator();
    case 30: return precpred(_ctx, 38);
    case 31: return this->notLineTerminator();
    case 32: return precpred(_ctx, 9);

  default:
    break;
  }
  return true;
}

bool JavaScriptParser::getterSempred(GetterContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 33: return this->n("get");

  default:
    break;
  }
  return true;
}

bool JavaScriptParser::setterSempred(SetterContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 34: return this->n("set");

  default:
    break;
  }
  return true;
}

bool JavaScriptParser::eosSempred(EosContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 35: return this->lineTerminatorAhead();
    case 36: return this->closeBrace();

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> JavaScriptParser::_decisionToDFA;
atn::PredictionContextCache JavaScriptParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN JavaScriptParser::_atn;
std::vector<uint16_t> JavaScriptParser::_serializedATN;

std::vector<std::string> JavaScriptParser::_ruleNames = {
  "program", "sourceElement", "statement", "block", "statementList", "importStatement", 
  "importFromBlock", "moduleItems", "importDefault", "importNamespace", 
  "importFrom", "aliasName", "exportStatement", "exportFromBlock", "declaration", 
  "variableStatement", "variableDeclarationList", "variableDeclaration", 
  "emptyStatement_", "expressionStatement", "ifStatement", "iterationStatement", 
  "varModifier", "continueStatement", "breakStatement", "returnStatement", 
  "yieldStatement", "withStatement", "switchStatement", "caseBlock", "caseClauses", 
  "caseClause", "defaultClause", "labelledStatement", "throwStatement", 
  "tryStatement", "catchProduction", "finallyProduction", "debuggerStatement", 
  "functionDeclaration", "classDeclaration", "classTail", "classElement", 
  "methodDefinition", "formalParameterList", "formalParameterArg", "lastFormalParameterArg", 
  "functionBody", "sourceElements", "arrayLiteral", "elementList", "arrayElement", 
  "propertyAssignment", "propertyName", "arguments", "argument", "expressionSequence", 
  "singleExpression", "assignable", "objectLiteral", "anonymousFunction", 
  "arrowFunctionParameters", "arrowFunctionBody", "assignmentOperator", 
  "literal", "templateStringLiteral", "templateStringAtom", "numericLiteral", 
  "bigintLiteral", "getter", "setter", "identifierName", "identifier", "reservedWord", 
  "keyword", "let_", "eos"
};

std::vector<std::string> JavaScriptParser::_literalNames = {
  "", "", "", "", "", "'['", "']'", "'('", "')'", "'{'", "", "'}'", "';'", 
  "','", "'='", "'\u003F'", "':'", "'...'", "'.'", "'++'", "'--'", "'+'", 
  "'-'", "'~'", "'!'", "'*'", "'/'", "'%'", "'**'", "'\u003F\u003F'", "'#'", 
  "'>>'", "'<<'", "'>>>'", "'<'", "'>'", "'<='", "'>='", "'=='", "'!='", 
  "'==='", "'!=='", "'&'", "'^'", "'|'", "'&&'", "'||'", "'*='", "'/='", 
  "'%='", "'+='", "'-='", "'<<='", "'>>='", "'>>>='", "'&='", "'^='", "'|='", 
  "'**='", "'=>'", "'null'", "", "", "", "", "", "", "", "", "", "", "'break'", 
  "'do'", "'instanceof'", "'typeof'", "'case'", "'else'", "'new'", "'var'", 
  "'catch'", "'finally'", "'return'", "'void'", "'continue'", "'for'", "'switch'", 
  "'while'", "'debugger'", "'function'", "'this'", "'with'", "'default'", 
  "'if'", "'throw'", "'delete'", "'in'", "'try'", "'as'", "'from'", "'class'", 
  "'enum'", "'extends'", "'super'", "'const'", "'export'", "'import'", "'async'", 
  "'await'", "'yield'", "'implements'", "", "", "'private'", "'public'", 
  "'interface'", "'package'", "'protected'", "'static'", "", "", "", "", 
  "", "", "", "", "'${'"
};

std::vector<std::string> JavaScriptParser::_symbolicNames = {
  "", "HashBangLine", "MultiLineComment", "SingleLineComment", "RegularExpressionLiteral", 
  "OpenBracket", "CloseBracket", "OpenParen", "CloseParen", "OpenBrace", 
  "TemplateCloseBrace", "CloseBrace", "SemiColon", "Comma", "Assign", "QuestionMark", 
  "Colon", "Ellipsis", "Dot", "PlusPlus", "MinusMinus", "Plus", "Minus", 
  "BitNot", "Not", "Multiply", "Divide", "Modulus", "Power", "NullCoalesce", 
  "Hashtag", "RightShiftArithmetic", "LeftShiftArithmetic", "RightShiftLogical", 
  "LessThan", "MoreThan", "LessThanEquals", "GreaterThanEquals", "Equals_", 
  "NotEquals", "IdentityEquals", "IdentityNotEquals", "BitAnd", "BitXOr", 
  "BitOr", "And", "Or", "MultiplyAssign", "DivideAssign", "ModulusAssign", 
  "PlusAssign", "MinusAssign", "LeftShiftArithmeticAssign", "RightShiftArithmeticAssign", 
  "RightShiftLogicalAssign", "BitAndAssign", "BitXorAssign", "BitOrAssign", 
  "PowerAssign", "ARROW", "NullLiteral", "BooleanLiteral", "DecimalLiteral", 
  "HexIntegerLiteral", "OctalIntegerLiteral", "OctalIntegerLiteral2", "BinaryIntegerLiteral", 
  "BigHexIntegerLiteral", "BigOctalIntegerLiteral", "BigBinaryIntegerLiteral", 
  "BigDecimalIntegerLiteral", "Break", "Do", "Instanceof", "Typeof", "Case", 
  "Else", "New", "Var", "Catch", "Finally", "Return", "Void", "Continue", 
  "For", "Switch", "While", "Debugger", "Function_", "This", "With", "Default", 
  "If", "Throw", "Delete", "In", "Try", "As", "From", "Class", "Enum", "Extends", 
  "Super", "Const", "Export", "Import", "Async", "Await", "Yield", "Implements", 
  "StrictLet", "NonStrictLet", "Private", "Public", "Interface", "Package", 
  "Protected", "Static", "Identifier", "StringLiteral", "BackTick", "WhiteSpaces", 
  "LineTerminator", "HtmlComment", "CDataComment", "UnexpectedCharacter", 
  "TemplateStringStartExpression", "TemplateStringAtom"
};

dfa::Vocabulary JavaScriptParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> JavaScriptParser::_tokenNames;

JavaScriptParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  static const uint16_t serializedATNSegment0[] = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
       0x3, 0x81, 0x407, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
       0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 
       0x7, 0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 
       0x4, 0xb, 0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 
       0xe, 0x9, 0xe, 0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 
       0x9, 0x11, 0x4, 0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 
       0x9, 0x14, 0x4, 0x15, 0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 
       0x9, 0x17, 0x4, 0x18, 0x9, 0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 
       0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 
       0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 0x1f, 0x9, 0x1f, 0x4, 0x20, 
       0x9, 0x20, 0x4, 0x21, 0x9, 0x21, 0x4, 0x22, 0x9, 0x22, 0x4, 0x23, 
       0x9, 0x23, 0x4, 0x24, 0x9, 0x24, 0x4, 0x25, 0x9, 0x25, 0x4, 0x26, 
       0x9, 0x26, 0x4, 0x27, 0x9, 0x27, 0x4, 0x28, 0x9, 0x28, 0x4, 0x29, 
       0x9, 0x29, 0x4, 0x2a, 0x9, 0x2a, 0x4, 0x2b, 0x9, 0x2b, 0x4, 0x2c, 
       0x9, 0x2c, 0x4, 0x2d, 0x9, 0x2d, 0x4, 0x2e, 0x9, 0x2e, 0x4, 0x2f, 
       0x9, 0x2f, 0x4, 0x30, 0x9, 0x30, 0x4, 0x31, 0x9, 0x31, 0x4, 0x32, 
       0x9, 0x32, 0x4, 0x33, 0x9, 0x33, 0x4, 0x34, 0x9, 0x34, 0x4, 0x35, 
       0x9, 0x35, 0x4, 0x36, 0x9, 0x36, 0x4, 0x37, 0x9, 0x37, 0x4, 0x38, 
       0x9, 0x38, 0x4, 0x39, 0x9, 0x39, 0x4, 0x3a, 0x9, 0x3a, 0x4, 0x3b, 
       0x9, 0x3b, 0x4, 0x3c, 0x9, 0x3c, 0x4, 0x3d, 0x9, 0x3d, 0x4, 0x3e, 
       0x9, 0x3e, 0x4, 0x3f, 0x9, 0x3f, 0x4, 0x40, 0x9, 0x40, 0x4, 0x41, 
       0x9, 0x41, 0x4, 0x42, 0x9, 0x42, 0x4, 0x43, 0x9, 0x43, 0x4, 0x44, 
       0x9, 0x44, 0x4, 0x45, 0x9, 0x45, 0x4, 0x46, 0x9, 0x46, 0x4, 0x47, 
       0x9, 0x47, 0x4, 0x48, 0x9, 0x48, 0x4, 0x49, 0x9, 0x49, 0x4, 0x4a, 
       0x9, 0x4a, 0x4, 0x4b, 0x9, 0x4b, 0x4, 0x4c, 0x9, 0x4c, 0x4, 0x4d, 
       0x9, 0x4d, 0x4, 0x4e, 0x9, 0x4e, 0x3, 0x2, 0x5, 0x2, 0x9e, 0xa, 0x2, 
       0x3, 0x2, 0x5, 0x2, 0xa1, 0xa, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 
       0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
       0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
       0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
       0x4, 0x3, 0x4, 0x5, 0x4, 0xbb, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x5, 
       0x5, 0xbf, 0xa, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x6, 0x6, 0xc4, 
       0xa, 0x6, 0xd, 0x6, 0xe, 0x6, 0xc5, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
       0x3, 0x8, 0x5, 0x8, 0xcc, 0xa, 0x8, 0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 
       0xd0, 0xa, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
       0x5, 0x8, 0xd7, 0xa, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 
       0x7, 0x9, 0xdd, 0xa, 0x9, 0xc, 0x9, 0xe, 0x9, 0xe0, 0xb, 0x9, 0x3, 
       0x9, 0x3, 0x9, 0x5, 0x9, 0xe4, 0xa, 0x9, 0x5, 0x9, 0xe6, 0xa, 0x9, 
       0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 
       0xb, 0x5, 0xb, 0xef, 0xa, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0xf3, 
       0xa, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 
       0xd, 0x5, 0xd, 0xfb, 0xa, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x5, 
       0xe, 0x100, 0xa, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 
       0xe, 0x3, 0xe, 0x3, 0xe, 0x5, 0xe, 0x109, 0xa, 0xe, 0x3, 0xf, 0x3, 
       0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x5, 0xf, 0x111, 0xa, 
       0xf, 0x3, 0xf, 0x3, 0xf, 0x5, 0xf, 0x115, 0xa, 0xf, 0x3, 0x10, 0x3, 
       0x10, 0x3, 0x10, 0x5, 0x10, 0x11a, 0xa, 0x10, 0x3, 0x11, 0x3, 0x11, 
       0x3, 0x11, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x7, 0x12, 
       0x123, 0xa, 0x12, 0xc, 0x12, 0xe, 0x12, 0x126, 0xb, 0x12, 0x3, 0x13, 
       0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 0x12b, 0xa, 0x13, 0x3, 0x14, 0x3, 
       0x14, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x16, 0x3, 
       0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x5, 
       0x16, 0x13a, 0xa, 0x16, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 
       0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 
       0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 
       0x3, 0x17, 0x3, 0x17, 0x5, 0x17, 0x14e, 0xa, 0x17, 0x3, 0x17, 0x3, 
       0x17, 0x5, 0x17, 0x152, 0xa, 0x17, 0x3, 0x17, 0x3, 0x17, 0x5, 0x17, 
       0x156, 0xa, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 
       0x17, 0x3, 0x17, 0x5, 0x17, 0x15e, 0xa, 0x17, 0x3, 0x17, 0x3, 0x17, 
       0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x5, 0x17, 
       0x167, 0xa, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x5, 0x17, 0x16c, 
       0xa, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 
       0x3, 0x17, 0x5, 0x17, 0x174, 0xa, 0x17, 0x3, 0x18, 0x3, 0x18, 0x3, 
       0x18, 0x5, 0x18, 0x179, 0xa, 0x18, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 
       0x5, 0x19, 0x17e, 0xa, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x1a, 0x3, 
       0x1a, 0x3, 0x1a, 0x5, 0x1a, 0x185, 0xa, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 
       0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x5, 0x1b, 0x18c, 0xa, 0x1b, 0x3, 
       0x1b, 0x3, 0x1b, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x5, 0x1c, 0x193, 
       0xa, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 
       0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 
       0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 0x5, 0x1f, 
       0x1a5, 0xa, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x5, 0x1f, 0x1a9, 0xa, 0x1f, 
       0x5, 0x1f, 0x1ab, 0xa, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x20, 0x6, 
       0x20, 0x1b0, 0xa, 0x20, 0xd, 0x20, 0xe, 0x20, 0x1b1, 0x3, 0x21, 0x3, 
       0x21, 0x3, 0x21, 0x3, 0x21, 0x5, 0x21, 0x1b8, 0xa, 0x21, 0x3, 0x22, 
       0x3, 0x22, 0x3, 0x22, 0x5, 0x22, 0x1bd, 0xa, 0x22, 0x3, 0x23, 0x3, 
       0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 0x3, 
       0x24, 0x3, 0x24, 0x3, 0x25, 0x3, 0x25, 0x3, 0x25, 0x3, 0x25, 0x5, 
       0x25, 0x1cc, 0xa, 0x25, 0x3, 0x25, 0x5, 0x25, 0x1cf, 0xa, 0x25, 0x3, 
       0x26, 0x3, 0x26, 0x3, 0x26, 0x5, 0x26, 0x1d4, 0xa, 0x26, 0x3, 0x26, 
       0x5, 0x26, 0x1d7, 0xa, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x27, 0x3, 
       0x27, 0x3, 0x27, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x29, 0x5, 
       0x29, 0x1e2, 0xa, 0x29, 0x3, 0x29, 0x3, 0x29, 0x5, 0x29, 0x1e6, 0xa, 
       0x29, 0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 0x5, 0x29, 0x1eb, 0xa, 0x29, 
       0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 
       0x3, 0x2a, 0x3, 0x2b, 0x3, 0x2b, 0x5, 0x2b, 0x1f6, 0xa, 0x2b, 0x3, 
       0x2b, 0x3, 0x2b, 0x7, 0x2b, 0x1fa, 0xa, 0x2b, 0xc, 0x2b, 0xe, 0x2b, 
       0x1fd, 0xb, 0x2b, 0x3, 0x2b, 0x3, 0x2b, 0x3, 0x2c, 0x3, 0x2c, 0x3, 
       0x2c, 0x3, 0x2c, 0x7, 0x2c, 0x205, 0xa, 0x2c, 0xc, 0x2c, 0xe, 0x2c, 
       0x208, 0xb, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x3, 
       0x2c, 0x3, 0x2c, 0x5, 0x2c, 0x210, 0xa, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 
       0x5, 0x2c, 0x214, 0xa, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x3, 
       0x2c, 0x5, 0x2c, 0x21a, 0xa, 0x2c, 0x3, 0x2d, 0x5, 0x2d, 0x21d, 0xa, 
       0x2d, 0x3, 0x2d, 0x5, 0x2d, 0x220, 0xa, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 
       0x3, 0x2d, 0x5, 0x2d, 0x225, 0xa, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x3, 
       0x2d, 0x3, 0x2d, 0x5, 0x2d, 0x22b, 0xa, 0x2d, 0x3, 0x2d, 0x5, 0x2d, 
       0x22e, 0xa, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x3, 
       0x2d, 0x3, 0x2d, 0x5, 0x2d, 0x236, 0xa, 0x2d, 0x3, 0x2d, 0x5, 0x2d, 
       0x239, 0xa, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x5, 0x2d, 0x23e, 
       0xa, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x5, 0x2d, 0x243, 0xa, 
       0x2d, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x7, 0x2e, 0x248, 0xa, 0x2e, 
       0xc, 0x2e, 0xe, 0x2e, 0x24b, 0xb, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x5, 
       0x2e, 0x24f, 0xa, 0x2e, 0x3, 0x2e, 0x5, 0x2e, 0x252, 0xa, 0x2e, 0x3, 
       0x2f, 0x3, 0x2f, 0x3, 0x2f, 0x5, 0x2f, 0x257, 0xa, 0x2f, 0x3, 0x30, 
       0x3, 0x30, 0x3, 0x30, 0x3, 0x31, 0x3, 0x31, 0x5, 0x31, 0x25e, 0xa, 
       0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x32, 0x6, 0x32, 0x263, 0xa, 0x32, 
       0xd, 0x32, 0xe, 0x32, 0x264, 0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x3, 
       0x33, 0x3, 0x34, 0x7, 0x34, 0x26c, 0xa, 0x34, 0xc, 0x34, 0xe, 0x34, 
       0x26f, 0xb, 0x34, 0x3, 0x34, 0x5, 0x34, 0x272, 0xa, 0x34, 0x3, 0x34, 
       0x6, 0x34, 0x275, 0xa, 0x34, 0xd, 0x34, 0xe, 0x34, 0x276, 0x3, 0x34, 
       0x7, 0x34, 0x27a, 0xa, 0x34, 0xc, 0x34, 0xe, 0x34, 0x27d, 0xb, 0x34, 
       0x3, 0x34, 0x7, 0x34, 0x280, 0xa, 0x34, 0xc, 0x34, 0xe, 0x34, 0x283, 
       0xb, 0x34, 0x3, 0x35, 0x5, 0x35, 0x286, 0xa, 0x35, 0x3, 0x35, 0x3, 
       0x35, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 
       0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x5, 
       0x36, 0x295, 0xa, 0x36, 0x3, 0x36, 0x5, 0x36, 0x298, 0xa, 0x36, 0x3, 
       0x36, 0x3, 0x36, 0x3, 0x36, 0x5, 0x36, 0x29d, 0xa, 0x36, 0x3, 0x36, 
       0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 
       0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 
       0x3, 0x36, 0x3, 0x36, 0x5, 0x36, 0x2ae, 0xa, 0x36, 0x3, 0x36, 0x5, 
       0x36, 0x2b1, 0xa, 0x36, 0x3, 0x37, 0x3, 0x37, 0x3, 0x37, 0x3, 0x37, 
       0x3, 0x37, 0x3, 0x37, 0x3, 0x37, 0x5, 0x37, 0x2ba, 0xa, 0x37, 0x3, 
       0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x7, 0x38, 0x2c0, 0xa, 0x38, 
       0xc, 0x38, 0xe, 0x38, 0x2c3, 0xb, 0x38, 0x3, 0x38, 0x5, 0x38, 0x2c6, 
       0xa, 0x38, 0x5, 0x38, 0x2c8, 0xa, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 
       0x39, 0x5, 0x39, 0x2cd, 0xa, 0x39, 0x3, 0x39, 0x3, 0x39, 0x5, 0x39, 
       0x2d1, 0xa, 0x39, 0x3, 0x3a, 0x3, 0x3a, 0x3, 0x3a, 0x7, 0x3a, 0x2d6, 
       0xa, 0x3a, 0xc, 0x3a, 0xe, 0x3a, 0x2d9, 0xb, 0x3a, 0x3, 0x3b, 0x3, 
       0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x5, 0x3b, 0x2df, 0xa, 0x3b, 0x3, 0x3b, 
       0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 
       0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 
       0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 
       0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 
       0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 
       0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 
       0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 
       0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x5, 0x3b, 0x30f, 0xa, 0x3b, 0x3, 
       0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 
       0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 
       0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 
       0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 
       0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 
       0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 
       0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 
       0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 
       0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 
       0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 
       0x3b, 0x3, 0x3b, 0x5, 0x3b, 0x34f, 0xa, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 
       0x5, 0x3b, 0x353, 0xa, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 
       0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 
       0x3b, 0x3, 0x3b, 0x7, 0x3b, 0x360, 0xa, 0x3b, 0xc, 0x3b, 0xe, 0x3b, 
       0x363, 0xb, 0x3b, 0x3, 0x3c, 0x3, 0x3c, 0x3, 0x3c, 0x5, 0x3c, 0x368, 
       0xa, 0x3c, 0x3, 0x3d, 0x3, 0x3d, 0x3, 0x3d, 0x3, 0x3d, 0x7, 0x3d, 
       0x36e, 0xa, 0x3d, 0xc, 0x3d, 0xe, 0x3d, 0x371, 0xb, 0x3d, 0x3, 0x3d, 
       0x5, 0x3d, 0x374, 0xa, 0x3d, 0x5, 0x3d, 0x376, 0xa, 0x3d, 0x3, 0x3d, 
       0x3, 0x3d, 0x3, 0x3e, 0x3, 0x3e, 0x5, 0x3e, 0x37c, 0xa, 0x3e, 0x3, 
       0x3e, 0x3, 0x3e, 0x5, 0x3e, 0x380, 0xa, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 
       0x5, 0x3e, 0x384, 0xa, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x5, 
       0x3e, 0x389, 0xa, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 
       0x5, 0x3e, 0x38f, 0xa, 0x3e, 0x3, 0x3f, 0x3, 0x3f, 0x3, 0x3f, 0x5, 
       0x3f, 0x394, 0xa, 0x3f, 0x3, 0x3f, 0x5, 0x3f, 0x397, 0xa, 0x3f, 0x3, 
       0x40, 0x3, 0x40, 0x5, 0x40, 0x39b, 0xa, 0x40, 0x3, 0x41, 0x3, 0x41, 
       0x3, 0x42, 0x3, 0x42, 0x3, 0x42, 0x3, 0x42, 0x3, 0x42, 0x3, 0x42, 
       0x3, 0x42, 0x5, 0x42, 0x3a6, 0xa, 0x42, 0x3, 0x43, 0x3, 0x43, 0x7, 
       0x43, 0x3aa, 0xa, 0x43, 0xc, 0x43, 0xe, 0x43, 0x3ad, 0xb, 0x43, 0x3, 
       0x43, 0x3, 0x43, 0x3, 0x44, 0x3, 0x44, 0x3, 0x44, 0x3, 0x44, 0x3, 
       0x44, 0x5, 0x44, 0x3b6, 0xa, 0x44, 0x3, 0x45, 0x3, 0x45, 0x3, 0x46, 
       0x3, 0x46, 0x3, 0x47, 0x3, 0x47, 0x3, 0x47, 0x3, 0x47, 0x3, 0x48, 
       0x3, 0x48, 0x3, 0x48, 0x3, 0x48, 0x3, 0x49, 0x3, 0x49, 0x5, 0x49, 
       0x3c6, 0xa, 0x49, 0x3, 0x4a, 0x3, 0x4a, 0x3, 0x4b, 0x3, 0x4b, 0x3, 
       0x4b, 0x5, 0x4b, 0x3cd, 0xa, 0x4b, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 
       0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 
       0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 
       0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 
       0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 
       0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 
       0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 
       0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 
       0x3, 0x4c, 0x5, 0x4c, 0x3fd, 0xa, 0x4c, 0x3, 0x4d, 0x3, 0x4d, 0x3, 
       0x4e, 0x3, 0x4e, 0x3, 0x4e, 0x3, 0x4e, 0x5, 0x4e, 0x405, 0xa, 0x4e, 
       0x3, 0x4e, 0x2, 0x3, 0x74, 0x4f, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 
       0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 
       0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 
       0x3c, 0x3e, 0x40, 0x42, 0x44, 0x46, 0x48, 0x4a, 0x4c, 0x4e, 0x50, 
       0x52, 0x54, 0x56, 0x58, 0x5a, 0x5c, 0x5e, 0x60, 0x62, 0x64, 0x66, 
       0x68, 0x6a, 0x6c, 0x6e, 0x70, 0x72, 0x74, 0x76, 0x78, 0x7a, 0x7c, 
       0x7e, 0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c, 0x8e, 0x90, 0x92, 
       0x94, 0x96, 0x98, 0x9a, 0x2, 0xc, 0x3, 0x2, 0x1b, 0x1d, 0x3, 0x2, 
       0x17, 0x18, 0x3, 0x2, 0x21, 0x23, 0x3, 0x2, 0x24, 0x27, 0x3, 0x2, 
       0x28, 0x2b, 0x3, 0x2, 0x31, 0x3c, 0x3, 0x2, 0x40, 0x44, 0x3, 0x2, 
       0x45, 0x48, 0x5, 0x2, 0x6c, 0x6c, 0x71, 0x71, 0x78, 0x78, 0x3, 0x2, 
       0x70, 0x71, 0x2, 0x4ab, 0x2, 0x9d, 0x3, 0x2, 0x2, 0x2, 0x4, 0xa4, 
       0x3, 0x2, 0x2, 0x2, 0x6, 0xba, 0x3, 0x2, 0x2, 0x2, 0x8, 0xbc, 0x3, 
       0x2, 0x2, 0x2, 0xa, 0xc3, 0x3, 0x2, 0x2, 0x2, 0xc, 0xc7, 0x3, 0x2, 
       0x2, 0x2, 0xe, 0xd6, 0x3, 0x2, 0x2, 0x2, 0x10, 0xd8, 0x3, 0x2, 0x2, 
       0x2, 0x12, 0xe9, 0x3, 0x2, 0x2, 0x2, 0x14, 0xee, 0x3, 0x2, 0x2, 0x2, 
       0x16, 0xf4, 0x3, 0x2, 0x2, 0x2, 0x18, 0xf7, 0x3, 0x2, 0x2, 0x2, 0x1a, 
       0x108, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x114, 0x3, 0x2, 0x2, 0x2, 0x1e, 
       0x119, 0x3, 0x2, 0x2, 0x2, 0x20, 0x11b, 0x3, 0x2, 0x2, 0x2, 0x22, 
       0x11e, 0x3, 0x2, 0x2, 0x2, 0x24, 0x127, 0x3, 0x2, 0x2, 0x2, 0x26, 
       0x12c, 0x3, 0x2, 0x2, 0x2, 0x28, 0x12e, 0x3, 0x2, 0x2, 0x2, 0x2a, 
       0x132, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x173, 0x3, 0x2, 0x2, 0x2, 0x2e, 
       0x178, 0x3, 0x2, 0x2, 0x2, 0x30, 0x17a, 0x3, 0x2, 0x2, 0x2, 0x32, 
       0x181, 0x3, 0x2, 0x2, 0x2, 0x34, 0x188, 0x3, 0x2, 0x2, 0x2, 0x36, 
       0x18f, 0x3, 0x2, 0x2, 0x2, 0x38, 0x196, 0x3, 0x2, 0x2, 0x2, 0x3a, 
       0x19c, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x1a2, 0x3, 0x2, 0x2, 0x2, 0x3e, 
       0x1af, 0x3, 0x2, 0x2, 0x2, 0x40, 0x1b3, 0x3, 0x2, 0x2, 0x2, 0x42, 
       0x1b9, 0x3, 0x2, 0x2, 0x2, 0x44, 0x1be, 0x3, 0x2, 0x2, 0x2, 0x46, 
       0x1c2, 0x3, 0x2, 0x2, 0x2, 0x48, 0x1c7, 0x3, 0x2, 0x2, 0x2, 0x4a, 
       0x1d0, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x1da, 0x3, 0x2, 0x2, 0x2, 0x4e, 
       0x1dd, 0x3, 0x2, 0x2, 0x2, 0x50, 0x1e1, 0x3, 0x2, 0x2, 0x2, 0x52, 
       0x1ef, 0x3, 0x2, 0x2, 0x2, 0x54, 0x1f5, 0x3, 0x2, 0x2, 0x2, 0x56, 
       0x219, 0x3, 0x2, 0x2, 0x2, 0x58, 0x242, 0x3, 0x2, 0x2, 0x2, 0x5a, 
       0x251, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x253, 0x3, 0x2, 0x2, 0x2, 0x5e, 
       0x258, 0x3, 0x2, 0x2, 0x2, 0x60, 0x25b, 0x3, 0x2, 0x2, 0x2, 0x62, 
       0x262, 0x3, 0x2, 0x2, 0x2, 0x64, 0x266, 0x3, 0x2, 0x2, 0x2, 0x66, 
       0x26d, 0x3, 0x2, 0x2, 0x2, 0x68, 0x285, 0x3, 0x2, 0x2, 0x2, 0x6a, 
       0x2b0, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x2b9, 0x3, 0x2, 0x2, 0x2, 0x6e, 
       0x2bb, 0x3, 0x2, 0x2, 0x2, 0x70, 0x2cc, 0x3, 0x2, 0x2, 0x2, 0x72, 
       0x2d2, 0x3, 0x2, 0x2, 0x2, 0x74, 0x30e, 0x3, 0x2, 0x2, 0x2, 0x76, 
       0x367, 0x3, 0x2, 0x2, 0x2, 0x78, 0x369, 0x3, 0x2, 0x2, 0x2, 0x7a, 
       0x38e, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x396, 0x3, 0x2, 0x2, 0x2, 0x7e, 
       0x39a, 0x3, 0x2, 0x2, 0x2, 0x80, 0x39c, 0x3, 0x2, 0x2, 0x2, 0x82, 
       0x3a5, 0x3, 0x2, 0x2, 0x2, 0x84, 0x3a7, 0x3, 0x2, 0x2, 0x2, 0x86, 
       0x3b5, 0x3, 0x2, 0x2, 0x2, 0x88, 0x3b7, 0x3, 0x2, 0x2, 0x2, 0x8a, 
       0x3b9, 0x3, 0x2, 0x2, 0x2, 0x8c, 0x3bb, 0x3, 0x2, 0x2, 0x2, 0x8e, 
       0x3bf, 0x3, 0x2, 0x2, 0x2, 0x90, 0x3c5, 0x3, 0x2, 0x2, 0x2, 0x92, 
       0x3c7, 0x3, 0x2, 0x2, 0x2, 0x94, 0x3cc, 0x3, 0x2, 0x2, 0x2, 0x96, 
       0x3fc, 0x3, 0x2, 0x2, 0x2, 0x98, 0x3fe, 0x3, 0x2, 0x2, 0x2, 0x9a, 
       0x404, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x9e, 0x7, 0x3, 0x2, 0x2, 0x9d, 
       0x9c, 0x3, 0x2, 0x2, 0x2, 0x9d, 0x9e, 0x3, 0x2, 0x2, 0x2, 0x9e, 0xa0, 
       0x3, 0x2, 0x2, 0x2, 0x9f, 0xa1, 0x5, 0x62, 0x32, 0x2, 0xa0, 0x9f, 
       0x3, 0x2, 0x2, 0x2, 0xa0, 0xa1, 0x3, 0x2, 0x2, 0x2, 0xa1, 0xa2, 0x3, 
       0x2, 0x2, 0x2, 0xa2, 0xa3, 0x7, 0x2, 0x2, 0x3, 0xa3, 0x3, 0x3, 0x2, 
       0x2, 0x2, 0xa4, 0xa5, 0x5, 0x6, 0x4, 0x2, 0xa5, 0x5, 0x3, 0x2, 0x2, 
       0x2, 0xa6, 0xbb, 0x5, 0x8, 0x5, 0x2, 0xa7, 0xbb, 0x5, 0x20, 0x11, 
       0x2, 0xa8, 0xbb, 0x5, 0xc, 0x7, 0x2, 0xa9, 0xbb, 0x5, 0x1a, 0xe, 
       0x2, 0xaa, 0xbb, 0x5, 0x26, 0x14, 0x2, 0xab, 0xbb, 0x5, 0x52, 0x2a, 
       0x2, 0xac, 0xbb, 0x5, 0x28, 0x15, 0x2, 0xad, 0xbb, 0x5, 0x2a, 0x16, 
       0x2, 0xae, 0xbb, 0x5, 0x2c, 0x17, 0x2, 0xaf, 0xbb, 0x5, 0x30, 0x19, 
       0x2, 0xb0, 0xbb, 0x5, 0x32, 0x1a, 0x2, 0xb1, 0xbb, 0x5, 0x34, 0x1b, 
       0x2, 0xb2, 0xbb, 0x5, 0x36, 0x1c, 0x2, 0xb3, 0xbb, 0x5, 0x38, 0x1d, 
       0x2, 0xb4, 0xbb, 0x5, 0x44, 0x23, 0x2, 0xb5, 0xbb, 0x5, 0x3a, 0x1e, 
       0x2, 0xb6, 0xbb, 0x5, 0x46, 0x24, 0x2, 0xb7, 0xbb, 0x5, 0x48, 0x25, 
       0x2, 0xb8, 0xbb, 0x5, 0x4e, 0x28, 0x2, 0xb9, 0xbb, 0x5, 0x50, 0x29, 
       0x2, 0xba, 0xa6, 0x3, 0x2, 0x2, 0x2, 0xba, 0xa7, 0x3, 0x2, 0x2, 0x2, 
       0xba, 0xa8, 0x3, 0x2, 0x2, 0x2, 0xba, 0xa9, 0x3, 0x2, 0x2, 0x2, 0xba, 
       0xaa, 0x3, 0x2, 0x2, 0x2, 0xba, 0xab, 0x3, 0x2, 0x2, 0x2, 0xba, 0xac, 
       0x3, 0x2, 0x2, 0x2, 0xba, 0xad, 0x3, 0x2, 0x2, 0x2, 0xba, 0xae, 0x3, 
       0x2, 0x2, 0x2, 0xba, 0xaf, 0x3, 0x2, 0x2, 0x2, 0xba, 0xb0, 0x3, 0x2, 
       0x2, 0x2, 0xba, 0xb1, 0x3, 0x2, 0x2, 0x2, 0xba, 0xb2, 0x3, 0x2, 0x2, 
       0x2, 0xba, 0xb3, 0x3, 0x2, 0x2, 0x2, 0xba, 0xb4, 0x3, 0x2, 0x2, 0x2, 
       0xba, 0xb5, 0x3, 0x2, 0x2, 0x2, 0xba, 0xb6, 0x3, 0x2, 0x2, 0x2, 0xba, 
       0xb7, 0x3, 0x2, 0x2, 0x2, 0xba, 0xb8, 0x3, 0x2, 0x2, 0x2, 0xba, 0xb9, 
       0x3, 0x2, 0x2, 0x2, 0xbb, 0x7, 0x3, 0x2, 0x2, 0x2, 0xbc, 0xbe, 0x7, 
       0xb, 0x2, 0x2, 0xbd, 0xbf, 0x5, 0xa, 0x6, 0x2, 0xbe, 0xbd, 0x3, 0x2, 
       0x2, 0x2, 0xbe, 0xbf, 0x3, 0x2, 0x2, 0x2, 0xbf, 0xc0, 0x3, 0x2, 0x2, 
       0x2, 0xc0, 0xc1, 0x7, 0xd, 0x2, 0x2, 0xc1, 0x9, 0x3, 0x2, 0x2, 0x2, 
       0xc2, 0xc4, 0x5, 0x6, 0x4, 0x2, 0xc3, 0xc2, 0x3, 0x2, 0x2, 0x2, 0xc4, 
       0xc5, 0x3, 0x2, 0x2, 0x2, 0xc5, 0xc3, 0x3, 0x2, 0x2, 0x2, 0xc5, 0xc6, 
       0x3, 0x2, 0x2, 0x2, 0xc6, 0xb, 0x3, 0x2, 0x2, 0x2, 0xc7, 0xc8, 0x7, 
       0x6b, 0x2, 0x2, 0xc8, 0xc9, 0x5, 0xe, 0x8, 0x2, 0xc9, 0xd, 0x3, 0x2, 
       0x2, 0x2, 0xca, 0xcc, 0x5, 0x12, 0xa, 0x2, 0xcb, 0xca, 0x3, 0x2, 
       0x2, 0x2, 0xcb, 0xcc, 0x3, 0x2, 0x2, 0x2, 0xcc, 0xcf, 0x3, 0x2, 0x2, 
       0x2, 0xcd, 0xd0, 0x5, 0x14, 0xb, 0x2, 0xce, 0xd0, 0x5, 0x10, 0x9, 
       0x2, 0xcf, 0xcd, 0x3, 0x2, 0x2, 0x2, 0xcf, 0xce, 0x3, 0x2, 0x2, 0x2, 
       0xd0, 0xd1, 0x3, 0x2, 0x2, 0x2, 0xd1, 0xd2, 0x5, 0x16, 0xc, 0x2, 
       0xd2, 0xd3, 0x5, 0x9a, 0x4e, 0x2, 0xd3, 0xd7, 0x3, 0x2, 0x2, 0x2, 
       0xd4, 0xd5, 0x7, 0x79, 0x2, 0x2, 0xd5, 0xd7, 0x5, 0x9a, 0x4e, 0x2, 
       0xd6, 0xcb, 0x3, 0x2, 0x2, 0x2, 0xd6, 0xd4, 0x3, 0x2, 0x2, 0x2, 0xd7, 
       0xf, 0x3, 0x2, 0x2, 0x2, 0xd8, 0xde, 0x7, 0xb, 0x2, 0x2, 0xd9, 0xda, 
       0x5, 0x18, 0xd, 0x2, 0xda, 0xdb, 0x7, 0xf, 0x2, 0x2, 0xdb, 0xdd, 
       0x3, 0x2, 0x2, 0x2, 0xdc, 0xd9, 0x3, 0x2, 0x2, 0x2, 0xdd, 0xe0, 0x3, 
       0x2, 0x2, 0x2, 0xde, 0xdc, 0x3, 0x2, 0x2, 0x2, 0xde, 0xdf, 0x3, 0x2, 
       0x2, 0x2, 0xdf, 0xe5, 0x3, 0x2, 0x2, 0x2, 0xe0, 0xde, 0x3, 0x2, 0x2, 
       0x2, 0xe1, 0xe3, 0x5, 0x18, 0xd, 0x2, 0xe2, 0xe4, 0x7, 0xf, 0x2, 
       0x2, 0xe3, 0xe2, 0x3, 0x2, 0x2, 0x2, 0xe3, 0xe4, 0x3, 0x2, 0x2, 0x2, 
       0xe4, 0xe6, 0x3, 0x2, 0x2, 0x2, 0xe5, 0xe1, 0x3, 0x2, 0x2, 0x2, 0xe5, 
       0xe6, 0x3, 0x2, 0x2, 0x2, 0xe6, 0xe7, 0x3, 0x2, 0x2, 0x2, 0xe7, 0xe8, 
       0x7, 0xd, 0x2, 0x2, 0xe8, 0x11, 0x3, 0x2, 0x2, 0x2, 0xe9, 0xea, 0x5, 
       0x18, 0xd, 0x2, 0xea, 0xeb, 0x7, 0xf, 0x2, 0x2, 0xeb, 0x13, 0x3, 
       0x2, 0x2, 0x2, 0xec, 0xef, 0x7, 0x1b, 0x2, 0x2, 0xed, 0xef, 0x5, 
       0x90, 0x49, 0x2, 0xee, 0xec, 0x3, 0x2, 0x2, 0x2, 0xee, 0xed, 0x3, 
       0x2, 0x2, 0x2, 0xef, 0xf2, 0x3, 0x2, 0x2, 0x2, 0xf0, 0xf1, 0x7, 0x63, 
       0x2, 0x2, 0xf1, 0xf3, 0x5, 0x90, 0x49, 0x2, 0xf2, 0xf0, 0x3, 0x2, 
       0x2, 0x2, 0xf2, 0xf3, 0x3, 0x2, 0x2, 0x2, 0xf3, 0x15, 0x3, 0x2, 0x2, 
       0x2, 0xf4, 0xf5, 0x7, 0x64, 0x2, 0x2, 0xf5, 0xf6, 0x7, 0x79, 0x2, 
       0x2, 0xf6, 0x17, 0x3, 0x2, 0x2, 0x2, 0xf7, 0xfa, 0x5, 0x90, 0x49, 
       0x2, 0xf8, 0xf9, 0x7, 0x63, 0x2, 0x2, 0xf9, 0xfb, 0x5, 0x90, 0x49, 
       0x2, 0xfa, 0xf8, 0x3, 0x2, 0x2, 0x2, 0xfa, 0xfb, 0x3, 0x2, 0x2, 0x2, 
       0xfb, 0x19, 0x3, 0x2, 0x2, 0x2, 0xfc, 0xff, 0x7, 0x6a, 0x2, 0x2, 
       0xfd, 0x100, 0x5, 0x1c, 0xf, 0x2, 0xfe, 0x100, 0x5, 0x1e, 0x10, 0x2, 
       0xff, 0xfd, 0x3, 0x2, 0x2, 0x2, 0xff, 0xfe, 0x3, 0x2, 0x2, 0x2, 0x100, 
       0x101, 0x3, 0x2, 0x2, 0x2, 0x101, 0x102, 0x5, 0x9a, 0x4e, 0x2, 0x102, 
       0x109, 0x3, 0x2, 0x2, 0x2, 0x103, 0x104, 0x7, 0x6a, 0x2, 0x2, 0x104, 
       0x105, 0x7, 0x5d, 0x2, 0x2, 0x105, 0x106, 0x5, 0x74, 0x3b, 0x2, 0x106, 
       0x107, 0x5, 0x9a, 0x4e, 0x2, 0x107, 0x109, 0x3, 0x2, 0x2, 0x2, 0x108, 
       0xfc, 0x3, 0x2, 0x2, 0x2, 0x108, 0x103, 0x3, 0x2, 0x2, 0x2, 0x109, 
       0x1b, 0x3, 0x2, 0x2, 0x2, 0x10a, 0x10b, 0x5, 0x14, 0xb, 0x2, 0x10b, 
       0x10c, 0x5, 0x16, 0xc, 0x2, 0x10c, 0x10d, 0x5, 0x9a, 0x4e, 0x2, 0x10d, 
       0x115, 0x3, 0x2, 0x2, 0x2, 0x10e, 0x110, 0x5, 0x10, 0x9, 0x2, 0x10f, 
       0x111, 0x5, 0x16, 0xc, 0x2, 0x110, 0x10f, 0x3, 0x2, 0x2, 0x2, 0x110, 
       0x111, 0x3, 0x2, 0x2, 0x2, 0x111, 0x112, 0x3, 0x2, 0x2, 0x2, 0x112, 
       0x113, 0x5, 0x9a, 0x4e, 0x2, 0x113, 0x115, 0x3, 0x2, 0x2, 0x2, 0x114, 
       0x10a, 0x3, 0x2, 0x2, 0x2, 0x114, 0x10e, 0x3, 0x2, 0x2, 0x2, 0x115, 
       0x1d, 0x3, 0x2, 0x2, 0x2, 0x116, 0x11a, 0x5, 0x20, 0x11, 0x2, 0x117, 
       0x11a, 0x5, 0x52, 0x2a, 0x2, 0x118, 0x11a, 0x5, 0x50, 0x29, 0x2, 
       0x119, 0x116, 0x3, 0x2, 0x2, 0x2, 0x119, 0x117, 0x3, 0x2, 0x2, 0x2, 
       0x119, 0x118, 0x3, 0x2, 0x2, 0x2, 0x11a, 0x1f, 0x3, 0x2, 0x2, 0x2, 
       0x11b, 0x11c, 0x5, 0x22, 0x12, 0x2, 0x11c, 0x11d, 0x5, 0x9a, 0x4e, 
       0x2, 0x11d, 0x21, 0x3, 0x2, 0x2, 0x2, 0x11e, 0x11f, 0x5, 0x2e, 0x18, 
       0x2, 0x11f, 0x124, 0x5, 0x24, 0x13, 0x2, 0x120, 0x121, 0x7, 0xf, 
       0x2, 0x2, 0x121, 0x123, 0x5, 0x24, 0x13, 0x2, 0x122, 0x120, 0x3, 
       0x2, 0x2, 0x2, 0x123, 0x126, 0x3, 0x2, 0x2, 0x2, 0x124, 0x122, 0x3, 
       0x2, 0x2, 0x2, 0x124, 0x125, 0x3, 0x2, 0x2, 0x2, 0x125, 0x23, 0x3, 
       0x2, 0x2, 0x2, 0x126, 0x124, 0x3, 0x2, 0x2, 0x2, 0x127, 0x12a, 0x5, 
       0x76, 0x3c, 0x2, 0x128, 0x129, 0x7, 0x10, 0x2, 0x2, 0x129, 0x12b, 
       0x5, 0x74, 0x3b, 0x2, 0x12a, 0x128, 0x3, 0x2, 0x2, 0x2, 0x12a, 0x12b, 
       0x3, 0x2, 0x2, 0x2, 0x12b, 0x25, 0x3, 0x2, 0x2, 0x2, 0x12c, 0x12d, 
       0x7, 0xe, 0x2, 0x2, 0x12d, 0x27, 0x3, 0x2, 0x2, 0x2, 0x12e, 0x12f, 
       0x6, 0x15, 0x2, 0x2, 0x12f, 0x130, 0x5, 0x72, 0x3a, 0x2, 0x130, 0x131, 
       0x5, 0x9a, 0x4e, 0x2, 0x131, 0x29, 0x3, 0x2, 0x2, 0x2, 0x132, 0x133, 
       0x7, 0x5e, 0x2, 0x2, 0x133, 0x134, 0x7, 0x9, 0x2, 0x2, 0x134, 0x135, 
       0x5, 0x72, 0x3a, 0x2, 0x135, 0x136, 0x7, 0xa, 0x2, 0x2, 0x136, 0x139, 
       0x5, 0x6, 0x4, 0x2, 0x137, 0x138, 0x7, 0x4e, 0x2, 0x2, 0x138, 0x13a, 
       0x5, 0x6, 0x4, 0x2, 0x139, 0x137, 0x3, 0x2, 0x2, 0x2, 0x139, 0x13a, 
       0x3, 0x2, 0x2, 0x2, 0x13a, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x13b, 0x13c, 
       0x7, 0x4a, 0x2, 0x2, 0x13c, 0x13d, 0x5, 0x6, 0x4, 0x2, 0x13d, 0x13e, 
       0x7, 0x58, 0x2, 0x2, 0x13e, 0x13f, 0x7, 0x9, 0x2, 0x2, 0x13f, 0x140, 
       0x5, 0x72, 0x3a, 0x2, 0x140, 0x141, 0x7, 0xa, 0x2, 0x2, 0x141, 0x142, 
       0x5, 0x9a, 0x4e, 0x2, 0x142, 0x174, 0x3, 0x2, 0x2, 0x2, 0x143, 0x144, 
       0x7, 0x58, 0x2, 0x2, 0x144, 0x145, 0x7, 0x9, 0x2, 0x2, 0x145, 0x146, 
       0x5, 0x72, 0x3a, 0x2, 0x146, 0x147, 0x7, 0xa, 0x2, 0x2, 0x147, 0x148, 
       0x5, 0x6, 0x4, 0x2, 0x148, 0x174, 0x3, 0x2, 0x2, 0x2, 0x149, 0x14a, 
       0x7, 0x56, 0x2, 0x2, 0x14a, 0x14d, 0x7, 0x9, 0x2, 0x2, 0x14b, 0x14e, 
       0x5, 0x72, 0x3a, 0x2, 0x14c, 0x14e, 0x5, 0x22, 0x12, 0x2, 0x14d, 
       0x14b, 0x3, 0x2, 0x2, 0x2, 0x14d, 0x14c, 0x3, 0x2, 0x2, 0x2, 0x14d, 
       0x14e, 0x3, 0x2, 0x2, 0x2, 0x14e, 0x14f, 0x3, 0x2, 0x2, 0x2, 0x14f, 
       0x151, 0x7, 0xe, 0x2, 0x2, 0x150, 0x152, 0x5, 0x72, 0x3a, 0x2, 0x151, 
       0x150, 0x3, 0x2, 0x2, 0x2, 0x151, 0x152, 0x3, 0x2, 0x2, 0x2, 0x152, 
       0x153, 0x3, 0x2, 0x2, 0x2, 0x153, 0x155, 0x7, 0xe, 0x2, 0x2, 0x154, 
       0x156, 0x5, 0x72, 0x3a, 0x2, 0x155, 0x154, 0x3, 0x2, 0x2, 0x2, 0x155, 
       0x156, 0x3, 0x2, 0x2, 0x2, 0x156, 0x157, 0x3, 0x2, 0x2, 0x2, 0x157, 
       0x158, 0x7, 0xa, 0x2, 0x2, 0x158, 0x174, 0x5, 0x6, 0x4, 0x2, 0x159, 
       0x15a, 0x7, 0x56, 0x2, 0x2, 0x15a, 0x15d, 0x7, 0x9, 0x2, 0x2, 0x15b, 
       0x15e, 0x5, 0x74, 0x3b, 0x2, 0x15c, 0x15e, 0x5, 0x22, 0x12, 0x2, 
       0x15d, 0x15b, 0x3, 0x2, 0x2, 0x2, 0x15d, 0x15c, 0x3, 0x2, 0x2, 0x2, 
       0x15e, 0x15f, 0x3, 0x2, 0x2, 0x2, 0x15f, 0x160, 0x7, 0x61, 0x2, 0x2, 
       0x160, 0x161, 0x5, 0x72, 0x3a, 0x2, 0x161, 0x162, 0x7, 0xa, 0x2, 
       0x2, 0x162, 0x163, 0x5, 0x6, 0x4, 0x2, 0x163, 0x174, 0x3, 0x2, 0x2, 
       0x2, 0x164, 0x166, 0x7, 0x56, 0x2, 0x2, 0x165, 0x167, 0x7, 0x6d, 
       0x2, 0x2, 0x166, 0x165, 0x3, 0x2, 0x2, 0x2, 0x166, 0x167, 0x3, 0x2, 
       0x2, 0x2, 0x167, 0x168, 0x3, 0x2, 0x2, 0x2, 0x168, 0x16b, 0x7, 0x9, 
       0x2, 0x2, 0x169, 0x16c, 0x5, 0x74, 0x3b, 0x2, 0x16a, 0x16c, 0x5, 
       0x22, 0x12, 0x2, 0x16b, 0x169, 0x3, 0x2, 0x2, 0x2, 0x16b, 0x16a, 
       0x3, 0x2, 0x2, 0x2, 0x16c, 0x16d, 0x3, 0x2, 0x2, 0x2, 0x16d, 0x16e, 
       0x5, 0x92, 0x4a, 0x2, 0x16e, 0x16f, 0x6, 0x17, 0x3, 0x2, 0x16f, 0x170, 
       0x5, 0x72, 0x3a, 0x2, 0x170, 0x171, 0x7, 0xa, 0x2, 0x2, 0x171, 0x172, 
       0x5, 0x6, 0x4, 0x2, 0x172, 0x174, 0x3, 0x2, 0x2, 0x2, 0x173, 0x13b, 
       0x3, 0x2, 0x2, 0x2, 0x173, 0x143, 0x3, 0x2, 0x2, 0x2, 0x173, 0x149, 
       0x3, 0x2, 0x2, 0x2, 0x173, 0x159, 0x3, 0x2, 0x2, 0x2, 0x173, 0x164, 
       0x3, 0x2, 0x2, 0x2, 0x174, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x175, 0x179, 
       0x7, 0x50, 0x2, 0x2, 0x176, 0x179, 0x5, 0x98, 0x4d, 0x2, 0x177, 0x179, 
       0x7, 0x69, 0x2, 0x2, 0x178, 0x175, 0x3, 0x2, 0x2, 0x2, 0x178, 0x176, 
       0x3, 0x2, 0x2, 0x2, 0x178, 0x177, 0x3, 0x2, 0x2, 0x2, 0x179, 0x2f, 
       0x3, 0x2, 0x2, 0x2, 0x17a, 0x17d, 0x7, 0x55, 0x2, 0x2, 0x17b, 0x17c, 
       0x6, 0x19, 0x4, 0x2, 0x17c, 0x17e, 0x5, 0x92, 0x4a, 0x2, 0x17d, 0x17b, 
       0x3, 0x2, 0x2, 0x2, 0x17d, 0x17e, 0x3, 0x2, 0x2, 0x2, 0x17e, 0x17f, 
       0x3, 0x2, 0x2, 0x2, 0x17f, 0x180, 0x5, 0x9a, 0x4e, 0x2, 0x180, 0x31, 
       0x3, 0x2, 0x2, 0x2, 0x181, 0x184, 0x7, 0x49, 0x2, 0x2, 0x182, 0x183, 
       0x6, 0x1a, 0x5, 0x2, 0x183, 0x185, 0x5, 0x92, 0x4a, 0x2, 0x184, 0x182, 
       0x3, 0x2, 0x2, 0x2, 0x184, 0x185, 0x3, 0x2, 0x2, 0x2, 0x185, 0x186, 
       0x3, 0x2, 0x2, 0x2, 0x186, 0x187, 0x5, 0x9a, 0x4e, 0x2, 0x187, 0x33, 
       0x3, 0x2, 0x2, 0x2, 0x188, 0x18b, 0x7, 0x53, 0x2, 0x2, 0x189, 0x18a, 
       0x6, 0x1b, 0x6, 0x2, 0x18a, 0x18c, 0x5, 0x72, 0x3a, 0x2, 0x18b, 0x189, 
       0x3, 0x2, 0x2, 0x2, 0x18b, 0x18c, 0x3, 0x2, 0x2, 0x2, 0x18c, 0x18d, 
       0x3, 0x2, 0x2, 0x2, 0x18d, 0x18e, 0x5, 0x9a, 0x4e, 0x2, 0x18e, 0x35, 
       0x3, 0x2, 0x2, 0x2, 0x18f, 0x192, 0x7, 0x6e, 0x2, 0x2, 0x190, 0x191, 
       0x6, 0x1c, 0x7, 0x2, 0x191, 0x193, 0x5, 0x72, 0x3a, 0x2, 0x192, 0x190, 
       0x3, 0x2, 0x2, 0x2, 0x192, 0x193, 0x3, 0x2, 0x2, 0x2, 0x193, 0x194, 
       0x3, 0x2, 0x2, 0x2, 0x194, 0x195, 0x5, 0x9a, 0x4e, 0x2, 0x195, 0x37, 
       0x3, 0x2, 0x2, 0x2, 0x196, 0x197, 0x7, 0x5c, 0x2, 0x2, 0x197, 0x198, 
       0x7, 0x9, 0x2, 0x2, 0x198, 0x199, 0x5, 0x72, 0x3a, 0x2, 0x199, 0x19a, 
       0x7, 0xa, 0x2, 0x2, 0x19a, 0x19b, 0x5, 0x6, 0x4, 0x2, 0x19b, 0x39, 
       0x3, 0x2, 0x2, 0x2, 0x19c, 0x19d, 0x7, 0x57, 0x2, 0x2, 0x19d, 0x19e, 
       0x7, 0x9, 0x2, 0x2, 0x19e, 0x19f, 0x5, 0x72, 0x3a, 0x2, 0x19f, 0x1a0, 
       0x7, 0xa, 0x2, 0x2, 0x1a0, 0x1a1, 0x5, 0x3c, 0x1f, 0x2, 0x1a1, 0x3b, 
       0x3, 0x2, 0x2, 0x2, 0x1a2, 0x1a4, 0x7, 0xb, 0x2, 0x2, 0x1a3, 0x1a5, 
       0x5, 0x3e, 0x20, 0x2, 0x1a4, 0x1a3, 0x3, 0x2, 0x2, 0x2, 0x1a4, 0x1a5, 
       0x3, 0x2, 0x2, 0x2, 0x1a5, 0x1aa, 0x3, 0x2, 0x2, 0x2, 0x1a6, 0x1a8, 
       0x5, 0x42, 0x22, 0x2, 0x1a7, 0x1a9, 0x5, 0x3e, 0x20, 0x2, 0x1a8, 
       0x1a7, 0x3, 0x2, 0x2, 0x2, 0x1a8, 0x1a9, 0x3, 0x2, 0x2, 0x2, 0x1a9, 
       0x1ab, 0x3, 0x2, 0x2, 0x2, 0x1aa, 0x1a6, 0x3, 0x2, 0x2, 0x2, 0x1aa, 
       0x1ab, 0x3, 0x2, 0x2, 0x2, 0x1ab, 0x1ac, 0x3, 0x2, 0x2, 0x2, 0x1ac, 
       0x1ad, 0x7, 0xd, 0x2, 0x2, 0x1ad, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x1ae, 
       0x1b0, 0x5, 0x40, 0x21, 0x2, 0x1af, 0x1ae, 0x3, 0x2, 0x2, 0x2, 0x1b0, 
       0x1b1, 0x3, 0x2, 0x2, 0x2, 0x1b1, 0x1af, 0x3, 0x2, 0x2, 0x2, 0x1b1, 
       0x1b2, 0x3, 0x2, 0x2, 0x2, 0x1b2, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x1b3, 
       0x1b4, 0x7, 0x4d, 0x2, 0x2, 0x1b4, 0x1b5, 0x5, 0x72, 0x3a, 0x2, 0x1b5, 
       0x1b7, 0x7, 0x12, 0x2, 0x2, 0x1b6, 0x1b8, 0x5, 0xa, 0x6, 0x2, 0x1b7, 
       0x1b6, 0x3, 0x2, 0x2, 0x2, 0x1b7, 0x1b8, 0x3, 0x2, 0x2, 0x2, 0x1b8, 
       0x41, 0x3, 0x2, 0x2, 0x2, 0x1b9, 0x1ba, 0x7, 0x5d, 0x2, 0x2, 0x1ba, 
       0x1bc, 0x7, 0x12, 0x2, 0x2, 0x1bb, 0x1bd, 0x5, 0xa, 0x6, 0x2, 0x1bc, 
       0x1bb, 0x3, 0x2, 0x2, 0x2, 0x1bc, 0x1bd, 0x3, 0x2, 0x2, 0x2, 0x1bd, 
       0x43, 0x3, 0x2, 0x2, 0x2, 0x1be, 0x1bf, 0x5, 0x92, 0x4a, 0x2, 0x1bf, 
       0x1c0, 0x7, 0x12, 0x2, 0x2, 0x1c0, 0x1c1, 0x5, 0x6, 0x4, 0x2, 0x1c1, 
       0x45, 0x3, 0x2, 0x2, 0x2, 0x1c2, 0x1c3, 0x7, 0x5f, 0x2, 0x2, 0x1c3, 
       0x1c4, 0x6, 0x24, 0x8, 0x2, 0x1c4, 0x1c5, 0x5, 0x72, 0x3a, 0x2, 0x1c5, 
       0x1c6, 0x5, 0x9a, 0x4e, 0x2, 0x1c6, 0x47, 0x3, 0x2, 0x2, 0x2, 0x1c7, 
       0x1c8, 0x7, 0x62, 0x2, 0x2, 0x1c8, 0x1ce, 0x5, 0x8, 0x5, 0x2, 0x1c9, 
       0x1cb, 0x5, 0x4a, 0x26, 0x2, 0x1ca, 0x1cc, 0x5, 0x4c, 0x27, 0x2, 
       0x1cb, 0x1ca, 0x3, 0x2, 0x2, 0x2, 0x1cb, 0x1cc, 0x3, 0x2, 0x2, 0x2, 
       0x1cc, 0x1cf, 0x3, 0x2, 0x2, 0x2, 0x1cd, 0x1cf, 0x5, 0x4c, 0x27, 
       0x2, 0x1ce, 0x1c9, 0x3, 0x2, 0x2, 0x2, 0x1ce, 0x1cd, 0x3, 0x2, 0x2, 
       0x2, 0x1cf, 0x49, 0x3, 0x2, 0x2, 0x2, 0x1d0, 0x1d6, 0x7, 0x51, 0x2, 
       0x2, 0x1d1, 0x1d3, 0x7, 0x9, 0x2, 0x2, 0x1d2, 0x1d4, 0x5, 0x76, 0x3c, 
       0x2, 0x1d3, 0x1d2, 0x3, 0x2, 0x2, 0x2, 0x1d3, 0x1d4, 0x3, 0x2, 0x2, 
       0x2, 0x1d4, 0x1d5, 0x3, 0x2, 0x2, 0x2, 0x1d5, 0x1d7, 0x7, 0xa, 0x2, 
       0x2, 0x1d6, 0x1d1, 0x3, 0x2, 0x2, 0x2, 0x1d6, 0x1d7, 0x3, 0x2, 0x2, 
       0x2, 0x1d7, 0x1d8, 0x3, 0x2, 0x2, 0x2, 0x1d8, 0x1d9, 0x5, 0x8, 0x5, 
       0x2, 0x1d9, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x1da, 0x1db, 0x7, 0x52, 0x2, 
       0x2, 0x1db, 0x1dc, 0x5, 0x8, 0x5, 0x2, 0x1dc, 0x4d, 0x3, 0x2, 0x2, 
       0x2, 0x1dd, 0x1de, 0x7, 0x59, 0x2, 0x2, 0x1de, 0x1df, 0x5, 0x9a, 
       0x4e, 0x2, 0x1df, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x1e0, 0x1e2, 0x7, 0x6c, 
       0x2, 0x2, 0x1e1, 0x1e0, 0x3, 0x2, 0x2, 0x2, 0x1e1, 0x1e2, 0x3, 0x2, 
       0x2, 0x2, 0x1e2, 0x1e3, 0x3, 0x2, 0x2, 0x2, 0x1e3, 0x1e5, 0x7, 0x5a, 
       0x2, 0x2, 0x1e4, 0x1e6, 0x7, 0x1b, 0x2, 0x2, 0x1e5, 0x1e4, 0x3, 0x2, 
       0x2, 0x2, 0x1e5, 0x1e6, 0x3, 0x2, 0x2, 0x2, 0x1e6, 0x1e7, 0x3, 0x2, 
       0x2, 0x2, 0x1e7, 0x1e8, 0x5, 0x92, 0x4a, 0x2, 0x1e8, 0x1ea, 0x7, 
       0x9, 0x2, 0x2, 0x1e9, 0x1eb, 0x5, 0x5a, 0x2e, 0x2, 0x1ea, 0x1e9, 
       0x3, 0x2, 0x2, 0x2, 0x1ea, 0x1eb, 0x3, 0x2, 0x2, 0x2, 0x1eb, 0x1ec, 
       0x3, 0x2, 0x2, 0x2, 0x1ec, 0x1ed, 0x7, 0xa, 0x2, 0x2, 0x1ed, 0x1ee, 
       0x5, 0x60, 0x31, 0x2, 0x1ee, 0x51, 0x3, 0x2, 0x2, 0x2, 0x1ef, 0x1f0, 
       0x7, 0x65, 0x2, 0x2, 0x1f0, 0x1f1, 0x5, 0x92, 0x4a, 0x2, 0x1f1, 0x1f2, 
       0x5, 0x54, 0x2b, 0x2, 0x1f2, 0x53, 0x3, 0x2, 0x2, 0x2, 0x1f3, 0x1f4, 
       0x7, 0x67, 0x2, 0x2, 0x1f4, 0x1f6, 0x5, 0x74, 0x3b, 0x2, 0x1f5, 0x1f3, 
       0x3, 0x2, 0x2, 0x2, 0x1f5, 0x1f6, 0x3, 0x2, 0x2, 0x2, 0x1f6, 0x1f7, 
       0x3, 0x2, 0x2, 0x2, 0x1f7, 0x1fb, 0x7, 0xb, 0x2, 0x2, 0x1f8, 0x1fa, 
       0x5, 0x56, 0x2c, 0x2, 0x1f9, 0x1f8, 0x3, 0x2, 0x2, 0x2, 0x1fa, 0x1fd, 
       0x3, 0x2, 0x2, 0x2, 0x1fb, 0x1f9, 0x3, 0x2, 0x2, 0x2, 0x1fb, 0x1fc, 
       0x3, 0x2, 0x2, 0x2, 0x1fc, 0x1fe, 0x3, 0x2, 0x2, 0x2, 0x1fd, 0x1fb, 
       0x3, 0x2, 0x2, 0x2, 0x1fe, 0x1ff, 0x7, 0xd, 0x2, 0x2, 0x1ff, 0x55, 
       0x3, 0x2, 0x2, 0x2, 0x200, 0x205, 0x7, 0x77, 0x2, 0x2, 0x201, 0x202, 
       0x6, 0x2c, 0x9, 0x2, 0x202, 0x205, 0x5, 0x92, 0x4a, 0x2, 0x203, 0x205, 
       0x7, 0x6c, 0x2, 0x2, 0x204, 0x200, 0x3, 0x2, 0x2, 0x2, 0x204, 0x201, 
       0x3, 0x2, 0x2, 0x2, 0x204, 0x203, 0x3, 0x2, 0x2, 0x2, 0x205, 0x208, 
       0x3, 0x2, 0x2, 0x2, 0x206, 0x204, 0x3, 0x2, 0x2, 0x2, 0x206, 0x207, 
       0x3, 0x2, 0x2, 0x2, 0x207, 0x20f, 0x3, 0x2, 0x2, 0x2, 0x208, 0x206, 
       0x3, 0x2, 0x2, 0x2, 0x209, 0x210, 0x5, 0x58, 0x2d, 0x2, 0x20a, 0x20b, 
       0x5, 0x76, 0x3c, 0x2, 0x20b, 0x20c, 0x7, 0x10, 0x2, 0x2, 0x20c, 0x20d, 
       0x5, 0x78, 0x3d, 0x2, 0x20d, 0x20e, 0x7, 0xe, 0x2, 0x2, 0x20e, 0x210, 
       0x3, 0x2, 0x2, 0x2, 0x20f, 0x209, 0x3, 0x2, 0x2, 0x2, 0x20f, 0x20a, 
       0x3, 0x2, 0x2, 0x2, 0x210, 0x21a, 0x3, 0x2, 0x2, 0x2, 0x211, 0x21a, 
       0x5, 0x26, 0x14, 0x2, 0x212, 0x214, 0x7, 0x20, 0x2, 0x2, 0x213, 0x212, 
       0x3, 0x2, 0x2, 0x2, 0x213, 0x214, 0x3, 0x2, 0x2, 0x2, 0x214, 0x215, 
       0x3, 0x2, 0x2, 0x2, 0x215, 0x216, 0x5, 0x6c, 0x37, 0x2, 0x216, 0x217, 
       0x7, 0x10, 0x2, 0x2, 0x217, 0x218, 0x5, 0x74, 0x3b, 0x2, 0x218, 0x21a, 
       0x3, 0x2, 0x2, 0x2, 0x219, 0x206, 0x3, 0x2, 0x2, 0x2, 0x219, 0x211, 
       0x3, 0x2, 0x2, 0x2, 0x219, 0x213, 0x3, 0x2, 0x2, 0x2, 0x21a, 0x57, 
       0x3, 0x2, 0x2, 0x2, 0x21b, 0x21d, 0x7, 0x1b, 0x2, 0x2, 0x21c, 0x21b, 
       0x3, 0x2, 0x2, 0x2, 0x21c, 0x21d, 0x3, 0x2, 0x2, 0x2, 0x21d, 0x21f, 
       0x3, 0x2, 0x2, 0x2, 0x21e, 0x220, 0x7, 0x20, 0x2, 0x2, 0x21f, 0x21e, 
       0x3, 0x2, 0x2, 0x2, 0x21f, 0x220, 0x3, 0x2, 0x2, 0x2, 0x220, 0x221, 
       0x3, 0x2, 0x2, 0x2, 0x221, 0x222, 0x5, 0x6c, 0x37, 0x2, 0x222, 0x224, 
       0x7, 0x9, 0x2, 0x2, 0x223, 0x225, 0x5, 0x5a, 0x2e, 0x2, 0x224, 0x223, 
       0x3, 0x2, 0x2, 0x2, 0x224, 0x225, 0x3, 0x2, 0x2, 0x2, 0x225, 0x226, 
       0x3, 0x2, 0x2, 0x2, 0x226, 0x227, 0x7, 0xa, 0x2, 0x2, 0x227, 0x228, 
       0x5, 0x60, 0x31, 0x2, 0x228, 0x243, 0x3, 0x2, 0x2, 0x2, 0x229, 0x22b, 
       0x7, 0x1b, 0x2, 0x2, 0x22a, 0x229, 0x3, 0x2, 0x2, 0x2, 0x22a, 0x22b, 
       0x3, 0x2, 0x2, 0x2, 0x22b, 0x22d, 0x3, 0x2, 0x2, 0x2, 0x22c, 0x22e, 
       0x7, 0x20, 0x2, 0x2, 0x22d, 0x22c, 0x3, 0x2, 0x2, 0x2, 0x22d, 0x22e, 
       0x3, 0x2, 0x2, 0x2, 0x22e, 0x22f, 0x3, 0x2, 0x2, 0x2, 0x22f, 0x230, 
       0x5, 0x8c, 0x47, 0x2, 0x230, 0x231, 0x7, 0x9, 0x2, 0x2, 0x231, 0x232, 
       0x7, 0xa, 0x2, 0x2, 0x232, 0x233, 0x5, 0x60, 0x31, 0x2, 0x233, 0x243, 
       0x3, 0x2, 0x2, 0x2, 0x234, 0x236, 0x7, 0x1b, 0x2, 0x2, 0x235, 0x234, 
       0x3, 0x2, 0x2, 0x2, 0x235, 0x236, 0x3, 0x2, 0x2, 0x2, 0x236, 0x238, 
       0x3, 0x2, 0x2, 0x2, 0x237, 0x239, 0x7, 0x20, 0x2, 0x2, 0x238, 0x237, 
       0x3, 0x2, 0x2, 0x2, 0x238, 0x239, 0x3, 0x2, 0x2, 0x2, 0x239, 0x23a, 
       0x3, 0x2, 0x2, 0x2, 0x23a, 0x23b, 0x5, 0x8e, 0x48, 0x2, 0x23b, 0x23d, 
       0x7, 0x9, 0x2, 0x2, 0x23c, 0x23e, 0x5, 0x5a, 0x2e, 0x2, 0x23d, 0x23c, 
       0x3, 0x2, 0x2, 0x2, 0x23d, 0x23e, 0x3, 0x2, 0x2, 0x2, 0x23e, 0x23f, 
       0x3, 0x2, 0x2, 0x2, 0x23f, 0x240, 0x7, 0xa, 0x2, 0x2, 0x240, 0x241, 
       0x5, 0x60, 0x31, 0x2, 0x241, 0x243, 0x3, 0x2, 0x2, 0x2, 0x242, 0x21c, 
       0x3, 0x2, 0x2, 0x2, 0x242, 0x22a, 0x3, 0x2, 0x2, 0x2, 0x242, 0x235, 
       0x3, 0x2, 0x2, 0x2, 0x243, 0x59, 0x3, 0x2, 0x2, 0x2, 0x244, 0x249, 
       0x5, 0x5c, 0x2f, 0x2, 0x245, 0x246, 0x7, 0xf, 0x2, 0x2, 0x246, 0x248, 
       0x5, 0x5c, 0x2f, 0x2, 0x247, 0x245, 0x3, 0x2, 0x2, 0x2, 0x248, 0x24b, 
       0x3, 0x2, 0x2, 0x2, 0x249, 0x247, 0x3, 0x2, 0x2, 0x2, 0x249, 0x24a, 
       0x3, 0x2, 0x2, 0x2, 0x24a, 0x24e, 0x3, 0x2, 0x2, 0x2, 0x24b, 0x249, 
       0x3, 0x2, 0x2, 0x2, 0x24c, 0x24d, 0x7, 0xf, 0x2, 0x2, 0x24d, 0x24f, 
       0x5, 0x5e, 0x30, 0x2, 0x24e, 0x24c, 0x3, 0x2, 0x2, 0x2, 0x24e, 0x24f, 
       0x3, 0x2, 0x2, 0x2, 0x24f, 0x252, 0x3, 0x2, 0x2, 0x2, 0x250, 0x252, 
       0x5, 0x5e, 0x30, 0x2, 0x251, 0x244, 0x3, 0x2, 0x2, 0x2, 0x251, 0x250, 
       0x3, 0x2, 0x2, 0x2, 0x252, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x253, 0x256, 
       0x5, 0x76, 0x3c, 0x2, 0x254, 0x255, 0x7, 0x10, 0x2, 0x2, 0x255, 0x257, 
       0x5, 0x74, 0x3b, 0x2, 0x256, 0x254, 0x3, 0x2, 0x2, 0x2, 0x256, 0x257, 
       0x3, 0x2, 0x2, 0x2, 0x257, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x258, 0x259, 
       0x7, 0x13, 0x2, 0x2, 0x259, 0x25a, 0x5, 0x74, 0x3b, 0x2, 0x25a, 0x5f, 
       0x3, 0x2, 0x2, 0x2, 0x25b, 0x25d, 0x7, 0xb, 0x2, 0x2, 0x25c, 0x25e, 
       0x5, 0x62, 0x32, 0x2, 0x25d, 0x25c, 0x3, 0x2, 0x2, 0x2, 0x25d, 0x25e, 
       0x3, 0x2, 0x2, 0x2, 0x25e, 0x25f, 0x3, 0x2, 0x2, 0x2, 0x25f, 0x260, 
       0x7, 0xd, 0x2, 0x2, 0x260, 0x61, 0x3, 0x2, 0x2, 0x2, 0x261, 0x263, 
       0x5, 0x4, 0x3, 0x2, 0x262, 0x261, 0x3, 0x2, 0x2, 0x2, 0x263, 0x264, 
       0x3, 0x2, 0x2, 0x2, 0x264, 0x262, 0x3, 0x2, 0x2, 0x2, 0x264, 0x265, 
       0x3, 0x2, 0x2, 0x2, 0x265, 0x63, 0x3, 0x2, 0x2, 0x2, 0x266, 0x267, 
       0x7, 0x7, 0x2, 0x2, 0x267, 0x268, 0x5, 0x66, 0x34, 0x2, 0x268, 0x269, 
       0x7, 0x8, 0x2, 0x2, 0x269, 0x65, 0x3, 0x2, 0x2, 0x2, 0x26a, 0x26c, 
       0x7, 0xf, 0x2, 0x2, 0x26b, 0x26a, 0x3, 0x2, 0x2, 0x2, 0x26c, 0x26f, 
       0x3, 0x2, 0x2, 0x2, 0x26d, 0x26b, 0x3, 0x2, 0x2, 0x2, 0x26d, 0x26e, 
       0x3, 0x2, 0x2, 0x2, 0x26e, 0x271, 0x3, 0x2, 0x2, 0x2, 0x26f, 0x26d, 
       0x3, 0x2, 0x2, 0x2, 0x270, 0x272, 0x5, 0x68, 0x35, 0x2, 0x271, 0x270, 
       0x3, 0x2, 0x2, 0x2, 0x271, 0x272, 0x3, 0x2, 0x2, 0x2, 0x272, 0x27b, 
       0x3, 0x2, 0x2, 0x2, 0x273, 0x275, 0x7, 0xf, 0x2, 0x2, 0x274, 0x273, 
       0x3, 0x2, 0x2, 0x2, 0x275, 0x276, 0x3, 0x2, 0x2, 0x2, 0x276, 0x274, 
       0x3, 0x2, 0x2, 0x2, 0x276, 0x277, 0x3, 0x2, 0x2, 0x2, 0x277, 0x278, 
       0x3, 0x2, 0x2, 0x2, 0x278, 0x27a, 0x5, 0x68, 0x35, 0x2, 0x279, 0x274, 
       0x3, 0x2, 0x2, 0x2, 0x27a, 0x27d, 0x3, 0x2, 0x2, 0x2, 0x27b, 0x279, 
       0x3, 0x2, 0x2, 0x2, 0x27b, 0x27c, 0x3, 0x2, 0x2, 0x2, 0x27c, 0x281, 
       0x3, 0x2, 0x2, 0x2, 0x27d, 0x27b, 0x3, 0x2, 0x2, 0x2, 0x27e, 0x280, 
       0x7, 0xf, 0x2, 0x2, 0x27f, 0x27e, 0x3, 0x2, 0x2, 0x2, 0x280, 0x283, 
       0x3, 0x2, 0x2, 0x2, 0x281, 0x27f, 0x3, 0x2, 0x2, 0x2, 0x281, 0x282, 
       0x3, 0x2, 0x2, 0x2, 0x282, 0x67, 0x3, 0x2, 0x2, 0x2, 0x283, 0x281, 
       0x3, 0x2, 0x2, 0x2, 0x284, 0x286, 0x7, 0x13, 0x2, 0x2, 0x285, 0x284, 
       0x3, 0x2, 0x2, 0x2, 0x285, 0x286, 0x3, 0x2, 0x2, 0x2, 0x286, 0x287, 
       0x3, 0x2, 0x2, 0x2, 0x287, 0x288, 0x5, 0x74, 0x3b, 0x2, 0x288, 0x69, 
       0x3, 0x2, 0x2, 0x2, 0x289, 0x28a, 0x5, 0x6c, 0x37, 0x2, 0x28a, 0x28b, 
       0x7, 0x12, 0x2, 0x2, 0x28b, 0x28c, 0x5, 0x74, 0x3b, 0x2, 0x28c, 0x2b1, 
       0x3, 0x2, 0x2, 0x2, 0x28d, 0x28e, 0x7, 0x7, 0x2, 0x2, 0x28e, 0x28f, 
       0x5, 0x74, 0x3b, 0x2, 0x28f, 0x290, 0x7, 0x8, 0x2, 0x2, 0x290, 0x291, 
       0x7, 0x12, 0x2, 0x2, 0x291, 0x292, 0x5, 0x74, 0x3b, 0x2, 0x292, 0x2b1, 
       0x3, 0x2, 0x2, 0x2, 0x293, 0x295, 0x7, 0x6c, 0x2, 0x2, 0x294, 0x293, 
       0x3, 0x2, 0x2, 0x2, 0x294, 0x295, 0x3, 0x2, 0x2, 0x2, 0x295, 0x297, 
       0x3, 0x2, 0x2, 0x2, 0x296, 0x298, 0x7, 0x1b, 0x2, 0x2, 0x297, 0x296, 
       0x3, 0x2, 0x2, 0x2, 0x297, 0x298, 0x3, 0x2, 0x2, 0x2, 0x298, 0x299, 
       0x3, 0x2, 0x2, 0x2, 0x299, 0x29a, 0x5, 0x6c, 0x37, 0x2, 0x29a, 0x29c, 
       0x7, 0x9, 0x2, 0x2, 0x29b, 0x29d, 0x5, 0x5a, 0x2e, 0x2, 0x29c, 0x29b, 
       0x3, 0x2, 0x2, 0x2, 0x29c, 0x29d, 0x3, 0x2, 0x2, 0x2, 0x29d, 0x29e, 
       0x3, 0x2, 0x2, 0x2, 0x29e, 0x29f, 0x7, 0xa, 0x2, 0x2, 0x29f, 0x2a0, 
       0x5, 0x60, 0x31, 0x2, 0x2a0, 0x2b1, 0x3, 0x2, 0x2, 0x2, 0x2a1, 0x2a2, 
       0x5, 0x8c, 0x47, 0x2, 0x2a2, 0x2a3, 0x7, 0x9, 0x2, 0x2, 0x2a3, 0x2a4, 
       0x7, 0xa, 0x2, 0x2, 0x2a4, 0x2a5, 0x5, 0x60, 0x31, 0x2, 0x2a5, 0x2b1, 
       0x3, 0x2, 0x2, 0x2, 0x2a6, 0x2a7, 0x5, 0x8e, 0x48, 0x2, 0x2a7, 0x2a8, 
       0x7, 0x9, 0x2, 0x2, 0x2a8, 0x2a9, 0x5, 0x5c, 0x2f, 0x2, 0x2a9, 0x2aa, 
       0x7, 0xa, 0x2, 0x2, 0x2aa, 0x2ab, 0x5, 0x60, 0x31, 0x2, 0x2ab, 0x2b1, 
       0x3, 0x2, 0x2, 0x2, 0x2ac, 0x2ae, 0x7, 0x13, 0x2, 0x2, 0x2ad, 0x2ac, 
       0x3, 0x2, 0x2, 0x2, 0x2ad, 0x2ae, 0x3, 0x2, 0x2, 0x2, 0x2ae, 0x2af, 
       0x3, 0x2, 0x2, 0x2, 0x2af, 0x2b1, 0x5, 0x74, 0x3b, 0x2, 0x2b0, 0x289, 
       0x3, 0x2, 0x2, 0x2, 0x2b0, 0x28d, 0x3, 0x2, 0x2, 0x2, 0x2b0, 0x294, 
       0x3, 0x2, 0x2, 0x2, 0x2b0, 0x2a1, 0x3, 0x2, 0x2, 0x2, 0x2b0, 0x2a6, 
       0x3, 0x2, 0x2, 0x2, 0x2b0, 0x2ad, 0x3, 0x2, 0x2, 0x2, 0x2b1, 0x6b, 
       0x3, 0x2, 0x2, 0x2, 0x2b2, 0x2ba, 0x5, 0x90, 0x49, 0x2, 0x2b3, 0x2ba, 
       0x7, 0x79, 0x2, 0x2, 0x2b4, 0x2ba, 0x5, 0x88, 0x45, 0x2, 0x2b5, 0x2b6, 
       0x7, 0x7, 0x2, 0x2, 0x2b6, 0x2b7, 0x5, 0x74, 0x3b, 0x2, 0x2b7, 0x2b8, 
       0x7, 0x8, 0x2, 0x2, 0x2b8, 0x2ba, 0x3, 0x2, 0x2, 0x2, 0x2b9, 0x2b2, 
       0x3, 0x2, 0x2, 0x2, 0x2b9, 0x2b3, 0x3, 0x2, 0x2, 0x2, 0x2b9, 0x2b4, 
       0x3, 0x2, 0x2, 0x2, 0x2b9, 0x2b5, 0x3, 0x2, 0x2, 0x2, 0x2ba, 0x6d, 
       0x3, 0x2, 0x2, 0x2, 0x2bb, 0x2c7, 0x7, 0x9, 0x2, 0x2, 0x2bc, 0x2c1, 
       0x5, 0x70, 0x39, 0x2, 0x2bd, 0x2be, 0x7, 0xf, 0x2, 0x2, 0x2be, 0x2c0, 
       0x5, 0x70, 0x39, 0x2, 0x2bf, 0x2bd, 0x3, 0x2, 0x2, 0x2, 0x2c0, 0x2c3, 
       0x3, 0x2, 0x2, 0x2, 0x2c1, 0x2bf, 0x3, 0x2, 0x2, 0x2, 0x2c1, 0x2c2, 
       0x3, 0x2, 0x2, 0x2, 0x2c2, 0x2c5, 0x3, 0x2, 0x2, 0x2, 0x2c3, 0x2c1, 
       0x3, 0x2, 0x2, 0x2, 0x2c4, 0x2c6, 0x7, 0xf, 0x2, 0x2, 0x2c5, 0x2c4, 
       0x3, 0x2, 0x2, 0x2, 0x2c5, 0x2c6, 0x3, 0x2, 0x2, 0x2, 0x2c6, 0x2c8, 
       0x3, 0x2, 0x2, 0x2, 0x2c7, 0x2bc, 0x3, 0x2, 0x2, 0x2, 0x2c7, 0x2c8, 
       0x3, 0x2, 0x2, 0x2, 0x2c8, 0x2c9, 0x3, 0x2, 0x2, 0x2, 0x2c9, 0x2ca, 
       0x7, 0xa, 0x2, 0x2, 0x2ca, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x2cb, 0x2cd, 
       0x7, 0x13, 0x2, 0x2, 0x2cc, 0x2cb, 0x3, 0x2, 0x2, 0x2, 0x2cc, 0x2cd, 
       0x3, 0x2, 0x2, 0x2, 0x2cd, 0x2d0, 0x3, 0x2, 0x2, 0x2, 0x2ce, 0x2d1, 
       0x5, 0x74, 0x3b, 0x2, 0x2cf, 0x2d1, 0x5, 0x92, 0x4a, 0x2, 0x2d0, 
       0x2ce, 0x3, 0x2, 0x2, 0x2, 0x2d0, 0x2cf, 0x3, 0x2, 0x2, 0x2, 0x2d1, 
       0x71, 0x3, 0x2, 0x2, 0x2, 0x2d2, 0x2d7, 0x5, 0x74, 0x3b, 0x2, 0x2d3, 
       0x2d4, 0x7, 0xf, 0x2, 0x2, 0x2d4, 0x2d6, 0x5, 0x74, 0x3b, 0x2, 0x2d5, 
       0x2d3, 0x3, 0x2, 0x2, 0x2, 0x2d6, 0x2d9, 0x3, 0x2, 0x2, 0x2, 0x2d7, 
       0x2d5, 0x3, 0x2, 0x2, 0x2, 0x2d7, 0x2d8, 0x3, 0x2, 0x2, 0x2, 0x2d8, 
       0x73, 0x3, 0x2, 0x2, 0x2, 0x2d9, 0x2d7, 0x3, 0x2, 0x2, 0x2, 0x2da, 
       0x2db, 0x8, 0x3b, 0x1, 0x2, 0x2db, 0x30f, 0x5, 0x7a, 0x3e, 0x2, 0x2dc, 
       0x2de, 0x7, 0x65, 0x2, 0x2, 0x2dd, 0x2df, 0x5, 0x92, 0x4a, 0x2, 0x2de, 
       0x2dd, 0x3, 0x2, 0x2, 0x2, 0x2de, 0x2df, 0x3, 0x2, 0x2, 0x2, 0x2df, 
       0x2e0, 0x3, 0x2, 0x2, 0x2, 0x2e0, 0x30f, 0x5, 0x54, 0x2b, 0x2, 0x2e1, 
       0x2e2, 0x7, 0x4f, 0x2, 0x2, 0x2e2, 0x2e3, 0x5, 0x74, 0x3b, 0x2, 0x2e3, 
       0x2e4, 0x5, 0x6e, 0x38, 0x2, 0x2e4, 0x30f, 0x3, 0x2, 0x2, 0x2, 0x2e5, 
       0x2e6, 0x7, 0x4f, 0x2, 0x2, 0x2e6, 0x30f, 0x5, 0x74, 0x3b, 0x2c, 
       0x2e7, 0x2e8, 0x7, 0x4f, 0x2, 0x2, 0x2e8, 0x2e9, 0x7, 0x14, 0x2, 
       0x2, 0x2e9, 0x30f, 0x5, 0x92, 0x4a, 0x2, 0x2ea, 0x2eb, 0x7, 0x60, 
       0x2, 0x2, 0x2eb, 0x30f, 0x5, 0x74, 0x3b, 0x27, 0x2ec, 0x2ed, 0x7, 
       0x54, 0x2, 0x2, 0x2ed, 0x30f, 0x5, 0x74, 0x3b, 0x26, 0x2ee, 0x2ef, 
       0x7, 0x4c, 0x2, 0x2, 0x2ef, 0x30f, 0x5, 0x74, 0x3b, 0x25, 0x2f0, 
       0x2f1, 0x7, 0x15, 0x2, 0x2, 0x2f1, 0x30f, 0x5, 0x74, 0x3b, 0x24, 
       0x2f2, 0x2f3, 0x7, 0x16, 0x2, 0x2, 0x2f3, 0x30f, 0x5, 0x74, 0x3b, 
       0x23, 0x2f4, 0x2f5, 0x7, 0x17, 0x2, 0x2, 0x2f5, 0x30f, 0x5, 0x74, 
       0x3b, 0x22, 0x2f6, 0x2f7, 0x7, 0x18, 0x2, 0x2, 0x2f7, 0x30f, 0x5, 
       0x74, 0x3b, 0x21, 0x2f8, 0x2f9, 0x7, 0x19, 0x2, 0x2, 0x2f9, 0x30f, 
       0x5, 0x74, 0x3b, 0x20, 0x2fa, 0x2fb, 0x7, 0x1a, 0x2, 0x2, 0x2fb, 
       0x30f, 0x5, 0x74, 0x3b, 0x1f, 0x2fc, 0x2fd, 0x7, 0x6d, 0x2, 0x2, 
       0x2fd, 0x30f, 0x5, 0x74, 0x3b, 0x1e, 0x2fe, 0x2ff, 0x7, 0x6b, 0x2, 
       0x2, 0x2ff, 0x300, 0x7, 0x9, 0x2, 0x2, 0x300, 0x301, 0x5, 0x74, 0x3b, 
       0x2, 0x301, 0x302, 0x7, 0xa, 0x2, 0x2, 0x302, 0x30f, 0x3, 0x2, 0x2, 
       0x2, 0x303, 0x30f, 0x5, 0x36, 0x1c, 0x2, 0x304, 0x30f, 0x7, 0x5b, 
       0x2, 0x2, 0x305, 0x30f, 0x5, 0x92, 0x4a, 0x2, 0x306, 0x30f, 0x7, 
       0x68, 0x2, 0x2, 0x307, 0x30f, 0x5, 0x82, 0x42, 0x2, 0x308, 0x30f, 
       0x5, 0x64, 0x33, 0x2, 0x309, 0x30f, 0x5, 0x78, 0x3d, 0x2, 0x30a, 
       0x30b, 0x7, 0x9, 0x2, 0x2, 0x30b, 0x30c, 0x5, 0x72, 0x3a, 0x2, 0x30c, 
       0x30d, 0x7, 0xa, 0x2, 0x2, 0x30d, 0x30f, 0x3, 0x2, 0x2, 0x2, 0x30e, 
       0x2da, 0x3, 0x2, 0x2, 0x2, 0x30e, 0x2dc, 0x3, 0x2, 0x2, 0x2, 0x30e, 
       0x2e1, 0x3, 0x2, 0x2, 0x2, 0x30e, 0x2e5, 0x3, 0x2, 0x2, 0x2, 0x30e, 
       0x2e7, 0x3, 0x2, 0x2, 0x2, 0x30e, 0x2ea, 0x3, 0x2, 0x2, 0x2, 0x30e, 
       0x2ec, 0x3, 0x2, 0x2, 0x2, 0x30e, 0x2ee, 0x3, 0x2, 0x2, 0x2, 0x30e, 
       0x2f0, 0x3, 0x2, 0x2, 0x2, 0x30e, 0x2f2, 0x3, 0x2, 0x2, 0x2, 0x30e, 
       0x2f4, 0x3, 0x2, 0x2, 0x2, 0x30e, 0x2f6, 0x3, 0x2, 0x2, 0x2, 0x30e, 
       0x2f8, 0x3, 0x2, 0x2, 0x2, 0x30e, 0x2fa, 0x3, 0x2, 0x2, 0x2, 0x30e, 
       0x2fc, 0x3, 0x2, 0x2, 0x2, 0x30e, 0x2fe, 0x3, 0x2, 0x2, 0x2, 0x30e, 
       0x303, 0x3, 0x2, 0x2, 0x2, 0x30e, 0x304, 0x3, 0x2, 0x2, 0x2, 0x30e, 
       0x305, 0x3, 0x2, 0x2, 0x2, 0x30e, 0x306, 0x3, 0x2, 0x2, 0x2, 0x30e, 
       0x307, 0x3, 0x2, 0x2, 0x2, 0x30e, 0x308, 0x3, 0x2, 0x2, 0x2, 0x30e, 
       0x309, 0x3, 0x2, 0x2, 0x2, 0x30e, 0x30a, 0x3, 0x2, 0x2, 0x2, 0x30f, 
       0x361, 0x3, 0x2, 0x2, 0x2, 0x310, 0x311, 0xc, 0x1d, 0x2, 0x2, 0x311, 
       0x312, 0x7, 0x1e, 0x2, 0x2, 0x312, 0x360, 0x5, 0x74, 0x3b, 0x1d, 
       0x313, 0x314, 0xc, 0x1c, 0x2, 0x2, 0x314, 0x315, 0x9, 0x2, 0x2, 0x2, 
       0x315, 0x360, 0x5, 0x74, 0x3b, 0x1d, 0x316, 0x317, 0xc, 0x1b, 0x2, 
       0x2, 0x317, 0x318, 0x9, 0x3, 0x2, 0x2, 0x318, 0x360, 0x5, 0x74, 0x3b, 
       0x1c, 0x319, 0x31a, 0xc, 0x1a, 0x2, 0x2, 0x31a, 0x31b, 0x7, 0x1f, 
       0x2, 0x2, 0x31b, 0x360, 0x5, 0x74, 0x3b, 0x1b, 0x31c, 0x31d, 0xc, 
       0x19, 0x2, 0x2, 0x31d, 0x31e, 0x9, 0x4, 0x2, 0x2, 0x31e, 0x360, 0x5, 
       0x74, 0x3b, 0x1a, 0x31f, 0x320, 0xc, 0x18, 0x2, 0x2, 0x320, 0x321, 
       0x9, 0x5, 0x2, 0x2, 0x321, 0x360, 0x5, 0x74, 0x3b, 0x19, 0x322, 0x323, 
       0xc, 0x17, 0x2, 0x2, 0x323, 0x324, 0x7, 0x4b, 0x2, 0x2, 0x324, 0x360, 
       0x5, 0x74, 0x3b, 0x18, 0x325, 0x326, 0xc, 0x16, 0x2, 0x2, 0x326, 
       0x327, 0x7, 0x61, 0x2, 0x2, 0x327, 0x360, 0x5, 0x74, 0x3b, 0x17, 
       0x328, 0x329, 0xc, 0x15, 0x2, 0x2, 0x329, 0x32a, 0x9, 0x6, 0x2, 0x2, 
       0x32a, 0x360, 0x5, 0x74, 0x3b, 0x16, 0x32b, 0x32c, 0xc, 0x14, 0x2, 
       0x2, 0x32c, 0x32d, 0x7, 0x2c, 0x2, 0x2, 0x32d, 0x360, 0x5, 0x74, 
       0x3b, 0x15, 0x32e, 0x32f, 0xc, 0x13, 0x2, 0x2, 0x32f, 0x330, 0x7, 
       0x2d, 0x2, 0x2, 0x330, 0x360, 0x5, 0x74, 0x3b, 0x14, 0x331, 0x332, 
       0xc, 0x12, 0x2, 0x2, 0x332, 0x333, 0x7, 0x2e, 0x2, 0x2, 0x333, 0x360, 
       0x5, 0x74, 0x3b, 0x13, 0x334, 0x335, 0xc, 0x11, 0x2, 0x2, 0x335, 
       0x336, 0x7, 0x2f, 0x2, 0x2, 0x336, 0x360, 0x5, 0x74, 0x3b, 0x12, 
       0x337, 0x338, 0xc, 0x10, 0x2, 0x2, 0x338, 0x339, 0x7, 0x30, 0x2, 
       0x2, 0x339, 0x360, 0x5, 0x74, 0x3b, 0x11, 0x33a, 0x33b, 0xc, 0xf, 
       0x2, 0x2, 0x33b, 0x33c, 0x7, 0x11, 0x2, 0x2, 0x33c, 0x33d, 0x5, 0x74, 
       0x3b, 0x2, 0x33d, 0x33e, 0x7, 0x12, 0x2, 0x2, 0x33e, 0x33f, 0x5, 
       0x74, 0x3b, 0x10, 0x33f, 0x360, 0x3, 0x2, 0x2, 0x2, 0x340, 0x341, 
       0xc, 0xe, 0x2, 0x2, 0x341, 0x342, 0x7, 0x10, 0x2, 0x2, 0x342, 0x360, 
       0x5, 0x74, 0x3b, 0xe, 0x343, 0x344, 0xc, 0xd, 0x2, 0x2, 0x344, 0x345, 
       0x5, 0x80, 0x41, 0x2, 0x345, 0x346, 0x5, 0x74, 0x3b, 0xd, 0x346, 
       0x360, 0x3, 0x2, 0x2, 0x2, 0x347, 0x348, 0xc, 0x2f, 0x2, 0x2, 0x348, 
       0x349, 0x7, 0x7, 0x2, 0x2, 0x349, 0x34a, 0x5, 0x72, 0x3a, 0x2, 0x34a, 
       0x34b, 0x7, 0x8, 0x2, 0x2, 0x34b, 0x360, 0x3, 0x2, 0x2, 0x2, 0x34c, 
       0x34e, 0xc, 0x2e, 0x2, 0x2, 0x34d, 0x34f, 0x7, 0x11, 0x2, 0x2, 0x34e, 
       0x34d, 0x3, 0x2, 0x2, 0x2, 0x34e, 0x34f, 0x3, 0x2, 0x2, 0x2, 0x34f, 
       0x350, 0x3, 0x2, 0x2, 0x2, 0x350, 0x352, 0x7, 0x14, 0x2, 0x2, 0x351, 
       0x353, 0x7, 0x20, 0x2, 0x2, 0x352, 0x351, 0x3, 0x2, 0x2, 0x2, 0x352, 
       0x353, 0x3, 0x2, 0x2, 0x2, 0x353, 0x354, 0x3, 0x2, 0x2, 0x2, 0x354, 
       0x360, 0x5, 0x90, 0x49, 0x2, 0x355, 0x356, 0xc, 0x2b, 0x2, 0x2, 0x356, 
       0x360, 0x5, 0x6e, 0x38, 0x2, 0x357, 0x358, 0xc, 0x29, 0x2, 0x2, 0x358, 
       0x359, 0x6, 0x3b, 0x1f, 0x2, 0x359, 0x360, 0x7, 0x15, 0x2, 0x2, 0x35a, 
       0x35b, 0xc, 0x28, 0x2, 0x2, 0x35b, 0x35c, 0x6, 0x3b, 0x21, 0x2, 0x35c, 
       0x360, 0x7, 0x16, 0x2, 0x2, 0x35d, 0x35e, 0xc, 0xb, 0x2, 0x2, 0x35e, 
       0x360, 0x5, 0x84, 0x43, 0x2, 0x35f, 0x310, 0x3, 0x2, 0x2, 0x2, 0x35f, 
       0x313, 0x3, 0x2, 0x2, 0x2, 0x35f, 0x316, 0x3, 0x2, 0x2, 0x2, 0x35f, 
       0x319, 0x3, 0x2, 0x2, 0x2, 0x35f, 0x31c, 0x3, 0x2, 0x2, 0x2, 0x35f, 
       0x31f, 0x3, 0x2, 0x2, 0x2, 0x35f, 0x322, 0x3, 0x2, 0x2, 0x2, 0x35f, 
       0x325, 0x3, 0x2, 0x2, 0x2, 0x35f, 0x328, 0x3, 0x2, 0x2, 0x2, 0x35f, 
       0x32b, 0x3, 0x2, 0x2, 0x2, 0x35f, 0x32e, 0x3, 0x2, 0x2, 0x2, 0x35f, 
       0x331, 0x3, 0x2, 0x2, 0x2, 0x35f, 0x334, 0x3, 0x2, 0x2, 0x2, 0x35f, 
       0x337, 0x3, 0x2, 0x2, 0x2, 0x35f, 0x33a, 0x3, 0x2, 0x2, 0x2, 0x35f, 
       0x340, 0x3, 0x2, 0x2, 0x2, 0x35f, 0x343, 0x3, 0x2, 0x2, 0x2, 0x35f, 
       0x347, 0x3, 0x2, 0x2, 0x2, 0x35f, 0x34c, 0x3, 0x2, 0x2, 0x2, 0x35f, 
       0x355, 0x3, 0x2, 0x2, 0x2, 0x35f, 0x357, 0x3, 0x2, 0x2, 0x2, 0x35f, 
       0x35a, 0x3, 0x2, 0x2, 0x2, 0x35f, 0x35d, 0x3, 0x2, 0x2, 0x2, 0x360, 
       0x363, 0x3, 0x2, 0x2, 0x2, 0x361, 0x35f, 0x3, 0x2, 0x2, 0x2, 0x361, 
       0x362, 0x3, 0x2, 0x2, 0x2, 0x362, 0x75, 0x3, 0x2, 0x2, 0x2, 0x363, 
       0x361, 0x3, 0x2, 0x2, 0x2, 0x364, 0x368, 0x5, 0x92, 0x4a, 0x2, 0x365, 
       0x368, 0x5, 0x64, 0x33, 0x2, 0x366, 0x368, 0x5, 0x78, 0x3d, 0x2, 
       0x367, 0x364, 0x3, 0x2, 0x2, 0x2, 0x367, 0x365, 0x3, 0x2, 0x2, 0x2, 
       0x367, 0x366, 0x3, 0x2, 0x2, 0x2, 0x368, 0x77, 0x3, 0x2, 0x2, 0x2, 
       0x369, 0x375, 0x7, 0xb, 0x2, 0x2, 0x36a, 0x36f, 0x5, 0x6a, 0x36, 
       0x2, 0x36b, 0x36c, 0x7, 0xf, 0x2, 0x2, 0x36c, 0x36e, 0x5, 0x6a, 0x36, 
       0x2, 0x36d, 0x36b, 0x3, 0x2, 0x2, 0x2, 0x36e, 0x371, 0x3, 0x2, 0x2, 
       0x2, 0x36f, 0x36d, 0x3, 0x2, 0x2, 0x2, 0x36f, 0x370, 0x3, 0x2, 0x2, 
       0x2, 0x370, 0x373, 0x3, 0x2, 0x2, 0x2, 0x371, 0x36f, 0x3, 0x2, 0x2, 
       0x2, 0x372, 0x374, 0x7, 0xf, 0x2, 0x2, 0x373, 0x372, 0x3, 0x2, 0x2, 
       0x2, 0x373, 0x374, 0x3, 0x2, 0x2, 0x2, 0x374, 0x376, 0x3, 0x2, 0x2, 
       0x2, 0x375, 0x36a, 0x3, 0x2, 0x2, 0x2, 0x375, 0x376, 0x3, 0x2, 0x2, 
       0x2, 0x376, 0x377, 0x3, 0x2, 0x2, 0x2, 0x377, 0x378, 0x7, 0xd, 0x2, 
       0x2, 0x378, 0x79, 0x3, 0x2, 0x2, 0x2, 0x379, 0x38f, 0x5, 0x50, 0x29, 
       0x2, 0x37a, 0x37c, 0x7, 0x6c, 0x2, 0x2, 0x37b, 0x37a, 0x3, 0x2, 0x2, 
       0x2, 0x37b, 0x37c, 0x3, 0x2, 0x2, 0x2, 0x37c, 0x37d, 0x3, 0x2, 0x2, 
       0x2, 0x37d, 0x37f, 0x7, 0x5a, 0x2, 0x2, 0x37e, 0x380, 0x7, 0x1b, 
       0x2, 0x2, 0x37f, 0x37e, 0x3, 0x2, 0x2, 0x2, 0x37f, 0x380, 0x3, 0x2, 
       0x2, 0x2, 0x380, 0x381, 0x3, 0x2, 0x2, 0x2, 0x381, 0x383, 0x7, 0x9, 
       0x2, 0x2, 0x382, 0x384, 0x5, 0x5a, 0x2e, 0x2, 0x383, 0x382, 0x3, 
       0x2, 0x2, 0x2, 0x383, 0x384, 0x3, 0x2, 0x2, 0x2, 0x384, 0x385, 0x3, 
       0x2, 0x2, 0x2, 0x385, 0x386, 0x7, 0xa, 0x2, 0x2, 0x386, 0x38f, 0x5, 
       0x60, 0x31, 0x2, 0x387, 0x389, 0x7, 0x6c, 0x2, 0x2, 0x388, 0x387, 
       0x3, 0x2, 0x2, 0x2, 0x388, 0x389, 0x3, 0x2, 0x2, 0x2, 0x389, 0x38a, 
       0x3, 0x2, 0x2, 0x2, 0x38a, 0x38b, 0x5, 0x7c, 0x3f, 0x2, 0x38b, 0x38c, 
       0x7, 0x3d, 0x2, 0x2, 0x38c, 0x38d, 0x5, 0x7e, 0x40, 0x2, 0x38d, 0x38f, 
       0x3, 0x2, 0x2, 0x2, 0x38e, 0x379, 0x3, 0x2, 0x2, 0x2, 0x38e, 0x37b, 
       0x3, 0x2, 0x2, 0x2, 0x38e, 0x388, 0x3, 0x2, 0x2, 0x2, 0x38f, 0x7b, 
       0x3, 0x2, 0x2, 0x2, 0x390, 0x397, 0x5, 0x92, 0x4a, 0x2, 0x391, 0x393, 
       0x7, 0x9, 0x2, 0x2, 0x392, 0x394, 0x5, 0x5a, 0x2e, 0x2, 0x393, 0x392, 
       0x3, 0x2, 0x2, 0x2, 0x393, 0x394, 0x3, 0x2, 0x2, 0x2, 0x394, 0x395, 
       0x3, 0x2, 0x2, 0x2, 0x395, 0x397, 0x7, 0xa, 0x2, 0x2, 0x396, 0x390, 
       0x3, 0x2, 0x2, 0x2, 0x396, 0x391, 0x3, 0x2, 0x2, 0x2, 0x397, 0x7d, 
       0x3, 0x2, 0x2, 0x2, 0x398, 0x39b, 0x5, 0x74, 0x3b, 0x2, 0x399, 0x39b, 
       0x5, 0x60, 0x31, 0x2, 0x39a, 0x398, 0x3, 0x2, 0x2, 0x2, 0x39a, 0x399, 
       0x3, 0x2, 0x2, 0x2, 0x39b, 0x7f, 0x3, 0x2, 0x2, 0x2, 0x39c, 0x39d, 
       0x9, 0x7, 0x2, 0x2, 0x39d, 0x81, 0x3, 0x2, 0x2, 0x2, 0x39e, 0x3a6, 
       0x7, 0x3e, 0x2, 0x2, 0x39f, 0x3a6, 0x7, 0x3f, 0x2, 0x2, 0x3a0, 0x3a6, 
       0x7, 0x79, 0x2, 0x2, 0x3a1, 0x3a6, 0x5, 0x84, 0x43, 0x2, 0x3a2, 0x3a6, 
       0x7, 0x6, 0x2, 0x2, 0x3a3, 0x3a6, 0x5, 0x88, 0x45, 0x2, 0x3a4, 0x3a6, 
       0x5, 0x8a, 0x46, 0x2, 0x3a5, 0x39e, 0x3, 0x2, 0x2, 0x2, 0x3a5, 0x39f, 
       0x3, 0x2, 0x2, 0x2, 0x3a5, 0x3a0, 0x3, 0x2, 0x2, 0x2, 0x3a5, 0x3a1, 
       0x3, 0x2, 0x2, 0x2, 0x3a5, 0x3a2, 0x3, 0x2, 0x2, 0x2, 0x3a5, 0x3a3, 
       0x3, 0x2, 0x2, 0x2, 0x3a5, 0x3a4, 0x3, 0x2, 0x2, 0x2, 0x3a6, 0x83, 
       0x3, 0x2, 0x2, 0x2, 0x3a7, 0x3ab, 0x7, 0x7a, 0x2, 0x2, 0x3a8, 0x3aa, 
       0x5, 0x86, 0x44, 0x2, 0x3a9, 0x3a8, 0x3, 0x2, 0x2, 0x2, 0x3aa, 0x3ad, 
       0x3, 0x2, 0x2, 0x2, 0x3ab, 0x3a9, 0x3, 0x2, 0x2, 0x2, 0x3ab, 0x3ac, 
       0x3, 0x2, 0x2, 0x2, 0x3ac, 0x3ae, 0x3, 0x2, 0x2, 0x2, 0x3ad, 0x3ab, 
       0x3, 0x2, 0x2, 0x2, 0x3ae, 0x3af, 0x7, 0x7a, 0x2, 0x2, 0x3af, 0x85, 
       0x3, 0x2, 0x2, 0x2, 0x3b0, 0x3b6, 0x7, 0x81, 0x2, 0x2, 0x3b1, 0x3b2, 
       0x7, 0x80, 0x2, 0x2, 0x3b2, 0x3b3, 0x5, 0x74, 0x3b, 0x2, 0x3b3, 0x3b4, 
       0x7, 0xc, 0x2, 0x2, 0x3b4, 0x3b6, 0x3, 0x2, 0x2, 0x2, 0x3b5, 0x3b0, 
       0x3, 0x2, 0x2, 0x2, 0x3b5, 0x3b1, 0x3, 0x2, 0x2, 0x2, 0x3b6, 0x87, 
       0x3, 0x2, 0x2, 0x2, 0x3b7, 0x3b8, 0x9, 0x8, 0x2, 0x2, 0x3b8, 0x89, 
       0x3, 0x2, 0x2, 0x2, 0x3b9, 0x3ba, 0x9, 0x9, 0x2, 0x2, 0x3ba, 0x8b, 
       0x3, 0x2, 0x2, 0x2, 0x3bb, 0x3bc, 0x6, 0x47, 0x23, 0x2, 0x3bc, 0x3bd, 
       0x5, 0x92, 0x4a, 0x2, 0x3bd, 0x3be, 0x5, 0x6c, 0x37, 0x2, 0x3be, 
       0x8d, 0x3, 0x2, 0x2, 0x2, 0x3bf, 0x3c0, 0x6, 0x48, 0x24, 0x2, 0x3c0, 
       0x3c1, 0x5, 0x92, 0x4a, 0x2, 0x3c1, 0x3c2, 0x5, 0x6c, 0x37, 0x2, 
       0x3c2, 0x8f, 0x3, 0x2, 0x2, 0x2, 0x3c3, 0x3c6, 0x5, 0x92, 0x4a, 0x2, 
       0x3c4, 0x3c6, 0x5, 0x94, 0x4b, 0x2, 0x3c5, 0x3c3, 0x3, 0x2, 0x2, 
       0x2, 0x3c5, 0x3c4, 0x3, 0x2, 0x2, 0x2, 0x3c6, 0x91, 0x3, 0x2, 0x2, 
       0x2, 0x3c7, 0x3c8, 0x9, 0xa, 0x2, 0x2, 0x3c8, 0x93, 0x3, 0x2, 0x2, 
       0x2, 0x3c9, 0x3cd, 0x5, 0x96, 0x4c, 0x2, 0x3ca, 0x3cd, 0x7, 0x3e, 
       0x2, 0x2, 0x3cb, 0x3cd, 0x7, 0x3f, 0x2, 0x2, 0x3cc, 0x3c9, 0x3, 0x2, 
       0x2, 0x2, 0x3cc, 0x3ca, 0x3, 0x2, 0x2, 0x2, 0x3cc, 0x3cb, 0x3, 0x2, 
       0x2, 0x2, 0x3cd, 0x95, 0x3, 0x2, 0x2, 0x2, 0x3ce, 0x3fd, 0x7, 0x49, 
       0x2, 0x2, 0x3cf, 0x3fd, 0x7, 0x4a, 0x2, 0x2, 0x3d0, 0x3fd, 0x7, 0x4b, 
       0x2, 0x2, 0x3d1, 0x3fd, 0x7, 0x4c, 0x2, 0x2, 0x3d2, 0x3fd, 0x7, 0x4d, 
       0x2, 0x2, 0x3d3, 0x3fd, 0x7, 0x4e, 0x2, 0x2, 0x3d4, 0x3fd, 0x7, 0x4f, 
       0x2, 0x2, 0x3d5, 0x3fd, 0x7, 0x50, 0x2, 0x2, 0x3d6, 0x3fd, 0x7, 0x51, 
       0x2, 0x2, 0x3d7, 0x3fd, 0x7, 0x52, 0x2, 0x2, 0x3d8, 0x3fd, 0x7, 0x53, 
       0x2, 0x2, 0x3d9, 0x3fd, 0x7, 0x54, 0x2, 0x2, 0x3da, 0x3fd, 0x7, 0x55, 
       0x2, 0x2, 0x3db, 0x3fd, 0x7, 0x56, 0x2, 0x2, 0x3dc, 0x3fd, 0x7, 0x57, 
       0x2, 0x2, 0x3dd, 0x3fd, 0x7, 0x58, 0x2, 0x2, 0x3de, 0x3fd, 0x7, 0x59, 
       0x2, 0x2, 0x3df, 0x3fd, 0x7, 0x5a, 0x2, 0x2, 0x3e0, 0x3fd, 0x7, 0x5b, 
       0x2, 0x2, 0x3e1, 0x3fd, 0x7, 0x5c, 0x2, 0x2, 0x3e2, 0x3fd, 0x7, 0x5d, 
       0x2, 0x2, 0x3e3, 0x3fd, 0x7, 0x5e, 0x2, 0x2, 0x3e4, 0x3fd, 0x7, 0x5f, 
       0x2, 0x2, 0x3e5, 0x3fd, 0x7, 0x60, 0x2, 0x2, 0x3e6, 0x3fd, 0x7, 0x61, 
       0x2, 0x2, 0x3e7, 0x3fd, 0x7, 0x62, 0x2, 0x2, 0x3e8, 0x3fd, 0x7, 0x65, 
       0x2, 0x2, 0x3e9, 0x3fd, 0x7, 0x66, 0x2, 0x2, 0x3ea, 0x3fd, 0x7, 0x67, 
       0x2, 0x2, 0x3eb, 0x3fd, 0x7, 0x68, 0x2, 0x2, 0x3ec, 0x3fd, 0x7, 0x69, 
       0x2, 0x2, 0x3ed, 0x3fd, 0x7, 0x6a, 0x2, 0x2, 0x3ee, 0x3fd, 0x7, 0x6b, 
       0x2, 0x2, 0x3ef, 0x3fd, 0x7, 0x6f, 0x2, 0x2, 0x3f0, 0x3fd, 0x5, 0x98, 
       0x4d, 0x2, 0x3f1, 0x3fd, 0x7, 0x72, 0x2, 0x2, 0x3f2, 0x3fd, 0x7, 
       0x73, 0x2, 0x2, 0x3f3, 0x3fd, 0x7, 0x74, 0x2, 0x2, 0x3f4, 0x3fd, 
       0x7, 0x75, 0x2, 0x2, 0x3f5, 0x3fd, 0x7, 0x76, 0x2, 0x2, 0x3f6, 0x3fd, 
       0x7, 0x77, 0x2, 0x2, 0x3f7, 0x3fd, 0x7, 0x6e, 0x2, 0x2, 0x3f8, 0x3fd, 
       0x7, 0x6c, 0x2, 0x2, 0x3f9, 0x3fd, 0x7, 0x6d, 0x2, 0x2, 0x3fa, 0x3fd, 
       0x7, 0x64, 0x2, 0x2, 0x3fb, 0x3fd, 0x7, 0x63, 0x2, 0x2, 0x3fc, 0x3ce, 
       0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3cf, 0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3d0, 
       0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3d1, 0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3d2, 
       0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3d3, 0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3d4, 
       0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3d5, 0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3d6, 
       0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3d7, 0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3d8, 
       0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3d9, 0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3da, 
       0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3db, 0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3dc, 
       0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3dd, 0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3de, 
       0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3df, 0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3e0, 
       0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3e1, 0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3e2, 
       0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3e3, 0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3e4, 
       0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3e5, 0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3e6, 
       0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3e7, 0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3e8, 
       0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3e9, 0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3ea, 
       0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3eb, 0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3ec, 
       0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3ed, 0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3ee, 
       0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3ef, 0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3f0, 
       0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3f1, 0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3f2, 
       0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3f3, 0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3f4, 
       0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3f5, 0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3f6, 
       0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3f7, 0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3f8, 
       0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3f9, 0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3fa, 
       0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3fb, 0x3, 0x2, 0x2, 0x2, 0x3fd, 0x97, 
       0x3, 0x2, 0x2, 0x2, 0x3fe, 0x3ff, 0x9, 0xb, 0x2, 0x2, 0x3ff, 0x99, 
       0x3, 0x2, 0x2, 0x2, 0x400, 0x405, 0x7, 0xe, 0x2, 0x2, 0x401, 0x405, 
       0x7, 0x2, 0x2, 0x3, 0x402, 0x405, 0x6, 0x4e, 0x25, 0x2, 0x403, 0x405, 
       0x6, 0x4e, 0x26, 0x2, 0x404, 0x400, 0x3, 0x2, 0x2, 0x2, 0x404, 0x401, 
       0x3, 0x2, 0x2, 0x2, 0x404, 0x402, 0x3, 0x2, 0x2, 0x2, 0x404, 0x403, 
       0x3, 0x2, 0x2, 0x2, 0x405, 0x9b, 0x3, 0x2, 0x2, 0x2, 0x72, 0x9d, 
       0xa0, 0xba, 0xbe, 0xc5, 0xcb, 0xcf, 0xd6, 0xde, 0xe3, 0xe5, 0xee, 
       0xf2, 0xfa, 0xff, 0x108, 0x110, 0x114, 0x119, 0x124, 0x12a, 0x139, 
       0x14d, 0x151, 0x155, 0x15d, 0x166, 0x16b, 0x173, 0x178, 0x17d, 0x184, 
       0x18b, 0x192, 0x1a4, 0x1a8, 0x1aa, 0x1b1, 0x1b7, 0x1bc, 0x1cb, 0x1ce, 
       0x1d3, 0x1d6, 0x1e1, 0x1e5, 0x1ea, 0x1f5, 0x1fb, 0x204, 0x206, 0x20f, 
       0x213, 0x219, 0x21c, 0x21f, 0x224, 0x22a, 0x22d, 0x235, 0x238, 0x23d, 
       0x242, 0x249, 0x24e, 0x251, 0x256, 0x25d, 0x264, 0x26d, 0x271, 0x276, 
       0x27b, 0x281, 0x285, 0x294, 0x297, 0x29c, 0x2ad, 0x2b0, 0x2b9, 0x2c1, 
       0x2c5, 0x2c7, 0x2cc, 0x2d0, 0x2d7, 0x2de, 0x30e, 0x34e, 0x352, 0x35f, 
       0x361, 0x367, 0x36f, 0x373, 0x375, 0x37b, 0x37f, 0x383, 0x388, 0x38e, 
       0x393, 0x396, 0x39a, 0x3a5, 0x3ab, 0x3b5, 0x3c5, 0x3cc, 0x3fc, 0x404, 
  };

  _serializedATN.insert(_serializedATN.end(), serializedATNSegment0,
    serializedATNSegment0 + sizeof(serializedATNSegment0) / sizeof(serializedATNSegment0[0]));


  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

JavaScriptParser::Initializer JavaScriptParser::_init;
