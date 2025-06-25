#ifndef FUZZFLOW_ABSTRACTMERGENODE_H
#define FUZZFLOW_ABSTRACTMERGENODE_H

#include "IRNode.h"
#include "FixedNode.h"
#include "AbstractBeginNode.h"
#include "EndMayMergeNode.h"

namespace FuzzFlow {

class PhiNode;

///
/// This is an abstract class.
/// The predecessor of merge node is null
///
class AbstractMergeNode : public AbstractBeginNode {
public:
    /// PhiNode can locate its MergeNode via merge_node member.
    ///
    /// Key observations about MergeNode -> PhiNode relationship:
    /// - Possible approach: MergeNode's uses contain PhiNodes (without order info)
    ///   - Implied MergeNode was PhiNode's input (semantically incorrect)
    ///   - Actually, PhiNode's inputs are dataflow edges; merge_node is just a reference
    ///
    /// Issues with uses-based approach:
    /// - Order not preserved: Depends on PhiNode construction order
    /// - walk_copy traversal can't guarantee original ordering
    ///
    /// New index-based solution:
    /// - Uses ordered map to maintain original phi sequence in phi_nodes()
    /// - Tolerates non-contiguous indices (from loop-induced phi creation/deletion)
    /// - Index magnitude still preserves relative ordering
    ///
    map<uint32_t,
        weak_ptr<PhiNode>> idx2phis;


    /// In Graal IR: An Extensible Declarative Intermediate Representation
    /// MergeNode points to the two End node of IfNode by inputs edge
    ///
    vector<weak_ptr<EndMayMergeNode>> merged_flows;

    AbstractMergeNode(const weak_ptr<EndMayMergeNode> &_single_flow,
                      const weak_ptr<FixedNode>& next)
        : AbstractBeginNode(next)
    {
        this->merged_flows.push_back(_single_flow);
    }

    AbstractMergeNode(const vector<weak_ptr<EndMayMergeNode>> &_merged_flow,
                      const weak_ptr<FixedNode>& next)
          : AbstractBeginNode(next)
    {
        this->merged_flows = _merged_flow;
    }

    void post_construct() override
    {
        /// maintain the connections with next
        this->UniSuccessorNode::post_construct();

        /// In GraalVM, the merge inputs has reverse edges
        const shared_ptr<AbstractMergeNode> node_self = dynamic_pointer_cast<AbstractMergeNode>(shared_from_this());

        for (auto &end_node: this->merged_flows) {
            /// merged_flows and
            end_node.lock()->merge_node = node_self;
        }
    }

    void clone_repair(map<weak_ptr<IRNode>,
                          weak_ptr<IRNode>,
                              std::owner_less<>> &refNode2ownNode) override
    {
        this->UniSuccessorNode::clone_repair(refNode2ownNode);

        for (auto & merged_flow : this->merged_flows) {
            ASSERT_OR_EXIT(refNode2ownNode.contains(merged_flow));
            ASSERT_OR_EXIT(! refNode2ownNode[merged_flow].expired());

            merged_flow = dynamic_pointer_cast<EndMayMergeNode>(refNode2ownNode[merged_flow].lock());

            ASSERT_OR_EXIT(merged_flow.lock() != nullptr);
        }

        this->post_construct();
    }

    weak_ptr<PhiNode> get_idx2phis(const unsigned int merge_index)
    {
        return idx2phis[merge_index];
    }

    unsigned int get_idx2phis_size() const
    {
        return idx2phis.size();
    }

    unsigned int get_next_phi_idx() const
    {
        unsigned int next_phi_idx = 0;

        for (const auto& [idx, phi_node] : idx2phis) {
            if (idx >= next_phi_idx) {
                next_phi_idx = idx+1;
            }
        }

        return next_phi_idx;
    }

    void add_idx2phis(const unsigned int merge_index, weak_ptr<PhiNode> phi)
    {
        idx2phis.insert_or_assign(merge_index, phi);
    }

    void del_idx2phis(const unsigned int merge_index)
    {
        idx2phis.erase(merge_index);
    }

    /// return phi nodes related to the merge
    vector<weak_ptr<PhiNode>> phi_nodes();
};

} /// end of namespace

#endif //FUZZFLOW_ABSTRACTMERGENODE_H
