#ifndef FUZZFLOW_EVENT_H
#define FUZZFLOW_EVENT_H

#include "../corpus/SeedEntry.h"

namespace FuzzFlow {

enum class EventType {
    Initialized,
    Shutdown,

    ///
    TryLift,

    /// Signals that a new (mutated) program has been generated.
    ProgramGenerated,

    ValidProgramFound,
    InvalidProgramFound,

    CrashFound,
    TimeOutFound,
    InterestingFound,

    PreExecute,
    PostExecute,

    PreExportStatistics,
};

struct EventData {
    virtual ~EventData() = default;
};

class DataCrashFound final : public EventData {
public:
    shared_ptr<SeedEntry> seed_entry;

    explicit DataCrashFound(shared_ptr<SeedEntry> seed_entry)
        : seed_entry(std::move(seed_entry)) {}
};

class DataTryLift final : public EventData {
public:
    bool lift_success;

    explicit DataTryLift(bool lift_success)
        : lift_success(lift_success) {}
};

class DataProgramGenerated final : public EventData {
public:
    uint32_t mutated_graph_size;

    explicit DataProgramGenerated(uint32_t mutated_graph_size)
        : mutated_graph_size(mutated_graph_size) {}
};

class DataValidProgramFound final : public EventData {
public:
    bool is_interesting;

    explicit DataValidProgramFound(const bool is_interesting)
        : is_interesting(is_interesting) {}
};

} // end namespace FuzzFlow

#endif //FUZZFLOW_EVENT_H
