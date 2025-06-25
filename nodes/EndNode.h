#ifndef FUZZFLOW_ENDNODE_H
#define FUZZFLOW_ENDNODE_H

#include "IRNode.h"
#include "AbstractEndNode.h"
#include "EndMayMergeNode.h"

namespace FuzzFlow {

class EndNode final : public EndMayMergeNode {
private:
    static const string label;

public:
    EndNode() = default;

    string get_label() override
    {
        return EndNode::label;
    }

    shared_ptr<IRNode> clone() override
    {
        return make_shared<EndNode>();
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<EndNode>(shared_from_this());
        visitor.visit(node);
    }
};

} /// end of namespace

#endif //FUZZFLOW_ENDNODE_H
