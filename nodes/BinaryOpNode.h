#ifndef FUZZFLOW_BINARYOPNODE_H
#define FUZZFLOW_BINARYOPNODE_H

#include "IRNode.h"
#include "DataProducerNode.h"
#include "DataConsumerNode.h"
#include "SequentialOperationNode.h"

#include "../js2graph/LanguageOperator.h"

namespace FuzzFlow {

class BinaryOpNode final : public SequentialOperationNode,
                           public DataProducerNode,
                           public DataConsumerNode
{
public:
    shared_ptr<LanguageOperator> op;

    BinaryOpNode(const weak_ptr<FixedNode> &next,
                 const weak_ptr<DataProducerNode> &left,
                 const weak_ptr<DataProducerNode> &right,
                 const shared_ptr<LanguageOperator> &op)
        : SequentialOperationNode(next)
    {
        this->op = op;
        this->inputs.push_back(left);
        this->inputs.push_back(right);

        this->node_hash_current = this->op->label;
    }

    void post_construct() override
    {
        this->DataConsumerNode::post_construct();
        this->UniSuccessorNode::post_construct();
    }

    string get_label() override
    {
        return this->op->label;
    }

    shared_ptr<DataProducerNode> left() const
    {
        return this->inputs[0].lock();
    }

    shared_ptr<DataProducerNode> right() const
    {
        return this->inputs[1].lock();
    }

    shared_ptr<IRNode> clone() override
    {
        auto _op = make_unique<LanguageOperator>(this->op->label, this->op->code);

        shared_ptr<DataProducerNode> left = this->inputs[0].lock();
        shared_ptr<DataProducerNode> right = this->inputs[1].lock();

        auto new_node = make_shared<BinaryOpNode>(this->next(), left, right, std::move(_op));
        return new_node;
    }

    void clone_repair(map<weak_ptr<IRNode>,
                          weak_ptr<IRNode>,
                          std::owner_less<>>& refNode2ownNode) override
    {
        this->DataConsumerNode::clone_repair(refNode2ownNode);

        this->UniSuccessorNode::clone_repair(refNode2ownNode);
    }

    std::size_t calc_hash() override
    {
        const auto left_hash = left()->calc_hash();
        const auto op_hash = std::hash<std::string>{}(this->op->label);
        const auto right_hash = right()->calc_hash();

        return left_hash + op_hash + right_hash;
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<BinaryOpNode>(shared_from_this());
        visitor.visit(node);
    }

    string get_producer_expr(JavaScriptLifter &visitor) override;
};

} /// end of namespace

#endif //FUZZFLOW_BINARYOPNODE_H
