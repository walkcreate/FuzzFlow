
#include "antlr4-runtime.h"
#include "TestVisit.h"

antlrcpp::Any TestVisit::visitProgram(JavaScriptParser::ProgramContext *ctx)
{
  std::cout << "I am here." << std::endl;
  return visitChildren(ctx);
}