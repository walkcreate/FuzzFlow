#ifndef FUZZFLOW_MERGENODE_H
#define FUZZFLOW_MERGENODE_H

#include "IRNode.h"
#include "FixedNode.h"
#include "AbstractMergeNode.h"
#include "EndMayMergeNode.h"

namespace FuzzFlow {

enum class MergeType {
    If,
    Try
};

class MergeNode final: public AbstractMergeNode {
private:
    static const string label;

public:
    MergeType merge_type;

    MergeNode(const vector<weak_ptr<EndMayMergeNode>>& _merged_flows,
              const weak_ptr<FixedNode>& next,
              const MergeType _merge_type)
        : AbstractMergeNode(_merged_flows, next)
    {
        /// MergeNode can use inputs to point to the EndNodes of IfNode
        /// Graal IR: An Extensible Declarative Intermediate Representation

        merge_type = _merge_type;

        this->node_hash_current = label;
    }

    string get_label() override
    {
        return label;
    }

    shared_ptr<IRNode> clone() override
    {
        return make_shared<MergeNode>(this->merged_flows, this->next(), this->merge_type);
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<MergeNode>(shared_from_this());
        visitor.visit(node);
    }
};

} /// end of namespace

#endif //FUZZFLOW_MERGENODE_H
