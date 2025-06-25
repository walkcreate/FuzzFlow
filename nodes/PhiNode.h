#ifndef FUZZFLOW_PHINODE_H
#define FUZZFLOW_PHINODE_H

#include <algorithm>

#include "IRNode.h"

#include "MergeNode.h"
#include "FakeDataProducerNode.h"
#include "../js2graph/VarProxy.h"

#include "DataConsumerNode.h"
#include "DataProducerNode.h"

#include "../utils/assert_or_throw.h"

namespace FuzzFlow {

class PhiNode final : public DataConsumerNode,
                      public DataProducerNode
{
private:
    static const string label;

public:
    weak_ptr<AbstractMergeNode> merge_node;

    /// Stores the PhiNode's index within MergeNode's phi list.
    /// This ordering affects both:
    /// 1. The walk-copy phase behavior
    /// 2. Subsequent Lift process outcomes
    uint32_t merge_index = 0;

    PhiNode(const weak_ptr<AbstractMergeNode> &_merge_node,
            const uint32_t _merge_index,
            vector<weak_ptr<DataProducerNode>> &_inputs)
    {
        this->merge_node = _merge_node;

        /// Why not auto-determine phi index from merge_node's idx2phis.size()?
        /// - During cloning, new phi nodes temporarily reference original merge_node
        /// - Original merge_node already has full phi list
        /// - Auto-indexing would produce non-zero-based indices (continuing from existing count)
        /// Solution: Prepare merge_index before construction and pass it explicitly.
        this->merge_index = _merge_index;

        for (auto &floating_node: _inputs) {
            this->inputs.push_back(floating_node);
        }

        this->node_hash_current = label;
    }

    string get_label() override
    {
        return PhiNode::label;
    }

    void post_construct() override
    {
        auto node_self = std::dynamic_pointer_cast<PhiNode>(shared_from_this());

        this->DataConsumerNode::post_construct();

        /// Phi nodes maintain bidirectional edges:
        /// 1. Forward edges to dataflow inputs
        /// 2. Back edge to merge node (with reverse link maintained)
        this->merge_node.lock()->add_idx2phis(merge_index, node_self);
    }

    shared_ptr<IRNode> clone() override
    {
        return make_shared<PhiNode>(this->merge_node, this->merge_index, this->inputs);
    }

    void clone_repair(map<weak_ptr<IRNode>,
                          weak_ptr<IRNode>,
                            std::owner_less<>> &refNode2ownNode) override
    {
        ASSERT_OR_EXIT(refNode2ownNode.contains(this->merge_node));
        ASSERT_OR_EXIT(! refNode2ownNode[this->merge_node].expired());

        this->DataConsumerNode::clone_repair(refNode2ownNode);

        const auto new_merge = dynamic_pointer_cast<AbstractMergeNode>(
            refNode2ownNode[this->merge_node].lock());

        this->merge_node = new_merge;

        ASSERT_OR_EXIT(this->merge_node.lock() != nullptr);

        this->post_construct();
    }

    bool need_back_fill() const
    {
        for (const auto & input : this->inputs) {
            if (dynamic_pointer_cast<FakeDataProducerNode>(input.lock())) {
                return true;
            }
        }
        return false;
    }

    void back_fill(const weak_ptr<DataProducerNode>& real_node)
    {
        for (auto & input : this->inputs) {
            if (dynamic_pointer_cast<FakeDataProducerNode>(input.lock())) {
                input = real_node;
                std::shared_ptr<PhiNode> node_self = dynamic_pointer_cast<PhiNode>(shared_from_this());
                real_node.lock()->uses.push_back(node_self);
            }
        }
    }

    void remove_unnecessary_loop_phi(map<shared_ptr<VarProxy>,
                                         weak_ptr<DataProducerNode>> &varProxy2node)
    {
        shared_ptr<DataProducerNode> real_data_node;

        for (const auto & input : this->inputs) {
            if (dynamic_pointer_cast<FakeDataProducerNode>(input.lock())) {
                shared_ptr<DataProducerNode> fake_data_node = input.lock();
            }
            else {
                real_data_node = dynamic_pointer_cast<DataProducerNode>(input.lock());
            }
        }

        const shared_ptr<PhiNode> node_self = dynamic_pointer_cast<PhiNode>(shared_from_this());

        /// 1. remove phi from uses of merge node
        weak_ptr<IRNode> wPtr = node_self;

        assert_or_throw_js2graph(node_self ==
                                    this->merge_node.lock()->get_idx2phis(this->merge_index).lock(),
                               ErrorMsgsJS2Graph::handleError(ErrorCodeJS2Graph::PhiIndexNotMatchMerge));

        this->merge_node.lock()->del_idx2phis(this->merge_index);

        /// 2. remove phi from uses of input nodes
        for (const auto & input : this->inputs) {
            if (dynamic_pointer_cast<FakeDataProducerNode>(input.lock()) != nullptr) {
                continue;
            }

            auto &uses = input.lock()->uses;

            const auto pos = std::find_if(uses.begin(),
                                          uses.end(),
                                          [&node_self](const std::weak_ptr<IRNode> &ptr1) {
                return ptr1.lock() == node_self;
            });

            uses.erase(pos);
        }

        /// 3. remove phi from nodes that takes phi as input.
        /// Replace the phi with real data node.
        /// The node which takes phi as input may be fixed node.
        for (auto &use_node: this->uses) {
            auto &upper_inputs = use_node.lock()->inputs;

            for (int i = 0; i < upper_inputs.size(); i++) {
                if (upper_inputs[i].lock() == node_self) {

                    if (dynamic_pointer_cast<AbstractMergeNode>(use_node.lock()) != nullptr) {
                        upper_inputs.erase(upper_inputs.begin() + i);
                    }
                    else {
                        upper_inputs[i] = real_data_node;

                        /// The real data node could also be a PhiNode or might need to be deleted.
                        /// Therefore, the use relationships of the real data node must be properly maintained.
                        //
                        /// Test case demonstrates this issue.
                        /// WebKit_JSTests_microbenchmarks_Int8Array-alloc-long-lived.js
                        real_data_node->uses.push_back(use_node);
                    }
                }
            }
        }

        /// 4. repair the varProxy2node.
        /// replace the proxy's pointing target with real data node.
        for (auto &[proxy, node]: varProxy2node) {
            if (node.lock() == node_self) {
                varProxy2node[proxy] = real_data_node;
            }
        }
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<PhiNode>(shared_from_this());
        visitor.visit(node);
    }
};

} /// end of namespace

#endif //FUZZFLOW_PHINODE_H
