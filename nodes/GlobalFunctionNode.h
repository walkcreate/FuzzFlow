#ifndef FUZZFLOW_GLOBALFUNCTIONNODE_H
#define FUZZFLOW_GLOBALFUNCTIONNODE_H

#include "TerminalNode.h"

namespace FuzzFlow {

class GlobalFunctionNode final : public TerminalNode {
public:
    string function_name;

    explicit GlobalFunctionNode(const string &function_name)
    {
        this->function_name = function_name;

        this->node_hash_current = function_name;
        this->node_hash_next = function_name;
    }

    string get_label() override
    {
        return "GlobalFunction:" + function_name;
    }

    shared_ptr<IRNode> clone() override
    {
        auto new_node = make_shared<GlobalFunctionNode>(this->function_name);
        return new_node;
    }

    std::size_t calc_hash() override
    {
        return std::hash<string>{}(this->function_name);
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<GlobalFunctionNode>(shared_from_this());
        visitor.visit(node);
    }

    string get_producer_expr(JavaScriptLifter &visitor) override;
};

} /// end of namespace

#endif //FUZZFLOW_GLOBALFUNCTIONNODE_H
