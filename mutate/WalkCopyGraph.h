#ifndef FUZZFLOW_WALKCOPYGRAPH_H
#define FUZZFLOW_WALKCOPYGRAPH_H

#include "../nodes/AllNodesInclude.h"

#include "../visitors/GraphVisitor.h"

namespace FuzzFlow {

class WalkCopyGraph final : public GraphVisitor {
public:
    shared_ptr<FunctionHeadNode> _graph_head;

    explicit WalkCopyGraph(shared_ptr<FunctionHeadNode> &graph_head)
    {
        _graph_head = graph_head;

        new_graph = make_shared<Graph>();
    }

    shared_ptr<Graph> new_graph;

    map<weak_ptr<IRNode>,
        weak_ptr<IRNode>,
        std::owner_less<>> origNode2newNode;

    void copy();

    bool check_duplicate(const shared_ptr<IRNode>& node);

    void walk_successor(const shared_ptr<UniSuccessorNode>& node);

    void walk_consumer(const shared_ptr<DataConsumerNode>& node);

    void visit(const shared_ptr<DataProducerNode> &node);

    void visit(shared_ptr<AbstractMergeNode> node);

    void visit(shared_ptr<EndMayMergeNode> node);

    void visit(shared_ptr<CtrlRelayNode> &node)         override;

    void visit(shared_ptr<FunctionHeadNode> &node)      override;

    void visit(shared_ptr<LoopBegin> &node)             override;

    void visit(shared_ptr<IfNode> &node)                override;

    void visit(shared_ptr<BeginNode> &node)             override;

    void visit(shared_ptr<LoopEnd> &node)               override;

    void visit(shared_ptr<LoopExit> &node)              override;

    void visit(shared_ptr<LoopIf> &node)                override;

    void visit(shared_ptr<MergeNode> &node)             override;

    void visit(shared_ptr<EndNode> &node)               override;

    void visit(shared_ptr<EndProgramNode> &node)        override;

    void visit(shared_ptr<InvokeNode> &node)            override;

    void visit(shared_ptr<InvokeMethodNode> &node)      override;

    void visit(shared_ptr<ReturnNode> &node)            override;

    void visit(shared_ptr<StoreNode> &node)             override;

    void visit(shared_ptr<LoadNode> &node)              override;

    void visit(shared_ptr<TryNode> &node)               override;

    void visit(shared_ptr<UnwindNode> &node)            override;

    void visit(shared_ptr<TryExit> &node)               override;

    void visit(shared_ptr<DeleteNode> &node)            override;

    void visit(shared_ptr<ForInEnum> &node)             override;

    void visit(shared_ptr<LiteralBoolNode> &node)       override;

    void visit(shared_ptr<LiteralFloatNode> &node)      override;

    void visit(shared_ptr<LiteralStringNode> &node)     override;

    void visit(shared_ptr<CatchIdNode> &node)           override;

    void visit(shared_ptr<GlobalVarNode> &node)         override;

    void visit(shared_ptr<GlobalFunctionNode> &node)    override;

    void visit(shared_ptr<PhiNode> &node)               override;

    void visit(shared_ptr<BinaryOpNode> &node)          override;

    void visit(shared_ptr<UnaryOpNode> &node)           override;

    void visit(shared_ptr<TernaryOpNode> &node)         override;

    void visit(shared_ptr<PropExprAssignNode> &node)    override;

    void visit(shared_ptr<FunctionPropertyNode> &node)  override;

    void visit(shared_ptr<ObjectLiteralNode> &node)     override;

    void visit(shared_ptr<BuiltinNode> &node)           override;

    void visit(shared_ptr<CatchNode> &node)             override;

    void visit(shared_ptr<ComputedPropExprAssignNode> &node) override;

    void visit(shared_ptr<FinallyNode> &node)           override;

    void visit(shared_ptr<ThisNode> &node)              override;

    void visit(shared_ptr<ArrayLiteralNode> &node)      override;

    void visit(shared_ptr<ForInPropName> &node)         override;

    void visit(shared_ptr<ParameterNode> &node)         override;
};

} // end of namespace

#endif //FUZZFLOW_WALKCOPYGRAPH_H
