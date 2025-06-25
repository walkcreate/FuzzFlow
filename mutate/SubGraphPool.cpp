#include "SubGraphPool.h"

namespace FuzzFlow {

vector<weak_ptr<TerminalNode>> SubGraphPool::get_terminal_nodes(const shared_ptr<Graph>& graph)
{
    vector<weak_ptr<TerminalNode>> nodes_terminal;

    for (auto& node : graph->nodes) {
        if (auto producer = dynamic_pointer_cast<DataProducerNode>(node);
            producer != nullptr && producer->uses.empty())
        {
            /// dead code elimination
            continue;
        }

        if (auto terminal_node = dynamic_pointer_cast<TerminalNode>(node)) {
            nodes_terminal.push_back(terminal_node);
        }
    }

    return nodes_terminal;
}

/// Attempts to add a node to the independent subgraph if:
/// 1. All target nodes of its outgoing edges can be added (or are already in subgraph)
/// 2. Its data-dependent producers (non-input edges) can be added
///
/// Performs DFS traversal to check each output edge:
/// - If target node exists in subgraph: OK
/// - Else: recursively attempts to add the target node
///
/// Some data producers are tightly coupled with structural fixed nodes.
/// Skip addition attempts when encountering these producers
///
bool SubGraphPool::try_add_consumer(const weak_ptr<DataConsumerNode>& node,
                                    set<weak_ptr<DataProducerNode>,
                                        std::owner_less<>>& sub_graph_nodes)
{
    if (auto _node = dynamic_pointer_cast<PhiNode>(node.lock())) {
        return false;
    }

    if (auto _node = dynamic_pointer_cast<ParameterNode>(node.lock())) {
        return false;
    }

    if (auto _node = dynamic_pointer_cast<FunctionPropertyNode>(node.lock())) {
        return false;
    }

    const auto current_consumer = node.lock();

    const auto current_also_producer = dynamic_pointer_cast<DataProducerNode>(current_consumer);
    sub_graph_nodes.insert(current_also_producer);

    /// Check if the end points of all outgoing edges from this node are within the subgraph.
    bool all_dest_in_sub_graph = true;

    for (auto& down_node_w : current_consumer->inputs) {

        if (down_node_w.expired()) {
            throw MutateError("Cracked seed. The consumer's input is expired.");

            /// todo: remove the seed from queue
        }

        auto down_node = down_node_w.lock();

        if (auto down_fixed = dynamic_pointer_cast<FixedNode>(down_node); down_fixed != nullptr) {
            all_dest_in_sub_graph = false;
            sub_graph_nodes.erase(current_also_producer);
            break;
        }

        if (! sub_graph_nodes.contains(down_node)) {
            if (auto down_also_consumer = dynamic_pointer_cast<DataConsumerNode>(down_node)) {

                /// The down node is not yet in the subgraph - ensure it gets included.
                /// Recursively attempt to add the down node to the subgraph.
                bool add_success = this->try_add_consumer(down_also_consumer, sub_graph_nodes);

                if (! add_success) {
                    all_dest_in_sub_graph = false;
                    sub_graph_nodes.erase(current_also_producer);
                    break;
                }
            }
            else {
                sub_graph_nodes.insert(down_node);
            }
        }
    }

    /// A producer can be added to the subgraph not only when all its inputs are subgraph-compatible,
    /// but also when any node referenced via member variables meets subgraph criteria.
    ///
    /// Example: An InvokeMethod node has a member LoadNode. While FlowIR doesn't represent this
    /// data dependency via input/use edges, the InvokeMethod can only be fully integrated
    /// when its associated LoadNode is also included in the subgraph.
    ///
    if (const auto invoke_method = dynamic_pointer_cast<InvokeMethodNode>(node.lock()))
    {
        auto load_method = invoke_method->get_load_node();

        if (! sub_graph_nodes.contains(load_method)) {
            bool add_success = this->try_add_consumer(load_method, sub_graph_nodes);

            if (! add_success) {
                all_dest_in_sub_graph = false;
                sub_graph_nodes.erase(current_also_producer);
            }
        }
    }

    if (all_dest_in_sub_graph) {
        if (const auto term_node = dynamic_pointer_cast<TerminalNode>(node.lock())) {
            if (! this->extracted_terminal_nodes.contains(term_node)) {
                this->extracted_terminal_nodes.insert(term_node);
            }
        }
    }

    return all_dest_in_sub_graph;
}

/// The `node` serves as the entry point for independent subgraph discovery.
/// Checks if each use-node (nodes with input edges pointing to `node`)
/// can be merged into the subgraph.
///
void SubGraphPool::grow_sub_graph(const weak_ptr<DataProducerNode> &node,
                                  set<weak_ptr<DataProducerNode>,
                                      std::owner_less<>> &sub_graph_nodes)
{
    /// To reduce the number of subgraphs and minimize memory usage,
    /// overlapping subgraphs are not saved redundantly.
    ///
    /// Subgraphs are extracted by recursively traversing upward from leaf nodes,
    /// specifically exploring whether upward consumer can be included in the subgraph.
    ///
    /// How to determine if a node can be added to a subgraph?
    /// A node can be included if all its data dependencies are already part of the subgraph.
    ///
    /// When is a subgraph considered complete?
    /// If a node A is being processed and none of its upward "uses" nodes can be added to the subgraph,
    /// then A becomes the head of its subgraph, and the subgraph should be saved.
    /// Since all descendant nodes of A are already within this subgraph,
    /// there is no need to create additional subgraphs with those descendants as heads.
    /// Moreover, during the Mutation phase, nodes are randomly selected from the subgraph as data flow inputs.
    ///
    /// Under this approach:
    /// If A is an upstream node of B, and B has another upstream node C that can also be included in a subgraph
    /// (assuming C is also a head), then B and all its descendants will appear in two subgraphs,
    /// one headed by A and the other by C.
    /// This redundancy remains unresolved.
    ///
    /// During mutation, if a subgraph is the intersection of many subgraphs,
    /// it will have a higher probability of being selected.

    /// TODO: An improved approach
    /// Instead of owning copies of all nodes,
    /// the subgraph object retains a copy of only the head node.

    /// Check if any upstream node has been successfully added to the subgraph.
    /// If so, the current node is already in the subgraph pool,
    /// and there is no need to save it as the head of a new subgraph.
    bool expanded_upstream_node = false;

    for (auto &up_consumer_w : node.lock()->uses) {

        if (up_consumer_w.expired()) {
            throw MutateError("Cracked seed. The use of a node is expired.");
        }

        shared_ptr<DataConsumerNode> upward_consumer = up_consumer_w.lock();

        if (auto upward_fixed = dynamic_pointer_cast<FixedNode>(upward_consumer); upward_fixed != nullptr) {
            /// the subgraph does not accepts data producers that are also subclass of FixedNode
            continue;
        }

        if (sub_graph_nodes.contains(upward_consumer)) {
            // Since the upstream node is part of the subgraph, the current node, as its input,
            // has also been analyzed and included in the subgraph, eliminating the need for redundant analysis.
            // Therefore, there is no need to take current node as a head to preserve an independent subgraph.
            expanded_upstream_node = true;

            continue;
        }

        const bool grow_success = this->try_add_consumer(upward_consumer, sub_graph_nodes);

        if (grow_success) {
            if (auto also_producer = dynamic_pointer_cast<DataProducerNode>(upward_consumer);
                also_producer != nullptr)
            {
                /// Recursively traverse upstream to explore new subgraphs (DFS via recursion).
                this->grow_sub_graph(also_producer, sub_graph_nodes);

                expanded_upstream_node = true;
            }
        }
    }

    if (! expanded_upstream_node) {
        /// Save the independent subgraph after recursion.
        /// If no upstream nodes were added to an independent subgraph,
        /// the current node is the highest-level node and should be saved as the head of the subgraph.
        this->save_independent_sub_graph(node, sub_graph_nodes);
    }
}

void SubGraphPool::save_independent_sub_graph(const weak_ptr<DataProducerNode> &head_node,
                                              set<weak_ptr<DataProducerNode>,
                                                  std::owner_less<>> &sub_graph_nodes)
{
    vector<shared_ptr<DataProducerNode>> sub_graph_nodes_copy;

    map<weak_ptr<IRNode>,
        weak_ptr<IRNode>,
            std::owner_less<>> refNode2ownNode;

    /// First pass: Clone all nodes in the subgraph.
    for (auto& node : sub_graph_nodes) {
        auto own_node = dynamic_pointer_cast<DataProducerNode>(node.lock()->clone());

        if (own_node == nullptr) {
            throw MutateError("Error when saving sub graph. Node in extracted sub graph is not a producer");
        }

        sub_graph_nodes_copy.push_back(own_node);

        /// Maintains mapping between original and copied nodes to fix connections (inputs/uses) in the copied graph.
        refNode2ownNode.insert({node, own_node});
    }

    /// Second pass: Rebuild dependency edges between copied nodes.
    for (const auto &node : sub_graph_nodes_copy) {
        node->clone_repair(refNode2ownNode);
    }

    /// A subgraph is a collection of data producer nodes
    const auto sub_graph = make_shared<SubGraph>(head_node, std::move(sub_graph_nodes_copy));

    /// calc the hash of subgraph
    std::size_t graph_hash = sub_graph->hash_graph();

    if (! this->sub_graphs_hashes.contains(graph_hash)) {
        this->sub_graphs_hashes.insert(graph_hash);
        this->sub_graphs.push_back(sub_graph);

        cout << "[+] Extract sub graph success, "
            << "head node: " << head_node.lock()->get_label() << ", "
            << sub_graph->nodes.size() << " nodes,"
            << " hash: 0x" << std::hex << graph_hash << std::endl;
    }
    else {
        cout << "[*] Duplicate graph hash" << std::endl;
    }
}

void SubGraphPool::extract(const shared_ptr<Graph> &graph)
{
    /// reset
    this->extracted_terminal_nodes.clear();

    /// Use leaf nodes as starting points for independent subgraph discovery
    auto nodes_terminal = this->get_terminal_nodes(graph);

    for (auto& terminal_node : nodes_terminal) {

        cout << "Extract SubGraph starting from terminal " << terminal_node.lock()->get_label() << std::endl;

        if (this->extracted_terminal_nodes.contains(terminal_node)) {
            /// Skip leaf nodes already covered by other subgraphs to avoid duplicates
            continue;
        }

        this->extracted_terminal_nodes.insert(terminal_node);

        set<weak_ptr<DataProducerNode>,
            std::owner_less<>> sub_graph_nodes;

        sub_graph_nodes.insert(terminal_node);

        /// Explore the independent subgraph from terminal node
        this->grow_sub_graph(terminal_node, sub_graph_nodes);
    }

    cout << "[*] Independent SubGraph num: " << std::to_string(this->sub_graphs.size()) << std::endl;
}

shared_ptr<SubGraph> SubGraphPool::random_sub_graph() const
{
    shared_ptr<SubGraph> sub_graph = random_vector_element(this->sub_graphs);
    return sub_graph;
}

weak_ptr<DataProducerNode> SubGraphPool::random_producer_from_pool() const
{
    const shared_ptr<SubGraph> sub_graph = random_vector_element(this->sub_graphs);
    weak_ptr<DataProducerNode> node = random_vector_element(sub_graph->nodes);
    return node;
}

} /// end of namespace