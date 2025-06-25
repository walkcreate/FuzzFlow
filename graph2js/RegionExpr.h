#ifndef FUZZFLOW_REGIONEXPR_H
#define FUZZFLOW_REGIONEXPR_H

#include "Region.h"

///
/// Like RegionSingle, RegionExpr is a terminal Region that actually holds source content.
/// It is specifically used to store expressions.
///
namespace FuzzFlow {

class RegionExpr final : public Region {
public:
    string expr;

    void emit_expression(const string &expr)
    {
        this->expr = expr;
    }
};

}

#endif //FUZZFLOW_REGIONEXPR_H
