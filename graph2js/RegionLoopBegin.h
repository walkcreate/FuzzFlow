#ifndef FUZZFLOW_REGIONLOOPBEGIN_H
#define FUZZFLOW_REGIONLOOPBEGIN_H

#include "Region.h"
#include "RegionExpr.h"
#include "RegionSingle.h"
#include "RegionNested.h"

namespace FuzzFlow {

enum class LoopMode {
    WHILE,
    FORIN
};

class RegionLoopBegin final : public Region {
public:
    LoopMode mode;

    /// Before the loop, the input[0] of the PhiNode in LoopBegin should be lifted to this point.
    shared_ptr<RegionSingle> loop_before;

    ///
    /// When lifting the loop condition, in addition to the final returned expression,
    /// statement code may need to be generated.
    /// Since the loop condition is lifted before the PhiNode, this part of the code is generated first.
    /// If lifted into the loop before section, it becomes difficult to distinguish.
    /// Therefore, a separate region is created to handle statements generated from the loop condition.
    /// The input[0] of the PhiNode in LoopBegin is lifted to the loop before section.
    /// This represents the actual pre-loop code.
    ///
    /// The data flow of expressions in the loop condition is outside the scope of PhiNode -> input[0].
    ///
    shared_ptr<RegionSingle> loop_fake_before;

    shared_ptr<RegionExpr> loop_condition;

    /// Only regions potentially nested inside the loop body are considered.
    shared_ptr<RegionNested> loop_body;

    shared_ptr<RegionSingle> loop_body_tail;

    explicit RegionLoopBegin(const LoopMode mode)
    {
        this->mode = mode;

        this->loop_before = make_shared<RegionSingle>();
        this->loop_fake_before = make_shared<RegionSingle>();
        this->loop_condition = make_shared<RegionExpr>();
        this->loop_body = make_shared<RegionNested>();
        this->loop_body_tail = make_shared<RegionSingle>();
    }

    /// Initializes the parent region (list) for sub-regions under RegionLoopBegin.
    void post_construct()
    {
        const auto node_self = static_pointer_cast<RegionLoopBegin>(shared_from_this());
        shared_ptr<const RegionNested> loop_parent = node_self->parent_region.lock();

        /// Bidirectional linkage.
        /// Set the parent to the parent of RegionLoopBegin.
        ///
        /// TODO: Can RegionLoopBegin and RegionIf be used as parents?
        auto sub_region1 = this->loop_before;
        sub_region1->parent_region = loop_parent;
        sub_region1->parent_region_list = loop_parent->parent_region_list;
        sub_region1->parent_region_list.push_back(loop_parent);

        auto sub_region4 = this->loop_fake_before;
        sub_region4->parent_region = loop_parent;
        sub_region4->parent_region_list = loop_parent->parent_region_list;
        sub_region4->parent_region_list.push_back(loop_parent);

        auto sub_region2 = this->loop_condition;
        sub_region2->parent_region = loop_parent;
        sub_region2->parent_region_list = loop_parent->parent_region_list;
        sub_region2->parent_region_list.push_back(loop_parent);

        auto sub_region3 = this->loop_body;
        sub_region3->parent_region = loop_parent;
        sub_region3->parent_region_list = loop_parent->parent_region_list;
        sub_region3->parent_region_list.push_back(loop_parent);

        /// The parent of the loop body tail is the loop body (RegionNested).
        auto sub_region5 = this->loop_body_tail;
        sub_region5->parent_region = this->loop_body;
        sub_region5->parent_region_list = this->loop_body->parent_region_list;
        sub_region5->parent_region_list.push_back(this->loop_body);
    }

};

} /// end of namespace

#endif //FUZZFLOW_REGIONLOOPBEGIN_H
