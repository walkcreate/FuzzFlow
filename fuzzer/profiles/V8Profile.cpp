#include "V8Profile.h"

#include "../../utils/common_using.h"

namespace FuzzFlow {

vector<string> V8Profile::get_process_arguments(const bool randomizing_args)
{
    vector<string> args = {"--expose-gc",
                           "--omit-quit",
                           "--allow-natives-syntax",
                           "--fuzzing",
                           "--jit-fuzzing",
                           "--future",
                           "--harmony"};

    if (randomizing_args == false) {
        return args;
    }

    //
    // Existing features that should sometimes be disabled.
    //
    bool has_no_turbofan = false;
    if (probability(0.1)) {
        args.push_back("--no-turbofan");
        has_no_turbofan = true;
    }

    bool has_no_turboshaft = false;
    if (probability(0.1)) {
        args.push_back("--no-turboshaft");
        has_no_turboshaft = true;
    }

    bool has_no_maglev = false;
    if (probability(0.1)) {
        args.push_back("--no-maglev");
        has_no_maglev = true;
    }

    if (probability(0.1)) {
        args.push_back("--no-sparkplug");
    }

    if (probability(0.1)) {
        args.push_back("--no-short-builtin-calls");
    }

    //
    // Future features that should sometimes be enabled.
    //
    if (probability(0.25)) {
        args.push_back("--minor-mc");
    }

    if (probability(0.25)) {
        args.push_back("--shared-string-table");
    }

    if (probability(0.25) && !has_no_maglev) {
        args.push_back("--maglev-future");
    }

    if (probability(0.1)) {
        args.push_back("--harmony-struct");
    }

    if (probability(0.1)) {
        args.push_back("--turboshaft-typed-optimizations");
    }

    //
    // Sometimes enable additional verification logic (which may be fairly expensive).
    //
    if (probability(0.1)) {
        args.push_back("--verify-heap");
    }

    if (probability(0.1)) {
        args.push_back("--turbo-verify");
    }

    if (probability(0.1)) {
        args.push_back("--turbo-verify-allocation");
    }

    if (probability(0.1)) {
        args.push_back("--assert-types");
    }

    if (probability(0.1)) {
        args.push_back("---turboshaft-assert-types");
    }

    //
    // More exotic configuration changes.
    //
    if (probability(0.5)) {
        args.push_back(probability(0.5) ? "--always-sparkplug" : "--no-always-sparkplug");
        args.push_back(probability(0.5) ? "--always-osr" : "--no-always-osr");
        args.push_back(probability(0.5) ? "--concurrent-osr" : "--no-concurrent-osr");
        args.push_back(probability(0.5) ? "--force-slow-path" : "--no-force-slow-path");

        if (!has_no_turbofan && !has_no_turboshaft) {
            args.push_back(probability(0.5) ? "--always-turbofan" : "--no-always-turbofan");
            args.push_back(probability(0.5) ? "--turbo-move-optimization" : "--no-turbo-move-optimization");
            args.push_back(probability(0.5) ? "--turbo-jt" : "--no-turbo-jt");
            args.push_back(probability(0.5) ? "--turbo-loop-peeling" : "--no-turbo-loop-peeling");
            args.push_back(probability(0.5) ? "--turbo-loop-variable" : "--no-turbo-loop-variable");
            args.push_back(probability(0.5) ? "--turbo-loop-rotation" : "--no-turbo-loop-rotation");
            args.push_back(probability(0.5) ? "--turbo-cf-optimization" : "--no-turbo-cf-optimization");
            args.push_back(probability(0.5) ? "--turbo-escape" : "--no-turbo-escape");
            args.push_back(probability(0.5) ? "--turbo-allocation-folding" : "--no-turbo-allocation-folding");
            args.push_back(probability(0.5) ? "--turbo-instruction-scheduling" : "--no-turbo-instruction-scheduling");
            args.push_back(probability(0.5) ? "--turbo-stress-instruction-scheduling"
                                            : "--no-turbo-stress-instruction-scheduling");
            args.push_back(probability(0.5) ? "--turbo-store-elimination" : "--no-turbo-store-elimination");
            args.push_back(probability(0.5) ? "--turbo-rewrite-far-jumps" : "--no-turbo-rewrite-far-jumps");
            args.push_back(probability(0.5) ? "--turbo-optimize-apply" : "--no-turbo-optimize-apply");

            vector<string> sse = {"--no-enable-sse3", "--no-enable-ssse3", "--no-enable-sse4-1", "--no-enable-sse4-2",
                                  "--no-enable-avx", "--no-enable-avx2"};
            args.push_back(random_vector_element(sse));

            args.push_back(probability(0.5) ? "--turbo-load-elimination" : "--no-turbo-load-elimination");
            args.push_back(probability(0.5) ? "--turbo-inlining" : "--no-turbo-inlining");
            args.push_back(probability(0.5) ? "--turbo-splitting" : "--no-turbo-splitting");

        }
    }

    return args;
}

} /// end of namespace