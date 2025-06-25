#ifndef FUZZFLOW_REGIONIFNODE_H
#define FUZZFLOW_REGIONIFNODE_H

#include "Region.h"
#include "RegionExpr.h"
#include "RegionSingle.h"
#include "RegionNested.h"

namespace FuzzFlow {

class RegionIfNode final : public Region {
public:
    shared_ptr<RegionExpr> condition;
    shared_ptr<RegionNested> branch_true;
    shared_ptr<RegionNested> branch_false;

    RegionIfNode()
    {
        this->condition = make_shared<RegionExpr>();
        this->branch_true = make_shared<RegionNested>();
        this->branch_false = make_shared<RegionNested>();
    }

    void post_construct()
    {
        const auto node_self = static_pointer_cast<RegionIfNode>(shared_from_this());
        weak_ptr<const RegionIfNode> node_self_const = const_pointer_cast<const RegionIfNode>(node_self);

        shared_ptr<const RegionNested> if_parent = node_self->parent_region.lock();

        auto sub_region1 = this->condition;
        sub_region1->parent_region = if_parent;
        sub_region1->parent_region_list = if_parent->parent_region_list;
        sub_region1->parent_region_list.push_back(if_parent);

        /// Both branch true and branch false are RegionNested and can be used as parents.
        /// Set their parent to the parent of the if statement.

        auto sub_region2 = this->branch_true;
        sub_region2->parent_region = if_parent;
        sub_region2->parent_region_list = if_parent->parent_region_list;
        sub_region2->parent_region_list.push_back(if_parent);

        auto sub_region3 = this->branch_false;
        sub_region3->parent_region = if_parent;
        sub_region3->parent_region_list = if_parent->parent_region_list;
        sub_region3->parent_region_list.push_back(if_parent);
    }
};

} /// end of namespace

#endif //FUZZFLOW_REGIONIFNODE_H
