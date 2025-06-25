#ifndef FUZZFLOW_SUBGRAPHPOOL_H
#define FUZZFLOW_SUBGRAPHPOOL_H

#include "../utils/util_rand.h"
#include "../utils/common_using.h"
#include "../js2graph/Graph.h"

#include "SubGraph.h"

#include "../nodes/AllNodesInclude.h"

#include "LiteralPool.h"
#include "OperationSequencePool.h"

namespace FuzzFlow {

class SubGraphPool {
public:
    SubGraphPool() = default;

    LiteralPool pool_literal;
    OperationSequencePool pool_operation_sequence;

    void extract(const shared_ptr<Graph> &graph);

    /// select a subGraph randomly for mutation
    shared_ptr<SubGraph> random_sub_graph() const;

    weak_ptr<DataProducerNode> random_producer_from_pool() const;

private:

    /// Tracks which leaf nodes in candidate graphs have been extracted into sub-graphs.
    ///
    /// A leaf node can be included in a subgraph through:
    /// 1. Being the starting point of extraction (leaf/terminal)
    /// 2. Being added during subgraph expansion
    ///
    /// Note: This collection must be cleared before extracting each new graph
    ///       to prevent contamination from previous extraction data.
    set<weak_ptr<TerminalNode>,
        std::owner_less<>> extracted_terminal_nodes;

    /// The extracted sub graphs
    vector<shared_ptr<SubGraph>> sub_graphs {};

    unordered_set<std::size_t> sub_graphs_hashes;

    static vector<weak_ptr<TerminalNode>> get_terminal_nodes(const shared_ptr<Graph>& graph);

    bool try_add_consumer(const weak_ptr<DataConsumerNode>& node,
                          set<weak_ptr<DataProducerNode>,
                          std::owner_less<>>& sub_graph_nodes);

    void grow_sub_graph(const weak_ptr<DataProducerNode> &node,
                        set<weak_ptr<DataProducerNode>,
                            std::owner_less<>>& sub_graph_nodes);

    void save_independent_sub_graph(const weak_ptr<DataProducerNode> &head_node,
                                    set<weak_ptr<DataProducerNode>,
                                        std::owner_less<>> &sub_graph_nodes);
};

} /// end of namespace

#endif //FUZZFLOW_SUBGRAPHPOOL_H
