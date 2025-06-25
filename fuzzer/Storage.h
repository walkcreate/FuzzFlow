#ifndef FUZZFLOW_STORAGE_H
#define FUZZFLOW_STORAGE_H

#include "../utils/common_using.h"

#include "corpus/SeedEntry.h"
#include "protobuf/ExportStatistics.h"
#include "events/Observer.h"

namespace FuzzFlow {

class Fuzzer;

///
/// Store programs to disk.
/// Store fuzzer statistics to disk.
///
class Storage : public Observer {
public:
    const string statistics_dir;
    const uint32_t export_interval_mins;

    Storage(const string storage_dir,
            const uint32_t export_interval_min=0,
            uint32_t dump_tests_num=0)
            :
            /// Initialization of Non-Static const Data Members with Initializer List
            storage_dir {storage_dir},
            crashes_dir {storage_dir + "/crashes"},
            duplicate_crashes_dir {storage_dir + "/duplicates"},
            corpus_dir {storage_dir + "/corpus"},
            failed_dir {storage_dir + "/failed"},
            timeout_dir {storage_dir + "/timeouts"},
            statistics_dir {storage_dir + "/stats"},
            diagnostics_dir {storage_dir + "/diagnostics"},
            dump_tests_dir {storage_dir + "/dumpTests"},
            export_interval_mins {export_interval_min},
            dump_tests_limit {dump_tests_num}
    {
        dump_tests_count = 0;
    }

    void initialize();

    void save_crash(const shared_ptr<SeedEntry>& seed) const;

    /// save specific number testcases for evaluation
    bool dump_generated_testcases(const shared_ptr<SeedEntry>& seed);

    void save_statistics(ExportStatistics proto_stats) const;

private:
    /// parent dir
    const string storage_dir;

    /// sub dirs
    const string crashes_dir;
    const string duplicate_crashes_dir;
    const string corpus_dir;
    const string failed_dir;
    const string timeout_dir;
    const string diagnostics_dir;

    const string dump_tests_dir;

    /// dump all the generated test cases
    uint32_t dump_tests_count = 0;

    /// user setting
    uint32_t dump_tests_limit;

    void onNotify(EventType eventType, const shared_ptr<EventData>& eventData) override;

    static void store_seed(const shared_ptr<SeedEntry>& seed, const string& filename, const string &directory) ;

    static void write_to_path(const string& path, const string &content);

    static void set_timer(unsigned int interval_seconds);

    void timer_callback(int signum);
};

} /// end of namespace

#endif //FUZZFLOW_STORAGE_H
