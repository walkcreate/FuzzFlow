#include "MovingStatistics.h"

namespace FuzzFlow {

void MovingStatistics::onNotify(EventType eventType,
                                const shared_ptr<EventData>& eventData)
{
    switch (eventType) {
        case EventType::TryLift: {
            if (auto dataTryLift = dynamic_pointer_cast<DataTryLift>(eventData)) {
                double lift_moving = dataTryLift->lift_success ? 0.0 : 1.0;
                lift_error_rate.add(lift_moving);
            }
            break;
        }
        case EventType::PostExecute: {
            current_execs += 1;
            json_data.total_execs += 1;
            break;
        }
        case EventType::ProgramGenerated: {
            if (auto dataProgramGenerated = dynamic_pointer_cast<DataProgramGenerated>(eventData)) {
                gen_program_size_avg.add(dataProgramGenerated->mutated_graph_size);
            }
            json_data.total_samples += 1;
            break;
        }
        case EventType::ValidProgramFound: {
            correctness_rate.add(1.0);
            timeout_rate.add(0.0);

            if (const auto dataValidProgramFound = dynamic_pointer_cast<DataValidProgramFound>(eventData)) {
                /// notify valid test case found
                ///
                /// A test case is counted as either 'interesting' or 'valid' - never both.
                /// 'Valid' here means the input is structurally correct but not interesting.
                if (! dataValidProgramFound->is_interesting) {
                    json_data.valid_samples += 1;
                }
            }
            break;
        }
        case EventType::InvalidProgramFound: {
            correctness_rate.add(0.0);
            timeout_rate.add(0.0);
            break;
        }
        case EventType::CrashFound: {
            json_data.crashing_samples += 1;
            timeout_rate.add(0.0);
            break;
        }
        case EventType::TimeOutFound: {
            json_data.timeout_samples += 1;
            timeout_rate.add(1.0);
            correctness_rate.add(0.0);
            break;
        }
        case EventType::InterestingFound: {
            last_interesting_sample_point = steady_clock::now();
            json_data.interesting_samples += 1;
            break;
        }
        default: {
            cout << "[" << name << "] Unknown signal received\n";
        }
    }
}

ExportStatistics MovingStatistics::compute()
{
    /// extract MovingStatistics to static json_data
    json_data.gen_program_size_avg = gen_program_size_avg.current_value();
    json_data.corpus_program_size_avg = corpus_program_size_avg.current_value();
    json_data.fuzzer_overhead = overhead_avg.current_value();
    json_data.correctness_rate = correctness_rate.current_value();
    json_data.timeout_rate = timeout_rate.current_value();
    json_data.lift_error_rate = lift_error_rate.current_value();

    const auto now = steady_clock::now();
    const long fuzzing_seconds =
            duration_cast<seconds>(now - this->fuzzing_start_point).count();
    json_data.fuzzing_seconds = fuzzing_seconds;

    const long last_interesting_duration =
            duration_cast<seconds>(now - this->last_interesting_sample_point).count();
    json_data.last_interesting_seconds = last_interesting_duration;

    return json_data;
}

void MovingStatistics::start_timer()
{
    const auto _now = steady_clock::now();
    fuzzing_start_point = _now;
    last_eps_update = _now;
    last_pre_exec_date = _now;
    last_exec_date = _now;
}

} /// end of namespace