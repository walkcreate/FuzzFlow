#include "ProgramCoverageEvaluator.h"
#include "../Fuzzer.h"

namespace FuzzFlow {

/// initialize static members
uint32_t ProgramCoverageEvaluator::instances = 0;

void ProgramCoverageEvaluator::onNotify(EventType eventType,
                                        const shared_ptr<EventData> &eventData)
{
    switch (eventType) {
        case EventType::PreExecute: {
            cov_clear_bitmap(this->cov_ctx_p);
            break;
        }
        default: {
            cout << "[" << name << "] Unknown signal received\n";
        }
    }
}

void ProgramCoverageEvaluator::set_fuzzer(weak_ptr<Fuzzer> fuzzer)
{
    this->fuzzer = fuzzer;
}

void ProgramCoverageEvaluator::initialize(unique_ptr<REPRL> &runner)
{
    //cov_clear_bitmap(this->cov_ctx_p);

    /*
     * We need a single run to finish initialization of ProgramCoverageEvaluator
     * The instrumented engine run sanitizer_trace_pc_guard_init to tell the edge set information to the fuzzer
     */
    string program = "print(\"Happy fuzzing!\");\n";

    Execution execution = runner->run(program, 250 * 1000);
    cout << reprl_fetch_stdout(runner->reprl_ctx);

    cov_finish_initialization(this->cov_ctx_p, this->should_track_edge_counts ? 1 : 0);
}

void ProgramCoverageEvaluator::eval_execution() const
{
    /// The memory of new_edge_set->edge_indices is allocated in cov_evaluate (libcoverage)
    struct edge_set new_edge_set;
    cov_evaluate(this->cov_ctx_p, &new_edge_set);
}

optional<unique_ptr<CovEdgeSet>> ProgramCoverageEvaluator::evaluate(const Execution &execution)
{
    assert(execution.outcome == ExecutionOutcome::succeeded
           && "The Execution to be evaluated should be succeeded.");

    /// The memory of new_edge_set->edge_indices is allocated in cov_evaluate (libcoverage)
    struct edge_set new_edge_set;
    int result = cov_evaluate(this->cov_ctx_p, &new_edge_set);

    if (result == -1) {
        cout << "Could not evaluate sample\n";
        return std::nullopt;
    }
    else if (result == 1) {
        auto cov_edge_set = make_unique<CovEdgeSet>(new_edge_set.edge_indices, new_edge_set.count);
        return std::move(cov_edge_set);
    }
    else {
        assert(new_edge_set.edge_indices == nullptr && new_edge_set.count == 0);
        return std::nullopt;
    }
}

void ProgramCoverageEvaluator::reset_edge(uint32_t edge)
{
    if (this->reset_counts.contains(edge)) {
        this->reset_counts[edge] += 1;
    } else {
        this->reset_counts.insert_or_assign(edge, 1);
    }

    if (this->reset_counts[edge] <= max_reset_count) {
        cov_clear_edge_data(this->cov_ctx_p, uint64_t(edge));
    }
}

void ProgramCoverageEvaluator::reset_aspects(unique_ptr<CovEdgeSet> &aspects)
{
    for (int i = 0; i < aspects->count(); i++) {
        this->reset_edge(aspects->edge_indices[i]);
    }
}

optional<unique_ptr<CovEdgeSet>>
ProgramCoverageEvaluator::compute_aspect_intersection(unique_ptr<CovEdgeSet> &first_cov_edge_set)
{
    this->reset_aspects(first_cov_edge_set);

    uint32_t timeout_us = 250 * 1000;

    Execution execution = fuzzer.lock()->only_execute(timeout_us, false);

    if (execution.outcome != ExecutionOutcome::succeeded) {
        return std::nullopt;
    }

    auto optional_cov_edge_set = this->evaluate(execution);
    if (optional_cov_edge_set == std::nullopt) {
        return std::nullopt;
    }

    unique_ptr<CovEdgeSet> second_cov_edge_set = std::move(optional_cov_edge_set.value());

    // Reset all edges that were only triggered by the 2nd execution (those only triggered by the 1st execution were already reset earlier).
    vector<uint32_t> only_covered_by_second = second_cov_edge_set->subtracting(first_cov_edge_set);

    for (auto &edge_idx: only_covered_by_second) {
        this->reset_edge(edge_idx);
    }

    // Compute the intersection of the edges.
    vector<uint32_t> inter_set = second_cov_edge_set->intersection(first_cov_edge_set);
    if (inter_set.size() == 0) {
        return std::nullopt;
    }

    // Here we reuse one of the existing CovEdgeSets instead of creating a new one to avoid a malloc() and free() of the backing buffer.
    second_cov_edge_set->set_edges(inter_set);
    return std::move(second_cov_edge_set);
}

} /// end of namespace FuzzFlow