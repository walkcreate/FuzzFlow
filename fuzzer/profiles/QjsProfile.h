#ifndef FUZZFLOW_QJSPROFILE_H
#define FUZZFLOW_QJSPROFILE_H

#include "Profile.h"

namespace FuzzFlow {

class QjsProfile : public Profile {
public:
    QjsProfile() {
        this->process_env = {"UBSAN_OPTIONS=handle_segv=0"};

        this->code_prefix = "";

        /// multiline string
        /// qjs does not support gc()
        this->code_suffix = "";

        this->crash_tests = {"fuzzilli('FUZZILLI_CRASH', 0)",
                             "fuzzilli('FUZZILLI_CRASH', 1)",
                             "fuzzilli('FUZZILLI_CRASH', 2)"};
    }

    vector<string> get_process_arguments(bool randomizing_args) override;
};

} /// end of namespace FuzzFlow

#endif //FUZZFLOW_QJSPROFILE_H
