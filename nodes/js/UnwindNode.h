#ifndef FUZZFLOW_UNWINDNODE_H
#define FUZZFLOW_UNWINDNODE_H

#include "../DataConsumerNode.h"
#include "../EndWontMergeNode.h"

namespace FuzzFlow {

class DataProducerNode;

/// When there is no catch in the function,
/// we use unwind node to propagate the exception
///
class UnwindNode final : public EndWontMergeNode,
                         public DataConsumerNode
{
private:
    static const string label;

public:
    explicit UnwindNode(const weak_ptr<DataProducerNode> &exception_node)
    {
        this->inputs = {exception_node};
        this->node_hash_current = label;
        this->node_hash_next = label;
    }

    string get_label() override
    {
        return UnwindNode::label;
    }

    shared_ptr<DataProducerNode> exception_node() const
    {
        return this->inputs[0].lock();
    }

    shared_ptr<IRNode> clone() override
    {
        return make_shared<UnwindNode>(this->exception_node());
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<UnwindNode>(shared_from_this());
        visitor.visit(node);
    }
};

} /// end of namespace

#endif //FUZZFLOW_UNWINDNODE_H
