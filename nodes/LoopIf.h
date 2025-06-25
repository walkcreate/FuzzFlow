#ifndef FUZZFLOW_LOOPIF_H
#define FUZZFLOW_LOOPIF_H

#include "IfNode.h"

/// The LoopIf is same as IfNode totally.
/// We create the class to express that LoopIf is the if node used in Loop
/// The type information is all we need.
/// In other words, this is an alias.

namespace FuzzFlow {

class DataProducerNode;

class LoopIf final : public IfNode {
private:
    static const string label;
public:
    LoopIf(const weak_ptr<DataProducerNode>& condition,
           const weak_ptr<FixedNode>& b_then,
           const weak_ptr<FixedNode>& b_else)
           : IfNode(condition, b_then, b_else)
    {}


    string get_label() override
    {
        return label;
    }

    shared_ptr<IRNode> clone() override
    {
        auto new_node = make_shared<LoopIf>(this->condition(),
            this->branch_true(),
            this->branch_false());

        return new_node;
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<LoopIf>(shared_from_this());
        visitor.visit(node);
    }
};

} /// namespace FuzzFlow

#endif //FUZZFLOW_LOOPIF_H
