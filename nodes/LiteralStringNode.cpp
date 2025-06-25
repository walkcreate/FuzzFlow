#include "LiteralStringNode.h"

namespace FuzzFlow {

string LiteralStringNode::get_producer_expr(JavaScriptLifter &visitor)
{
    return this->get_value();
}

} /// end of namespace