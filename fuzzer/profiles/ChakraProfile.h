#ifndef FUZZFLOW_CHAKRAPROFILE_H
#define FUZZFLOW_CHAKRAPROFILE_H

#include "Profile.h"

namespace FuzzFlow {

class ChakraProfile : public Profile {
public:
    ChakraProfile() {
        this->process_env = {"UBSAN_OPTIONS=handle_segv=0"};

        this->code_prefix = "";

        /// multiline string
        this->code_suffix = "";

        this->crash_tests = {"fuzzilli('FUZZILLI_CRASH', 0)",
                             "fuzzilli('FUZZILLI_CRASH', 1)",
                             "fuzzilli('FUZZILLI_CRASH', 2)"};
    }

    vector<string> get_process_arguments(bool randomizing_args) override;
};

}

#endif //FUZZFLOW_CHAKRAPROFILE_H
