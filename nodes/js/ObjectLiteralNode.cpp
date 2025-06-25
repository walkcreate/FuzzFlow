#include "ObjectLiteralNode.h"
#include "../../js2graph/Graph.h"
#include "../../graph2js/JavaScriptLifter.h"

namespace FuzzFlow {

const string ObjectLiteralNode::label = "ObjectLiteral";

string ObjectLiteralNode::get_producer_expr(JavaScriptLifter &visitor)
{
    string object_literal_code = "{";

    for (const auto& prop_assign_node : prop_expr_assignments())
    {
        prop_assign_node->accept(visitor);
        string prop_pair = visitor.visit_outcome;
        object_literal_code += prop_pair + ",";
    }

    for (const auto& func_prop_node : function_properties())
    {
        func_prop_node->accept(visitor);
        string prop_pair = visitor.visit_outcome;
        object_literal_code += prop_pair + ",";
    }

    object_literal_code += "}";

    return object_literal_code;
}

} /// end of namespace