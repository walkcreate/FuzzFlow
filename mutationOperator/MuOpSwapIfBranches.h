#ifndef FUZZFLOW_MUOPSWAPIFBRANCHES_H
#define FUZZFLOW_MUOPSWAPIFBRANCHES_H

#include <memory>

using std::weak_ptr;
using std::string;

#include "MuOp.h"
#include "../nodes/IfNode.h"

namespace FuzzFlow {

class MuOpSwapIfBranches final : public MuOp {
public:
    explicit MuOpSwapIfBranches(const weak_ptr<IfNode> &if_node)
    {
        this->_node = if_node;
    }

    void undo() override
    {
        this->_node.lock()->swap_branches();
    }

private:
    weak_ptr<IfNode> _node;
};

} /// end of namespace

#endif //FUZZFLOW_MUOPSWAPIFBRANCHES_H
