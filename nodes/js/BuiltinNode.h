#ifndef FUZZFLOW_BUILTINNODE_H
#define FUZZFLOW_BUILTINNODE_H

#include "../IRNode.h"
#include "../TerminalNode.h"

namespace FuzzFlow {

class BuiltinNode final : public TerminalNode {
public:
    explicit BuiltinNode(const string &name)
    {
        this->name = name;

        this->node_hash_current = name;
    }

    string get_label() override
    {
        return this->name;
    }

    shared_ptr<IRNode> clone() override
    {
        auto new_node = make_shared<BuiltinNode>(this->name);
        return new_node;
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<BuiltinNode>(shared_from_this());
        visitor.visit(node);
    }

private:
    string name;
};

} /// end of namespace

#endif //FUZZFLOW_BUILTINNODE_H
