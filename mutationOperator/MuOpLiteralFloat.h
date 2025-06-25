#ifndef FUZZFLOW_MUOPLITERALFLOAT_H
#define FUZZFLOW_MUOPLITERALFLOAT_H

#include <memory>
using std::weak_ptr;

#include "MuOp.h"
#include "../nodes/LiteralFloatNode.h"

namespace FuzzFlow {

class MuOpLiteralFloat final : public MuOp  {
public:
    MuOpLiteralFloat(const weak_ptr<LiteralFloatNode> &node,
                      const float pre_value)
    {
        this->node = node;
        this->pre_value = pre_value;
    }

    void undo() override
    {
        const auto node_s = node.lock();
        node_s->value = pre_value;
    }

private:
    float pre_value;

    weak_ptr<LiteralFloatNode> node;
};

} /// end of namespace

#endif //FUZZFLOW_MUOPLITERALFLOAT_H
