#include "ArrayLiteralNode.h"
#include "../../js2graph/Graph.h"
#include "../../graph2js/JavaScriptLifter.h"

namespace FuzzFlow {

const string ArrayLiteralNode::label = "ArrayLiteral";

string ArrayLiteralNode::get_producer_expr(JavaScriptLifter &visitor)
{
    string array_literal_code = "[";

    for (auto& element_node : elements()) {
        element_node.lock()->accept(visitor);
        string element_s = visitor.visit_outcome;

        array_literal_code += element_s + ",";
    }

    array_literal_code += "]";
    return array_literal_code;
}

} /// end of namespace