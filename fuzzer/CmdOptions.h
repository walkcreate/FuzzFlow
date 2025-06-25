#ifndef FUZZFLOW_CMDOPTIONS_H
#define FUZZFLOW_CMDOPTIONS_H

#include "../utils/common_using.h"

#include <boost/program_options.hpp>

#include "profiles/Profile.h"

namespace po = boost::program_options;

namespace FuzzFlow {

enum class TargetEngine {
    V8,
    JSC,
    SM,
    CHAKRA,
    JERRY,
    QJS
};

class CmdOptions {
public:
    /// js engine path
    string jsPath;

    TargetEngine targetEngine;

    /// engine name
    std::unique_ptr<Profile> profile;

    /// seed dir
    string inputDir;

    /// Path at which to store output files (crashes, corpus, etc.) to
    string storagePath;

    /// number of fuzzing process
    /// todo
    unsigned int jobs = 1;

    /// whether to export the fuzzing statistics to disk
    bool exportStatistics = false;

    /// Interval to export to disk
    /// default: 10 minutes
    unsigned int statisticsExportInterval = 600;

    /// execution timeout
    unsigned int timeout = 250;

    /// Determines if we use a static corpus, i.e. we don't add any programs to the corpus
    /// even if they find new coverage.
    bool staticCorpus = false;

    /// How many test cases do we need to dump.
    /// If zero (default), we do not need to dump the generated test cases.
    unsigned int dumpTestsLimit = 0;

    void parse(int argc, char* argv[]);
};

} /// end of namespace

#endif //FUZZFLOW_CMDOPTIONS_H
