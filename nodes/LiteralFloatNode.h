#ifndef FUZZFLOW_LITERALFLOATNODE_H
#define FUZZFLOW_LITERALFLOATNODE_H

#include "IRNode.h"
#include "TerminalNode.h"
#include "LiteralNode.h"

/// for std::stringstream and setprecision
#include <iomanip>

#include "LiteralNode.h"

namespace FuzzFlow {

class LiteralFloatNode final : public TerminalNode,
                               public LiteralNode
{
public:
    float value;

    explicit LiteralFloatNode(float value)
    {
        this->value = value;
        this->node_hash_current = std::to_string(value);
        this->node_hash_next = std::to_string(value);
    }

    ~LiteralFloatNode() override = default;

    string get_label() override
    {
        const string value_str = std::format("{:g}", value);
        return "Literal float(" + value_str + ")";
    }

    shared_ptr<IRNode> clone() override
    {
        auto new_node = make_shared<LiteralFloatNode>(this->value);
        return new_node;
    }

    std::size_t calc_hash() override
    {
        return std::hash<float>{}(this->value);
    }

    float get_value() const
    {
        return this->value;
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<LiteralFloatNode>(shared_from_this());
        visitor.visit(node);
    }

    string get_producer_expr(JavaScriptLifter &visitor) override;
};

} /// end of namespace

#endif //FUZZFLOW_LITERALFLOATNODE_H
