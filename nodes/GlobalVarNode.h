#ifndef FUZZFLOW_GLOBALVARNODE_H
#define FUZZFLOW_GLOBALVARNODE_H

#include "TerminalNode.h"

namespace FuzzFlow {

class GlobalVarNode final : public TerminalNode {
public:
    string var_name;

    explicit GlobalVarNode(const string &var_name)
    {
        this->var_name = var_name;

        this->node_hash_current = var_name;
        this->node_hash_next = var_name;
    }

    string get_label() override
    {
        return "GlobalVar:" + var_name;
    }

    shared_ptr<IRNode> clone() override
    {
        auto new_node = make_shared<GlobalVarNode>(this->var_name);
        return new_node;
    }

    std::size_t calc_hash() override
    {
        return std::hash<string>{}(this->var_name);
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<GlobalVarNode>(shared_from_this());
        visitor.visit(node);
    }

    string get_producer_expr(JavaScriptLifter &visitor) override;
};

} /// end of namespace

#endif //FUZZFLOW_GLOBALVARNODE_H
