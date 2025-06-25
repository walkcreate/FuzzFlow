
#include "utils/common_using.h"

#include "translator.h"

#include "fuzzer/Fuzzer.h"
#include "fuzzer/Storage.h"
#include "fuzzer/execution/REPRL.h"
#include "fuzzer/evaluation/ProgramCoverageEvaluator.h"
#include "fuzzer/corpus/Corpus.h"
#include "fuzzer/CmdOptions.h"

#include "utils/backtrace.h"

namespace FuzzFlow {

shared_ptr<Fuzzer> make_fuzzer(unique_ptr<CmdOptions> cmd_options)
{
    string engine_path = cmd_options->jsPath;
    if (!fs::exists(engine_path)) {
        std::cerr << "[-] The JS engine path does not exists\n";
        exit(0);
    }

    /// engine start settings
    bool rand_exec_args = false;
    vector<string> additional_exec_args = cmd_options->profile->get_process_arguments(rand_exec_args);

    vector<string> program_args = {engine_path};
    program_args.insert(program_args.end(),
                        additional_exec_args.begin(),
                        additional_exec_args.end());

    vector<string> program_envs = {};
    program_envs.insert(program_envs.end(),
                        cmd_options->profile->process_env.begin(),
                        cmd_options->profile->process_env.end());

    /// fuzzer components
    auto runner = make_unique<REPRL>(engine_path, program_args, program_envs);

    auto corpus = make_shared<Corpus>();
    auto js_environment = make_shared<JSEnvironment>();
    auto evaluator = make_shared<ProgramCoverageEvaluator>(runner);
    auto statistics = make_shared<MovingStatistics>();

    string storage_dir = cmd_options->storagePath;
    uint32_t stat_export_interval = cmd_options->statisticsExportInterval;
    uint32_t dump_tests_num = cmd_options->dumpTestsLimit;
    auto storage = make_shared<Storage>(storage_dir, stat_export_interval, dump_tests_num);

    /// Why doesn't Fuzzer use unique_ptr?
    /// Because components need to hold references to their parent Fuzzer,
    /// requiring multiple pointer copies - impossible with unique_ptr.
    ///
    /// Solution:
    /// - Main scope owns Fuzzer via shared_ptr
    /// - Components access it through weak_ptr
    /// This prevents circular references while maintaining safe access.
    ///
    /// This is the owner of fuzzer. Fuzzer is the owner of components.
    auto fuzzer = make_shared<Fuzzer>(std::move(cmd_options),
                                      std::move(runner),
                                      corpus,
                                      js_environment,
                                      evaluator,
                                      storage,
                                      statistics);
    fuzzer->initialize();
    fuzzer->set_fuzzer_for_component(fuzzer);

    return fuzzer;
}

} /// end of namespace

int main(const int argc, char* argv[])
{
    FuzzFlow::registerStackTrace();

    auto cmd_options = make_unique<FuzzFlow::CmdOptions>();
    cmd_options->parse(argc, argv);

    const shared_ptr<FuzzFlow::Fuzzer> fuzzer = make_fuzzer(std::move(cmd_options));

    fuzzer->start();

    return 0;
}
