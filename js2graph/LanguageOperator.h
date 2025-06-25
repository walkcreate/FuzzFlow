#ifndef FUZZFLOW_OPERATOR_H
#define FUZZFLOW_OPERATOR_H

#include "../utils/common_using.h"

///
/// For each operator, the string representation may differ between the lift phase and graph visualization.
/// Take the subtraction operator as an example:
/// - For graph display, we prefer a more intuitive label like `Minus(-)` for nodes
/// - For code generation, we simply use the symbol `-
///
class LanguageOperator {
public:
    /// the name used in showing the graph
    string label;

    /// the name used in graph2js
    string code;

    LanguageOperator(const string &_label, const string &code)
    {
        this->label = _label;
        this->code = code;
    }
};

#endif //FUZZFLOW_OPERATOR_H
