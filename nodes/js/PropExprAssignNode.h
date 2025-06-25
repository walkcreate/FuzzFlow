#ifndef FUZZFLOW_PROPEXPRASSIGNNODE_H
#define FUZZFLOW_PROPEXPRASSIGNNODE_H

#include "../DataProducerNode.h"
#include "../DataConsumerNode.h"

namespace FuzzFlow {

class PropExprAssignNode : public DataProducerNode,
                           public DataConsumerNode
{
private:
    static const string label;

public:
    PropExprAssignNode(const weak_ptr<DataProducerNode> &property_name,
                       const weak_ptr<DataProducerNode> &property_value)
    {
        this->inputs.push_back(property_name);
        this->inputs.push_back(property_value);
        this->node_hash_current = label;
    }

    string get_label() override
    {
        return PropExprAssignNode::label;
    }

    shared_ptr<DataProducerNode> property_name() const
    {
        return this->inputs[0].lock();
    }

    void set_property_name(const weak_ptr<DataProducerNode> &property_name)
    {
        this->inputs[0] = property_name;
    }

    shared_ptr<DataProducerNode> property_value() const
    {
        return this->inputs[1].lock();
    }

    /// todo: delete
    void set_property_value(const weak_ptr<DataProducerNode> &property_value)
    {
        this->inputs[1] = property_value;
    }

    shared_ptr<IRNode> clone() override
    {
        auto new_node = make_shared<PropExprAssignNode>(this->property_name(), this->property_value());

        return new_node;
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<PropExprAssignNode>(shared_from_this());
        visitor.visit(node);
    }
};

} /// end of namespace

#endif //FUZZFLOW_PROPEXPRASSIGNNODE_H
