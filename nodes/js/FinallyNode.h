#ifndef FUZZFLOW_FINALLYNODE_H
#define FUZZFLOW_FINALLYNODE_H

#include "../AbstractMergeNode.h"

namespace FuzzFlow {

class FinallyNode final : public AbstractBeginNode {
private:
    static const string label;

public:
    explicit FinallyNode(const weak_ptr<FixedNode> &next)
        : AbstractBeginNode(next)
    {
        this->node_hash_current = label;
    }

    string get_label() override
    {
        return FinallyNode::label;
    }

    shared_ptr<IRNode> clone() override {
        return make_shared<FinallyNode>(this->next());
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<FinallyNode>(shared_from_this());
        visitor.visit(node);
    }
};

}

#endif //FUZZFLOW_FINALLYNODE_H
