#include "ForInPropName.h"

namespace FuzzFlow {

const string ForInPropName::label = "ForInPropName";

string ForInPropName::get_producer_expr(JavaScriptLifter &visitor)
{
    return this->prop_name;
}

}