#include "translator.h"

#include "./fuzzer/environment/JSEnvironment.h"

#include "./fuzzer/corpus/Corpus.h"

namespace FuzzFlow {

void write_text_file(const string& path, const string& data)
{
    ofstream ofs(path, ofstream::out);
    ofs << data << std::endl;
}

bool antlr_parse(string_view script_path)
{
    ifstream stream;
    stream.open(string(script_path));

    ANTLRInputStream input(stream);

    JavaScriptLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    JavaScriptParser parser(&tokens);

    tree::ParseTree* ast = parser.program();

    string lex_err;
    lexer.getErrorDisplay(lex_err);

    /// return false when syntax error occurred
    if (size_t syntax_err_num = parser.getNumberOfSyntaxErrors(); syntax_err_num != 0) {
        return false;
    }
    else {
        return true;
    }
}

bool test_antlr_parse(const string_view script_path)
{
    const auto start = steady_clock::now();

    antlr_parse(script_path);

    const auto end = steady_clock::now();

    cout << "Antlr parsing elapsed time in microseconds: "
         << duration_cast<std::chrono::milliseconds>(end - start).count()
         << " ms" << std::endl;

    return true;
}

vector<shared_ptr<Graph>> js2multiGraphs(const fs::path& script_path)
{
    vector<shared_ptr<Graph>> graphs;

    if (! fs::exists(script_path)) {
        cerr << "The script does not exists.\n";
        return graphs;
    }

    ifstream stream;
    stream.open(script_path);
    ANTLRInputStream input(stream);

    JavaScriptLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    JavaScriptParser parser(&tokens);

    tree::ParseTree* ast = parser.program();

    if (size_t syntax_err_num = parser.getNumberOfSyntaxErrors(); syntax_err_num != 0) {
        throw AntlrParseError("AntlrParseError");
    }

    /// build the symbol table
    Enter scope_symbol;
    scope_symbol.visit(ast);

    /// reference resolve
    RefResolver resolver;
    resolver.visit(ast);

    /// set the left value attribute
    LeftValueAttributor lva;
    lva.visit(ast);

    IRGenerator ir_generator;
    ir_generator.visit(ast);

    graphs = ir_generator.program.graphs;

    for (int i = 0; i < graphs.size(); i++) {
        bool healthy = graphs[i]->verify_healthy();
        ASSERT_OR_EXIT(healthy);
    }

    return graphs;
}

vector<string> multiGraphs2js(const vector<shared_ptr<Graph>>& graphs)
{
    vector<string> graphs_code;

    for (auto& g : graphs) {
        string code = singleGraph2js(g);
        graphs_code.push_back(code);
    }

    return graphs_code;
}

string singleGraph2js(const shared_ptr<Graph>& graph)
{
    JavaScriptLifter lifter(graph);

    /// We need to create a script writer first, because during the lift phase,
    /// we will generate the code for the objectLiteral method.
    ScriptWriter script_writer;

    lifter.lift();

    string prefix_code;
    string suffix_code;
    string code = script_writer.emit(prefix_code,
                                        suffix_code,
                                        lifter.function_name,
                                        lifter.function_args,
                                        lifter.top_region);

    return code;
}

void js2multiGraphs2js(std::string_view script_path)
{
    const auto sub_graph_extractor = make_shared<SubGraphPool>();

    auto graphs = js2multiGraphs(script_path);

    cout << "Dump FlowIR to dot file" << std::endl;

    for (int i = 0; i < graphs.size(); i++)
    {
        auto function_head = dynamic_pointer_cast<FunctionHeadNode>(graphs[i]->nodes[0]);
        string function_name = function_head->get_label();

        string dot_save_name = function_name + ".dot";
        auto graph = graphs[i];

        string content = GraphPainter::to_dot(graph);
        write_text_file(dot_save_name, content);

        std::size_t hash1 = graph->hash_graph();
        cout << "Graph hash: 0x" << std::hex << hash1 << std::endl;

        sub_graph_extractor->extract(graph);

        cout << "Decompile: \n";
        string code = singleGraph2js(graph);

        cout << "---------------- ----------------" << std::endl;
        cout << code << std::endl;
        cout << "---------------- ----------------" << std::endl;
    }
}

///
/// used in TDD
///
void js2multiGraphs2js_mutate(std::string_view script_path)
{
    const auto graphs = js2multiGraphs(script_path);

    auto corpus = make_shared<Corpus>();

    cout << "Dump FlowIR to dot file" << std::endl;

    auto sub_graph_extractor = make_shared<SubGraphPool>();
    auto js_environment = make_shared<JSEnvironment>();

    for (int i = 0; i < graphs.size(); i++) {
        auto function_head = dynamic_pointer_cast<FunctionHeadNode>(graphs[i]->nodes[0]);
        string function_name = function_head->get_label();

        string dot_save_name = function_name + ".dot";
        auto graph = graphs[i];

        string content = GraphPainter::to_dot(graph);
        write_text_file(dot_save_name, content);

        const std::size_t hash1 = graph->hash_graph();
        cout << "Graph hash before mutation: 0x" << std::hex << hash1 << std::endl;

        sub_graph_extractor->extract(graph);

        cout << "De-compilation result before mutation:" << std::endl;
        string code = singleGraph2js(graph);

        cout << "---------------- ----------------" << std::endl;
        cout << code << std::endl;
        cout << "---------------- ----------------" << std::endl;

        /// mutate
        MutatorInsideGraph mutator(graph, js_environment, sub_graph_extractor, corpus);
        bool has_mutated = mutator.mutate();

        string msg = has_mutated ? "Mutation success" : "The mutation does not performed";
        cout << msg << std::endl;

        cout << "De-compilation result after mutation:" << std::endl;
        code = singleGraph2js(graph);

        cout << "---------------- ----------------" << std::endl;
        cout << code << std::endl;
        cout << "---------------- ----------------" << std::endl;

        dot_save_name = "mutate.dot";
        content = GraphPainter::to_dot(graph);
        write_text_file(dot_save_name, content);

        /// undo mutate
        cout << ">>> Let's undo the mutation\n";
        mutator.undo_mutate();

        const std::size_t hash2 = graph->hash_graph();
        cout << "Graph hash after handling: 0x" << std::hex << hash2 << std::endl;

        if (hash1 != hash2) {
            cout << "[-] Graph hash check failed! \n";
        }
        else {
            cout << "[+] Graph hash check passed! \n";
        }

        dot_save_name = "undo.dot";
        content = GraphPainter::to_dot(graph);
        write_text_file(dot_save_name, content);

        cout << "De-compilation result after undoing the mutation:" << std::endl;
        code = singleGraph2js(graph);

        cout << "---------------- ----------------" << std::endl;
        cout << code << std::endl;
        cout << "---------------- ----------------" << std::endl;
    }
}

void test_js2multiGraphs2js_mutate()
{
    const auto start = steady_clock::now();

    for (int i = 0; i < 100; i++) {
        js2multiGraphs2js_mutate("test.js"sv);
    }

    const auto end = steady_clock::now();
    cout << "Elapsed time in microseconds: "
         << duration_cast<std::chrono::milliseconds>(end - start).count()
         << " ms" << std::endl;
}

void test_clone_mutated_graph(const string_view script_path)
{
    shared_ptr<SubGraphPool> sub_graph_extractor;
    auto graphs = js2multiGraphs(script_path);

    unsigned int graph_idx = 1;
    auto graph = graphs[graph_idx];

    /// test the clone
    string dot_save_name = "seed.dot";
    string content = GraphPainter::to_dot(graph);
    write_text_file(dot_save_name, content);
    cout << "save seed.dot\n";

    auto js_environment = make_shared<JSEnvironment>();
    auto corpus = make_shared<Corpus>();
    MutatorInsideGraph mutator(graph, js_environment, sub_graph_extractor, corpus);
    mutator.mutate();

    /// decompile
    JavaScriptLifter lifter(graph);
    ScriptWriter script_writer;

    string graph_code = singleGraph2js(graph);

    auto new_graph = graph->clone_mutated_graph();
    //auto new_graph = graph->clone_non_mutated_graph();

    /// test the clone
    dot_save_name = "clone.dot";
    string dot_code = GraphPainter::to_dot(new_graph, true);
    write_text_file(dot_save_name, dot_code);
    cout << "save clone.dot\n";

    string new_code = singleGraph2js(new_graph);

    cout << "code before clone: \n";
    cout << graph_code;

    cout << "code after clone: \n";
    cout << new_code;

    mutator.undo_mutate();
}

void eval(const string_view script_path)
{
    shared_ptr<SubGraphPool> sub_graph_extractor;
    auto graphs = js2multiGraphs(script_path);

    unsigned int graph_idx = 1;
    auto graph = graphs[graph_idx];

    /// test the clone
    string dot_save_name = "seed.dot";
    string content = GraphPainter::to_dot(graph);
    write_text_file(dot_save_name, content);
    cout << "save seed.dot\n";

    int loop_times = 0;
    while (loop_times < 100)
    {
        auto new_graph = graph->clone_mutated_graph();

        loop_times++;
    }
}

} /// end of namespace