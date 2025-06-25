#include "Fuzzer.h"

#include <fstream>
#include <sstream>

#define BOOST_PROCESS_USE_STD_FS 1
#include <boost/process.hpp>

#include "../graph2js/JavaScriptLifter.h"
#include "../translator.h"
#include "../mutate/MutatorOutsideGraph.h"

namespace FuzzFlow {

namespace bp = boost::process;
namespace fs = std::filesystem;

void Fuzzer::initialize()
{
    runner->initialize();
    evaluator->initialize(runner);
    corpus->initialize();
    storage->initialize();
}

void Fuzzer::start()
{
    run_hello();
    prepare_corpus();
    register_event_listener();
    statistics->start_timer();
    fuzz();
}

void Fuzzer::register_event_listener()
{
    add_observer(EventType::CrashFound, storage);
    add_observer(EventType::PreExecute, evaluator);

    add_observer(EventType::TryLift, statistics);
    //addObserver(EventType::PreExecute, statistics);
    add_observer(EventType::PostExecute, statistics);
    add_observer(EventType::ProgramGenerated, statistics);
    add_observer(EventType::ValidProgramFound, statistics);
    add_observer(EventType::InvalidProgramFound, statistics);
    add_observer(EventType::CrashFound, statistics);
    add_observer(EventType::TimeOutFound, statistics);
    add_observer(EventType::InterestingFound, statistics);
}

void Fuzzer::shutdown()
{
    cout << "Shutdown the fuzzer... Bye...\n";
    std::exit(0);
}

void Fuzzer::set_fuzzer_for_component(const shared_ptr<Fuzzer> &self_fuzzer) const
{
    /// Set the fuzzer as a member of a component like ProgramCoverageEvaluator
    /// Because methods within ProgramCoverageEvaluator need to call member functions
    /// of the fuzzer
    evaluator->set_fuzzer(self_fuzzer);
}

/// Test whether the engine's instrumentation is normal,
/// and test whether the runner and evaluator components are normal.
void Fuzzer::run_hello() const
{
    const string program = "var a = \"1024\"; print(a);";

    const Execution execution = runner->run(program, 250 * 1000, true);

    optional<unique_ptr<CovEdgeSet>> ret = evaluator->evaluate(execution);
    if (ret.has_value()) {
        cout << "Covered new edges:" << ret.value()->count() << std::endl;
    }
    else {
        cerr << "No new edges found.\n";
        cerr << "The instrumentation may be wrong.\n";
        exit(1);
    }
}

void Fuzzer::normalize_js(const fs::path& input_js, const fs::path& output_js)
{
    auto executable_path = bp::search_path("node");
    if (executable_path.empty()) {
        cerr << "No executable `node` provided" << std::endl;
    }

    string js_normalize_path;

    if (const char *normalize_path = std::getenv("NORMALIZER");
        normalize_path != nullptr && fs::is_regular_file(normalize_path))
    {
        js_normalize_path = string(normalize_path);
    }
    else {
        cerr << "No NORMALIZER provided" << std::endl;
        shutdown();
    }

    bp::child child(executable_path,
        js_normalize_path,
        "-i", input_js.string(), "-o", output_js.string());
    child.wait();
}

fs::path Fuzzer::normalize_seeds(const fs::path& input_dir) const
{
    if (! is_directory(input_dir)) {
        return {};
    }

    fs::path input_dir_parent = input_dir.parent_path();
    fs::path lastDir = input_dir.filename();
    fs::path output_dir_name = input_dir_parent / (lastDir.string() + "_normalize");

    for (const auto& entry : fs::recursive_directory_iterator(input_dir)) {
        if (! entry.is_regular_file()) {
            continue;
        }

        auto input_js_path = fs::absolute(entry.path());
        ifstream file(input_js_path);

        if (! file.is_open()) {
            throw std::runtime_error("Could not open " + input_js_path.string());
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        string code = buffer.str();

        this->runner->run(code, 250 * 1000, false);
        this->evaluator->eval_execution();

        fs::path filename = input_js_path.filename();
        fs::path output_js_path = output_dir_name / filename;
        normalize_js(input_js_path, output_js_path);
    }

    return output_dir_name;
}

void Fuzzer::prepare_corpus() const
{
    unsigned int seed_index = 0;
    unsigned int js2son_success_num = 0;

    unsigned int num_antlr_error = 0;
    unsigned int num_enter_error = 0;
    unsigned int num_ref_resolve_error = 0;
    unsigned int num_js2son_error = 0;
    unsigned int num_son2js_error = 0;

    bool is_loading_seeds = false;
    set<string> valid_seed_paths;

    const char *seeds_path = std::getenv("VALIDSEEDS");

    if (seeds_path != nullptr) {
        if (fs::is_regular_file(seeds_path)) {
            std::ifstream ifs(seeds_path);
            string line;
            while (std::getline(ifs, line)) {
                fs::path seed_path(line);
                auto seed_name = seed_path.filename();
                valid_seed_paths.insert(seed_name);
            }
            ifs.close();

            is_loading_seeds = true;
            cout << "Loading saved valid paths...\n";
        }
    }

    fs::path seeds_dir = normalize_seeds(cmd_options->inputDir);
    //fs::path seeds_dir = cmd_options->inputDir;

    for (auto& dir_entry : fs::directory_iterator(seeds_dir)) {
        const fs::path& js_path = dir_entry.path();
        string js_file_name = js_path.filename();

        if (is_loading_seeds
            && (! valid_seed_paths.contains(js_file_name))) {
            continue;
        }

        auto seed_size_in_bytes = fs::file_size(js_path);
        cout << "Seed size: " << std::dec << seed_size_in_bytes << " bytes\n";
        if (seed_size_in_bytes > 2048) {
            cout << "Too large, may be ineffective. Please trim the seed.\n";
            continue;
        }

        /// skip some test cases that requires much time to parse
        if (js_file_name == "WebKit_JSTests_wasm_threads-spec-harness_wast.js"
            || js_file_name == "WebKit_JSTests_stress_v8-earley-boyer-strict.js"
            || js_file_name == "WebKit_JSTests_exceptionFuzz_earley-boyer.js"
            || js_file_name == "WebKit_JSTests_stress_maximum-inline-capacity.js"
            || js_file_name == "WebKit_JSTests_modules_module-jit-reachability.js"
            || js_file_name == "WebKit_JSTests_wasm_libwabt.js"
            || js_file_name == "ChakraCore_test_WasmSpec_testsuite_harness_wast.js"
            || js_file_name == "gecko-dev_js_src_jit-test_tests_cacheir_bug1357024.js"
            || js_file_name == "gecko-dev_js_src_jit-test_tests_ion_bug1356822.js"
            || js_file_name == "WebKit_JSTests_microbenchmarks_let-const-tdz-environment-parsing-and-hash-consing-speed.js")
        {
            continue;
        }

        seed_index += 1;
        cout << "Processing seed " << std::to_string(seed_index) << ", name: " << js_path << std::endl;

        try {
            shared_ptr<SeedEntry> seed = corpus->build_seed(js_path, this->sub_graph_pool);
            auto aspects = make_unique<ProgramAspects>(ExecutionOutcome::succeeded);
            corpus->add(seed, std::move(aspects));
            js2son_success_num += 1;

            /// Record the seeds that can be translated to avoid processing all seeds
            /// repeatedly every time the fuzzer is started.
            if (! is_loading_seeds) {
                valid_seed_paths.insert(js_path);
            }
        }
        catch (const AntlrParseError& e) {
            num_antlr_error += 1;
        }
        catch (const EnterError &e) {
            num_enter_error += 1;
        }
        catch (const RefResolverError &e) {
            num_ref_resolve_error += 1;
        }
        catch (const JS2GraphError &e) {
            cerr << e.what() << "\n";
            num_js2son_error += 1;
        }
        catch (const LiftError &e) {
            cerr << e.what() << "\n";
            num_son2js_error += 1;
        }

        cout << "JS2Graph translation success num: " << std::to_string(js2son_success_num) << "\n\n";
    }

    /// TODO dump to log file
    cout << "After seeds preparation, there are " << std::to_string(corpus->count()) << " seeds in corpus.\n";
    cout << "Error count: " << std::endl;
    cout << "Antlr SyntaxError: " << std::to_string(num_antlr_error) << std::endl;
    cout << "       EnterError: " << std::to_string(num_enter_error) << std::endl;
    cout << " RefResolverError: " << std::to_string(num_ref_resolve_error) << std::endl;
    cout << "    Js2GraphError: " << std::to_string(num_js2son_error) << std::endl;
    cout << "        LiftError: " << std::to_string(num_son2js_error) << std::endl;

    if (! is_loading_seeds) {
        std::ofstream ofs(seeds_path, std::ios::trunc);
        for (auto& js_path: valid_seed_paths) {
            ofs << js_path << std::endl;
        }
        ofs.close();
    }
}

/// todo
/// Implementation of `--jobs` (multi-process fuzzing) could start from here.
/// Child processes should share resources like the independent dataflow subgraph pool
/// to minimize memory usage.
void Fuzzer::fuzz()
{
    auto time_print_stat = steady_clock::now();
    auto time_export_stat = steady_clock::now();

    int executed_count = 0;
    while (true)
    {
        current_seed = corpus->random_element_for_mutating();

        bool debug = false;
        if (debug) {
            cout << "seed init name: " << current_seed->initial_name << "\n";
        }

        auto [graph_idx, mutating_graph] = random_vector_element_with_idx(current_seed->js_graphs);
        //unsigned int graph_idx = 0;
        //auto mutating_graph = current_seed->js_graphs[graph_idx];

        uint32_t graph_size_before_mutate = mutating_graph->nodes.size();

        if (graph_size_before_mutate < 8) {
            /// If the graph is very small, we will encounter the problem of no mutator available later
            /// in the execution. It would be better to end it here.
            continue;
        }

        if (debug) {
            string dot_save_name = "mutate_before.dot";
            string content = GraphPainter::to_dot(mutating_graph);
            write_text_file(dot_save_name, content);
        }

        try {
            JavaScriptLifter lifter_before(mutating_graph);
            ScriptWriter script_writer_before_mutate;
            lifter_before.lift();

            string graph_code = script_writer_before_mutate.emit(cmd_options->profile->code_prefix,
                                                                 cmd_options->profile->code_suffix,
                                                                 lifter_before.function_name,
                                                                 lifter_before.function_args,
                                                                 lifter_before.top_region);

            if (debug) {
                cout << "Graph code before mutation: \n" << graph_code << std::endl;
            }
        }
        catch (const LiftError &error) {
            cerr << "Lift Error before mutate!" << std::endl;
            cerr << error.what() << std::endl;

            std::erase_if(corpus->seeds, [this](shared_ptr<SeedEntry> seed) {
                return seed == current_seed;
            });
        }

        MutatorInsideGraph mutator(mutating_graph, js_environment, this->sub_graph_pool, this->corpus);

        try {
            if (bool has_mutated = mutator.mutate(); !has_mutated) {
                continue;
            }
        }
        catch (const MutateError &err) {
            continue;
        }

        if (debug) {
            string dot_save_name = "mutate_after.dot";
            string content = GraphPainter::to_dot(mutating_graph, true);
            write_text_file(dot_save_name, content);
        }

        /// update the done mutators for analysis
        for (auto& mut : mutator.done_mutators) {
            current_seed->append_newly_mutator(mut);
        }

        JavaScriptLifter lifter(mutating_graph);
        ScriptWriter script_writer;

        bool lift_result = false;

        try {
            uint32_t mutated_graph_size = 0;
            mutated_graph_size = lifter.lift();

            lift_result = true;

            notify_observers(EventType::ProgramGenerated,
                            make_shared<DataProgramGenerated>(mutated_graph_size));
        }
        catch (const LiftError &e) {}

        notify_observers(EventType::TryLift,
                        make_shared<DataTryLift>(lift_result));

        string newly_graph_code = script_writer.emit(cmd_options->profile->code_prefix,
                                                     cmd_options->profile->code_suffix,
                                                     lifter.function_name,
                                                     lifter.function_args,
                                                     lifter.top_region);
        current_seed->mutated_idx2code.insert_or_assign(graph_idx, newly_graph_code);

        /// Unmodified graphs can reuse their JS code without regeneration.
        current_seed->newly_js_code = current_seed->merge_mutated_code(graph_idx, newly_graph_code);

        /// log generate test cases

        this->execute(timeout_us);

        /// concat mutation here
        MutatorOutsideGraph mutator_outside_graph(this->cmd_options->targetEngine);
        current_seed->newly_js_code = mutator_outside_graph.mutate_concat(this->current_seed);
        if (! current_seed->newly_js_code.empty()) {
            this->execute(timeout_us * 5);
        }

        /// undo mutate, recover the graph
        mutator.undo_mutate();
        mutating_graph->splice_graph_varProxy2node.clear();

        current_seed->mutated_idx2code.clear();
        current_seed->clear_newly_mutator();

        executed_count += 1;

        if (executed_count % 10 == 0) {
            auto cur_time_point = steady_clock::now();

            auto duration_print =
                    duration_cast<minutes>(cur_time_point - time_print_stat).count();
            auto duration_export =
                    duration_cast<minutes>(cur_time_point - time_export_stat).count();

            if ((duration_print > 0)
                    && (duration_print % Fuzzer::terminal_update_minutes == 0)) {
                auto export_stats = this->export_statistics();
                TerminalUI::print_statistics(export_stats);
                time_print_stat = cur_time_point;
            }

            if ((! storage->statistics_dir.empty())
                    && (duration_export > 0)
                    && (duration_export % storage->export_interval_mins == 0)) {
                auto export_stats = this->export_statistics();
                storage->save_statistics(export_stats);
                time_export_stat = cur_time_point;
            }
        }
    }
}

/// Only executes the test case without further analysis or processing (e.g., handling interesting cases).
/// This function will also be called in ProgramCoverageEvaluator
Execution Fuzzer::only_execute(const uint32_t timeout_us, const bool verbose)
{
    notify_observers(EventType::PreExecute);

    Execution execution = runner->run(this->current_seed->newly_js_code, timeout_us, verbose);
    return execution;
}

Execution Fuzzer::execute(const uint32_t timeout_us)
{
    Execution execution = this->only_execute(timeout_us);

    if (cmd_options->dumpTestsLimit > 0) {
        if (bool count_enough = storage->dump_generated_testcases(current_seed)) {
            shutdown();
        }
    }

    if (execution.outcome == ExecutionOutcome::crashed) {
        process_crash(-1, execution.stderr, execution.stdout);

        notify_observers(EventType::CrashFound,
                        make_shared<DataCrashFound>(current_seed));
    }
    else if (execution.outcome == ExecutionOutcome::succeeded) {
        bool is_interesting = false;

        optional<unique_ptr<CovEdgeSet>> opt_cov = evaluator->evaluate(execution);
        if (opt_cov.has_value()) {
            is_interesting = true;
            process_interesting(std::move(opt_cov.value()));
            notify_observers(EventType::InterestingFound);
        }

        notify_observers(EventType::ValidProgramFound,
                        make_shared<DataValidProgramFound>(is_interesting));
    }
    else if (execution.outcome == ExecutionOutcome::failed) {
        notify_observers(EventType::InvalidProgramFound);
    }
    else if (execution.outcome == ExecutionOutcome::timeout) {
        notify_observers(EventType::TimeOutFound);
    }

    notify_observers(EventType::PostExecute);

    return execution;
}

/// If a seed triggered new coverage, copy it and add to the queue
void Fuzzer::finish_interesting(unique_ptr<CovEdgeSet> aspects) const
{
    auto new_seed = current_seed->clone_from_mutation();
    new_seed->age = current_seed->age + 1;

    statistics->corpus_program_size_avg.add(new_seed->program_size());

    if (! cmd_options->staticCorpus) {
        corpus->add(std::move(new_seed), std::move(aspects));
    }

    for (int i = 0; i < current_seed->js_graphs.size(); i++) {
        shared_ptr<Graph> new_graph;
        string graph_code;

        if (current_seed->mutated_idx2code.contains(i)) {
            //this->sub_graph_pool->extract(current_seed->js_graphs[i]);
            this->sub_graph_pool->pool_operation_sequence.extract(current_seed->js_graphs[i]);
        }
    }
}

void Fuzzer::process_interesting(unique_ptr<CovEdgeSet> aspects) const
{
    constexpr uint32_t min_attempts = 3;      /// 5 in Fuzzilli
    bool did_converge = false;
    uint32_t attempt = 0;

    do {
        attempt += 1;

        if (constexpr uint32_t max_attempts = 5; attempt > max_attempts) {
            cout << "Sample did not converge after max attempts. Discarding it\n";
            break;
        }

        optional<unique_ptr<CovEdgeSet>> opt_intersection = evaluator->compute_aspect_intersection(aspects);

        if (opt_intersection == std::nullopt) {
            // This likely means that no aspects are triggered deterministically, so discard this sample.
            return;
        }
        unique_ptr<CovEdgeSet> intersection = std::move(opt_intersection.value());

        // Since evaluateAndIntersect will only ever return aspects that are equivalent to, or a subset of,
        // the provided aspects, we can check if they are identical by comparing their sizes
        if (aspects->num_edges == intersection->num_edges) {
            did_converge = true;
        }
        else {
            did_converge = false;
        }

        aspects = std::move(intersection);
    }
    while (!did_converge || attempt < min_attempts);

    finish_interesting(std::move(aspects));
}

void process_common(shared_ptr<SeedEntry> seed)
{

}

void Fuzzer::process_crash(int termsig, const string &stderr_msg, const string &stdout_msg) const
{
    if (current_seed->footer_comments.find("CRASH INFO") != string::npos) {
        current_seed->footer_comments += "CRASH INFO\n==========\n";
        current_seed->footer_comments += "TERMSIG: " + std::to_string(termsig) + "\n";
        current_seed->footer_comments += "STDERR:\n" + stderr_msg + "\n";
        current_seed->footer_comments += "STDOUT:\n" + stdout_msg + "\n";
        current_seed->footer_comments += "ARGS: " + runner->get_program_args() + "\n";
    }
}

///
/// Before printing in the UI or outputting to a file,
/// we need to call this function to update the data related to statistics.
///
ExportStatistics Fuzzer::export_statistics() const
{
    /// The three statistics in json_data updated in this function
    /// are not maintained by MovingStatistics

    /// 1. update corpus size
    statistics->json_data.corpus_size = corpus->count();

    const auto now = steady_clock::now();

    /// 2. update execution speed
    /// Only when the return type is explicitly declared can we obtain the interval in seconds.
    /// Using `auto` as the return type will not yield the interval in seconds.
    const std::chrono::duration<double> interval = now - statistics->last_eps_update;
    auto elapsed_seconds = interval.count();
    auto execs_per_second = statistics->current_execs / elapsed_seconds;

    statistics->json_data.execs_per_second = execs_per_second;

    /// 3. update coverage
    statistics->json_data.coverage = evaluator->current_score();

    ExportStatistics stat = statistics->compute();

    return stat;
}

} /// end of namespace
