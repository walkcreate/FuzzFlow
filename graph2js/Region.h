#ifndef FUZZFLOW_REGION_H
#define FUZZFLOW_REGION_H

#include "../utils/common_using.h"

namespace FuzzFlow {

/// Composite pattern

class RegionNested;

class RegionSingle;

///
/// Region is an abstract class.
///
/// The Region class addresses code generation through graph node traversal, which is not a sequential process.
/// This is mainly due to control flow branches (if-else, loops) and related phi nodes.
///
class Region : public enable_shared_from_this<Region> {
public:
    Region() = default;

    /// enable poly
    virtual ~Region() = 0;

    /// Starting from the Region corresponding to the Graph, its depth is designated as 1,
    /// and for every subsequent level downwards, the depth increases by 1.
    unsigned int depth = 1;

    weak_ptr<const RegionNested> parent_region;

    weak_ptr<const RegionSingle> prev_region;

    /// The top-down sequence from the top region to the parent region.
    vector<weak_ptr<const RegionNested>> parent_region_list;

    /// Query for the nearest common parent Region among multiple Regions, searching from bottom to top.
    static weak_ptr<RegionNested> get_mini_parent_region(const set<weak_ptr<Region>,
                                                                   std::owner_less<>>& var2regions_set);
};

} /// end of namespace

#endif //FUZZFLOW_REGION_H
