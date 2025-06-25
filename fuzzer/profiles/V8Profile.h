#ifndef FUZZFLOW_V8PROFILE_H
#define FUZZFLOW_V8PROFILE_H

#include "Profile.h"
#include "../../utils/util_rand.h"

namespace FuzzFlow {

class V8Profile final : public Profile {
public:
    V8Profile()
    {
        this->process_env = {};

        this->code_prefix = "";

        this->code_suffix = "";

        this->crash_tests = {"fuzzilli('FUZZILLI_CRASH', 0)",
                                "fuzzilli('FUZZILLI_CRASH', 1)",
                                "fuzzilli('FUZZILLI_CRASH', 2)"};
    }

    vector<string> get_process_arguments(bool randomizing_args) override;

};

}

#endif //FUZZFLOW_V8PROFILE_H
