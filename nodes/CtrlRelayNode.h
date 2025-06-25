#ifndef FUZZFLOW_CTRLRELAYNODE_H
#define FUZZFLOW_CTRLRELAYNODE_H

#include "AbstractMergeNode.h"
#include "EndNode.h"

namespace FuzzFlow {

///
/// This node has only one usage scenario, which is when there is only a single branch
/// in the if-condition that proceeds the flow.
/// In this case, the node needs to receive the EndNode of the single branch as input.
///

class CtrlRelayNode final : public AbstractMergeNode {
private:
    static const string label;

public:
    CtrlRelayNode(const weak_ptr<EndMayMergeNode>& end_node,
                  const weak_ptr<FixedNode>& next)
                  : AbstractMergeNode(end_node, next)
    {
        this->node_hash_current = label;
    }

    string get_label() override
    {
        return label;
    }

    void post_construct() override
    {
        this->AbstractMergeNode::post_construct();

        shared_ptr<CtrlRelayNode> node_self = dynamic_pointer_cast<CtrlRelayNode>(shared_from_this());

        this->merged_flows[0].lock()->merge_node = node_self;
    }

    shared_ptr<IRNode> clone() override
    {
        return make_shared<CtrlRelayNode>(this->merged_flows[0], this->next());
    }

    void clone_repair(map<weak_ptr<IRNode>,
                          weak_ptr<IRNode>,
                              std::owner_less<>> &refNode2ownNode) override
    {
        ASSERT_OR_EXIT(refNode2ownNode.contains(this->successor));
        ASSERT_OR_EXIT(! refNode2ownNode[this->successor].expired());

        this->successor = dynamic_pointer_cast<FixedNode>(
            refNode2ownNode[this->successor].lock());

        ASSERT_OR_EXIT(! this->successor.expired());

        ASSERT_OR_EXIT(refNode2ownNode.contains(this->merged_flows[0]));
        ASSERT_OR_EXIT(! refNode2ownNode[this->merged_flows[0]].expired());

        this->merged_flows[0] = dynamic_pointer_cast<EndMayMergeNode>(
            refNode2ownNode[this->merged_flows[0]].lock());

        ASSERT_OR_EXIT(! this->merged_flows[0].expired());

        this->post_construct();
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<CtrlRelayNode>(shared_from_this());
        visitor.visit(node);
    }
};

} /// end of namespace

#endif //FUZZFLOW_CTRLRELAYNODE_H
