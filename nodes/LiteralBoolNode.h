#ifndef FUZZFLOW_LITERALBOOLNODE_H
#define FUZZFLOW_LITERALBOOLNODE_H

#include "IRNode.h"
#include "LiteralNode.h"
#include "TerminalNode.h"

namespace FuzzFlow {

class LiteralBoolNode final : public TerminalNode,
                              public LiteralNode
{
public:
    bool value;

    explicit LiteralBoolNode(const bool value)
    {
        this->value = value;

        this->node_hash_current = std::to_string(value);
        this->node_hash_next = std::to_string(value);
    }

    string get_label() override
    {
        return "Literal Bool(" + std::format("{}", value) + ")";
    }

    ~LiteralBoolNode() override = default;

    shared_ptr<IRNode> clone() override
    {
        auto new_node = make_shared<LiteralBoolNode>(this->value);
        return new_node;
    }

    std::size_t calc_hash() override
    {
        return std::hash<bool>{}(this->value);
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<LiteralBoolNode>(shared_from_this());
        visitor.visit(node);
    }

    string get_producer_expr(JavaScriptLifter &visitor) override;
};

} /// end of namespace

#endif //FUZZFLOW_LITERALBOOLNODE_H
