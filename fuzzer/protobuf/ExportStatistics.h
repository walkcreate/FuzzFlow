#ifndef FUZZFLOW_PROTOBUFSTATISTICS_H
#define FUZZFLOW_PROTOBUFSTATISTICS_H

#include <stdint.h>

/// boost json
#include <boost/json.hpp>
//#include <boost/json/src.hpp>

/// This will introduce ambiguous
//using namespace boost::json;

namespace FuzzFlow {

class ExportStatistics {
public:
    //// The total number of samples produced.
    uint64_t total_samples = 0;

    //// The number of valid samples produced.
    uint64_t valid_samples = 0;

    //// The number of interesting samples produced.
    uint64_t interesting_samples = 0;

    //// The number of timed-out samples produced.
    uint64_t timeout_samples = 0;

    //// The number of crashes found.
    uint64_t crashing_samples = 0;

    //// The total number of program executions.
    uint64_t total_execs = 0;

    //// The average size of produced programs over the last 1000 programs.
    double gen_program_size_avg = 0;

    //// The average size of the last 1000 programs added to the corpus. Only computed locally, not across workers.
    double corpus_program_size_avg = 0;

    //// The current executions per second.
    double execs_per_second = 0;

    //// The average (over the last 1000 executions) fraction of the total time that is not spent executing programs in the target engine.
    double fuzzer_overhead = 0;

    //// The number of workers connected directly or indirectly to this instance.
    uint64_t num_workers = 0;

    //// The percentage of edges covered if doing coverage-guided fuzzing.
    float coverage = 0;

    //// The correctness rate (i.e. number of valid programs divided by number of generated programs) over the last 1000 generated programs.
    double correctness_rate = 0;

    //// The timeout rate (i.e. number of timeouts
    double timeout_rate = 0;

    //// The lift error rate
    double lift_error_rate = 0;

    //// Corpus size. The number of seeds in the corpus
    uint32_t corpus_size = 0;

    /// The duration of fuzzing time
    uint64_t fuzzing_seconds = 0;

    /// The duration of founding last interesting sample
    uint64_t last_interesting_seconds = 0;
};

void tag_invoke(boost::json::value_from_tag,
                boost::json::value& jv,
                ExportStatistics const& stats);

} /// end of namespace FuzzFlow

#endif //FUZZFLOW_PROTOBUFSTATISTICS_H
