#include "CovEdgeSet.h"

namespace FuzzFlow {

/// Calc edge indices only in this object, not existing in another set
vector<uint32_t> CovEdgeSet::subtracting(const unique_ptr<CovEdgeSet>& another_set) const
{
    vector<uint32_t> sub_set;
    for (int i = 0; i < num_edges; i++) {
        uint32_t edge_idx = this->edge_indices[i];

        bool contains = false;
        for (int j = 0; j < another_set->num_edges; j++) {
            if (edge_idx == another_set->edge_indices[j]) {
                contains = true;
                break;
            }
        }

        if (!contains) {
            sub_set.push_back(edge_idx);
        }
    }

    return sub_set;
}

vector<uint32_t> CovEdgeSet::intersection(const unique_ptr<CovEdgeSet>& another_set) const
{
    vector<uint32_t> inter_set;
    for (int i = 0; i < num_edges; i++) {
        uint32_t edge_idx = this->edge_indices[i];

        bool contains = false;
        for (int j = 0; j < another_set->num_edges; j++) {
            if (edge_idx == another_set->edge_indices[j]) {
                contains = true;
                break;
            }
        }

        if (contains) {
            inter_set.push_back(edge_idx);
        }
    }

    return inter_set;
}

void CovEdgeSet::set_edges(vector<uint32_t> edge_idxs)
{
    assert(edge_idxs.size() <= this->num_edges
        && "Precondition false in CovEdgeSet::set_edges");

    this->num_edges = edge_idxs.size();

    for (int i=0; i < this->num_edges; i++) {
        this->edge_indices[i] = edge_idxs[i];
    }

    // null terminate
    this->edge_indices[this->num_edges] = 0;
}

} /// end of namespace