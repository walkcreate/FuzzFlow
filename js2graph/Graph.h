#ifndef FUZZFLOW_GRAPH_H
#define FUZZFLOW_GRAPH_H

#include "../utils/common_using.h"

#include "../semantic/FunctionSymbol.h"
#include "../semantic/VarSymbol.h"
#include "../js2graph/VarProxy.h"
#include "../nodes/IRNode.h"
#include "../nodes/DataProducerNode.h"
#include "../nodes/ParameterNode.h"

#include "antlr4-runtime.h"

namespace FuzzFlow {

using antlr4::ParserRuleContext;

///
/// Every procedural matches a graph
/// The main script matches __main__ function
///
class Graph : public enable_shared_from_this<Graph> {
private:
    /// The index of the next node to be generated
    unsigned int next_index = 1;

public:
    Graph() = default;

    /// tree structure
    vector<weak_ptr<Graph>> child_graphs;
    weak_ptr<Graph> parent_graph;

    void set_outer_graph(const weak_ptr<Graph>& outer)
    {
        outer.lock()->child_graphs.push_back(weak_from_this());
        this->parent_graph = outer;
    }

    Graph(const vector<shared_ptr<IRNode>> &_nodes,
          const map<shared_ptr<VarProxy>,
                    weak_ptr<DataProducerNode>> &_varProxy2node)
    {
        this->nodes = _nodes;
        this->varProxy2node = _varProxy2node;
    }

    /// The list of all nodes in a graph.
    /// Nodes are created in IRGenerator as shared_ptr.
    /// Graph does not create IRNodes，but owns the resource.
    vector<shared_ptr<IRNode>> nodes;

    /// Whenever a variable is encountered, we need to query the data flow node
    /// if the variable is a rvalue.
    /// The graph owning VarProxy.
    map<shared_ptr<VarProxy>,
        weak_ptr<DataProducerNode>> varProxy2node;

    /// when using MuOpSplice, we need the varProxy2node of graph b
    map<shared_ptr<VarProxy>,
        weak_ptr<DataProducerNode>> splice_graph_varProxy2node;

    /// Whether sub graphs_being_building have been extracted via SubGraphPool
    bool has_extracted = false;

    void add_node(const shared_ptr<IRNode>& node)
    {
        nodes.push_back(node);
        node->index = next_index++;
    }

    void remove_unused_producer(const shared_ptr<DataProducerNode> &node);

    shared_ptr<VarProxy> add_var_definition(const shared_ptr<VarSymbol> &var_sym,
                                            const shared_ptr<DataProducerNode> &node);

    weak_ptr<ParameterNode> get_parameter_node(const string& name);

    std::size_t hash_graph();

    /// copy a graph has not been mutated.
    shared_ptr<Graph> clone_non_mutated_graph();

    /// copy a graph that has been mutated.
    shared_ptr<Graph> clone_mutated_graph() const;

    void reindex_nodes();

    bool has_node(const shared_ptr<IRNode> &node);

    bool verify_healthy() const;

    string get_function_name() const;
};

} /// end of namespace

#endif //FUZZFLOW_GRAPH_H
