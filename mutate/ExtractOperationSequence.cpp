#include "ExtractOperationSequence.h"

namespace FuzzFlow {

bool ExtractOperationSequence::is_literal_node(const shared_ptr<DataProducerNode> &producer)
{
    if (dynamic_pointer_cast<LiteralBoolNode>(producer) != nullptr) {
        return true;
    }

    if (dynamic_pointer_cast<LiteralFloatNode>(producer) != nullptr) {
        return true;
    }

    if (dynamic_pointer_cast<LiteralStringNode>(producer) != nullptr) {
        return true;
    }

    if (dynamic_pointer_cast<ArrayLiteralNode>(producer) != nullptr) {
        return true;
    }

    if (dynamic_pointer_cast<ObjectLiteralNode>(producer) != nullptr) {
        return true;
    }

    return false;
}

bool ExtractOperationSequence::is_valid_producer(const shared_ptr<DataProducerNode> &producer) const
{
    if (! is_literal_node(producer)) {
        return false;
    }

    if (! valid_producers.contains(producer)) {
        return false;
    }

    return true;
}

void ExtractOperationSequence::add2sequence(const shared_ptr<SequentialOperationNode>& operation_node)
{
    if (current_sequence_head == nullptr) {
        sequences.push_back(make_shared<OperationSequence>());
        current_sequence_head = operation_node;
    }
    sequences.back()->nodes.push_back(operation_node);

    if (const auto producer = dynamic_pointer_cast<DataProducerNode>(operation_node)) {
        valid_producers.insert(producer);
    }
}

void ExtractOperationSequence::finish_sequence()
{
    current_sequence_head = nullptr;
    valid_producers.clear();
}

void ExtractOperationSequence::handler(const weak_ptr<FixedNode>& current_node)
{
    if (auto operation_node = dynamic_pointer_cast<SequentialOperationNode>(current_node.lock());
        operation_node != nullptr)
    {
        if (auto consumer = dynamic_pointer_cast<DataConsumerNode>(operation_node);
            consumer != nullptr)
        {
            for (int i = 0; i < consumer->inputs.size(); i++) {
                if (! is_valid_producer(consumer->inputs[i].lock())) {
                    if (current_sequence_head != nullptr) {
                        finish_sequence();
                    }
                    return;
                }
            }

            add2sequence(operation_node);
        }
        else {
            add2sequence(operation_node);
        }
    }
    else {
        if (current_sequence_head != nullptr) {
            finish_sequence();
        }
    }
}

} // FuzzFlow