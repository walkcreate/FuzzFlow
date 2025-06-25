#ifndef FUZZFLOW_FIXEDNODE_H
#define FUZZFLOW_FIXEDNODE_H

#include "IRNode.h"

namespace FuzzFlow {

class AbstractBeginNode;

class FixedNode : virtual public IRNode
{
public:
    weak_ptr<FixedNode> predecessor;

    weak_ptr<AbstractBeginNode> get_begin_node();

    string get_neighbor_hash();
};

} /// end of namespace

#endif //FUZZFLOW_FIXEDNODE_H
