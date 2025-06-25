#include "Graph.h"

#include "../mutate/WalkCopyGraph.h"
#include "../nodes/FunctionHeadNode.h"

namespace FuzzFlow {

void Graph::remove_unused_producer(const shared_ptr<DataProducerNode> &node)
{
    auto it0 = std::find_if(this->nodes.begin(), this->nodes.end(), [&node](const std::shared_ptr<IRNode> &item) {
        return node == item;
    });
    this->nodes.erase(it0);

    /// remove node from use-def chain
    for (auto &ite_node: this->nodes) {
        if (shared_ptr<DataConsumerNode> consumer = dynamic_pointer_cast<DataConsumerNode>(ite_node)) {
            auto it1 = std::find_if(consumer->inputs.begin(), consumer->inputs.end(),
                                    [&node](const std::weak_ptr<IRNode> &item) {
                                        return node == item.lock();
                                    });
            assert(it1 != consumer->inputs.end());
            consumer->inputs.erase(it1);
        }

        if (shared_ptr<DataProducerNode> producer = dynamic_pointer_cast<DataProducerNode>(ite_node)) {
            auto it2 = std::find_if(producer->uses.begin(), producer->uses.end(),
                                    [&node](const std::weak_ptr<IRNode> &item) {
                                        return node == item.lock();
                                    });
            assert(it2 != producer->uses.end());
            producer->uses.erase(it2);
        }
    }
}

shared_ptr<VarProxy> Graph::add_var_definition(const shared_ptr<VarSymbol> &var_sym,
                                               const shared_ptr<DataProducerNode> &node)
{
    unsigned int new_index = 0;
    int max_index = -1;

    /// Search existing var proxies to decide the new proxy index
    for (auto &it : this->varProxy2node) {
        if (it.first->var_symbol == var_sym) {
            int existing_index = it.first->index;
            if (existing_index > max_index) {
                max_index = existing_index;
            }
        }
    }

    if (max_index >= 0) {
        new_index = max_index + 1;
    }
    else {
        new_index = 0;
    }

    /// According to SSA, every definition generates a new proxy.
    /// Each proxy points to its corresponding data node.
    auto proxy = make_shared<VarProxy>(var_sym, new_index);
    this->varProxy2node.insert({proxy, node});

    return proxy;
}

///
/// Locate the parameter in the data flow
/// name is the formal parameter name
///
weak_ptr<ParameterNode> Graph::get_parameter_node(const string& name)
{
    for (auto &node1: this->nodes) {
        if (auto param_node = dynamic_pointer_cast<ParameterNode>(node1)) {
            if (param_node->get_parameter_name() == name) {
                return {param_node};
            }
        }
    }

    return {};
}

std::size_t Graph::hash_graph()
{
    unsigned int num_iterations = 2;

    for (int iter = 0; iter < num_iterations; ++iter) {
        for (const auto &node: this->nodes) {
            node->compute_hash_next();
        }

        for (const auto &node : this->nodes) {
            node->node_hash_current = node->node_hash_next;
        }
    }

    vector<string> final_labels;

    for (const auto &node : this->nodes) {
        final_labels.push_back(node->node_hash_current);
    }

    std::sort(final_labels.begin(), final_labels.end());

    std::size_t hash_val = 0;
    for (unsigned int i = 0; i < final_labels.size(); ++i) {
        hash_val += std::hash<string>()(final_labels[i]);
    }

    return hash_val;
}

/*
std::size_t Graph::hash_graph()
{
    std::size_t hash_val = 0;

    for (const auto &node: this->nodes) {
        hash_val += node->calc_hash();
    }

    return hash_val;
}
*/

shared_ptr<Graph> Graph::clone_non_mutated_graph()
{
    vector<shared_ptr<IRNode>> new_nodes;

    map<shared_ptr<VarProxy>,
        weak_ptr<DataProducerNode>> new_varProxy2node;

    /// ref node: copied node
    /// own node: new node
    map<weak_ptr<IRNode>,
        weak_ptr<IRNode>,
            std::owner_less<>> refNode2ownNode;

    map<shared_ptr<VarSymbol>,
        shared_ptr<VarSymbol>> origVarSym2newVarSym;

    for (auto &node: this->nodes) {
        /// The first iteration, cloning
        shared_ptr<IRNode> own_node = node->clone();
        own_node->index = node->index;

        new_nodes.push_back(own_node);

        /// keep the map of copied node and the new node
        /// we need this map to repair the inputs and uses
        refNode2ownNode.insert({node, own_node});
    }

    for (auto &node: new_nodes) {
        /// The second iteration, repair the dependencies among nodes
        node->clone_repair(refNode2ownNode);
    }

    map<shared_ptr<VarProxy>,
        shared_ptr<VarProxy>> proxy_old2new;

    /// clone varProxy2node
    for (auto &[_var_proxy, _node]: this->varProxy2node) {
        auto new_var_proxy = make_shared<VarProxy>(_var_proxy, origVarSym2newVarSym);

        /// Always check contains() before using operator[] to avoid accidental insertions of null/0 values.
        if (!refNode2ownNode.contains(_node)) {
            continue;
        }
        auto new_node = dynamic_pointer_cast<DataProducerNode>(
            refNode2ownNode[_node].lock());

        new_varProxy2node.insert_or_assign(new_var_proxy, new_node);

        proxy_old2new.insert_or_assign(_var_proxy, new_var_proxy);
    }

    auto graph = make_shared<Graph>(new_nodes, new_varProxy2node);
    return graph;
}

shared_ptr<Graph> Graph::clone_mutated_graph() const
{
    map<shared_ptr<VarProxy>,
        weak_ptr<DataProducerNode>> new_varProxy2node;

    map<shared_ptr<VarSymbol>,
        shared_ptr<VarSymbol>> origVarSym2newVarSym;

    const shared_ptr<IRNode> function_node = this->nodes.front();
    auto function_head = dynamic_pointer_cast<FunctionHeadNode>(function_node);
    if (function_head == nullptr) {
        assert_or_throw_mutate(false, "The first and the last node in graph are neither function node");
    }

    /// construct all nodes by flow
    auto walker_copy_graph = WalkCopyGraph(function_head);
    walker_copy_graph.copy();

    auto new_graph = walker_copy_graph.new_graph;
    map<weak_ptr<IRNode>,
            weak_ptr<IRNode>,
                std::owner_less<>> &origNode2newNode = walker_copy_graph.origNode2newNode;

    assert_or_throw_mutate(origNode2newNode.size() == new_graph->nodes.size(),
        "After copy, nodes size do not match");

    new_graph->reindex_nodes();

    for (auto &node: new_graph->nodes) {
        node->clone_repair(origNode2newNode);
    }

    for (unsigned int i = 0; i < this->nodes.size(); ++i) {
        if (this->nodes[i]->index == 0) {
            assert_or_throw_mutate(false, "Clone error detected.");
        }
    }

    map<shared_ptr<VarProxy>, shared_ptr<VarProxy>> proxy_old2new;

    /// The VarSymbol in VarProxy is crucial for data flow identification.
    /// Variables with the same name belong to the same data flow
    /// if and only if they share the same VarSymbol.
    ///
    /// During semantic analysis:
    /// - Each variable redeclaration generates a new VarSymbol
    ///
    /// When copying varProxy2node:
    /// - Not every VarProxy needs a brand-new VarSymbol
    /// - Creating VarSymbols indiscriminately would imply
    ///   every variable is a new declaration
    ///

    /// clone varProxy2node
    for (auto &[_var_proxy, _node]: this->varProxy2node) {
        if (!origNode2newNode.contains(_node)) {
            continue;
        }
        auto new_var_proxy = make_shared<VarProxy>(_var_proxy, origVarSym2newVarSym);
        auto new_node = dynamic_pointer_cast<DataProducerNode>(origNode2newNode[_node].lock());

        new_varProxy2node.insert_or_assign(new_var_proxy, new_node);

        proxy_old2new.insert_or_assign(_var_proxy, new_var_proxy);
    }

    /// clone splice varProxy2node
    for (auto &[_var_proxy, _node]: this->splice_graph_varProxy2node) {
        if (!origNode2newNode.contains(_node)) {
            continue;
        }
        auto new_var_proxy = make_shared<VarProxy>(_var_proxy, origVarSym2newVarSym);
        auto new_node = dynamic_pointer_cast<DataProducerNode>(origNode2newNode[_node].lock());

        new_varProxy2node.insert_or_assign(new_var_proxy, new_node);

        proxy_old2new.insert_or_assign(_var_proxy, new_var_proxy);
    }

    new_graph->varProxy2node = new_varProxy2node;

    const bool healthy = new_graph->verify_healthy();
    ASSERT_OR_EXIT(healthy);

    return new_graph;
}

void Graph::reindex_nodes()
{
    for (int i = 0; i < this->nodes.size(); ++i) {
        this->nodes[i]->index = i + 1;
    }
}

bool Graph::has_node(const shared_ptr<IRNode> &node)
{
    const auto it = std::find_if(nodes.begin(), nodes.end(), [&node](const weak_ptr<IRNode> &item) {
                    return node == item.lock();
                });

    if (it == nodes.end()) {
        return false;
    }

    return true;
}

bool Graph::verify_healthy() const
{
    if (dynamic_pointer_cast<FunctionHeadNode>(this->nodes[0]) == nullptr) {
        return false;
    }

    for (auto &node : this->nodes) {
        if (dynamic_pointer_cast<FixedNode>(node) != nullptr) {

            if (auto uni = dynamic_pointer_cast<UniSuccessorNode>(node); uni != nullptr) {
                const auto uni_next = uni->next();
                if (uni_next->predecessor.lock() != uni) {
                    return false;
                }
            }

            if (auto if_node = dynamic_pointer_cast<IfNode>(node); if_node != nullptr) {
                auto branch_true = if_node->branch_true();
                auto branch_false = if_node->branch_false();

                if (branch_true->predecessor.lock() != if_node) {
                    return false;
                }
                if (branch_false->predecessor.lock() != if_node) {
                    return false;
                }
            }

            if (auto merge_node = dynamic_pointer_cast<AbstractMergeNode>(node); merge_node != nullptr) {
                for (const auto& end_be_merged : merge_node->merged_flows) {
                    if (end_be_merged.lock()->merge_node.lock() != merge_node) {
                        return false;
                    }
                }

                for (const auto& [idx, phi_node] : merge_node->idx2phis) {
                    if (phi_node.lock()->merge_node.lock() != merge_node) {
                        return false;
                    }
                }
            }
        }

        if (auto phi_node = dynamic_pointer_cast<PhiNode>(node); phi_node != nullptr) {
            auto merge_node = phi_node->merge_node.lock();

            bool in_merge_node = false;

            for (const auto& [idx, phi] : merge_node->idx2phis) {
                if (phi.lock() == phi_node) {
                    in_merge_node = true;
                }
            }

            if (! in_merge_node) {
                return false;
            }
        }

        if (auto consumer = dynamic_pointer_cast<DataConsumerNode>(node); consumer != nullptr) {
            for (int i = 0; i < consumer->inputs.size(); ++i) {
                auto uses = consumer->inputs[i].lock()->uses;

                auto it = find_if(uses.begin(), uses.end(), [&consumer](const weak_ptr<DataConsumerNode> &item) {
                    return consumer == item.lock();
                });

                if (it == uses.end()) {
                    return false;
                }
            }
        }

        if (auto producer = dynamic_pointer_cast<DataProducerNode>(node); producer != nullptr) {
            for (int i = 0; i < producer->uses.size(); ++i) {
                auto inputs = producer->uses[i].lock()->inputs;

                auto it = find_if(inputs.begin(), inputs.end(), [&producer](const weak_ptr<DataProducerNode> &item) {
                    return producer == item.lock();
                });

                if (it == inputs.end()) {
                    return false;
                }
            }
        }
    }

    return true;
}

string Graph::get_function_name() const
{
    auto function_head = dynamic_pointer_cast<FunctionHeadNode>(this->nodes[0]);

    ASSERT_OR_EXIT(function_head != nullptr);

    string name = function_head->get_label();

    ASSERT_OR_EXIT(! name.empty());

    return name;
}

} /// end of namespace