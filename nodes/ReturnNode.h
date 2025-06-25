#ifndef FUZZFLOW_RETURNNODE_H
#define FUZZFLOW_RETURNNODE_H

#include "IRNode.h"
#include "AbstractEndNode.h"

#include "DataProducerNode.h"
#include "DataConsumerNode.h"

namespace FuzzFlow {

class ReturnNode final : public AbstractEndNode,
                         public DataConsumerNode
{
private:
    static const string label;

public:
    /// the inputs member is empty.

    ReturnNode()
    {
        this->node_hash_current = label;
    }

    string get_label() override
    {
        return ReturnNode::label;
    }

    explicit ReturnNode(const weak_ptr<DataProducerNode> &return_value)
    {
        this->inputs.push_back(return_value);
    }

    /// The return value may be empty.
    optional<shared_ptr<DataProducerNode>> return_value() const
    {
        if (! this->inputs.empty()) {
            return this->inputs[0].lock();
        }

        return {};
    }

    ~ReturnNode() override = default;

    void set_value(const shared_ptr<ReturnNode>& node_self,
                   const weak_ptr<DataProducerNode>& _return_value)
    {
        this->inputs.clear();
        this->inputs.push_back(_return_value);

        if (! this->inputs.empty()) {
            this->inputs[0].lock()->uses.push_back(node_self);
        }
    }

    shared_ptr<IRNode> clone() override
    {
        shared_ptr<ReturnNode> new_node;

        if (! this->inputs.empty()) {
            new_node = make_shared<ReturnNode>(this->inputs[0]);
        }
        else {
            new_node = make_shared<ReturnNode>();
        }

        return new_node;
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<ReturnNode>(shared_from_this());
        visitor.visit(node);
    }
};

} /// end of namespace

#endif //FUZZFLOW_RETURNNODE_H
