#ifndef FUZZFLOW_SCRIPTWRITER_H
#define FUZZFLOW_SCRIPTWRITER_H

#include "../utils/common_using.h"

#include "RegionSingle.h"
#include "RegionIfNode.h"
#include "RegionLoopBegin.h"
#include "RegionNested.h"
#include "RegionTry.h"

namespace FuzzFlow {

class ScriptWriter {
public:
    /// Code generation for ordinary functions (including `main`).
    string emit(const string& prefix_code,
                const string& suffix_code,
                const string& function_name,
                const vector<string>& function_args,
                const shared_ptr<const RegionNested>& graph_region);

    /// Code generation for member functions.
    string emit_method(const vector<string>& function_args,
                       const shared_ptr<const RegionNested>& graph_region);

private:

    // How many spaces to use per indention level.
    int indent = 4;

    vector<string> special_characters = {"_", "$", "-"};

    char space = ' ';

    // the current script code
    string code;

    // The current number of spaces to use for indention.
    int current_indention = 0;

    void emit_formatted_line(const string& line);

    void emit_region_nested(const weak_ptr<const RegionNested>& region);

    void emit_regionSingle(const weak_ptr<const RegionSingle>& region_single);

    void emit_regionIfNode(const weak_ptr<const RegionIfNode>& region_if);

    void emit_regionLoopBegin(const weak_ptr<const RegionLoopBegin>& region_loop);

    void emit_regionTry(const weak_ptr<const RegionTry>& region_try_w);

    void emitComment(string comment);

    void emitBlock(string block);

    void increaseIndentLevel();

    void decreaseIndentLevel();
};

}

#endif //FUZZFLOW_SCRIPTWRITER_H
