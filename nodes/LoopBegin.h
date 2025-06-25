#ifndef FUZZFLOW_LOOPBEGIN_H
#define FUZZFLOW_LOOPBEGIN_H

#include "IRNode.h"
#include "FixedNode.h"
#include "AbstractMergeNode.h"
#include "LoopIf.h"
#include "./js/ForInEnum.h"

/**
 * LoopBegin merges the loop start and end.
 */
namespace FuzzFlow {

enum class LoopType {
    IF,
    FORIN
};

class LoopBegin final : public AbstractMergeNode {
private:
    static const string label;

public:
    LoopType loop_type = LoopType::IF;
    weak_ptr<LoopIf> loop_if;
    weak_ptr<ForInEnum> loop_forin;

    string get_label() override
    {
        return LoopBegin::label;
    }

    /// The next arg may be IfNode, but not sure.
    /// If there is any sequential operation in the conditional expression,
    /// there would be Uni node between LoopBegin and LoopIf.
    LoopBegin(const vector<weak_ptr<EndMayMergeNode>> &_merged_flows,
              const weak_ptr<FixedNode>& next)
        : AbstractMergeNode(_merged_flows, next)
    {
        this->node_hash_current = label;
    }

    void set_loop_if(const weak_ptr<LoopIf>& _loop_if)
    {
        this->loop_type = LoopType::IF;
        this->loop_if = _loop_if;
    }

    void set_for_in(const weak_ptr<ForInEnum>& _loop_forin)
    {
        this->loop_type = LoopType::FORIN;
        this->loop_forin = _loop_forin;
    }

    shared_ptr<IRNode> clone() override
    {
        auto new_node = make_shared<LoopBegin>(this->merged_flows, this->next());
        new_node->set_loop_if(this->loop_if);
        return new_node;
    }

    void clone_repair(map<weak_ptr<IRNode>,
                          weak_ptr<IRNode>,
                              std::owner_less<>> &refNode2ownNode) override
    {
        ASSERT_OR_EXIT(refNode2ownNode.contains(this->successor));
        ASSERT_OR_EXIT(! refNode2ownNode[this->successor].expired());

        this->successor = dynamic_pointer_cast<FixedNode>(
            refNode2ownNode[this->successor].lock());

        ASSERT_OR_EXIT(this->successor.lock() != nullptr);

        for (auto & merged_flow : this->merged_flows) {
            ASSERT_OR_EXIT(refNode2ownNode.contains(merged_flow));
            ASSERT_OR_EXIT(! refNode2ownNode[merged_flow].expired());

            merged_flow = dynamic_pointer_cast<EndMayMergeNode>(
                refNode2ownNode[merged_flow].lock());

            ASSERT_OR_EXIT(merged_flow.lock() != nullptr);
        }

        if (! this->loop_if.expired()) {
            ASSERT_OR_EXIT(refNode2ownNode.contains(this->loop_if));
            ASSERT_OR_EXIT(! refNode2ownNode[this->loop_if].expired());

            this->loop_if = dynamic_pointer_cast<LoopIf>(
            refNode2ownNode[this->loop_if].lock());

            ASSERT_OR_EXIT(this->loop_if.lock() != nullptr);
        }

        if (! this->loop_forin.expired()) {
            ASSERT_OR_EXIT(refNode2ownNode.contains(this->loop_forin));
            ASSERT_OR_EXIT(! refNode2ownNode[this->loop_forin].expired());

            this->loop_forin = dynamic_pointer_cast<ForInEnum>(
            refNode2ownNode[this->loop_forin].lock());

            ASSERT_OR_EXIT(this->loop_forin.lock() != nullptr);
        }

        this->post_construct();
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<LoopBegin>(shared_from_this());
        visitor.visit(node);
    }
};

} /// end of namespace

#endif //FUZZFLOW_LOOPBEGIN_H
