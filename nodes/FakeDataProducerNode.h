#ifndef FUZZFLOW_FAKEDATAPRODUCERNODE_H
#define FUZZFLOW_FAKEDATAPRODUCERNODE_H

#include "../utils/common_using.h"

#include "DataProducerNode.h"

namespace FuzzFlow {

class FakeDataProducerNode final : public DataProducerNode {
private:
    static const string label;
public:
    FakeDataProducerNode()
    {
        this->uses = {};
    }

    string get_label () override
    {
        return FakeDataProducerNode::label;
    }

    shared_ptr<IRNode> clone() override
    {
        assert("clone FakeDataNode" && false);
        return nullptr;
    }

    void accept(GraphVisitor &visitor) override
    {
        assert("copy FakeCtrlNode" && false);

        throw std::runtime_error("Visiting FakeCtrlNode");
    }
};

}

#endif //FUZZFLOW_FAKEDATAPRODUCERNODE_H
