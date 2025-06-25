#ifndef FUZZFLOW_MOVINGSTATISTICS_H
#define FUZZFLOW_MOVINGSTATISTICS_H

#include <chrono>

#include "./Util/MovingAverage.h"
#include "./protobuf/ExportStatistics.h"
#include "../utils/util_time.h"

#include "events/Observer.h"

using std::chrono::duration_cast;
using std::chrono::steady_clock;
using std::chrono::seconds;

namespace FuzzFlow {

///
/// Fuzzer runtime statistics
///

class MovingStatistics final : public Observer {
private:
    static constexpr string_view name ="MovingStatistics";

    /// The time point of starting fuzzing
    std::chrono::time_point<steady_clock> fuzzing_start_point;

    void onNotify(EventType eventType, const shared_ptr<EventData>& eventData) override;
public:
    MovingStatistics() :
        overhead_avg(1000),
        gen_program_size_avg(1000),
        corpus_program_size_avg(1000),
        correctness_rate(1000),
        timeout_rate(1000),
        lift_error_rate(1000) {
    }

    /// The data just for this instance.
    ExportStatistics json_data;

    /// The last time an interesting sample was found
    std::chrono::time_point<steady_clock> last_interesting_sample_point;

    /// Data required to compute Executions Per Second.
    double current_execs = 0;
    std::chrono::time_point<steady_clock> last_eps_update;

    /// Data required to compute the fuzzer overhead
    /// (i.e. the fraction of the total time that is not spent executing generated programs in the target engine).
    /// This includes time required for worker synchronization,
    ///     to mutate/generate a program, to lift it,
    ///     to restart the target process after crashes/timeouts, etc.
    std::chrono::time_point<steady_clock> last_pre_exec_date;
    std::chrono::time_point<steady_clock> last_exec_date;

    MovingAverage overhead_avg;

    /// Moving average to keep track of average program size.
    MovingAverage gen_program_size_avg;

    /// Moving average to keep track of average program size in the corpus.
    /// Only computed locally, not across workers.
    MovingAverage corpus_program_size_avg;

    /// Moving average of the number of valid programs in the last 1000 generated programs.
    MovingAverage correctness_rate;

    /// Moving average of the number of timeouts in the last 1000 generated programs.
    MovingAverage timeout_rate;

    /// All data from connected workers.

    /// The IDs of workers that are currently inactive.

    /// Moving average of the number of failed graph2js in the last 1000 mutated seeds.
    MovingAverage lift_error_rate;

    /// member functions

    void start_timer();

    ExportStatistics compute();
};

} /// end of namespace


#endif //FUZZFLOW_MOVINGSTATISTICS_H
