#include "WalkCtrlFlow.h"

namespace FuzzFlow {

WalkCtrlFlow::~WalkCtrlFlow() {}

void WalkCtrlFlow::walk()
{
    this->_walk_start->accept(*this);
}

void WalkCtrlFlow::visit(shared_ptr<FunctionHeadNode> &node)
{
    handler(node);
    node->next()->accept(*this);
}

void WalkCtrlFlow::visit(shared_ptr<FixedNode> &node)
{
    handler(node);
}

void WalkCtrlFlow::visit(shared_ptr<UniSuccessorNode> &node)
{
    handler(node);
    node->next()->accept(*this);
}

void WalkCtrlFlow::visit(shared_ptr<MergeNode> &node)
{
    handler(node);
    node->next()->accept(*this);
}

void WalkCtrlFlow::visit(shared_ptr<EndNode> &node)
{
    handler(node);

    if (! node->merge_node.expired()) {
        const auto _end_merge = node->merge_node.lock();

        if (auto _node1 = dynamic_pointer_cast<MergeNode>(_end_merge)) {
            set_merge_node(_node1);
        }
        else if (auto _node2 = dynamic_pointer_cast<LoopBegin>(_end_merge)) {
            _node2->accept(*this);
        }
        else if (auto _node3 = dynamic_pointer_cast<CtrlRelayNode>(_end_merge)) {
            _node3->accept(*this); /// todo set_merge_node(_node3);
        }
    }
}

void WalkCtrlFlow::visit(shared_ptr<LoopIf> &node)
{
    handler(node);

    /// true brance
    node->branch_true()->accept(*this);

    /// false branch
    node->branch_false()->accept(*this);
}

void WalkCtrlFlow::visit(shared_ptr<IfNode> &node)
{
    handler(node);

    /// true brance
    node->branch_true()->accept(*this);

    /// may be null
    const auto true_merge_node = get_merge_node();
    this->reset_merge_node();

    /// false branch
    node->branch_false()->accept(*this);

    const auto false_merge_node = get_merge_node();
    this->reset_merge_node();

    if ((true_merge_node != nullptr) && (false_merge_node != nullptr)) {
        ASSERT_OR_EXIT(true_merge_node == false_merge_node);
    }

    if (true_merge_node != nullptr) {
        true_merge_node->accept(*this);
    }
    else if (false_merge_node != nullptr) {
        false_merge_node->accept(*this);
    }
}

void WalkCtrlFlow::visit(shared_ptr<LoopBegin> &node)
{
    handler(node);
    node->next()->accept(*this);
}

void WalkCtrlFlow::visit(shared_ptr<BeginNode> &node)
{
    handler(node);
    node->next()->accept(*this);
}

void WalkCtrlFlow::visit(shared_ptr<CatchNode> &node)
{
    handler(node);
    node->next()->accept(*this);
}

void WalkCtrlFlow::visit(shared_ptr<FinallyNode> &node)
{
    handler(node);
    node->next()->accept(*this);
}

void WalkCtrlFlow::visit(shared_ptr<TryNode> &node)
{
    handler(node);

    /// try body
    node->next()->accept(*this);

    auto try_merge = this->get_merge_node();
    this->reset_merge_node();

    /// catch block
    if (! node->catch_node.expired()) {
        node->catch_node.lock()->accept(*this);
    }

    auto catch_merge = this->get_merge_node();
    this->reset_merge_node();

    /// finally block
    if (! node->finally_node.expired()) {
        node->finally_node.lock()->accept(*this);
    }
    else {
        /// try and catch may end with EndNode and then be merged.
        ///
        if ((try_merge != nullptr) && (catch_merge != nullptr)) {
            ASSERT_OR_EXIT(try_merge == catch_merge);
        }

        if (try_merge != nullptr) {
            try_merge->accept(*this);
        }
        else if (catch_merge != nullptr) {
            catch_merge->accept(*this);
        }
    }
}

void WalkCtrlFlow::visit(shared_ptr<DeleteNode> &node)
{
    handler(node);
    node->next()->accept(*this);
}

void WalkCtrlFlow::visit(shared_ptr<TryExit> &node)
{
    handler(node);
    node->next()->accept(*this);
}

void WalkCtrlFlow::visit(shared_ptr<StoreNode> &node)
{
    handler(node);
    node->next()->accept(*this);
}

void WalkCtrlFlow::visit(shared_ptr<LoadNode> &node)
{
    handler(node);
    node->next()->accept(*this);
}

void WalkCtrlFlow::visit(shared_ptr<BinaryOpNode> &node)
{
    handler(node);
    node->next()->accept(*this);
}

void WalkCtrlFlow::visit(shared_ptr<UnaryOpNode> &node)
{
    handler(node);
    node->next()->accept(*this);
}

void WalkCtrlFlow::visit(shared_ptr<LoopExit> &node)
{
    handler(node);
    node->next()->accept(*this);
}

void WalkCtrlFlow::visit(shared_ptr<InvokeNode> &node)
{
    handler(node);
    node->next()->accept(*this);
}

void WalkCtrlFlow::visit(shared_ptr<InvokeMethodNode> &node)
{
    handler(node);
    node->next()->accept(*this);
}

void WalkCtrlFlow::visit(shared_ptr<CtrlRelayNode> &node)
{
    handler(node);
    node->next()->accept(*this);
}

void WalkCtrlFlow::visit(shared_ptr<ReturnNode> &node)
{
    handler(node);
}

void WalkCtrlFlow::visit(shared_ptr<LoopEnd> &node)
{
    handler(node);
}

void WalkCtrlFlow::visit(shared_ptr<UnwindNode> &node)
{
    handler(node);
}

void WalkCtrlFlow::visit(shared_ptr<EndProgramNode> &node)
{
    handler(node);
}

} /// end of namespace