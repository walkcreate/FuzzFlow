#include "ScriptWriter.h"

namespace FuzzFlow {

void ScriptWriter::increaseIndentLevel()
{
    this->current_indention += this->indent;
}

void ScriptWriter::decreaseIndentLevel()
{
    this->current_indention -= this->indent;
    assert(this->current_indention >= 0);
}

void ScriptWriter::emit_formatted_line(const string& line)
{
    this->code += string(this->current_indention, this->space) + line + "\n";
}

void ScriptWriter::emit_region_nested(const weak_ptr<const RegionNested>& region)
{
    for (int i = 0; i < region.lock()->regions.size(); i++) {
        auto region_unit = region.lock()->regions[i];

        if (auto region_single = dynamic_pointer_cast<const RegionSingle>(region_unit)) {
            this->emit_regionSingle(region_single);
        }
        else if (auto region_if = dynamic_pointer_cast<const RegionIfNode>(region_unit)) {
            this->emit_regionIfNode(region_if);
        }
        else if (auto region_loop = dynamic_pointer_cast<const RegionLoopBegin>(region_unit)) {
            this->emit_regionLoopBegin(region_loop);
        }
        else if (auto region_try = dynamic_pointer_cast<const RegionTry>(region_unit)) {
            this->emit_regionTry(region_try);
        }
        else if (auto region_nested = dynamic_pointer_cast<const RegionNested>(region_unit)) {
            this->emit_region_nested(region_nested);
        }

        else {
            assert("Error Region type" && false);
        }
    }
}

void ScriptWriter::emit_regionSingle(const weak_ptr<const RegionSingle>& region_single_w)
{
    auto region_single = region_single_w.lock();

    for (auto& stmt : region_single->statements) {
        this->emit_formatted_line(stmt);
    }

    if (! region_single->throw_statement.empty()) {
        this->emit_formatted_line(region_single->throw_statement);
    }
}

void ScriptWriter::emit_regionIfNode(const weak_ptr<const RegionIfNode>& region_if_w)
{
    auto region_if = region_if_w.lock();

    string line = "if (" + region_if->condition->expr + ") {";

    emit_formatted_line(line);

    increaseIndentLevel();

    emit_region_nested(region_if->branch_true);

    decreaseIndentLevel();

    emit_formatted_line("}");
    emit_formatted_line("else {");

    increaseIndentLevel();

    emit_region_nested(region_if->branch_false);

    decreaseIndentLevel();

    emit_formatted_line("}");
}

void ScriptWriter::emit_regionLoopBegin(const weak_ptr<const RegionLoopBegin>& region_loop_w)
{
    auto region_loop = region_loop_w.lock();

    this->emit_regionSingle(region_loop->loop_before);

    this->emit_regionSingle(region_loop->loop_fake_before);

    if (region_loop->mode == LoopMode::WHILE) {
        string line = "while (" + region_loop->loop_condition->expr + ") {";
        emit_formatted_line(line);
    }
    else {
        string line = "for (" + region_loop->loop_condition->expr + ") {";
        emit_formatted_line(line);
    }


    increaseIndentLevel();

    emit_region_nested(region_loop->loop_body);

    emit_regionSingle(region_loop->loop_body_tail);

    /// The `fake before` node belongs to the conditional expression sequence.
    /// Since it was not generated during that sequence, it must be generated again after
    /// the loop tail to preserve semantics.
    if (region_loop->mode == LoopMode::WHILE) {
        emit_regionSingle(region_loop->loop_fake_before);
    }

    decreaseIndentLevel();

    emit_formatted_line("}");
}

void ScriptWriter::emit_regionTry(const weak_ptr<const RegionTry>& region_try_w)
{
    auto region_try = region_try_w.lock();

    string line = "try {";

    emit_formatted_line(line);

    increaseIndentLevel();

    emit_region_nested(region_try->try_block);

    decreaseIndentLevel();

    emit_formatted_line("}");

    if (region_try->has_catch) {

        if (! region_try->catch_expr->expr.empty()) {
            emit_formatted_line("catch (" + region_try->catch_expr->expr + ") {");
        }
        else {
            emit_formatted_line("catch {");
        }

        increaseIndentLevel();

        emit_region_nested(region_try->catch_block);

        decreaseIndentLevel();

        emit_formatted_line("}");
    }

    if (region_try->has_finally) {
        emit_formatted_line("finally {");

        increaseIndentLevel();

        emit_region_nested(region_try->finally_block);

        decreaseIndentLevel();

        emit_formatted_line("}");
    }
}

string ScriptWriter::emit(const string& prefix_code,
                          const string& suffix_code,
                          const string& function_name,
                          const vector<string>& function_args,
                          const shared_ptr<const RegionNested>& graph_region)
{
    bool is_real_func = false;

    if (function_name != "__main__") {
        is_real_func = true;

        string line = "function " + function_name + "(";

        for (int i = 0; i < function_args.size(); i++) {
            if (i == 0) {
                line += function_args[i];
            }
            else {
                line += ", " + function_args[i];
            }
        }
        line += ") {";

        emit_formatted_line(line);

        increaseIndentLevel();
    }

    if (! is_real_func) {
        this->code += prefix_code + "\n";
    }

    emit_region_nested(graph_region);

    if (is_real_func) {

        decreaseIndentLevel();

        emit_formatted_line("}");
    }

    if (! is_real_func) {
        this->code += suffix_code;
    }

    return this->code;
}

/// no function_name
string ScriptWriter::emit_method(const vector<string>& function_args,
                                 const shared_ptr<const RegionNested>& graph_region)
{
    string line = "(";

    for (int i = 0; i < function_args.size(); i++) {
        if (i == 0) {
            line += function_args[i];
        }
        else {
            line += ", " + function_args[i];
        }
    }

    line += ") {";

    emit_formatted_line(line);

    increaseIndentLevel();

    emit_region_nested(graph_region);

    decreaseIndentLevel();

    emit_formatted_line("}");

    return this->code;
}

} /// end of namespace