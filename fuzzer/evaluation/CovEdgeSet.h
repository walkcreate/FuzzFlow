#ifndef FUZZFLOW_COVEDGESET_H
#define FUZZFLOW_COVEDGESET_H

#include "../../utils/common_using.h"

#include "../libcoverage/include/libcoverage.h"
#include "ProgramAspects.h"

namespace FuzzFlow {

class CovEdgeSet final : public ProgramAspects {
public:
    uint64_t num_edges;
    uint32_t * edge_indices;

    CovEdgeSet(uint32_t* edge_indices, uint64_t num_edges)
        : ProgramAspects(ExecutionOutcome::succeeded)
    {
        this->edge_indices = edge_indices;
        this->num_edges = num_edges;
    }

    CovEdgeSet& operator=(const CovEdgeSet& c)
    {
        cout << "Call defined copy assignment\n";
        this->edge_indices = c.edge_indices;
        this->num_edges = c.num_edges;
        return *this;
    }

    CovEdgeSet(CovEdgeSet&& c)  noexcept
        : ProgramAspects(ExecutionOutcome::succeeded)
    {
        cout << "Call defined move constructor\n";

        this->edge_indices = c.edge_indices;
        this->num_edges = c.num_edges;

        c.num_edges = 0;
        c.edge_indices = nullptr;
    }

    ~CovEdgeSet() override
    {
        /// The memory is allocated in libcoverage internal_evaluate
        free(this->edge_indices);
    }

    uint64_t count() override
    {
        return num_edges;
    }

    [[nodiscard]] string description() const
    {
        return "new coverage: " + std::to_string(num_edges) + "newly discovered edge in the CFG of the target";
    }

    vector<uint32_t> subtracting(const unique_ptr<CovEdgeSet>& another_set) const;

    vector<uint32_t> intersection(const unique_ptr<CovEdgeSet>& another_set) const;

    void set_edges(vector<uint32_t> edge_idxs);
};

} /// end of namespace

#endif //FUZZFLOW_COVEDGESET_H
