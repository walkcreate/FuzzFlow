#include "REPRL.h"

namespace FuzzFlow {

void REPRL::initialize()
{
    this->reprl_ctx = reprl_create_context();
    if (this->reprl_ctx == nullptr) {
        // log
        cout << "Failed to create REPRL context" << std::endl;
    }

    const char **args_array = (const char **) calloc(this->program_args.size()+1, sizeof(char *));

    for (int i = 0; i < this->program_args.size(); i++) {
        args_array[i] = this->program_args[i].data();
    }

    const char **envs_array = (const char **) calloc(this->program_envs.size()+1, sizeof(char *));

    for (int i = 0; i < this->program_envs.size(); i++) {
        envs_array[i] = this->program_envs[i].data();
    }

    int capture_stdout = 1;
    int capture_stderr = 1;
    if (reprl_initialize_context(this->reprl_ctx, args_array, envs_array, capture_stdout, capture_stderr) != 0) {
        cout << "Failed to initialize REPRL context" << reprl_get_last_error(this->reprl_ctx) << std::endl;
    }

    free(args_array);
    free(envs_array);
}

Execution REPRL::run(const string &script, const uint64_t timeout_us, const bool verbose) const
{
    REPRLExecution execution = REPRLExecution();

    uint64_t exec_time;
    int fresh_instance = 0;
    int status = reprl_execute(this->reprl_ctx,
                               script.data(),
                               script.size(),
                               timeout_us,
                               &exec_time,
                               fresh_instance);

    if (status < 0) {
        cout << "Script execution failed again: "<< reprl_get_last_error(this->reprl_ctx) << ". Giving up.\n";
        execution.outcome = ExecutionOutcome::failed;
        return execution;
    }

    if (RIFEXITED(status) != 0) {
        int code = REXITSTATUS(status);
        if (code == 0) {
            execution.outcome = ExecutionOutcome::succeeded;
        }
        else {
            execution.outcome = ExecutionOutcome::failed;
        }
    }
    else if (RIFSIGNALED(status) != 0) {
        execution.outcome = ExecutionOutcome::crashed;
    }
    else if (RIFTIMEDOUT(status) != 0) {
        execution.outcome = ExecutionOutcome::timeout;
    }
    else {
        cout << "Unknown REPRL exit status " << std::to_string(status) << std::endl;
    }

    if (verbose) {
        cout << "------ STDOUT ------" << std::endl;
        cout << reprl_fetch_stdout(this->reprl_ctx) << std::endl;
        cout << "------ ++++++ ------" << std::endl;

        cout << "------ STDERR ------" << std::endl;
        cout << reprl_fetch_stderr(this->reprl_ctx) << std::endl;
        cout << "------ ++++++ ------" << std::endl;
    }

    // milli seconds to seconds
    execution.exec_time = exec_time / 1000000;
    return execution;
}

void REPRL::set_env(const string &name, const string &value) {

    // no use
    if (setenv(name.data(), value.data(), 1) != 0) {
        cout << "setenv failed: " << "name: " << name << " value: " << value << std::endl;
    }

    // take effect
    program_envs.push_back(name + "=" + value);
}

string REPRL::get_program_args()
{
    string str = std::accumulate(this->program_args.begin(), this->program_args.end(), std::string{});
    return str;
}

} /// end of namespace FuzzFlow
