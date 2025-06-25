#ifndef FUZZFLOW_FULLPROGRAM_H
#define FUZZFLOW_FULLPROGRAM_H

#include "../thirdparty/antlr4/JavaScriptParserBaseVisitor.h"
#include "antlr4-runtime.h"

#include "../utils/common_using.h"

#include "Graph.h"

namespace FuzzFlow {

using antlr4::ParserRuleContext;

///
/// The IRGenerator is not preserved long-term, so all IR information used
/// during the mutation and lift phases should be stored within this class.

///
/// Program is the resource owner of graphs
///
/// Each test case matches a Program
///
class FullProgram {
public:
    vector<shared_ptr<Graph>> graphs;
};

} /// end of namespace

#endif //FUZZFLOW_FULLPROGRAM_H
