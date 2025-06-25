#include "GlobalFunctionNode.h"

namespace FuzzFlow {

string GlobalFunctionNode::get_producer_expr(JavaScriptLifter &visitor)
{
    return this->function_name;
}

} /// end of namespace