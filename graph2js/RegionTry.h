#ifndef FUZZFLOW_REGIONTRY_H
#define FUZZFLOW_REGIONTRY_H

#include "Region.h"
#include "RegionExpr.h"
#include "RegionNested.h"

namespace FuzzFlow {

class RegionTry final : public Region {
public:
    bool has_catch = false;
    bool has_finally = false;

    /// This is a nested region
    shared_ptr<RegionNested> try_block = nullptr;
    shared_ptr<RegionExpr> catch_expr = nullptr;
    shared_ptr<RegionNested> catch_block = nullptr;
    shared_ptr<RegionNested> finally_block = nullptr;

    RegionTry(const bool has_catch, const bool has_finally)
    {
        this->try_block = make_shared<RegionNested>();

        if (has_catch) {
            this->has_catch = true;
            this->catch_block = make_shared<RegionNested>();
            this->catch_expr = make_shared<RegionExpr>();
        }

        if (has_finally) {
            this->has_finally = true;
            this->finally_block = make_shared<RegionNested>();
        }
    }

    void post_construct()
    {
        auto node_self = static_pointer_cast<RegionTry>(shared_from_this());
        weak_ptr<const RegionTry> node_self_const = std::const_pointer_cast<const RegionTry>(node_self);

        const shared_ptr<const RegionNested> try_parent = node_self->parent_region.lock();

        if (catch_expr) {
            auto sub_region = this->catch_expr;
            sub_region->parent_region = try_parent;
            sub_region->parent_region_list = try_parent->parent_region_list;
            sub_region->parent_region_list.push_back(try_parent);
        }

        /// The try, catch, and finally blocks are themselves RegionNested and can serve as parents.
        /// Their parent should be set to the parent of the RegionTry.
        ///
        auto sub_region1 = this->try_block;
        sub_region1->parent_region = try_parent;
        sub_region1->parent_region_list = try_parent->parent_region_list;
        sub_region1->parent_region_list.push_back(try_parent);

        if (this->catch_block) {
            auto sub_region2 = this->catch_block;
            sub_region2->parent_region = try_parent;
            sub_region2->parent_region_list = try_parent->parent_region_list;
            sub_region2->parent_region_list.push_back(try_parent);
        }

        if (this->finally_block) {
            auto sub_region3 = this->finally_block;
            sub_region3->parent_region = try_parent;
            sub_region3->parent_region_list = try_parent->parent_region_list;
            sub_region3->parent_region_list.push_back(try_parent);
        }
    }
};

} /// end of namespace


#endif //FUZZFLOW_REGIONTRY_H
