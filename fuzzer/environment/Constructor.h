#ifndef FUZZFLOW_CONSTRUCTOR_H
#define FUZZFLOW_CONSTRUCTOR_H

#include "../../utils/common_using.h"

namespace FuzzFlow {

class Constructor {
public:
    unsigned int parameter_num;

    explicit Constructor(unsigned int num)
    {
        parameter_num = num;
    }
};

} /// end of namespace

#endif //FUZZFLOW_CONSTRUCTOR_H
