#include "ExportStatistics.h"

void FuzzFlow::tag_invoke(boost::json::value_from_tag,
                          boost::json::value& jv,
                          ExportStatistics const& stats)
{
    jv = {
        { "total_samples" , stats.total_samples },
        { "valid_samples", stats.valid_samples },
        { "interesting_samples", stats.interesting_samples},
        { "timeout_samples" , stats.timeout_samples },
        { "crashing_samples" , stats.crashing_samples },
        { "total_execs" , stats.total_execs },
        { "avg_program_size" , stats.gen_program_size_avg },
        { "avg_corpus_program_size" , stats.corpus_program_size_avg },
        { "execs_per_second" , stats.execs_per_second },
        { "fuzzer_overhead" , stats.fuzzer_overhead },
        { "num_workers" , stats.num_workers },
        { "coverage" , stats.coverage },
        { "correctness_rate" , stats.correctness_rate },
        { "timeout_rate" , stats.timeout_rate },
        { "lift_error_rate" , stats.lift_error_rate },
    };
}