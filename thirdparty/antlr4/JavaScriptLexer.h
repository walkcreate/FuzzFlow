
    #include "JavaScriptLexerBase.h"


// Generated from JavaScriptLexer.g4 by ANTLR 4.9.3

#pragma once


#include "antlr4-runtime.h"




class  JavaScriptLexer : public JavaScriptLexerBase {
public:
  enum {
    HashBangLine = 1, MultiLineComment = 2, SingleLineComment = 3, RegularExpressionLiteral = 4, 
    OpenBracket = 5, CloseBracket = 6, OpenParen = 7, CloseParen = 8, OpenBrace = 9, 
    TemplateCloseBrace = 10, CloseBrace = 11, SemiColon = 12, Comma = 13, 
    Assign = 14, QuestionMark = 15, Colon = 16, Ellipsis = 17, Dot = 18, 
    PlusPlus = 19, MinusMinus = 20, Plus = 21, Minus = 22, BitNot = 23, 
    Not = 24, Multiply = 25, Divide = 26, Modulus = 27, Power = 28, NullCoalesce = 29, 
    Hashtag = 30, RightShiftArithmetic = 31, LeftShiftArithmetic = 32, RightShiftLogical = 33, 
    LessThan = 34, MoreThan = 35, LessThanEquals = 36, GreaterThanEquals = 37, 
    Equals_ = 38, NotEquals = 39, IdentityEquals = 40, IdentityNotEquals = 41, 
    BitAnd = 42, BitXOr = 43, BitOr = 44, And = 45, Or = 46, MultiplyAssign = 47, 
    DivideAssign = 48, ModulusAssign = 49, PlusAssign = 50, MinusAssign = 51, 
    LeftShiftArithmeticAssign = 52, RightShiftArithmeticAssign = 53, RightShiftLogicalAssign = 54, 
    BitAndAssign = 55, BitXorAssign = 56, BitOrAssign = 57, PowerAssign = 58, 
    ARROW = 59, NullLiteral = 60, BooleanLiteral = 61, DecimalLiteral = 62, 
    HexIntegerLiteral = 63, OctalIntegerLiteral = 64, OctalIntegerLiteral2 = 65, 
    BinaryIntegerLiteral = 66, BigHexIntegerLiteral = 67, BigOctalIntegerLiteral = 68, 
    BigBinaryIntegerLiteral = 69, BigDecimalIntegerLiteral = 70, Break = 71, 
    Do = 72, Instanceof = 73, Typeof = 74, Case = 75, Else = 76, New = 77, 
    Var = 78, Catch = 79, Finally = 80, Return = 81, Void = 82, Continue = 83, 
    For = 84, Switch = 85, While = 86, Debugger = 87, Function_ = 88, This = 89, 
    With = 90, Default = 91, If = 92, Throw = 93, Delete = 94, In = 95, 
    Try = 96, As = 97, From = 98, Class = 99, Enum = 100, Extends = 101, 
    Super = 102, Const = 103, Export = 104, Import = 105, Async = 106, Await = 107, 
    Yield = 108, Implements = 109, StrictLet = 110, NonStrictLet = 111, 
    Private = 112, Public = 113, Interface = 114, Package = 115, Protected = 116, 
    Static = 117, Identifier = 118, StringLiteral = 119, BackTick = 120, 
    WhiteSpaces = 121, LineTerminator = 122, HtmlComment = 123, CDataComment = 124, 
    UnexpectedCharacter = 125, TemplateStringStartExpression = 126, TemplateStringAtom = 127
  };

  enum {
    ERROR = 2
  };

  enum {
    TEMPLATE = 1
  };

  explicit JavaScriptLexer(antlr4::CharStream *input);
  ~JavaScriptLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

  virtual void action(antlr4::RuleContext *context, size_t ruleIndex, size_t actionIndex) override;
  virtual bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.
  void OpenBraceAction(antlr4::RuleContext *context, size_t actionIndex);
  void CloseBraceAction(antlr4::RuleContext *context, size_t actionIndex);
  void StringLiteralAction(antlr4::RuleContext *context, size_t actionIndex);
  void BackTickAction(antlr4::RuleContext *context, size_t actionIndex);
  void BackTickInsideAction(antlr4::RuleContext *context, size_t actionIndex);

  // Individual semantic predicate functions triggered by sempred() above.
  bool HashBangLineSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool RegularExpressionLiteralSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool TemplateCloseBraceSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool OctalIntegerLiteralSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool ImplementsSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool StrictLetSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool NonStrictLetSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool PrivateSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool PublicSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool InterfaceSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool PackageSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool ProtectedSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);
  bool StaticSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

