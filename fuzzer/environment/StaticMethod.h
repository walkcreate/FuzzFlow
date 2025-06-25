#ifndef FUZZFLOW_STATICMETHOD_H
#define FUZZFLOW_STATICMETHOD_H

#include "../../utils/common_using.h"

namespace FuzzFlow {

class StaticMethod {
public:
    string name;
    vector<unsigned int> param_count;

    StaticMethod(const string &name, const unsigned int param_count)
    {
        this->name = name;
        this->param_count.push_back(param_count);
    }

    StaticMethod(const string &name, const vector<unsigned int> &param_count)
    {
        this->name = name;
        this->param_count = param_count;
    }

    bool operator<(const StaticMethod& other) const
    {
        return std::tie(name, param_count) < std::tie(other.name, other.param_count);
    }
};

} /// end of namespace

#endif //FUZZFLOW_STATICMETHOD_H
