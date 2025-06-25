#ifndef FUZZFLOW_THISNODE_H
#define FUZZFLOW_THISNODE_H

#include "../../utils/common_using.h"

#include "../IRNode.h"

#include "../DataProducerNode.h"

namespace FuzzFlow {

class ThisNode final : public DataProducerNode {
private:
    static const string label;

public:
    ThisNode()
    {
        this->node_hash_current = label;
        this->node_hash_next = label;
    }

    shared_ptr<IRNode> clone() override
    {
        auto new_node = make_shared<ThisNode>();
        return new_node;
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<ThisNode>(shared_from_this());
        visitor.visit(node);
    }
};

} /// end of namespace

#endif //FUZZFLOW_THISNODE_H
