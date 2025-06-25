#include "Storage.h"

#include "../utils/util_time.h"

/// for timer
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>

namespace FuzzFlow {

void Storage::initialize()
{
    fs::create_directories(this->crashes_dir);
    fs::create_directories(this->duplicate_crashes_dir);
    fs::create_directories(this->corpus_dir);
    fs::create_directories(this->statistics_dir);
    fs::create_directories(this->dump_tests_dir);

    bool diagnostics = false;
    if (diagnostics) {
        fs::create_directories(this->failed_dir);
        fs::create_directories(this->timeout_dir);
        fs::create_directories(this->diagnostics_dir);
    }
}

void Storage::onNotify(EventType eventType, const shared_ptr<EventData> &eventData)
{
    switch (eventType) {
        case EventType::CrashFound: {
            auto dataCrashFound = dynamic_pointer_cast<DataCrashFound>(eventData);
            save_crash(dataCrashFound->seed_entry);
            break;
        }
        case EventType::Shutdown: {
            break;
        }
        default: {
            return;
        }
    }
}

void Storage::write_to_path(const string& path, const string &content)
{
    std::ofstream ofs(path, std::ofstream::out);
    ofs << content << std::endl;
    ofs.close();
}

void Storage::store_seed(const shared_ptr<SeedEntry>& seed,
                         const string& filename,
                         const string &directory)
{
    const string path = directory + "/" + filename + ".js";
    write_to_path(path, seed->newly_js_code);

    // Also store the seed program in its protobuf format. This can later be imported again or inspected

    // If inspection is enabled, we also include the programs ancestor chain in a separate .history file
}

void Storage::save_statistics(ExportStatistics proto_stats) const
{
    std::cout << "Enumerating save statistics: "
              << std::to_string(proto_stats.total_samples) << "\n";

    string sr_data = boost::json::serialize((boost::json::value_from(proto_stats)));

    string path = this->statistics_dir + "/" + format_date() + ".json";

    std::ofstream ofs(path, std::ofstream::out);
    ofs << sr_data << std::endl;
    ofs.close();
}

void Storage::save_crash(const shared_ptr<SeedEntry>& seed) const
{
    const string file_name = "program_" + format_date() + seed->uuid2str() + ".js";
    store_seed(seed, file_name, this->crashes_dir);
}

/// returns true when the dumped test cases
bool Storage::dump_generated_testcases(const shared_ptr<SeedEntry>& seed)
{
    const string file_name = "program_" + format_date() + seed->uuid2str() + ".js";
    store_seed(seed, file_name, this->dump_tests_dir);
    this->dump_tests_count += 1;

    if (this->dump_tests_count >= this->dump_tests_limit) {
        std::cout << "We have collected specific number of generated test cases\n";
        return true;
    }

    return false;
}

void Storage::timer_callback(int signum)
{
    //this->save_statistics();
}

///
/// Print and save fuzzing statistics through timer
///
void Storage::set_timer(const unsigned int interval_seconds)
{
    struct itimerval new_timer;
    struct itimerval old_timer;

    /// notify your application for `a` second and then every `b` seconds can be set up as follows:
    new_timer.it_value.tv_sec = interval_seconds;         /// a
    new_timer.it_value.tv_usec = 0;
    new_timer.it_interval.tv_sec = interval_seconds;      /// b
    new_timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_REAL, &new_timer, &old_timer);
    //signal(SIGALRM, this->timer_callback);
}

} /// end of namespace