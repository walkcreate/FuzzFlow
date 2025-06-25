#ifndef FUZZFLOW_DATACONSUMERNODE_H
#define FUZZFLOW_DATACONSUMERNODE_H

#include "DataProducerNode.h"
#include "../utils/common_using.h"

#include "IRNode.h"

namespace FuzzFlow {

class DataProducerNode;

class DataConsumerNode : virtual public IRNode
{
public:
    vector<weak_ptr<DataProducerNode>> inputs;

    virtual void post_construct();

    void clone_repair(map<weak_ptr<IRNode>,
                          weak_ptr<IRNode>,
                            std::owner_less<>> &refNode2ownNode) override;

    shared_ptr<DataProducerNode> get_input(const unsigned int index) const
    {
        auto node = this->inputs[index].lock();
        return node;
    }

    std::size_t calc_hash() override
    {
        std::size_t result = 0;

        for (auto &input : this->inputs) {
            result += input.lock()->calc_hash();
        }

        return result;
    }

    string get_neighbor_hash() const
    {
        string result;

        for (auto &input : this->inputs) {
            result += input.lock()->node_hash_current;
        }

        return result;
    }
};

} /// end of namespace FuzzFlow

#endif //FUZZFLOW_DATACONSUMERNODE_H
