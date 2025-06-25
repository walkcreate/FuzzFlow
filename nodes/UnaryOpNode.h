#ifndef FUZZFLOW_UNARYOPNODE_H
#define FUZZFLOW_UNARYOPNODE_H

#include "IRNode.h"
#include "DataProducerNode.h"
#include "DataConsumerNode.h"
#include "SequentialOperationNode.h"

#include "../js2graph/LanguageOperator.h"

namespace FuzzFlow {

class UnaryOpNode final : public SequentialOperationNode,
                          public DataProducerNode,
                          public DataConsumerNode
{
public:
    shared_ptr<LanguageOperator> op;

    ///
    /// Both the increment and decrement operators have an implicit data input,
    /// making them binary operations.
    /// Therefore, the UnaryOpNode does not include increment or decrement operations
    /// like post/pre increment/decrement.
    ///
    /// Except for increment and decrement, no other nodes need to consider
    /// whether the operator is prefix or postfix.
    /// As a result, UnaryOpNode does not need to handle this distinction.
    /// For UnaryOp, the operator is always a prefix.
    ///
    UnaryOpNode(const weak_ptr<FixedNode> &next,
                const weak_ptr<DataProducerNode> &data_node,
                const shared_ptr<LanguageOperator>& op)
        : SequentialOperationNode(next)
    {
        this->op = op;
        this->inputs.push_back(data_node);

        this->node_hash_current = op->label;
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

    /// fake member
    shared_ptr<DataProducerNode> data_node() const
    {
        return this->inputs[0].lock();
    }

    shared_ptr<IRNode> clone() override
    {
        auto _op = make_unique<LanguageOperator>(this->op->label, this->op->code);

        shared_ptr<DataProducerNode> data_node = this->inputs[0].lock();
        auto new_node = make_shared<UnaryOpNode>(this->next(), data_node, std::move(_op));
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
        const auto op_hash = std::hash<string>{}(this->op->label);
        const auto data_hash = this->inputs[0].lock()->calc_hash();
        return op_hash + data_hash;
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<UnaryOpNode>(shared_from_this());
        visitor.visit(node);
    }

    string get_producer_expr(JavaScriptLifter &visitor) override;
};

} /// end of namespace

#endif //FUZZFLOW_UNARYOPNODE_H
