#ifndef FUZZFLOW_TRANSLATOR_H
#define FUZZFLOW_TRANSLATOR_H

#include <string_view>
#include <filesystem>

#include "./utils/common_using.h"

#include "antlr4-runtime.h"
#include "thirdparty/antlr4/JavaScriptLexer.h"
#include "thirdparty/antlr4/JavaScriptParser.h"
#include "visitors/Enter.h"
#include "visitors/RefResolver.h"
#include "visitors/LeftValueAttributor.h"
#include "js2graph/TestVisit.h"
#include "js2graph/IRGenerator.h"
#include "js2graph/GraphPainter.h"
#include "graph2js/JavaScriptLifter.h"

#include "mutate/SubGraphPool.h"

#include "exceptions/AntlrParseError.h"

#include "mutate/MutatorInsideGraph.h"

namespace FuzzFlow {

using std::string_view;
using namespace std::literals::string_view_literals;

using namespace antlr4;

/// time
#include <chrono>
using std::chrono::duration_cast;
using std::chrono::steady_clock;
using std::chrono::seconds;
using std::chrono::microseconds;

void js2multiGraphs2js_mutate(std::string_view script_path);

void js2multiGraphs2js(std::string_view script_path);

vector<shared_ptr<Graph>> js2multiGraphs(const fs::path& script_path);

vector<string> multiGraphs2js(const vector<shared_ptr<Graph>>& graphs);

string singleGraph2js(const shared_ptr<Graph>& graph);

void write_text_file(const string& path, const string& data);

void test_clone_mutated_graph(string_view script_path);

void eval(string_view script_path);

/// returns true if no syntax error occurred during parsing
bool test_parse(string_view script_path);

bool test_antlr_parse(const string_view script_path);

} /// end of namespace

#endif //FUZZFLOW_TRANSLATOR_H
