#include "LiteralBoolNode.h"

namespace FuzzFlow {

string LiteralBoolNode::get_producer_expr(JavaScriptLifter &visitor)
{
    return std::format("{}", this->value);
}

} /// end of namespace