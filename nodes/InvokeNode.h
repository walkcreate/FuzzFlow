#ifndef FUZZFLOW_INVOKENODE_H
#define FUZZFLOW_INVOKENODE_H

#include <utility>

#include "IRNode.h"
#include "FixedNode.h"
#include "UniSuccessorNode.h"
#include "SequentialOperationNode.h"

#include "DataProducerNode.h"
#include "DataConsumerNode.h"

namespace FuzzFlow {

enum class InvokeType {
    CallFunction,
    NewInstance,
};

class InvokeNode final : public SequentialOperationNode,
                         public DataConsumerNode,
                         public DataProducerNode
{
private:
    string function_name;
    InvokeType invoke_type;

public:
    static const string label;

    InvokeNode(string _name,
               const vector<weak_ptr<DataProducerNode>> &args,
               const weak_ptr<FixedNode> &next,
               const InvokeType _type)
        : SequentialOperationNode(next),
        function_name(std::move(_name))
    {
        this->inputs = args;
        this->invoke_type = _type;

        this->node_hash_current = label;
    }

    string get_label() override
    {
        return InvokeNode::label + "::" + function_name;
    }

    vector<weak_ptr<DataProducerNode>> get_args()
    {
        return this->inputs;
    }

    string get_function_name()
    {
        return this->function_name;
    }

    InvokeType get_invoke_type() const
    {
        return this->invoke_type;
    }

    void post_construct() override
    {
        this->UniSuccessorNode::post_construct();
        this->DataConsumerNode::post_construct();
    }

    shared_ptr<IRNode> clone() override
    {
        auto node = make_shared<InvokeNode>(function_name,
                                            this->inputs,
                                            this->next(),
                                            this->invoke_type);
        return node;
    }

    void clone_repair(map<weak_ptr<IRNode>,
                          weak_ptr<IRNode>,
                            std::owner_less<>> &refNode2ownNode) override
    {
        this->UniSuccessorNode::clone_repair(refNode2ownNode);
        this->DataConsumerNode::clone_repair(refNode2ownNode);
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<InvokeNode>(shared_from_this());
        visitor.visit(node);
    }
};

} /// end of namespace

#endif //FUZZFLOW_INVOKENODE_H
