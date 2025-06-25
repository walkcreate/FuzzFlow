#include "Region.h"
#include "RegionNested.h"

namespace FuzzFlow {

/**
 * Even if you declare a destructor as a pure virtual function, you must provide an implementation for it.
 * Although you cannot instantiate an abstract class directly, it is always instantiated when you instantiate
 * one of its derived (concrete) classes.
 * And so at some point such instances will be destroyed, thus requiring a destructor.
 *
 * The implementation of the pure virtual destructor can be (and normally is) an empty function
 */
Region::~Region() = default;

///
/// Finds the nearest common parent Region of multiple Regions (bottom-up),
/// used to determine where to declare a variable.
///
weak_ptr<RegionNested> Region::get_mini_parent_region(const set<weak_ptr<Region>,
                                                                std::owner_less<>>& var2regions_set)
{
    /// convert set to vector to access by index
    vector<weak_ptr<Region>> var2regions_v(var2regions_set.begin(), var2regions_set.end());

    /// The smallest common parent node exists in the parent node set of every region
    /// and must also be present in the parent node set of the first region.
    ///
    auto var2regions_0 = var2regions_v[0].lock()->parent_region_list;
    if (var2regions_0.empty()) {
        auto top_region = std::dynamic_pointer_cast<RegionNested>(var2regions_v[0].lock());
        assert((top_region != nullptr));
        return top_region;
    }

    /// Search from front to back; in the worst case, the first item in the parent region list,
    /// the top region, is the mini parent region.
    ///
    weak_ptr<const RegionNested> mini_parent = var2regions_v[0].lock()->parent_region_list[0];

    /// Traverse each region in var2regions_0 from front to back until the mini parent.
    /// Each region is present in all var2regions.
    /// When i = 0, it's the top region, so no traversal is needed.
    for (int i = 1; i < var2regions_0.size(); i++) {
        bool all_regions_have = true;
        shared_ptr<const RegionNested> cur_parent_region = var2regions_0[i].lock();

        for (int j = 1; j < var2regions_v.size(); j++) {
            vector<weak_ptr<const RegionNested>> parent_list = var2regions_v[j].lock()->parent_region_list;

            if ( (parent_list.size() <= i)
                || (parent_list[i].lock() != cur_parent_region) )
            {
                all_regions_have = false;
                break;
            }
        }

        if (all_regions_have) {
            mini_parent = cur_parent_region;
        }
        else {
            break;
        }
    }

    /// convert const ptr to non-const
    return std::const_pointer_cast<RegionNested>(mini_parent.lock());
}

} /// end of namespace