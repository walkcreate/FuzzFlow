#ifndef FUZZFLOW_SYMKIND_H
#define FUZZFLOW_SYMKIND_H

namespace FuzzFlow {

enum class SymKind {
    Variable,
    Function,
    Class,
    Interface,
    Parameter,
    Prog,
    Unknown // parameter of function args
};

}

#endif //FUZZFLOW_SYMKIND_H
