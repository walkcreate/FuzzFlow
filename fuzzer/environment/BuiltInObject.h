#ifndef FUZZFLOW_BUILTINOBJECT_H
#define FUZZFLOW_BUILTINOBJECT_H

#include "../../utils/common_using.h"

#include "Constructor.h"
#include "StaticMethod.h"
#include "InstanceMethod.h"

namespace FuzzFlow {

class BuiltInObject {
public:
    string name;
    Constructor constructor;
    set<StaticMethod> static_methods;
    set<InstanceMethod> instance_methods;

    BuiltInObject(const string &name,
                  const Constructor &_constructor,
                  const set<StaticMethod> &_static_methods,
                  const set<InstanceMethod> &_instance_methods)
        : constructor(_constructor)
    {
        this->name = name;
        this->static_methods = _static_methods;
        this->instance_methods = _instance_methods;
    }
};

} /// end of namespace

#endif //FUZZFLOW_BUILTINOBJECT_H
