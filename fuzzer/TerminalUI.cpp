#include "TerminalUI.h"

#include <iomanip>

using std::to_string;
using std::endl;

namespace FuzzFlow {

void TerminalUI::print_statistics(ExportStatistics const& stats)
{
    string fuzzing_seconds = format_seconds_duration(stats.fuzzing_seconds);
    string last_interesting_duration = format_seconds_duration(stats.last_interesting_seconds);

    cout <<  "-----------------\n" << std::fixed << std::setprecision(2);
    cout << "Fuzzer state:                 " << endl;
    cout << "Uptime:                       " << fuzzing_seconds << endl;
    cout << "Total Samples:                " << to_string(stats.total_samples) << endl;
    cout << "Interesting Samples Found:    " << to_string(stats.interesting_samples) << endl;
    cout << "Last Interesting Sample:      " << last_interesting_duration << endl;
    cout << "Valid Samples Found:          " << to_string(stats.valid_samples) << endl;
    cout << "Corpus Size:                  " << to_string(stats.corpus_size) << endl;
    cout << "Correctness Rate:             " << to_string(stats.correctness_rate) << endl;
    cout << "Timeout Rate:                 " << to_string(stats.timeout_rate) << endl;
    cout << "Crashes Found:                " << to_string(stats.crashing_samples) << endl;
    cout << "Timeouts Hit:                 " << to_string(stats.timeout_samples) << endl;
    cout << "Coverage:                     " << to_string(stats.coverage) << endl;
    cout << "Avg. program size:            " << to_string(stats.gen_program_size_avg) << endl;
    cout << "Avg. corpus program size:     " << to_string(stats.corpus_program_size_avg) << endl;
    cout << "Connected nodes:              " << to_string(1) << endl;
    cout << "Execs / Second:               " << to_string(stats.execs_per_second) << endl;
    cout << "Total Execs:                  " << to_string(stats.total_execs) << endl;
    cout <<  "-----------------\n";
}

} /// end of namespace FuzzFlow