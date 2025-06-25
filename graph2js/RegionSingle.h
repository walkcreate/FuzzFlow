#ifndef FUZZFLOW_REGIONSINGLE_H
#define FUZZFLOW_REGIONSINGLE_H

#include "Region.h"
#include "../nodes/js/AccessObjectNode.h"
#include "../semantic/VarSymbol.h"

///
/// RegionSingle: A basic Region element containing only statements (no subregions)
///
namespace FuzzFlow {

class RegionSingle final : public Region {
public:
    RegionSingle() = default;

    ~RegionSingle() override = default;

    deque<string> statements {};

    /// A RegionSingle only needs to preserve a single throw statement,
    /// as only one throw can take effect. The throw statement is placed at the tail.
    string throw_statement = "";

    unordered_set<string> decl_var_names;

    void emit_var_declaration(const shared_ptr<VarSymbol> &var_sym);

    void emit_assignment(const vector<shared_ptr<VarSymbol>>& names,
                         const string &assignment_expr,
                         bool self_assignment);

    void emit_return(const string &return_value);

    void emit_invoke(const string &invoke_expr);

    void emit_load(const string &load_expr);

    void emit_delete(const string &delete_expr);

    void emit_invoke_proxies(string invoke_expr, vector<string> var_names);

    void emit_invoke_virtual_proxy(string invoke_expr, string virtual_name);

    void emit_store(const string& object_expr,
                    const string& member,
                    const string &assignment_expr,
                    ObjectAccessType access_type,
                    const bool self_assignment);

    void emit_throw(const string &throw_value);
};

}

#endif //FUZZFLOW_REGIONSINGLE_H
