#ifndef FUZZFLOW_INVOKEMETHODNODE_H
#define FUZZFLOW_INVOKEMETHODNODE_H

#include "SequentialOperationNode.h"
#include "DataProducerNode.h"
#include "DataConsumerNode.h"
#include "./js/LoadNode.h"

namespace FuzzFlow {

class InvokeMethodNode final : public SequentialOperationNode,
                               public DataProducerNode,
                               public DataConsumerNode
{
private:
    static const string label;
    weak_ptr<LoadNode> load_node;

public:
    InvokeMethodNode(const weak_ptr<LoadNode> &load_node,
                     const vector<weak_ptr<DataProducerNode>> &args,
                     const weak_ptr<FixedNode> &next)
                         : SequentialOperationNode(next)
    {
        this->inputs.push_back(load_node);

        for (const auto &arg : args) {
            this->inputs.push_back(arg);
        }

        this->node_hash_current = label;
    }

    /// used in clone
    InvokeMethodNode(const vector<weak_ptr<DataProducerNode>> &inputs, /// inputs : {load_node, args}
                     const weak_ptr<FixedNode> &next)
                         : SequentialOperationNode(next)
    {
        this->inputs = inputs;
    }

    string get_label() override
    {
        return InvokeMethodNode::label;
    }

    shared_ptr<IRNode> clone() override
    {
        return make_shared<InvokeMethodNode>(this->inputs, this->successor);
    }

    void post_construct() override
    {
        this->UniSuccessorNode::post_construct();
        this->DataConsumerNode::post_construct();
    }

    void clone_repair(map<weak_ptr<IRNode>, weak_ptr<IRNode>, std::owner_less<>> &refNode2ownNode) override
    {
        this->UniSuccessorNode::clone_repair(refNode2ownNode);
        this->DataConsumerNode::clone_repair(refNode2ownNode);
    }

    shared_ptr<LoadNode> get_load_node() const
    {
        auto load_node = dynamic_pointer_cast<LoadNode>(this->inputs[0].lock());
        return load_node;
    }

    vector<weak_ptr<DataProducerNode>> get_args () const
    {
        vector<weak_ptr<DataProducerNode>> args;

        if (this->inputs.size() >= 2) {
            for (int i = 1; i < this->inputs.size(); i++) {
                args.push_back(this->inputs[i]);
            }
        }

        return args;
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<InvokeMethodNode>(shared_from_this());
        visitor.visit(node);
    }
};

} /// end of namespace


#endif //FUZZFLOW_INVOKEMETHODNODE_H
