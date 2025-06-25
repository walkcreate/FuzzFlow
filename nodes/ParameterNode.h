#ifndef FUZZFLOW_PARAMETERNODE_H
#define FUZZFLOW_PARAMETERNODE_H

#include "TerminalNode.h"

namespace FuzzFlow {

class ParameterNode final : public TerminalNode {
public:
    explicit ParameterNode(const string &name)
    {
        this->name = name;

        this->node_hash_current = get_label();
        this->node_hash_next = get_label();
    }

    string get_label() override
    {
        return "P(" + this->name + ")";
    };

    shared_ptr<IRNode> clone() override
    {
        auto new_node = make_shared<ParameterNode>(this->name);
        return new_node;
    }

    string get_parameter_name()
    {
        return this->name;
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<ParameterNode>(shared_from_this());
        visitor.visit(node);
    }

private:
    string name;
};

} /// end of namespace

#endif //FUZZFLOW_PARAMETERNODE_H
