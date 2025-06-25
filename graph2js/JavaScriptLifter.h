#ifndef FUZZFLOW_JAVASCRIPTLIFTER_H
#define FUZZFLOW_JAVASCRIPTLIFTER_H

#include "../utils/common_using.h"

#include "ScriptWriter.h"

#include "../js2graph/Graph.h"

#include "RegionSingle.h"
#include "RegionNested.h"
#include "RegionTry.h"

#include "../exceptions/LiftError.h"
#include "../utils/assert_or_throw.h"

#include "../visitors/GraphVisitor.h"

namespace FuzzFlow {

enum class InEdgeType {
    Ctrl,
    Data
};

class JavaScriptLifter final : public GraphVisitor {
public: // interface
    ///
    /// Code of each graph is managed by a top-level region (Regions are hierarchical).
    ///
    /// IfNodeRegion and LoopBeginRegion are complex units, which may contain nested regions.
    /// RegionSingle is a simple unit that only contains code strings.
    ///
    /// A region does not directly correspond to an AbstractBeginNode.
    /// A region is generated when an AbstractBeginNode starts, and also when the next AbstractBeginNode begins, after the current one ends.
    ///
    /// When is a new Region created?
    /// 1. When encountering nodes like IfNode or LoopBegin.
    /// 2. When ending a previous IfNode or LoopBegin node, and the next control flow node generates code that doesn't fall into the above categories, a new RegionSingle is created.
    /// 3. Data flow nodes may also require the creation of RegionSingle.
    ///
    /// When converting Regions to JS code, perform code generation in depth-first order.
    ///
    shared_ptr<RegionNested> top_region;

    string function_name;
    vector<string> function_args;

    /// JavaScriptLifter won't change Graph object
    explicit JavaScriptLifter(const shared_ptr<const Graph> &graph)
    {
        this->graph = graph;

        build_node2varProxy(graph->varProxy2node);

        /// create top region
        this->top_region = make_shared<RegionNested>();
        this->current_parent_region = this->top_region;
    }

    /// The entry of the lifting process.
    /// The return value is the number of nodes that have been lifted.
    uint32_t lift();

    string visit_outcome;

private: // implementation

    shared_ptr<const Graph> graph;

    uint32_t visited_nodes_num = 0;

    map<weak_ptr<DataProducerNode>,
        vector<shared_ptr<VarProxy>>,
            std::owner_less<>> node2varProxy;

    shared_ptr<RegionNested> current_parent_region;

    /// When processing FinallyExit nodes, the region needs to be reset
    vector<pair<weak_ptr<TryNode>,
                shared_ptr<RegionNested>>> try2parentRegions;

    /// Generate statements here whenever needed.
    shared_ptr<RegionSingle> current_region_single;

    /// Avoid duplicate var proxy assignments to visited nodes.
    set<weak_ptr<IRNode>,
        std::owner_less<>> visited_nodes;

    /// Some fixed nodes are also data producers - revisiting them through Input edges may create cycles if we follow next edges.
    set<weak_ptr<FixedNode>,
        std::owner_less<>> visited_fixed;

    InEdgeType in_edge_type = InEdgeType::Ctrl;
    stack<InEdgeType> in_edge_stack;

    void walk_along_uniSuccessor(const shared_ptr<UniSuccessorNode> &node);

    /// The regions where a var symbol is used determine that its declaration should be placed
    /// in the most mini common parent region of those regions.
    unordered_map<shared_ptr<VarSymbol>,
                  set<weak_ptr<Region>, std::owner_less<>>> varSymbol2Regions;

    /// Variable proxies assigned within each RegionNested.
    /// Used to determine whether to regenerate the assignment for a floating node when revisited,
    /// based on its attached var proxy.
    ///
    /// A `vector` is used instead of a `set` to store var proxies for a region
    /// because the insertion order (under the same region key)
    /// reflects the order of assignment statements in the original JS source code.
    /// This ordering is important and would be lost with a `set`.
    ///
    /// Additionally, duplicates in the vector represent successive assignments
    /// to the same var proxy, where later assignments override earlier ones (flow semantics).
    map<weak_ptr<const RegionNested>,
        vector<shared_ptr<VarProxy>>,
            std::owner_less<>> region2varProxies;

    /// Whether we should emit the behavioral fixed nodes to expressions
    bool emit_fixed_to_expr = false;

    shared_ptr<CtrlRelayNode> last_relay_node;

    void set_relay_node(const shared_ptr<CtrlRelayNode> &relay_node)
    {
        this->last_relay_node = relay_node;
    }

    shared_ptr<CtrlRelayNode> get_relay_node()
    {
        auto relay_node = this->last_relay_node;
        this->last_relay_node.reset();
        return relay_node;
    }

    shared_ptr<AbstractMergeNode> last_merge_node;

    void set_merge_node(const shared_ptr<AbstractMergeNode> &merge)
    {
        this->last_merge_node = merge;
    }

    shared_ptr<AbstractMergeNode> get_merge_node()
    {
        auto merge_node = this->last_merge_node;
        this->last_merge_node.reset();
        return merge_node;
    }

    void build_node2varProxy(const map<shared_ptr<VarProxy>,
                                       weak_ptr<DataProducerNode>>& varProxy2node);

    vector<shared_ptr<VarSymbol>> get_varSymbols_on_producer(const weak_ptr<DataProducerNode>& producer);

    vector<shared_ptr<VarProxy>> get_varProxies_on_producer(const weak_ptr<DataProducerNode>& producer);

    shared_ptr<VarSymbol> get_phi_main_proxy(const weak_ptr<PhiNode>& phi_node_w);

    void check_region_single();

    bool varProxy_reach_current_region(const shared_ptr<VarProxy> &var_proxy);

    bool all_varProxy_available(const weak_ptr<DataProducerNode>& node);

    void gen_assignment_for_producer(const weak_ptr<DataProducerNode> &producer,
                                     const string &assign_expr,
                                     const bool self_assignment);

    void update_varSymbol2Regions(vector<shared_ptr<VarSymbol>>& var_syms);

    void update_region2varProxies(const weak_ptr<DataProducerNode>& node);

    void gen_assignment_for_FloatingNode(weak_ptr<DataProducerNode> producer,
                                         string assign_expr);

    static string get_invoke_expr(const string& function_name,
                                  const vector<string> &arg_names,
                                  bool new_constructor);

    bool single_step = false;

    void visit(const shared_ptr<DataProducerNode> &node);

    void visit(shared_ptr<LoopBegin> &node)             override;

    void visit(shared_ptr<IfNode> &node)                override;

    void visit(shared_ptr<BeginNode> &node)             override;

    void visit(shared_ptr<LoopEnd> &node)               override;

    void visit(shared_ptr<EndNode> &node)               override;

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

    void visit(shared_ptr<ThisNode> &node)              override;

    void visit(shared_ptr<ArrayLiteralNode> &node)      override;

    void visit(shared_ptr<ForInPropName> &node)         override;

    void visit(shared_ptr<ParameterNode> &node)         override;

};

} /// end of namespace

#endif //FUZZFLOW_JAVASCRIPTLIFTER_H
