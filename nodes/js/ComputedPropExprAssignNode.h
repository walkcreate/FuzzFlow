#ifndef FUZZFLOW_COMPUTEDPROPERTYEXPRESSIONASSIGNMENTNODE_H
#define FUZZFLOW_COMPUTEDPROPERTYEXPRESSIONASSIGNMENTNODE_H

#include "PropExprAssignNode.h"

namespace FuzzFlow {

class ComputedPropExprAssignNode final : public PropExprAssignNode {
private:
    static const string label;

public:
    ///
    /// EBNF
    /// propertyAssignment: '[' singleExpression ']' ':' singleExpression
    ///
    ComputedPropExprAssignNode(const weak_ptr<DataProducerNode>& property_name_computed,
                               const weak_ptr<DataProducerNode>& property_value)
        : PropExprAssignNode(property_name_computed, property_value)
    {
        this->inputs = {property_name_computed, property_value};

        this->node_hash_current = label;
    }

    string get_label() override
    {
        return label;
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<ComputedPropExprAssignNode>(shared_from_this());
        visitor.visit(node);
    }
};

} /// end of namespace

#endif //FUZZFLOW_COMPUTEDPROPERTYEXPRESSIONASSIGNMENTNODE_H
