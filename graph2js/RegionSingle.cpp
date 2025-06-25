#include "RegionSingle.h"

namespace FuzzFlow {

void RegionSingle::emit_var_declaration(const shared_ptr<VarSymbol> &var_sym)
{
    string name = var_sym->name;

    if (this->decl_var_names.count(name)) {
        return;
    }

    const string assign_stmt = "let " + name + ";";
    this->decl_var_names.insert(name);

    /// Variable declarations are always inserted at the beginning of the first RegionSingle within the RegionNested.
    this->statements.push_front(assign_stmt);
}

void RegionSingle::emit_assignment(const vector<shared_ptr<VarSymbol>>& names,
                                   const string &assignment_expr,
                                   const bool self_assignment)
{
    for (int i = 0; i < names.size(); i ++) {
        auto var_symbol = names[i];

        string real_assign_expr;
        if (i == 0) {
            real_assign_expr = assignment_expr;
        }
        else {
            real_assign_expr = names[0]->name;
        }

        string assign_stmt;

        if (! self_assignment) {
            assign_stmt = var_symbol->name + " = " + real_assign_expr + ";";
        }
        else {
            assign_stmt = real_assign_expr + ";";
        }

        this->statements.push_back(assign_stmt);
    }
}

void RegionSingle::emit_return(const string &return_value)
{
    string return_stmt = "return ";

    if (return_value.empty()) {
        return_stmt += ";";
    }
    else {
        return_stmt += return_value + ";";
    }

    this->statements.push_back(return_stmt);
}

/// Function call statements are categorized based on whether the return value is used:
/// 1. If the return value is unused, no additional handling is required.
/// 2. If the return value is used, an assignment is generated to store the return value.
///
/// There are two cases when the return value is used:
///
/// - Direct usage, e.g.:
///     let x;
///     x = foo("test");
///   In this case, the `Invoke` node is directly associated with the var proxy of `x`.
///
/// - Indirect usage, e.g.:
///     x = foo("Hello") + "world";
///   Here, `foo("Hello")` is not assigned directly to a variable, but is part of a binary operation.
///   During lifting, a temporary variable proxy is created for the `Invoke` node:
///     temp = foo("Hello");
///     x = temp + "world";

void RegionSingle::emit_invoke(const string &invoke_expr)
{
    string invoke_stmt = invoke_expr + ";";
    this->statements.push_back(invoke_stmt);
}

void RegionSingle::emit_load(const string &load_expr)
{
    const string load_stmt = load_expr + ";";
    this->statements.push_back(load_stmt);
}

void RegionSingle::emit_delete(const string &del_tgt_expr)
{
    string del_stmt = del_tgt_expr + ";";
    this->statements.push_back(del_stmt);
}

void emit_invoke_proxies(string invoke_expr, vector<string> var_names) {

}

void RegionSingle::emit_store(const string& object_expr,
                              const string& member,
                              const string &assignment_expr,
                              const ObjectAccessType access_type,
                              const bool self_assignment)
{
    string assign_stmt;

    if (self_assignment) {
        assign_stmt = assignment_expr + ";";
    }
    else {
        if (access_type == ObjectAccessType::field) {
            assign_stmt = object_expr + "." + member + " = " + assignment_expr + ";";
        }
        else {
            assign_stmt = object_expr + "[" + member + "]" + " = " + assignment_expr + ";";
        }
    }

    this->statements.push_back(assign_stmt);
}

void RegionSingle::emit_throw(const string &throw_value)
{
    string throw_stmt = "throw ";

    if (throw_value.empty()) {
        throw_stmt += ";";
    }
    else {
        throw_stmt += throw_value + ";";
    }

    /// The throw statement is generated before the PhiNodes on Catch/Finally merge nodes.
    /// However, semantically it should appear last, so it is saved as a tail statement.
    this->throw_statement = throw_stmt;
}

} /// end of namespace