#ifndef FUZZFLOW_OPERATORPAIRS_H
#define FUZZFLOW_OPERATORPAIRS_H

#include "../utils/common_using.h"

class OperatorPairs {
public:
    static string label2code(const string& label);

    static unordered_map<string, string> arithmetic_op;

    static unordered_map<string, string> relational_op;

    static unordered_map<string, string> equality_op;

    static unordered_map<string, string> bit_op;

    static unordered_map<string, string> logical_op;

    static unordered_map<string, string> assignment_op;

    /// operators in BitShiftExpression
    static unordered_map<string, string> shift_op;

    static unordered_map<string, string> js_op;
};

#endif //FUZZFLOW_OPERATORPAIRS_H
