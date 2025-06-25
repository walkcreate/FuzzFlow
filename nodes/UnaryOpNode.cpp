#include "UnaryOpNode.h"
#include "../js2graph/Graph.h"
#include "../graph2js/JavaScriptLifter.h"

namespace FuzzFlow {

string UnaryOpNode::get_producer_expr(JavaScriptLifter &visitor)
{
    data_node()->accept(visitor);
    const string data_node_code = visitor.visit_outcome;

    /// For operators like void and typeof, the space between the operator and the operand is essential.
    /// For operators like Plus (+) and Minus (-), the space is optional.
    auto producer_expr = op->code + " " + data_node_code;
    return producer_expr;
}

} /// end of namespace