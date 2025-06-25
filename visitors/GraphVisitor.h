#ifndef FUZZFLOW_GRAPHVISITOR_H
#define FUZZFLOW_GRAPHVISITOR_H

#include "../nodes/AllNodesDeclare.h"

namespace FuzzFlow {

class GraphVisitor {
public:
    virtual ~GraphVisitor() = default;

    /// Fixed node

    virtual void visit(shared_ptr<IRNode> &node) {}

    virtual void visit(shared_ptr<FixedNode> &node) {}

    virtual void visit(shared_ptr<UniSuccessorNode> &node) {}

    virtual void visit(shared_ptr<FunctionHeadNode> &node) {}

    virtual void visit(shared_ptr<BeginNode> &node) {}

    virtual void visit(shared_ptr<LoopIf> &node) {}

    virtual void visit(shared_ptr<LoopBegin> &node) {}

    virtual void visit(shared_ptr<IfNode> &node) {}

    virtual void visit(shared_ptr<MergeNode> &node) {}

    virtual void visit(shared_ptr<InvokeNode> &node) {}

    virtual void visit(shared_ptr<InvokeMethodNode> &node) {}

    virtual void visit(shared_ptr<StoreNode> &node) {}

    virtual void visit(shared_ptr<LoadNode> &node) {}

    virtual void visit(shared_ptr<TryNode> &node) {}

    virtual void visit(shared_ptr<CatchNode> &node) {}

    virtual void visit(shared_ptr<FinallyNode> &node) {}

    virtual void visit(shared_ptr<TryExit> &node) {}

    virtual void visit(shared_ptr<DeleteNode> &node) {}

    virtual void visit(shared_ptr<ForInEnum> &node) {}

    virtual void visit(shared_ptr<LoopExit> &node) {}

    virtual void visit(shared_ptr<CtrlRelayNode> &node) {}

    virtual void visit(shared_ptr<BinaryOpNode> &node) {}

    virtual void visit(shared_ptr<UnaryOpNode> &node) {}

    /// EndWontMergeNode

    virtual void visit(shared_ptr<ReturnNode> &node) {}

    virtual void visit(shared_ptr<UnwindNode> &node) {}

    virtual void visit(shared_ptr<EndProgramNode> &node) {}

    /// EndMayMergeNode

    virtual void visit(shared_ptr<EndMayMergeNode> &node) {}

    virtual void visit(shared_ptr<EndNode> &node) {}

    virtual void visit(shared_ptr<LoopEnd> &node) {}

    ///  Data producer

    virtual void visit(shared_ptr<TerminalNode> &node) {}

    virtual void visit(shared_ptr<PhiNode> &node) {}

    virtual void visit(shared_ptr<TernaryOpNode> &node) {}

    virtual void visit(shared_ptr<PropExprAssignNode> &node) {}

    virtual void visit(shared_ptr<ObjectLiteralNode> &node) {}

    virtual void visit(shared_ptr<BuiltinNode> &node) {}

    virtual void visit(shared_ptr<ThisNode> &node) {}

    virtual void visit(shared_ptr<ArrayLiteralNode> &node) {}

    virtual void visit(shared_ptr<ForInPropName> &node) {}

    virtual void visit(shared_ptr<GlobalVarNode> &node) {}

    virtual void visit(shared_ptr<GlobalFunctionNode> &node) {}

    virtual void visit(shared_ptr<LiteralBoolNode> &node) {}

    virtual void visit(shared_ptr<LiteralFloatNode> &node) {}

    virtual void visit(shared_ptr<LiteralStringNode> &node) {}

    virtual void visit(shared_ptr<ParameterNode> &node) {}

    virtual void visit(shared_ptr<CatchIdNode> &node) {}

    virtual void visit(shared_ptr<ComputedPropExprAssignNode> &node) {}

    virtual void visit(shared_ptr<FunctionPropertyNode> &node) {}
};

} /// end of namespace

#endif //FUZZFLOW_GRAPHVISITOR_H
