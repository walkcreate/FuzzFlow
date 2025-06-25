#ifndef FUZZFLOW_BEGINNODE_H
#define FUZZFLOW_BEGINNODE_H

#include "IRNode.h"
#include "FixedNode.h"
#include "AbstractBeginNode.h"
#include "../visitors/GraphVisitor.h"

namespace FuzzFlow {

class BeginNode final : public AbstractBeginNode {
private:
    static const string label;

public:
    explicit BeginNode(const weak_ptr<FixedNode>& next)
        : AbstractBeginNode(next)
    {
        this->node_hash_current = label;
    }

    string get_label() override
    {
        return BeginNode::label;
    }

    shared_ptr<IRNode> clone() override
    {
        return make_shared<BeginNode>(this->next());
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<BeginNode>(shared_from_this());
        visitor.visit(node);
    }
};

} /// end of namespace

#endif //FUZZFLOW_BEGINNODE_H
