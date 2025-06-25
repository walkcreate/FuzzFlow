#include "TernaryOpNode.h"
#include "../js2graph/Graph.h"
#include "../graph2js/JavaScriptLifter.h"

namespace FuzzFlow {

const string TernaryOpNode::label = "TernaryOp";

string TernaryOpNode::get_producer_expr(JavaScriptLifter &visitor)
{
    operand_1()->accept(visitor);
    const string operand_1_code = visitor.visit_outcome;

    operand_2()->accept(visitor);
    const string operand_2_code = visitor.visit_outcome;

    operand_3()->accept(visitor);
    const string operand_3_code = visitor.visit_outcome;

    auto producer_expr = operand_1_code + " ? " + operand_2_code + " : " + operand_3_code;
    return producer_expr;
}

}