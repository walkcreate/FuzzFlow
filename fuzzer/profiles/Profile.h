#ifndef FUZZFLOW_PROFILE_H
#define FUZZFLOW_PROFILE_H

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

namespace FuzzFlow {

class Profile {
public:
    virtual ~Profile() = default;

    /// vector of "key=value"
    vector<string> process_env;

    string code_prefix;
    string code_suffix;

    /// JavaScript code snippets that cause a crash in the target engine.
    /// Used to verify that crashes can be detected.
    vector<string> crash_tests;

    virtual vector<string> get_process_arguments(bool randomizing_args) {
        return {};
    }
};

} /// end of namespace

#endif //FUZZFLOW_PROFILE_H
