#ifndef FUZZFLOW_MUOPFLOATINGNODEINPUT_H
#define FUZZFLOW_MUOPFLOATINGNODEINPUT_H

#include <memory>
using std::weak_ptr;

#include "MuOp.h"

namespace FuzzFlow {

class MuOpConsumerInput final : public MuOp {
public:
    MuOpConsumerInput(const weak_ptr<DataConsumerNode> &_consumer,
                      const unsigned int input_index,
                      const weak_ptr<DataProducerNode> &_pre_input,
                      const weak_ptr<DataProducerNode> &_new_input)
    {
        this->consumer = _consumer;
        this->input_index = input_index;
        this->pre_input = _pre_input;
        this->new_input = _new_input;
    }

    void undo() override
    {
        const auto node_s = this->consumer.lock();

        node_s->inputs[input_index] = pre_input;

        new_input.lock()->uses.pop_back();
    }

private:
    weak_ptr<DataConsumerNode> consumer;

    unsigned int input_index;

    weak_ptr<DataProducerNode> pre_input;

    weak_ptr<DataProducerNode> new_input;
};

} /// end of namespace

#endif //FUZZFLOW_MUOPFLOATINGNODEINPUT_H
