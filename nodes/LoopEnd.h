#ifndef FUZZFLOW_LOOPEND_H
#define FUZZFLOW_LOOPEND_H

#include "AbstractEndNode.h"
#include "LoopBegin.h"

namespace FuzzFlow {

class LoopEnd final : public EndMayMergeNode {
private:
    static const string label;

public:
    /// The merge_node of loop end is the loop begin
    explicit LoopEnd(const weak_ptr<LoopBegin> &loop_begin)
    {
        this->merge_node = loop_begin;

        this->node_hash_current = label;
        this->node_hash_next = label;
    }

    string get_label() override
    {
        return label;
    }

    shared_ptr<LoopBegin> loop_begin() const
    {
        return dynamic_pointer_cast<LoopBegin>(this->merge_node.lock());
    }

    shared_ptr<IRNode> clone() override
    {
        return make_shared<LoopEnd>(this->loop_begin());
    }

    void clone_repair(map<weak_ptr<IRNode>,
                          weak_ptr<IRNode>,
                          std::owner_less<>> &refNode2ownNode) override
    {
        /// This will be handled in the clone_repair -> post_construct in LoopBegin

        //this->merge_node = std::dynamic_pointer_cast<LoopBegin>(
        //    refNode2ownNode[this->merge_node].lock());
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<LoopEnd>(shared_from_this());
        visitor.visit(node);
    }

};

} /// end of namespace

#endif //FUZZFLOW_LOOPEND_H
