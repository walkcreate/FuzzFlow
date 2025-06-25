#ifndef FUZZFLOW_ENDMAYMERGENODE_H
#define FUZZFLOW_ENDMAYMERGENODE_H

#include "AbstractEndNode.h"

namespace FuzzFlow {

class AbstractMergeNode;

class EndMayMergeNode : public AbstractEndNode {
public:
    weak_ptr<AbstractMergeNode> merge_node;
};

} /// end of namespace

#endif //FUZZFLOW_ENDMAYMERGENODE_H
