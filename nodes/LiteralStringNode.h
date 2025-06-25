#ifndef FUZZFLOW_LITERALSTRINGNODE_H
#define FUZZFLOW_LITERALSTRINGNODE_H

#include "IRNode.h"
#include "LiteralNode.h"
#include "TerminalNode.h"

namespace FuzzFlow {

class LiteralStringNode final : public TerminalNode,
                                public LiteralNode
{
public:
    LiteralStringNode(const string &literal_text,
                       const bool has_quotation)
    {
        /*
         * When constructing ConstantString from literal, the literal text contains quotation
         *
         * literal_text contains the beginning and ending quotation `"` or `'`
         * like "xxx" or 'xxx'
         * example: "123\n"
         *
         * When constructing ConstantString from identifier(as property name), the literal text
         * does not contain quotation
         */
        this->value = literal_text;
        this->has_quotation = has_quotation;

        this->node_hash_current = literal_text;
        this->node_hash_next = literal_text;
    }

    string get_label() override
    {
        if (has_quotation) {
            return "Literal string(" + LiteralStringNode::quoted(this->value) + ")";
        }

        return "Literal string(" + this->value + ")";
    }

    /*
     * remove the beginning and ending "" or ''
     *
     * example:
     * "hello" (7 chars) -> hello (5 chars)
     */
    static string raw_text_to_real(const string& literal_text)
    {
        string real_text = literal_text.substr(1, literal_text.size() - 2);
        return real_text;
    }

    static string quoted(const string& literal_text)
    {
        string new_s;

        for (auto &c: literal_text) {
            if (c == '"') {
                new_s.append("\\");
            }
            new_s += c;
        }
        return new_s;
    }

    ~LiteralStringNode() override = default;

    shared_ptr<IRNode> clone() override
    {
        auto new_node = make_shared<LiteralStringNode>(this->value, this->has_quotation);
        return new_node;
    }

    std::size_t calc_hash() override
    {
        return std::hash<std::string>{}(this->value);
    }

    string get_value() const
    {
        return this->value;
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<LiteralStringNode>(shared_from_this());
        visitor.visit(node);
    }

    string get_producer_expr(JavaScriptLifter &visitor) override;

private:
    string value;
    bool has_quotation = true;
};

} /// end of namespace

#endif //FUZZFLOW_LITERALSTRINGNODE_H
