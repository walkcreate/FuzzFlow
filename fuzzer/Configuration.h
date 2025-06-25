#ifndef FUZZFLOW_CONFIGURATION_H
#define FUZZFLOW_CONFIGURATION_H

#include <stdint.h>
#include <vector>
#include <string>

#include "./logging/Logger.h"
#include "InspectionOptions.h"

using std::vector;
using std::string;

namespace FuzzFlow {

class Configuration {
public:
    uint32_t timeout;
    LogLevel log_level;

    /// Code snippets that cause an observable crash in the target engine.
    ///  Used to verify that crashes can be detected.
    vector<string> crash_tests;

    /// Whether this instance fuzzes (i.e. generates new samples, executes, then evaulates them).
    /// This flag is true by default, so all instances, regardless of whether they run standalone, as
    /// master or as worker, perform fuzzing. However, it can make sense to configure master
    /// instances to not perform fuzzing tasks so they can concentrate on the synchronization of
    /// their workers and ensure smooth communication.
    bool is_fuzzing;

    double minimization_limit;

    /// When importing programs from a master instance, discard this percentage of samples.
    ///
    /// Dropout can provide a way to make multiple instances less "similar" to each
    /// other as it forces them to (re)discover edges in a different way.
    double dropout_rate;

    bool enable_diagnostics;

    InspectionOptions inspection_ops;

    Configuration(uint32_t timeout = 250,
                  bool skip_startup_tests = false,
                  LogLevel log_level = LogLevel::info,
                  vector<string> crash_tests = {},
                  bool is_fuzzing = true,
                  double minimization_limit = 0.0,
                  double dropout_rate = 0,
                  bool collect_runtime_types = false,
                  bool enable_diagnostics = false,
                  InspectionOptions inspection_ops = {}) {

        this->timeout = timeout;
        this->log_level = log_level;
        this->crash_tests = crash_tests;
        this->is_fuzzing = is_fuzzing;
        this->minimization_limit = minimization_limit;
        this->dropout_rate = dropout_rate;
        this->enable_diagnostics = enable_diagnostics;
        this->inspection_ops = inspection_ops;
    }
};

} /// end of namespace

#endif //FUZZFLOW_CONFIGURATION_H
