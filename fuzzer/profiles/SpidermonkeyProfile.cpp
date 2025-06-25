#include "SpidermonkeyProfile.h"

#include <array>
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace FuzzFlow {

vector<string> SpidermonkeyProfile::get_process_arguments(bool randomizing_args)
{
    vector<string> args = {"--baseline-warmup-threshold=10",
                           "--ion-warmup-threshold=100",
                           "--ion-check-range-analysis",
                           "--ion-extra-checks",
                           "--fuzzing-safe",
                           "--reprl"};

    if (randomizing_args == false) {
        return args;
    }

    unsigned int value = 1 << random_between_integer(7, 12);
    args.push_back("--small-function-length=" + std::to_string(value));

    value = 1 << random_between_integer(2, 10);
    args.push_back("--inlining-entry-threshold=" + std::to_string(value));

    value = probability(0.5) ? 0 : random_between_integer(1, 24);
    args.push_back("--gc-zeal=" + std::to_string(value));

    string value_str = probability(0.9) ? "on" : "off";
    args.push_back("--ion-scalar-replacement=" + value_str);

    value_str = probability(0.9) ? "on" : "off";
    args.push_back("--ion-pruning=" + value_str);

    value_str = probability(0.9) ? "on" : "off";
    args.push_back("--ion-range-analysis=" + value_str);

    value_str = probability(0.9) ? "on" : "off";
    args.push_back("--ion-inlining=" + value_str);

    value_str = probability(0.9) ? "on" : "off";
    args.push_back("--ion-gvn=" + value_str);

    value_str = probability(0.9) ? "on" : "off";
    args.push_back("--ion-osr=" + value_str);

    value_str = probability(0.9) ? "on" : "off";
    args.push_back("--ion-edgecase-analysis=" + value_str);

    value = 1 << random_between_integer(0, 5);
    args.push_back("--nursery-size=" + std::to_string(value));

    value_str = probability(0.9) ? "on" : "off";
    args.push_back("--nursery-strings=" + value_str);

    value_str = probability(0.9) ? "on" : "off";
    args.push_back("--nursery-bigints=" + value_str);

    value_str = probability(0.1) ? "on" : "off";
    args.push_back("--spectre-mitigations=" + value_str);

    if (probability(0.1)) {
        args.push_back("--no-native-regexp");
    }

    value_str = probability(0.9) ? "on" : "off";
    args.push_back("--ion-optimize-shapeguards=" + value_str);

    value_str = probability(0.9) ? "on" : "off";
    args.push_back("--ion-licm=" + value_str);

    value_str = probability(0.9) ? "on" : "off";
    args.push_back("--ion-instruction-reordering=" + value_str);

    value_str = probability(0.9) ? "on" : "off";
    args.push_back("--cache-ir-stubs=" + value_str);

    const std::array<string, 5> sse_candidates = {"--no-sse3", "--no-ssse3", "--no-sse41", "--no-sse42", "--enable-avx"};
    unsigned int uniform_index = random_between_integer(0, sse_candidates.size() - 1);
    args.push_back(sse_candidates[uniform_index]);

    if (probability(0.1)) {
        args.push_back("--ion-regalloc=testbed");
    }

    value_str = probability(0.9) ? "--enable-watchtower" : "--disable-watchtower";
    args.push_back(value_str);

    value_str = probability(0.0) ? "on" : "off";
    args.push_back("--ion-sink=" + value_str);  /// disabled

    return args;
}

} /// end of namespace