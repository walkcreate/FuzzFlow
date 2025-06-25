#ifndef FUZZFLOW_SUBGRAPH_H
#define FUZZFLOW_SUBGRAPH_H

#include "../nodes/DataProducerNode.h"
#include "../nodes/IRNode.h"
#include "../js2graph/VarProxy.h"

namespace FuzzFlow {

class SubGraph {
public:
    SubGraph(const weak_ptr<DataProducerNode> &head,
             const vector<shared_ptr<DataProducerNode>> &nodes)
    {
        this->head = head;
        this->nodes = nodes;
    }

    std::size_t hash_graph()
    {
        /// Calculate the hash of the entire independent subgraph by summing the hashes of all nodes.
        /// This ensures consistent hashing regardless of node ordering.
        std::size_t hash_val = 0;
        for (const auto& node : this->nodes) {
            hash_val += node->calc_hash();
        }

        this->graph_hash = hash_val;
        return hash_val;
    }

    vector<shared_ptr<DataProducerNode>> nodes;

    std::size_t graph_hash = 0;

private:
    /// In independent subgraphs, the last node added in bottom-up order is treated as the root vertex.
    /// Using this root vertex during mutation ensures the longest dataflow path, improving mutation efficiency.
    weak_ptr<DataProducerNode> head;

    map<shared_ptr<VarProxy>, weak_ptr<DataProducerNode>> varProxy2node;
};

} /// end of namespace

#endif //FUZZFLOW_SUBGRAPH_H
