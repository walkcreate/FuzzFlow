#include "JSCProfile.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

#include "../../utils/util_rand.h"

namespace FuzzFlow {

vector<string> JSCProfile::get_process_arguments(const bool randomizing_args)
{
    vector<string> args = {"--validateOptions=true",
                           // No need to call functions thousands of times before they are JIT compiled
                           "--thresholdForJITSoon=10",
                           "--thresholdForJITAfterWarmUp=10",
                           "--thresholdForOptimizeAfterWarmUp=50",
                           "--thresholdForOptimizeAfterLongWarmUp=50",
                           "--thresholdForOptimizeSoon=50",
                           "--thresholdForFTLOptimizeAfterWarmUp=100",
                           "--thresholdForFTLOptimizeSoon=100",
                           // Enable bounds check elimination validation
                           "--validateBCE=true",
                           "--reprl"};

    if (! randomizing_args) {
        return args;
    }

    string value_str = probability(0.9) ? "true" : "false";
    args.push_back("--useBaselineJIT=" + value_str);

    value_str = probability(0.9) ? "true" : "false";
    args.push_back("--useDFGJIT==" + value_str);

    value_str = probability(0.9) ? "true" : "false";
    args.push_back("--useFTLJIT=" + value_str);

    value_str = probability(0.9) ? "true" : "false";
    args.push_back("--useRegExpJIT=" + value_str);

    value_str = probability(0.9) ? "true" : "false";
    args.push_back("--useTailCalls=" + value_str);

    value_str = probability(0.9) ? "true" : "false";
    args.push_back("--optimizeRecursiveTailCalls=" + value_str);

    value_str = probability(0.9) ? "true" : "false";
    args.push_back("--useObjectAllocationSinking=" + value_str);

    value_str = probability(0.9) ? "true" : "false";
    args.push_back("--useArityFixupInlining=" + value_str);

    value_str = probability(0.9) ? "true" : "false";
    args.push_back("--useValueRepElimination=" + value_str);

    value_str = probability(0.9) ? "true" : "false";
    args.push_back("--useArchitectureSpecificOptimizations=" + value_str);

    value_str = probability(0.9) ? "true" : "false";
    args.push_back("--useAccessInlining=" + value_str);

    return args;
}

} /// end of namespace