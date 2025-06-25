#ifndef FUZZFLOW_ARRAYLITERAL_H
#define FUZZFLOW_ARRAYLITERAL_H

#include "../../js2graph/Graph.h"

#include "../LiteralNode.h"
#include "../DataConsumerNode.h"

/**
 * production rule about ArrayLiteral

singleExpression: arrayLiteral      # ArrayLiteralExpression

arrayLiteral
    : ('[' elementList ']')
    ;

elementList
    : ','* arrayElement? (','+ arrayElement)* ','* // Yes, everything is optional
    ;

arrayElement
    : Ellipsis? singleExpression
    ;
 */

namespace FuzzFlow {

class ArrayLiteralNode final : public LiteralNode,
                               public DataConsumerNode
{
private:
    static const string label;

public:
    explicit ArrayLiteralNode(const vector<weak_ptr<DataProducerNode>> &elements)
    {
        /// Data producers can all be considered as elements.
        /// This includes `StoreNode`, since assignment is an expression.
        /// The following code is valid:
        /// a = 0
        /// b = [a=1, 2, 3]
        /// The value of the array `b` will be [1, 2, 3].
        for (auto &elem: elements) {
            this->inputs.push_back(elem);
        }

        this->node_hash_current = label;
    }

    string get_label() override
    {
        return ArrayLiteralNode::label;
    }

    vector<weak_ptr<DataProducerNode>> elements()
    {
        return inputs;
    }

    shared_ptr<IRNode> clone() override
    {
        auto new_node = make_shared<ArrayLiteralNode>(this->elements());
        return new_node;
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<ArrayLiteralNode>(shared_from_this());
        visitor.visit(node);
    }

    string get_producer_expr(JavaScriptLifter &visitor) override;
};

} /// end of namespace

#endif //FUZZFLOW_ARRAYLITERAL_H
