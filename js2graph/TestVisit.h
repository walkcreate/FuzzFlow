
#include "../thirdparty/antlr4/JavaScriptParser.h"
#include "../thirdparty/antlr4/JavaScriptParserBase.h"
#include "../thirdparty/antlr4/JavaScriptParserBaseVisitor.h"

class TestVisit : public JavaScriptParserBaseVisitor
{
public:
    antlrcpp::Any visitProgram(JavaScriptParser::ProgramContext *ctx) override;
};