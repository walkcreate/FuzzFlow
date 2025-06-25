#ifndef FUZZFLOW_FUZZER_H
#define FUZZFLOW_FUZZER_H

#include <chrono>
using std::chrono::steady_clock;
using std::chrono::minutes;
using std::chrono::duration_cast;

/// use boost's uuid
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

/// used to string representation
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "../utils/common_using.h"

#include "events/Subject.h"
#include "CmdOptions.h"
#include "Storage.h"
#include "TerminalUI.h"
#include "MovingStatistics.h"
#include "evaluation/ProgramCoverageEvaluator.h"
#include "corpus/Corpus.h"
#include "environment/JSEnvironment.h"

namespace FuzzFlow {

/// Fuzzer is a Concrete Observer
class Fuzzer : public Subject {
public:
    bool is_initialized = false;
    bool is_stopped = false;

    Fuzzer(unique_ptr<CmdOptions> cmd_options,
           unique_ptr<REPRL> runner,
           const shared_ptr<Corpus> &corpus,
           const shared_ptr<JSEnvironment> &environment,
           const shared_ptr<ProgramCoverageEvaluator> &evaluator,
           const shared_ptr<Storage> &storage,
           const shared_ptr<MovingStatistics> &statistics)
    {
        this->cmd_options = std::move(cmd_options);
        this->runner = std::move(runner);

        this->corpus = corpus;
        this->js_environment = environment;
        this->evaluator = evaluator;
        this->storage = storage;
        this->statistics = statistics;

        this->timeout_us = 250 * 1000;
        this->sub_graph_pool = make_shared<SubGraphPool>();
    }

    void initialize();

    void set_fuzzer_for_component(const shared_ptr<Fuzzer> &fuzzer) const;

    [[nodiscard]] string uuid2str() const {
        auto uuid = boost::lexical_cast<std::string>(id);
        return uuid;
    }

    Execution only_execute(uint32_t timeout_us, bool verbose=false);

    Execution execute(uint32_t timeout_us);

    void fuzz();

    void start();

    static void shutdown();

    void run_hello() const;

    void finish_interesting(unique_ptr<CovEdgeSet> aspects) const;

    void process_interesting(unique_ptr<CovEdgeSet> aspects) const;

    void process_crash(int termsig, const string &stderr_msg, const string &stdout_msg) const;

    void prepare_corpus() const;

    [[nodiscard]] ExportStatistics export_statistics() const;

    [[nodiscard]] fs::path normalize_seeds(const std::filesystem::path& input_dir) const;

    static void normalize_js(const fs::path& input_js, const fs::path& output_js);

private:
    static constexpr unsigned int terminal_update_minutes = 2;

    boost::uuids::uuid id = boost::uuids::random_generator()();

    unique_ptr<CmdOptions> cmd_options;
    unique_ptr<REPRL> runner;
    shared_ptr<Corpus> corpus;

    shared_ptr<ProgramCoverageEvaluator> evaluator;
    shared_ptr<Storage> storage;

    shared_ptr<JSEnvironment> js_environment;

    /// The Statistics class is associated with the Fuzzer, though its output
    /// is handled by the Storage class. Note that Storage has broader
    /// responsibilities beyond Statistics output (e.g., dump seed),
    /// which is why we keep the Statistics instance within the Fuzzer class.
    ///
    /// We use shared_ptr for Statistics because:
    /// It needs to be accessible by Storage for output
    shared_ptr<MovingStatistics> statistics;

    shared_ptr<SubGraphPool> sub_graph_pool;

    uint32_t timeout_us;

    shared_ptr<SeedEntry> current_seed;

    void register_event_listener();
};

} /// end of namespace

#endif //FUZZFLOW_FUZZER_H
