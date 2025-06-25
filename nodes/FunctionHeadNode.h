#ifndef FUZZFLOW_FUNCTIONHEADNODE_H
#define FUZZFLOW_FUNCTIONHEADNODE_H

#include "IRNode.h"
#include "FixedNode.h"
#include "AbstractBeginNode.h"
#include "ParameterNode.h"

#include "DataConsumerNode.h"

namespace FuzzFlow {

class FunctionHeadNode final : public AbstractBeginNode,
                               public DataConsumerNode
{
private:
    string name;

public:
    FunctionHeadNode(const string &name,
                     const vector<weak_ptr<ParameterNode>>& params,
                     const shared_ptr<FixedNode>& next)
        : AbstractBeginNode(next)
    {
        this->name = name;

        for (auto &param : params) {
            this->inputs.push_back(param);
        }
    }

    string get_label() override
    {
        return name;
    }

    void post_construct() override
    {
        this->UniSuccessorNode::post_construct();
        this->DataConsumerNode::post_construct();
    }

    vector<weak_ptr<ParameterNode>> get_params() const
    {
        vector<weak_ptr<ParameterNode>> _params;

        _params.reserve(this->inputs.size());

        for (auto &param : this->inputs) {
            _params.push_back(dynamic_pointer_cast<ParameterNode>(param.lock()));
        }

        return _params;
    }

    shared_ptr<IRNode> clone() override
    {
        auto head_next = dynamic_pointer_cast<FixedNode>(this->successor.lock());

        return make_shared<FunctionHeadNode>(this->name,
                                             this->get_params(),
                                             head_next);
    }

    void clone_repair(map<weak_ptr<IRNode>,
                          weak_ptr<IRNode>,
                              std::owner_less<>> &refNode2ownNode) override
    {
        ASSERT_OR_EXIT(refNode2ownNode.contains(this->successor));
        ASSERT_OR_EXIT(! refNode2ownNode[this->successor].expired());

        this->successor = dynamic_pointer_cast<FixedNode>(
            refNode2ownNode[this->successor].lock());

        ASSERT_OR_EXIT(this->successor.lock() != nullptr);

        auto params = get_params();

        for (int i = 0; i < params.size(); i++) {
            ASSERT_OR_EXIT(refNode2ownNode.contains(params[i]));
            ASSERT_OR_EXIT(! refNode2ownNode[params[i]].expired());

            this->inputs[i] = dynamic_pointer_cast<ParameterNode>(
                refNode2ownNode[params[i]].lock());

            ASSERT_OR_EXIT(this->inputs[i].lock() != nullptr);
        }

        this->post_construct();
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<FunctionHeadNode>(shared_from_this());
        visitor.visit(node);
    }

    void compute_hash_next() override {} /// node hash remains empty
};

} /// end of namespace

#endif //FUZZFLOW_FUNCTIONHEADNODE_H
