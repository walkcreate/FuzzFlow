#ifndef FUZZFLOW_FUZZER_ENVIRONMENT_MATERIAL_V8_H
#define FUZZFLOW_FUZZER_ENVIRONMENT_MATERIAL_V8_H

#include "../../../utils/common_using.h"

namespace FuzzFlow {

class MaterialV8 {
public:
    static vector<pair<string, string>> prefix_suffix_pairs;

    string code_prefix;
    string code_suffix;

    MaterialV8() = default;
};

} // FuzzFlow

#endif //FUZZFLOW_FUZZER_ENVIRONMENT_MATERIAL_V8_H
