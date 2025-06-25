#include "CmdOptions.h"

#include "profiles/V8Profile.h"
#include "profiles/SpidermonkeyProfile.h"
#include "profiles/JSCProfile.h"
#include "profiles/ChakraProfile.h"
#include "profiles/QjsProfile.h"
#include "profiles/JerryProfile.h"

namespace FuzzFlow {

void CmdOptions::parse(int argc, char* argv[])
{
    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help","produce help message")
        ("jsPath", po::value<string>(),"The path of instrumented JS engine")
        ("profile", po::value<string>(),"Select one of several preconfigured profiles. Available options: v8, spidermonkey, jsc, chakra, qjs, jerry")
        ("jobs", po::value<unsigned int>(),"The fuzzer process numbers")
        ("timeout", po::value<unsigned int>(),"Execution timeout (micro seconds)")
        ("logInterval", po::value<unsigned int>(),"Log interval (seconds)")
        ("inputDir", po::value<string>(),"The directory of initial input seeds")
        ("storagePath", po::value<string>(),"Path at which to store output files (crashes, corpus, etc.) to.")
        ("exportStatistics", po::value<bool>(),"If enabled, fuzzing statistics will be collected and saved to disk in regular intervals.")
        ("statisticsExportInterval", po::value<unsigned int>(),"Interval in minutes for saving fuzzing statistics to disk (default: 10). Requires --exportStatistics.")
        ("staticCorpus",po::value<bool>(),"In this mode, we will just mutate the existing corpus and look for crashes. No new samples are added to the corpus, regardless of their coverage.")
        ("dumpTestsLimit", po::value<unsigned int>(),"Save specific number of test cases to disk, and shutdown the fuzzer")
        ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << "\n";
        exit(0);
    }

    if (vm.count("jsPath")) {
        this->jsPath = vm["jsPath"].as<string>();
        cout << "The JS engine path is set to " << this->jsPath << std::endl;
    }
    else {
        cout << "The js engine path has not been set\n";
        exit(0);
    }

    if (vm.contains("profile")) {
        const auto profile = vm["profile"].as<string>();

        if (profile == "v8") {
            this->profile = std::make_unique<V8Profile>();
            this->targetEngine = TargetEngine::V8;
        }
        else if (profile == "spidermonkey") {
            this->profile = std::make_unique<SpidermonkeyProfile>();
            this->targetEngine = TargetEngine::SM;
        }
        else if (profile == "jsc") {
            this->profile = std::make_unique<JSCProfile>();
            this->targetEngine = TargetEngine::JSC;
        }
        else if (profile == "chakra") {
            this->profile = std::make_unique<ChakraProfile>();
            this->targetEngine = TargetEngine::CHAKRA;
        }
        else if (profile == "jerry") {
            this->profile = std::make_unique<JerryProfile>();
            this->targetEngine = TargetEngine::JERRY;
        }
        else if (profile == "qjs") {
            this->profile = std::make_unique<QjsProfile>();
            this->targetEngine = TargetEngine::QJS;
        }
        else {
            cerr << "Not supported engine(profile)\n";
            exit(0);
        }

        cout << "The profile is set to " << profile << std::endl;
    }
    else {
        cout << "The profile(v8, spidermonkey, jsc, chakra, qjs, jerry) has not been set\n";
        exit(0);
    }

    if (vm.contains("inputDir")) {
        this->inputDir = vm["inputDir"].as<string>();

        if (!fs::exists(this->inputDir) || !fs::is_directory(this->inputDir)) {
            cout << "The inputDir does not exists or is not a dir\n";
            exit(0);
        }
    }
    else {
        cout << "Input seed dir has not been set.\n";
        exit(0);
    }

    if (vm.count("jobs")) {
        this->jobs = vm["jobs"].as<unsigned int>();
        cout << "The number of jobs is set to " << std::to_string(this->jobs) << std::endl;
    }

    if (vm.count("timeout")) {
        this->timeout = vm["timeout"].as<unsigned int>();
        cout << "The Execution timeout is set to " << std::to_string(this->timeout) << "micro seconds\n";
    }

    if (vm.count("storagePath")) {
        this->storagePath = vm["storagePath"].as<string>();
        cout << "StoragePath is set to " << this->storagePath << std::endl;
    }

    if (vm.count("exportStatistics")) {
        this->exportStatistics = vm["exportStatistics"].as<bool>();
        if (this->exportStatistics) {
            cout << "Turn on export statistics" << std::endl;
        }
        if (this->storagePath.empty()) {
            cout << "Turn on export statistics requires setting of storagePath\n";
            exit(0);
        }
    }

    if (vm.count("statisticsExportInterval")) {
        this->statisticsExportInterval = vm["statisticsExportInterval"].as<unsigned int>();
        if (this->statisticsExportInterval) {
            cout << "StatisticsExportInterval is set to " << std::to_string(this->statisticsExportInterval) << std::endl;
        }
    }

    if (vm.count("staticCorpus")) {
        this->staticCorpus = vm["staticCorpus"].as<bool>();
        if (this->staticCorpus) {
            cout << "Turn on static corpus" << std::endl;
        }
    }

    if (vm.count("dumpTestsLimit")) {
        this->dumpTestsLimit = vm["dumpTestsLimit"].as<unsigned int>();
        if (this->dumpTestsLimit) {
            cout << "dumpTestsLimit is set to " << std::to_string(this->dumpTestsLimit) << std::endl;
        }
    }
}

} /// end of namespace