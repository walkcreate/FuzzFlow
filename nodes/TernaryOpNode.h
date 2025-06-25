#ifndef FUZZFLOW_TERNARYOPNODE_H
#define FUZZFLOW_TERNARYOPNODE_H

#include "DataProducerNode.h"
#include "DataConsumerNode.h"

namespace FuzzFlow {

class TernaryOpNode final : public DataProducerNode,
                            public DataConsumerNode
{
private:
    static const string label;

public:
    TernaryOpNode(const weak_ptr<DataProducerNode>& operand_1,
                  const weak_ptr<DataProducerNode>& operand_2,
                  const weak_ptr<DataProducerNode>& operand_3)
    {
        this->inputs.push_back(operand_1);
        this->inputs.push_back(operand_2);
        this->inputs.push_back(operand_3);

        this->node_hash_current = label;
    }

    string get_label() override
    {
        return TernaryOpNode::label;
    }

    shared_ptr<DataProducerNode> operand_1() const
    {
        return this->inputs[0].lock();
    }

    shared_ptr<DataProducerNode> operand_2() const
    {
        return this->inputs[1].lock();
    }

    shared_ptr<DataProducerNode> operand_3() const
    {
        return this->inputs[2].lock();
    }

    void post_construct() override
    {
        this->DataConsumerNode::post_construct();
    }

    shared_ptr<IRNode> clone() override
    {
        /// Reuse the original inputs of the nodes. After all nodes in the new graph
        /// have been cloned, perform repairs during the clone repair phase.
        shared_ptr<DataProducerNode> operand_1 = this->inputs[0].lock();
        shared_ptr<DataProducerNode> operand_2 = this->inputs[1].lock();
        shared_ptr<DataProducerNode> operand_3 = this->inputs[2].lock();

        auto new_node = make_shared<TernaryOpNode>(operand_1, operand_2, operand_3);
        return new_node;
    }

    void clone_repair(map<weak_ptr<IRNode>,
                          weak_ptr<IRNode>,
                              std::owner_less<>> &refNode2ownNode) override
    {
        this->DataConsumerNode::clone_repair(refNode2ownNode);
    }

    std::size_t calc_hash() override
    {
        auto hash_1 = this->operand_1()->calc_hash();
        auto hash_2 = this->operand_2()->calc_hash();
        auto hash_3 = this->operand_3()->calc_hash();
        return hash_1 + hash_2 + hash_3;
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<TernaryOpNode>(shared_from_this());
        visitor.visit(node);
    }

    string get_producer_expr(JavaScriptLifter &visitor) override;
};

} /// end of namespace

#endif //FUZZFLOW_TERNARYOPNODE_H
