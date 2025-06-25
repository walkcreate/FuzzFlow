#ifndef FUZZFLOW_INSTANCEMETHOD_H
#define FUZZFLOW_INSTANCEMETHOD_H

#include "../../utils/common_using.h"

namespace FuzzFlow {

class InstanceMethod {
public:
    string name;
    //unsigned int param_count;
    vector<unsigned int> param_count;

    InstanceMethod(const string &name, const unsigned int param_count)
    {
        this->name = name;
        this->param_count.push_back(param_count);
    }

    InstanceMethod(const string &name, const vector<unsigned int> &param_count)
    {
        this->name = name;
        this->param_count = param_count;
    }

    bool operator<(const InstanceMethod& other) const
    {
        return std::tie(name, param_count) < std::tie(other.name, other.param_count);
    }
};

}

#endif //FUZZFLOW_INSTANCEMETHOD_H
