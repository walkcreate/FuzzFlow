#ifndef FUZZFLOW_MUOPBINARYOP_H
#define FUZZFLOW_MUOPBINARYOP_H

#include "../utils/common_using.h"

#include "MuOp.h"
#include "../nodes/BinaryOpNode.h"

namespace FuzzFlow {

class MuOpBinaryOp final : public MuOp {
public:

    MuOpBinaryOp(const weak_ptr<BinaryOpNode> &node,
        shared_ptr<LanguageOperator> pre_op)
    {
        this->node = node;
        this->pre_op = std::move(pre_op);
    }

    void undo() override
    {
        const auto node_s = node.lock();
        node_s->op = std::move(this->pre_op);
    }

private:
    shared_ptr<LanguageOperator> pre_op;

    weak_ptr<BinaryOpNode> node;
};

} /// end of namespace


#endif //FUZZFLOW_MUOPBINARYOP_H
