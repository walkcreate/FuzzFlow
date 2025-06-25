#ifndef FUZZFLOW_PROGRAMCOVERAGEEVALUATOR_H
#define FUZZFLOW_PROGRAMCOVERAGEEVALUATOR_H

#include <cassert>

extern "C" {
#include "../libcoverage/include/libcoverage.h"
};

#include "../../utils/common_using.h"

#include "CovEdgeSet.h"
#include "../execution/REPRL.h"
#include "../corpus/SeedEntry.h"

#include "../events/Event.h"
#include "../events/Observer.h"

namespace FuzzFlow {

/// forward declaration
class Fuzzer;

class ProgramCoverageEvaluator final : public Observer {
public:
    /// Counts the number of instances.
    /// Used to create unique shared memory regions in every instance.
    static uint32_t instances;

    ProgramCoverageEvaluator(const unique_ptr<REPRL>& runner)
    {
        cov_ctx_p = &cov_ctx;

        cov_ctx.id = ProgramCoverageEvaluator::instances;
        ProgramCoverageEvaluator::instances += 1;

        cov_initialize(cov_ctx_p);

        int process_id = getpid();
        runner->set_env("SHM_ID",
                        "shm_id_" + std::to_string(process_id) + "_" + std::to_string(cov_ctx.id));

        const char* shm_key = getenv("SHM_ID");
        cout << shm_key << std::endl;
    }

    ~ProgramCoverageEvaluator() override
    {
        // Unlink the shared memory regions on shutdown
        cout << "ProgramCoverageEvaluator shutdown. Unlink the shared memory.\n";
        cov_shutdown(this->cov_ctx_p);
    }

    void set_fuzzer(weak_ptr<Fuzzer> fuzzer);

    void initialize(unique_ptr<REPRL>& runner);

    void eval_execution() const;

    optional<unique_ptr<CovEdgeSet>> evaluate(const Execution& execution);

    optional<unique_ptr<CovEdgeSet>> compute_aspect_intersection(unique_ptr<CovEdgeSet>& aspects);

    void reset_edge(uint32_t edge);

    void reset_aspects(unique_ptr<CovEdgeSet>& aspects);

    /// The current edge coverage percentage.
    float current_score() {
        return double(cov_ctx.found_edges) / double(cov_ctx.num_edges);
    }

private:
    static constexpr string_view name {"ProgramEvaluator"};

    /// ProgramCoverageEvaluator is a member of Fuzzer class but needs to call
    /// methods from its parent Fuzzer instance.
    ///
    /// While main() holds the Fuzzer's shared_ptr (as owner), we keep a weak_ptr
    /// here for non-owning access to the Fuzzer instance.
    ///
    weak_ptr<Fuzzer> fuzzer;

    struct cov_context cov_ctx;
    struct cov_context* cov_ctx_p;

    /// Whether per-edge hit counts should be tracked as well.
    /// These are expensive to compute, so this need to be enabled explicitly.
    bool should_track_edge_counts = false;

    /// Keep track of how often an edge has been reset. Frequently set/cleared edges will be ignored
    map<uint32_t, uint64_t> reset_counts;

    /// How often an edge may be reset at most before it is considered non-deterministic.
    /// In that case, the edge is marked as found, but will not be considered an aspect of any program.
    uint64_t max_reset_count = 1000;

    void onNotify(EventType eventType, const shared_ptr<EventData>& eventData) override;
};

} /// end of namespace

#endif //FUZZFLOW_PROGRAMCOVERAGEEVALUATOR_H
