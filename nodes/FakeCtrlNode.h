#ifndef FUZZFLOW_FAKECTRLNODE_H
#define FUZZFLOW_FAKECTRLNODE_H

#include <stdexcept>

#include "../utils/common_using.h"

#include "IRNode.h"

namespace FuzzFlow {

class FakeCtrlNode final: public FixedNode {
private:
    static const string label;

public:
    FakeCtrlNode() = default;

    shared_ptr<IRNode> clone() override
    {
        assert(false);

        throw std::runtime_error("Cloning FakeCtrlNode");

        return nullptr;
    }

    void accept(GraphVisitor &visitor) override
    {
        assert("copy FakeCtrlNode" && false);

        throw std::runtime_error("Visiting FakeCtrlNode");
    }
};

} /// end of namespace

#endif //FUZZFLOW_FAKECTRLNODE_H
