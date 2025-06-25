#include "WalkCopyGraph.h"

namespace FuzzFlow {

void WalkCopyGraph::copy()
{
    this->_graph_head->accept(*this);
}

bool WalkCopyGraph::check_duplicate(const shared_ptr<IRNode>& node)
{
    /// The node may has been cloned in other flow
    if (origNode2newNode.contains(node)) {
        return true;
    }

    auto new_node = node->clone();

    /// add to graph
    new_graph->nodes.push_back(new_node);

    origNode2newNode.insert_or_assign(node, new_node);

    return false;
}

void WalkCopyGraph::walk_successor(const shared_ptr<UniSuccessorNode>& node)
{
    node->successor.lock()->accept(*this);
}

void WalkCopyGraph::walk_consumer(const shared_ptr<DataConsumerNode>& node)
{
    for (auto &_input : node->inputs) {
        _input.lock()->accept(*this);
    }
}

void WalkCopyGraph::visit(shared_ptr<BeginNode> &node)
{
    if (check_duplicate(node)) {
        return;
    }

    walk_successor(node);
}

void WalkCopyGraph::visit(shared_ptr<BinaryOpNode> &node)
{
    if (check_duplicate(node)) {
        return;
    }

    walk_consumer(node);

    walk_successor(node);
}

void WalkCopyGraph::visit(shared_ptr<AbstractMergeNode> node)
{
    if (check_duplicate(node)) {
        return;
    }

    for (auto &[idx, phi_node]: node->idx2phis) {
        phi_node.lock()->accept(*this);
    }

    /// copy next
    node->successor.lock()->accept(*this);
}

void WalkCopyGraph::visit(shared_ptr<CtrlRelayNode> &node)
{
    this->visit(dynamic_pointer_cast<AbstractMergeNode>(node));
}

void WalkCopyGraph::visit(shared_ptr<EndMayMergeNode> node)
{
    if (check_duplicate(node)) {
        return;
    }

    if (! node->merge_node.expired()) {
        node->merge_node.lock()->accept(*this);
    }
}

void WalkCopyGraph::visit(shared_ptr<EndNode> &node)
{
    this->visit(dynamic_pointer_cast<EndMayMergeNode>(node));
}

void WalkCopyGraph::visit(shared_ptr<EndProgramNode> &node)
{
    if (check_duplicate(node)) {
        return;
    }
}

void WalkCopyGraph::visit(shared_ptr<FunctionHeadNode> &node)
{
    if (check_duplicate(node)) {
        return;
    }

    walk_consumer(node);

    walk_successor(node);
}

void WalkCopyGraph::visit(shared_ptr<GlobalFunctionNode> &node)
{
    if (check_duplicate(node)) {
        return;
    }
}

void WalkCopyGraph::visit(shared_ptr<GlobalVarNode> &node)
{
    if (check_duplicate(node)) {
        return;
    }
}

void WalkCopyGraph::visit(shared_ptr<IfNode> &node)
{
    if (check_duplicate(node)) {
        return;
    }

    walk_consumer(node);

    /// copy branch true
    node->branch_true()->accept(*this);

    /// copy branch false
    node->branch_false()->accept(*this);
}

void WalkCopyGraph::visit(shared_ptr<InvokeMethodNode> &node)
{
    if (check_duplicate(node)) {
        return;
    }

    walk_consumer(node);

    walk_successor(node);
}

void WalkCopyGraph::visit(shared_ptr<InvokeNode> &node)
{
    if (check_duplicate(node)) {
        return;
    }

    walk_consumer(node);

    walk_successor(node);
}

void WalkCopyGraph::visit(shared_ptr<LiteralBoolNode> &node)
{
    if (check_duplicate(node)) {
        return;
    }
}

void WalkCopyGraph::visit(shared_ptr<LiteralFloatNode> &node)
{
    if (check_duplicate(node)) {
        return;
    }
}

void WalkCopyGraph::visit(shared_ptr<LiteralStringNode> &node)
{
    if (check_duplicate(node)) {
        return;
    }
}

void WalkCopyGraph::visit(shared_ptr<LoopBegin> &node)
{
    this->visit(dynamic_pointer_cast<AbstractMergeNode>(node));
}

void WalkCopyGraph::visit(shared_ptr<LoopEnd> &node)
{
    this->visit(dynamic_pointer_cast<EndMayMergeNode>(node));
}

void WalkCopyGraph::visit(shared_ptr<LoopExit> &node)
{
    if (check_duplicate(node)) {
        return;
    }

    walk_successor(node);
}

void WalkCopyGraph::visit(shared_ptr<LoopIf> &node)
{
    if (check_duplicate(node)) {
        return;
    }

    walk_consumer(node);

    /// copy branch true
    node->branch_true()->accept(*this);

    /// copy branch false
    node->branch_false()->accept(*this);
}

void WalkCopyGraph::visit(shared_ptr<MergeNode> &node)
{
    this->visit(dynamic_pointer_cast<AbstractMergeNode>(node));
}

void WalkCopyGraph::visit(shared_ptr<ParameterNode> &node)
{
    if (check_duplicate(node)) {
        return;
    }
}

void WalkCopyGraph::visit(shared_ptr<PhiNode> &node)
{
    if (check_duplicate(node)) {
        return;
    }

    walk_consumer(node);
}

void WalkCopyGraph::visit(shared_ptr<ReturnNode> &node)
{
    if (check_duplicate(node)) {
        return;
    }

    walk_consumer(node);
}

void WalkCopyGraph::visit(shared_ptr<TernaryOpNode> &node)
{
    if (check_duplicate(node)) {
        return;
    }

    walk_consumer(node);
}

void WalkCopyGraph::visit(shared_ptr<UnaryOpNode> &node)
{
    if (check_duplicate(node)) {
        return;
    }

    walk_consumer(node);

    walk_successor(node);
}

void WalkCopyGraph::visit(shared_ptr<ArrayLiteralNode> &node)
{
    if (check_duplicate(node)) {
        return;
    }

    walk_consumer(node);
}

void WalkCopyGraph::visit(shared_ptr<BuiltinNode> &node)
{
    if (check_duplicate(node)) {
        return;
    }
}

void WalkCopyGraph::visit(shared_ptr<CatchIdNode> &node)
{
    if (check_duplicate(node)) {
        return;
    }
}

void WalkCopyGraph::visit(shared_ptr<CatchNode> &node)
{
    if (check_duplicate(node)) {
        return;
    }

    /// copy catch id
    if (node->opt_catch_id_node.has_value()) {
        node->opt_catch_id_node.value().lock()->accept(*this);
    }

    walk_successor(node);
}

void WalkCopyGraph::visit(shared_ptr<ComputedPropExprAssignNode> &node)
{
    if (check_duplicate(node)) {
        return;
    }

    walk_consumer(node);
}

void WalkCopyGraph::visit(shared_ptr<DeleteNode> &node)
{
    if (check_duplicate(node)) {
        return;
    }

    walk_consumer(node);

    walk_successor(node);
}

void WalkCopyGraph::visit(shared_ptr<FinallyNode> &node)
{
    if (check_duplicate(node)) {
        return;
    }

    walk_successor(node);
}

void WalkCopyGraph::visit(shared_ptr<ForInEnum> &node)
{
    if (check_duplicate(node)) {
        return;
    }

    walk_consumer(node);

    node->branch_true()->accept(*this);

    node->branch_false()->accept(*this);
}

void WalkCopyGraph::visit(shared_ptr<ForInPropName> &node)
{
    if (check_duplicate(node)) {
        return;
    }
}

void WalkCopyGraph::visit(shared_ptr<FunctionPropertyNode> &node)
{
    if (check_duplicate(node)) {
        return;
    }

    walk_consumer(node);
}

void WalkCopyGraph::visit(shared_ptr<LoadNode> &node)
{
    if (check_duplicate(node)) {
        return;
    }

    walk_consumer(node);

    walk_successor(node);
}

void WalkCopyGraph::visit(shared_ptr<ObjectLiteralNode> &node)
{
    if (check_duplicate(node)) {
        return;
    }

    walk_consumer(node);
}

void WalkCopyGraph::visit(shared_ptr<PropExprAssignNode> &node)
{
    if (check_duplicate(node)) {
        return;
    }

    walk_consumer(node);
}

void WalkCopyGraph::visit(shared_ptr<StoreNode> &node)
{
    if (check_duplicate(node)) {
        return;
    }

    walk_consumer(node);

    walk_successor(node);
}

void WalkCopyGraph::visit(shared_ptr<ThisNode> &node)
{
    if (check_duplicate(node)) {
        return;
    }
}

void WalkCopyGraph::visit(shared_ptr<TryExit> &node)
{
    if (check_duplicate(node)) {
        return;
    }

    walk_successor(node);
}

void WalkCopyGraph::visit(shared_ptr<TryNode> &node)
{
    if (check_duplicate(node)) {
        return;
    }

    walk_successor(node);

    if (! node->catch_node.expired()) {
        node->catch_node.lock()->accept(*this);
    }

    if (! node->finally_node.expired()) {
        node->finally_node.lock()->accept(*this);
    }
}

void WalkCopyGraph::visit(shared_ptr<UnwindNode> &node)
{
    if (check_duplicate(node)) {
        return;
    }

    walk_consumer(node);
}

} /// end of namespace