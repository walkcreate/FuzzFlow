#ifndef FUZZFLOW_REPRL_H
#define FUZZFLOW_REPRL_H

#include "../../utils/common_using.h"

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

/// for std::accumulate()
#include <numeric>

/// avoid name mangling
extern "C" {
#include "../libreprl/include/libreprl.h"
}

#include "Execution.h"
#include "REPRLExecution.h"

namespace FuzzFlow {

class REPRL {
public:
    REPRL(const string &executable,
          const vector<string>& process_args,
          const vector<string>& process_envs)
    {
        this->executable = executable;
        this->program_args = process_args;
        this->program_envs = process_envs;
    }

    ~REPRL()
    {
        reprl_destroy_context(this->reprl_ctx);
    }

    void initialize();

    Execution run(const string &script, uint64_t timeout_us, bool verbose=false) const;

    void set_env(const string &name, const string &value);

    struct reprl_context* reprl_ctx;

    string get_program_args();

private:
    string executable;

    // Commandline arguments for the executable
    vector<string> program_args;

    // Environment variables for the child process
    // Only by this way, the envs can be passed to child process -- the engine process
    vector<string> program_envs;
};

} /// end of namespace FuzzFlow

#endif //FUZZFLOW_REPRL_H
