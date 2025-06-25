#ifndef FUZZFLOW_MUOPDELETESEQUENTIALOPERATION_H
#define FUZZFLOW_MUOPDELETESEQUENTIALOPERATION_H

#include "MuOp.h"
#include "../nodes/SequentialOperationNode.h"
#include "../exceptions/MutateError.h"

namespace FuzzFlow {

class MuOpDeleteSequentialOperation final : public MuOp {
public:
    explicit MuOpDeleteSequentialOperation(const weak_ptr<SequentialOperationNode> &node)
    {
        this->_node = node;
    }

    void undo() override
    {
        const auto uni_node = this->_node.lock();
        const auto prev_node = uni_node->predecessor.lock();
        const auto next_node = uni_node->next();
        const auto prev_uni_node = dynamic_pointer_cast<UniSuccessorNode>(prev_node);

        if (prev_uni_node == nullptr) {
            throw MutateError("The deleting mutator has remove a node whose prev is not a uni");
        }

        /// recover the pred and succ
        prev_uni_node->successor = uni_node;
        next_node->predecessor = uni_node;
    }
private:
    weak_ptr<SequentialOperationNode> _node;
};

} /// end of namespace

#endif //FUZZFLOW_MUOPDELETESEQUENTIALOPERATION_H
