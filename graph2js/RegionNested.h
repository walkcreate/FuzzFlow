#ifndef FUZZFLOW_REGIONNESTED_H
#define FUZZFLOW_REGIONNESTED_H

#include "../utils/common_using.h"
#include "../utils/assert_or_throw.h"

namespace FuzzFlow {

class RegionSingle;

class RegionNested final : public Region {
public:
    /// todo
    /// Each Region contains a default RegionSingle?
    /// This simplifies the timing of RegionSingle creation.
    RegionNested() = default;

    ~RegionNested() override = default;

    /// RegionNested is composed of base region units ().
    /// A superior Region serves as the owner of a subordinate Region.
    vector<shared_ptr<Region>> regions {};

    void add_region(const shared_ptr<Region>& sub_region)
    {
        if (const shared_ptr<RegionNested> node_self = static_pointer_cast<RegionNested>(shared_from_this());
            node_self != sub_region)
        {
            sub_region->depth = node_self->depth + 1;

            /// double link
            this->regions.push_back(sub_region);
            sub_region->parent_region = node_self;

            /// copy parent's list and add new one
            sub_region->parent_region_list = node_self->parent_region_list;
            sub_region->parent_region_list.push_back(node_self);
        }
        else {
            assert_or_throw_graph2js(false, "Circle in regions");
        }
    }

    shared_ptr<Region> get_first_region() const
    {
        return regions[0];
    }

};

} /// end of namespace

#endif //FUZZFLOW_REGIONNESTED_H
