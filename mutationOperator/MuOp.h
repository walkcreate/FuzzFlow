#ifndef FUZZFLOW_MUOP_H
#define FUZZFLOW_MUOP_H

namespace FuzzFlow {

///
/// Why design the MuOp class?
///
/// To improve efficiency, the mutation process does not start by copying the entire graph.
/// Instead, mutations are applied directly to the original graph while recording the operations performed.
/// After the mutation, the undo method is used to restore the original graph.
///
class MuOp {
public:
    /// virtual destructor is necessary
    virtual ~MuOp() = default;

    virtual void undo() = 0;
};

} /// end of namespace

#endif //FUZZFLOW_MUOP_H
