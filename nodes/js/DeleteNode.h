#ifndef FUZZFLOW_DELETENODE_H
#define FUZZFLOW_DELETENODE_H

#include "../SequentialOperationNode.h"
#include "../DataConsumerNode.h"
#include "../DataProducerNode.h"

namespace FuzzFlow {
/*
 * Delete is a unary operator that attempts to delete the object property
 * or array element specified as its operand.
 * Delete expects its operand to be a lvalue.
 * If it is not a lvalue, the operator takes no action and returns true.
 */

class DeleteNode final : public SequentialOperationNode,
                         public DataConsumerNode,
                         public DataProducerNode
{
private:
    static const string label;

public:
    DeleteNode(const weak_ptr<FixedNode> &next,
               const weak_ptr<DataProducerNode> &del_tgt)
        : SequentialOperationNode(next)
    {
        /// Note that the uses property of del_tgt_node and del_ret_node have not been set.
        this->inputs.push_back(del_tgt);

        this->node_hash_current = label;
    }

    string get_label() override
    {
        return DeleteNode::label;
    }

    shared_ptr<DataProducerNode> del_tgt() const
    {
        return this->inputs[0].lock();
    }

    void post_construct() override
    {
        this->UniSuccessorNode::post_construct();

        this->DataConsumerNode::post_construct();
    }

    shared_ptr<IRNode> clone() override
    {
        return make_shared<DeleteNode>(this->next(), this->del_tgt());
    }

    void clone_repair(map<weak_ptr<IRNode>, weak_ptr<IRNode>, std::owner_less<> > &refNode2ownNode) override
    {
        this->UniSuccessorNode::clone_repair(refNode2ownNode);

        this->DataConsumerNode::clone_repair(refNode2ownNode);
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<DeleteNode>(shared_from_this());
        visitor.visit(node);
    }
};

} /// end of namespace

#endif //FUZZFLOW_DELETENODE_H
