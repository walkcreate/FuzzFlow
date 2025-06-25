#include "ChakraProfile.h"

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

namespace FuzzFlow {

vector<string> ChakraProfile::get_process_arguments(bool randomizing_args) {
    vector<string> args = {
                           //"--maxinterpretcount=10",
                           // No need to call functions thousands of times before they are JIT compiled
                           //"--maxsimplejitruncount=100",
                           "--bgjit",
                           "--oopjit",
                            "-reprl", /// Requires patching and recompiling the engine to fix parameter misalignment issues
                           "fuzzcode.js"};

    return args;
}

} /// end of namespace