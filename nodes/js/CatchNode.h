#ifndef FUZZFLOW_CATCHNODE_H
#define FUZZFLOW_CATCHNODE_H

#include "../AbstractMergeNode.h"
#include "../DataConsumerNode.h"
#include "../EndMayMergeNode.h"
#include "CatchIdNode.h"

namespace FuzzFlow {

class CatchNode final : public AbstractBeginNode
{
private:
    static const string label;

public:
    optional<weak_ptr<CatchIdNode>> opt_catch_id_node;

    explicit CatchNode(const weak_ptr<FixedNode> &next)
        : AbstractBeginNode(next)
    {
        this->node_hash_current = label;
    }

    string get_label() override
    {
        return label;
    }

    void set_catch_id(const weak_ptr<CatchIdNode> &catch_id)
    {
        this->opt_catch_id_node = catch_id;
    }

    shared_ptr<IRNode> clone() override
    {
        auto node =  make_shared<CatchNode>(this->next());

        if (opt_catch_id_node.has_value()) {
            node->opt_catch_id_node = opt_catch_id_node;
        }

        return node;
    }

    void clone_repair(map<weak_ptr<IRNode>,
                      weak_ptr<IRNode>,
                        std::owner_less<>>& refNode2ownNode) override
    {
        this->UniSuccessorNode::clone_repair(refNode2ownNode);

        if (this->opt_catch_id_node.has_value()) {
            ASSERT_OR_EXIT(refNode2ownNode.contains(this->opt_catch_id_node.value()));
            ASSERT_OR_EXIT(! refNode2ownNode[this->opt_catch_id_node.value()].expired());

            this->opt_catch_id_node.value() = dynamic_pointer_cast<CatchIdNode>(
            refNode2ownNode[this->opt_catch_id_node.value()].lock());

            ASSERT_OR_EXIT(this->opt_catch_id_node.value().lock() != nullptr);
        }

        this->post_construct();
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<CatchNode>(shared_from_this());
        visitor.visit(node);
    }
};

} /// end of namespace

#endif //FUZZFLOW_CATCHNODE_H
