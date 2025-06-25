#ifndef FUZZFLOW_SPIDERMONKEYPROFILE_H
#define FUZZFLOW_SPIDERMONKEYPROFILE_H

#include "../../utils/util_rand.h"
#include "Profile.h"

namespace FuzzFlow {

class SpidermonkeyProfile : public Profile {
public:
    SpidermonkeyProfile()
    {
        this->process_env = {"UBSAN_OPTIONS=handle_segv=0"};

        this->code_prefix = "function main() {";

        /// multiline string
        this->code_suffix = "gc();\n"
                            "}\n"
                            "main();\n";

        this->crash_tests = {"fuzzilli('FUZZILLI_CRASH', 0)",
                             "fuzzilli('FUZZILLI_CRASH', 1)",
                             "fuzzilli('FUZZILLI_CRASH', 2)"};
    }

    vector<string> get_process_arguments(bool randomizing_args) override;
};

} /// end of namespace

#endif //FUZZFLOW_SPIDERMONKEYPROFILE_H
