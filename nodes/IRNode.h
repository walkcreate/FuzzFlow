#ifndef FUZZFLOW_IRNODE_H
#define FUZZFLOW_IRNODE_H

#include "../utils/common_using.h"

#include "../utils/assert_or_throw.h"

#include "../js2graph/JS2GraphErrorMsgs.h"
#include "../visitors/GraphVisitor.h"

#include "../utils/assert_or_exit.h"

namespace FuzzFlow {

class Graph;

/// edges between nodes are implemented with weak ptr.
/// weak_ptr is used to access the resource(IRNode) without
/// cyclic references between shared_ptr instances.
class IRNode : public std::enable_shared_from_this<IRNode> {
private:
    /// Nodes of one type share one label
    static const string label;

public:
    unsigned int index = 0;

    string node_hash_current;
    string node_hash_next;

    virtual ~IRNode() = default;

    virtual string get_label() {
        return IRNode::label;
    }

    virtual std::size_t calc_hash() {
        return 0;
    }

    /// Copy the un-mutated graph will call this function
    ///
    /// During the graph cloning process, all nodes are first copied.
    /// In this process, the edges from the original graph are also replicated.
    /// As a result, in the new graph, the new nodes still point to the nodes
    /// from the original graph.
    /// After the `clone` function is called, a mapping between the original nodes
    /// and the new nodes is established.
    /// The `refNode2ownNode` map represents the mapping from original nodes to new nodes.
    /// Then, the new node sequence is traversed, and the edges in the new graph
    /// are repaired using the clone repair process.
    virtual shared_ptr<IRNode> clone() = 0;

    /// the finalization of node clone
    virtual void clone_repair(map<weak_ptr<IRNode>,
                                  weak_ptr<IRNode>,
                                      std::owner_less<>>& refNode2ownNode) {}

    virtual void accept(GraphVisitor &visitor);

    virtual void compute_hash_next();
};

} /// end of namespace

#endif //FUZZFLOW_IRNODE_H
