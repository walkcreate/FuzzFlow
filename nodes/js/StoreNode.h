#ifndef FUZZFLOW_STORENODE_H
#define FUZZFLOW_STORENODE_H

#include "../IRNode.h"
#include "../SequentialOperationNode.h"
#include "AccessObjectNode.h"

namespace FuzzFlow {

class StoreNode final : public AccessObjectNode,
                        public SequentialOperationNode
{
private:
    static const string label;

public:
    StoreNode(const weak_ptr<FixedNode> &next,
              const weak_ptr<DataProducerNode> &object,
              const weak_ptr<DataProducerNode> &property_name_or_index,
              const weak_ptr<DataProducerNode> &new_value,
              const ObjectAccessType _access_type)
        : SequentialOperationNode(next)
    {
        this->inputs = {object, property_name_or_index, new_value};
        this->access_type = _access_type;

        this->node_hash_current = label;
    }

    string get_label() override
    {
        return StoreNode::label;
    }

    void post_construct() override
    {
        this->DataConsumerNode::post_construct();

        this->UniSuccessorNode::post_construct();
    }

    shared_ptr<DataProducerNode> new_value() const
    {
        return this->inputs[2].lock();
    }

    shared_ptr<IRNode> clone() override
    {
        return make_shared<StoreNode>(this->next(),
                                      this->object(),
                                      this->property(),
                                      this->new_value(),
                                      this->access_type);
    }

    void clone_repair(map<weak_ptr<IRNode>,
                          weak_ptr<IRNode>,
                            std::owner_less<>>& refNode2ownNode) override
    {
        this->DataConsumerNode::clone_repair(refNode2ownNode);

        this->UniSuccessorNode::clone_repair(refNode2ownNode);
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<StoreNode>(shared_from_this());
        visitor.visit(node);
    }
};

} /// end of namespace


#endif //FUZZFLOW_STORENODE_H
