#ifndef FUZZFLOW_MUOPCONCAT_H
#define FUZZFLOW_MUOPCONCAT_H

#include "../utils/common_using.h"

#include "MuOp.h"

namespace FuzzFlow {

class MuOpConcat : public MuOp {
public:
    MuOpConcat()
    {

    }

private:
    string initial_code;
};

}

#endif //FUZZFLOW_MUOPCONCAT_H
