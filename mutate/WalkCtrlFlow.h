#ifndef FUZZFLOW_WALKCTRLFLOW_H
#define FUZZFLOW_WALKCTRLFLOW_H

#include "../nodes/AllNodesInclude.h"

#include "../visitors/GraphVisitor.h"

namespace FuzzFlow {
///
/// Traverses the control flow nodes of a graph starting from FunctionHeadNode.
///
/// The graph is traversed along control flow edges. For each visited node,
/// the handler function is invoked to perform specific operations.
///
/// In this base class, the handler simply prints the current node.
/// Derived classes should override the handler to implement custom node processing
/// or recording logic.
///
class WalkCtrlFlow : public GraphVisitor {
public:
    shared_ptr<FixedNode> _walk_start;

    shared_ptr<AbstractMergeNode> _last_merge_node;

    explicit WalkCtrlFlow(const shared_ptr<FixedNode> &walk_start)
    {
        _walk_start = walk_start;
    }

    ~WalkCtrlFlow() override;

    void walk();

    virtual void handler(const weak_ptr<FixedNode> &current_node) {}

    void visit(shared_ptr<FixedNode> &node) override;
    void visit(shared_ptr<UniSuccessorNode> &node) override;

    void visit(shared_ptr<FunctionHeadNode> &node) override;

    void visit(shared_ptr<IfNode> &node) override;
    void visit(shared_ptr<BeginNode> &node) override;
    void visit(shared_ptr<MergeNode> &node) override;

    void visit(shared_ptr<LoopBegin> &node) override;
    void visit(shared_ptr<LoopIf> &node) override;
    void visit(shared_ptr<LoopExit> &node) override;

    void visit(shared_ptr<TryNode> &node) override;
    void visit(shared_ptr<TryExit> &node) override;

    void visit(shared_ptr<CatchNode> &node) override;
    void visit(shared_ptr<FinallyNode> &node) override;

    void visit(shared_ptr<CtrlRelayNode> &node) override;

    void visit(shared_ptr<StoreNode> &node) override;
    void visit(shared_ptr<LoadNode> &node) override;
    void visit(shared_ptr<InvokeNode> &node) override;
    void visit(shared_ptr<InvokeMethodNode> &node) override;

    void visit(shared_ptr<DeleteNode> &node) override;
    void visit(shared_ptr<BinaryOpNode> &node) override;
    void visit(shared_ptr<UnaryOpNode> &node) override;

    void visit(shared_ptr<ReturnNode> &node) override;
    void visit(shared_ptr<LoopEnd> &node) override;
    void visit(shared_ptr<EndNode> &node) override;
    void visit(shared_ptr<UnwindNode> &node) override;
    void visit(shared_ptr<EndProgramNode> &node) override;

    void set_merge_node(const shared_ptr<AbstractMergeNode> &merge)
    {
        this->_last_merge_node = merge;
    }

    void reset_merge_node()
    {
        this->_last_merge_node.reset();
    }

    [[nodiscard]] shared_ptr<AbstractMergeNode> get_merge_node() const
    {
        auto merge_node = this->_last_merge_node;
        return merge_node;
    }
};

} /// end of namespace

#endif //FUZZFLOW_WALKCTRLFLOW_H
