#include "BinaryOpNode.h"
#include "../js2graph/Graph.h"
#include "../graph2js/JavaScriptLifter.h"

namespace FuzzFlow {

string BinaryOpNode::get_producer_expr(JavaScriptLifter &visitor)
{
    left()->accept(visitor);
    const string left_code = visitor.visit_outcome;

    right()->accept(visitor);
    const string right_code = visitor.visit_outcome;

    string producer_expr = left_code + " " + op->code + " " + right_code;
    return producer_expr;
}

} /// end of namespace