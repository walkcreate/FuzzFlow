#ifndef CATCHIDNODE_H
#define CATCHIDNODE_H

#include "../TerminalNode.h"

namespace FuzzFlow {

class CatchIdNode final : public TerminalNode {
private:
    static const string label;

public:
    explicit CatchIdNode(const string &name)
    {
        this->name = name;

        this->node_hash_current = label;
    }

    string get_label() override
    {
        return CatchIdNode::label;
    }

    shared_ptr<IRNode> clone() override
    {
        return make_shared<CatchIdNode>(this->name);
    }

    string get_id_name()
    {
        return this->name;
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<CatchIdNode>(shared_from_this());
        visitor.visit(node);
    }

private:
    string name;
};

} /// end of namespace

#endif //CATCHIDNODE_H
