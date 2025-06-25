#ifndef FUZZFLOW_LOADNODE_H
#define FUZZFLOW_LOADNODE_H

#include "AccessObjectNode.h"
#include "../FixedNode.h"
#include "../SequentialOperationNode.h"

namespace FuzzFlow {

class LoadNode final : public DataProducerNode,
                       public AccessObjectNode,
                       public SequentialOperationNode
{
private:
    static const string label;

public:
    LoadNode(const weak_ptr<DataProducerNode>& object,
             const weak_ptr<DataProducerNode>& property_or_index,
             const weak_ptr<FixedNode> &next,
             const ObjectAccessType _loadType)
        : SequentialOperationNode(next)
    {
        this->inputs = {object, property_or_index};
        this->access_type = _loadType;

        this->node_hash_current = this->label;
    }

    string get_label() override
    {
        return LoadNode::label;
    }

    void post_construct() override
    {
        this->DataConsumerNode::post_construct();
        this->UniSuccessorNode::post_construct();
    }

    shared_ptr<IRNode> clone() override
    {
        return make_shared<LoadNode>(this->object(),
                                     this->property(),
                                     this->next(),
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
        auto node = dynamic_pointer_cast<LoadNode>(shared_from_this());
        visitor.visit(node);
    }
};

} /// end of namespace


#endif //FUZZFLOW_LOADNODE_H
