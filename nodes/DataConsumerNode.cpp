#include "DataConsumerNode.h"

#include "DataProducerNode.h"

namespace FuzzFlow {

void DataConsumerNode::post_construct()
{
    auto node_self = dynamic_pointer_cast<DataConsumerNode>(shared_from_this());

    for (auto producer : inputs) {
        producer.lock()->uses.push_back(node_self);
    }
}

void DataConsumerNode::clone_repair(map<weak_ptr<IRNode>,
                                        weak_ptr<IRNode>,
                                            std::owner_less<>> &refNode2ownNode)
{
    for (auto &_input : inputs) {
        ASSERT_OR_EXIT(refNode2ownNode.contains(_input));
        ASSERT_OR_EXIT(! refNode2ownNode[_input].expired());

        auto real_node = refNode2ownNode.at(_input);
        _input = dynamic_pointer_cast<DataProducerNode>(real_node.lock());
    }

    this->DataConsumerNode::post_construct();
}

} /// end of namespace