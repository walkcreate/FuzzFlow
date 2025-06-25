#ifndef FUZZFLOW_FORINPROPNAME_H
#define FUZZFLOW_FORINPROPNAME_H

#include "../TerminalNode.h"

namespace FuzzFlow {

class ForInPropName final : public TerminalNode {
private:
    static const string label;

public:
    string prop_name;

    explicit ForInPropName (const string& prop_name)
    {
        this->prop_name = prop_name;

        this->node_hash_current = this->label;
    }

    string get_label() override
    {
        return "ForInPropName " + prop_name;
    }

    shared_ptr<IRNode> clone() override
    {
        auto new_node = make_shared<ForInPropName>(this->prop_name);
        return new_node;
    }

    std::size_t calc_hash() override
    {
        return std::hash<std::string>{}(this->prop_name);
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<ForInPropName>(shared_from_this());
        visitor.visit(node);
    }

    string get_producer_expr(JavaScriptLifter &visitor) override;
};

} /// end of namespace

#endif //FUZZFLOW_FORINPROPNAME_H
