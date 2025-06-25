#include "OperatorPairs.h"

/// Group operators of the same type together.
unordered_map<string, string> OperatorPairs::arithmetic_op = {
    {"Minus(-)", "-"},
    {"Add(+)", "+"},
    {"Mul(*)", "*"},
    {"Div(/)", "/"},
    {"Mod(%)", "%"},
    ///
    {"UnaryPlus(+)", "+"},
    {"UnaryMinus(-)", "-"},
    {"Power(**)", "**"},        // PowerExpression
};

unordered_map<string, string> OperatorPairs::relational_op = {
    {">", ">"},
    {">=", ">="},
    {"<", "<"},
    {"<=", "<="},
};

unordered_map<string, string> OperatorPairs::equality_op = {
    {"==", "=="},
    {"!=", "!="},
    {"===", "==="},
    {"!==", "!=="},
};

unordered_map<string, string> OperatorPairs::bit_op = {
    {"&", "&"},
    {"^", "^"},
    {"|", "|"},
    {"BitNot(~)", "~"}  // BitNotExpression
};

unordered_map<string, string> OperatorPairs::logical_op = {
    {"&&", "&&"},
    {"||", "||"},
    {"Not(!)", "!"},    // NotExpression
};

unordered_map<string, string> OperatorPairs::assignment_op = {
    {"*=", "*="},
    {"/=", "/="},
    {"%=", "%="},
    {"+=", "+="},
    {"-=", "-="},
    {"<<=", "<<="},
    {">>=", ">>="},
    {">>>=", ">>>="},
    {"&=", "&="},
    {"^=", "^="},
    {"|=", "|="},
    {"**=", "**="},
};

unordered_map<string, string> OperatorPairs::shift_op = {
    {"<<", "<<"},
    {">>", ">>"},
    {">>>", ">>>"},
};

unordered_map<string, string> OperatorPairs::js_op = {
    {"void", "void"},                   // VoidExpression
    {"typeof", "typeof"},               // TypeofExpression
    {"instanceof", "instanceof"},       // InstanceofExpression
    {"in", "in"}                        // InExpression

};

string OperatorPairs::label2code(const string& label)
{
    if (OperatorPairs::arithmetic_op.contains(label)) {
        return OperatorPairs::arithmetic_op.at(label);
    }

    if (OperatorPairs::relational_op.contains(label)) {
        return OperatorPairs::relational_op.at(label);
    }

    if (OperatorPairs::equality_op.contains(label)) {
        return OperatorPairs::equality_op.at(label);
    }

    if (OperatorPairs::bit_op.contains(label)) {
        return OperatorPairs::bit_op.at(label);
    }

    if (OperatorPairs::logical_op.contains(label)) {
        return OperatorPairs::logical_op.at(label);
    }

    if (OperatorPairs::assignment_op.contains(label)) {
        return OperatorPairs::assignment_op.at(label);
    }

    if (OperatorPairs::shift_op.contains(label)) {
        return OperatorPairs::shift_op.at(label);
    }

    if (OperatorPairs::js_op.contains(label)) {
        return OperatorPairs::js_op.at(label);
    }

    assert("Error Operator label" && false);
    return nullptr; /// todo
}
