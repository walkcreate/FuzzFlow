#ifndef FUZZFLOW_RECOGNIZECTRLGROUP_H
#define FUZZFLOW_RECOGNIZECTRLGROUP_H

#include "../nodes/FixedNode.h"
#include "../nodes/LoopBegin.h"
#include "../nodes/IfNode.h"

#include "./WalkCtrlFlow.h"

namespace FuzzFlow {

///
/// Identifies control node group boundaries and internal nodes.
///
/// The head node of a control node group is well-defined.
/// This class extracts the group's tail node (end boundary)
/// and records internal uni successor nodes (potential move targets).
///
class RecognizeCtrlGroup final : public WalkCtrlFlow {
public:
    explicit RecognizeCtrlGroup(const shared_ptr<FixedNode> &walk_start)
        : WalkCtrlFlow(walk_start)
    {}

    void handler(const weak_ptr<FixedNode> &current_node) override;

    void add_group_members(const weak_ptr<UniSuccessorNode>& uni_node);

    void set_if_tail(const weak_ptr<AbstractMergeNode> &uni_node);

    void set_loop_tail(const weak_ptr<LoopExit> &uni_node);

    /// tail node for placeholder
    shared_ptr<LoopExit> fake_loop_tail;
    shared_ptr<AbstractMergeNode> fake_if_tail;

    ///
    /// The head node of Loop group is the EndNode before LoopBegin. We can not move
    /// The tail node of Loop group is LoopExit.
    /// The inner nodes can be used as predecessors of moving target.
    ///
    /// Due to nested loops, we may encounter a deeper-level LoopBegin before reaching LoopExit.
    /// Each LoopExit always pairs with the last(most recent) LoopBegin encountered.
    ///
    map<weak_ptr<LoopBegin>,
        pair<weak_ptr<LoopExit>,                /// tail node
             set<weak_ptr<UniSuccessorNode>,
                 std::owner_less<>>>,           /// inner nodes before head and tail
             std::owner_less<>> loop_tail_body;

    /// The head node of If group is IfNode itself.
    /// The tail node of If group can be MergeNode or CtrlRelayNode.
    map<weak_ptr<IfNode>,
        pair<weak_ptr<AbstractMergeNode>,       /// tail node
             set<weak_ptr<UniSuccessorNode>,
                 std::owner_less<>>>,
             std::owner_less<>> if_tail_body;

    map<weak_ptr<TryNode>,
        pair<weak_ptr<UniSuccessorNode>,        /// tail node
             set<weak_ptr<UniSuccessorNode>,
                 std::owner_less<>>>,
             std::owner_less<>> try2innerUniNodes;

    /// To handle nesting, stores the currently traversed node groups.
    /// Uses a vector instead of a stack because:
    /// - Stacks do not support random access or iteration.
    /// - Order reflects nesting: later elements are inside earlier ones.
    ///
    vector<weak_ptr<LoopBegin>> current_in_loops;
    vector<weak_ptr<IfNode>> current_in_ifs;

};

} /// end of namespace

#endif //FUZZFLOW_RECOGNIZECTRLGROUP_H
