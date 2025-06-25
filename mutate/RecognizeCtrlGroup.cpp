#include "RecognizeCtrlGroup.h"

namespace FuzzFlow {

void RecognizeCtrlGroup::set_loop_tail(const weak_ptr<LoopExit> &loop_exit)
{
    if (! current_in_loops.empty()) {
        loop_tail_body[current_in_loops.back()].first = loop_exit;
        current_in_loops.pop_back();
    }
}

void RecognizeCtrlGroup::set_if_tail(const weak_ptr<AbstractMergeNode> &uni_node)
{
    if (! current_in_ifs.empty()) {
        if_tail_body[current_in_ifs.back()].first = uni_node;
        current_in_ifs.pop_back();
    }
}

void RecognizeCtrlGroup::add_group_members(const weak_ptr<UniSuccessorNode>& uni_node)
{
    for (auto& loop_begin : this->current_in_loops) {
        loop_tail_body[loop_begin].second.insert(uni_node);
    }

    for (auto& if_node : this->current_in_ifs) {
        if_tail_body[if_node].second.insert(uni_node);
    }
}

void RecognizeCtrlGroup::handler(const weak_ptr<FixedNode>& current_node)
{
    if (auto uni_current = dynamic_pointer_cast<UniSuccessorNode>(current_node.lock())) {
        assert(uni_current->next()->predecessor.lock() == uni_current);
    }

    if (auto loop_begin = dynamic_pointer_cast<LoopBegin>(current_node.lock())) {
        set<weak_ptr<UniSuccessorNode>,
            std::owner_less<>> inner_uni_nodes;
        auto group_nodes = make_pair(this->fake_loop_tail, inner_uni_nodes);

        loop_tail_body.insert({loop_begin, group_nodes});
        current_in_loops.push_back(loop_begin);
    }
    else if (const auto loop_exit = dynamic_pointer_cast<LoopExit>(current_node.lock())) {
        /// Step A.
        this->set_loop_tail(loop_exit);

        /// The tail node of a group is the last member
        /// Step B.
        /// Performing A before B prevents the tail node from being added to its corresponding head's body set.
        this->add_group_members(loop_exit);
    }
    else if (auto if_node = dynamic_pointer_cast<IfNode>(current_node.lock())) {
        if (dynamic_pointer_cast<LoopIf>(if_node)) {
            return;
        }

        set<weak_ptr<UniSuccessorNode>,
            std::owner_less<>> inner_uni_nodes;

        auto group_nodes = make_pair(this->fake_if_tail, inner_uni_nodes);

        if_tail_body.insert({if_node, group_nodes});
        current_in_ifs.push_back(if_node);
    }
    else if (const auto merge_node = dynamic_pointer_cast<MergeNode>(current_node.lock())) {
        /// MergeNode can merge the two EndNodes of an IfNode, and may also interact with a TryNode in some cases.
        if (merge_node->merge_type == MergeType::If) {
            /// Step A
            this->set_if_tail(merge_node);
        }

        /// Step B
        /// The tail node also needs to be added to the inner nodes set.
        /// It is meaningless to move the group after its tail.
        this->add_group_members(merge_node);
    }
    else if (auto _node = dynamic_pointer_cast<CtrlRelayNode>(current_node.lock())) {
        /// Step A
        this->set_if_tail(_node);

        /// Step B
        this->add_group_members(_node);
    }
    else if (auto _node = dynamic_pointer_cast<UniSuccessorNode>(current_node.lock())) {
        /// LoopBegin can not be used as the insertion point ,
        /// but that case is already handled in the preceding if-branch and won't reach here.
        this->add_group_members(_node);
    }
}

} /// end of namespace