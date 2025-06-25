#include "GlobalVarNode.h"

namespace FuzzFlow {

string GlobalVarNode::get_producer_expr(JavaScriptLifter &visitor)
{
    return this->var_name;
}

} /// end of namespace