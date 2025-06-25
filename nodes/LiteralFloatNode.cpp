#include "LiteralFloatNode.h"

namespace FuzzFlow {

string LiteralFloatNode::get_producer_expr(JavaScriptLifter &visitor)
{
    return std::format("{:g}", this->get_value());
}

} /// end of namespace