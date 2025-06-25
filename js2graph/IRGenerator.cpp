#include "IRGenerator.h"
#include "../exceptions/JS2GraphError.h"

namespace FuzzFlow {

///
/// flow matches nodes of type AbstractBeginNode
/// AbstractBeginNode matches scope
///
void IRGenerator::set_VarProxy_for_flow(const weak_ptr<AbstractBeginNode> &begin_node,
                                        shared_ptr<VarSymbol> var_sym,
                                        const shared_ptr<VarProxy> &proxy)
{
    if (! this->flow2varProxies.contains(begin_node)) {
        stack<shared_ptr<VarProxy> > proxies{{proxy}};
        map<shared_ptr<VarSymbol>,
            stack<shared_ptr<VarProxy> >,
            std::owner_less<> > m = {{var_sym, proxies}};
        this->flow2varProxies.insert({begin_node, m});
    }
    else {
        // be careful not to copy map!
        auto &inside_map = this->flow2varProxies.find(begin_node)->second;
        if (inside_map.contains(var_sym)) {
            inside_map[var_sym].push(proxy);
        }
        else {
            stack<shared_ptr<VarProxy> > proxies{{proxy}};
            inside_map[var_sym] = proxies;
        }
    }
}

///
/// Each branch in the data flow generates a Phi node.
/// Only the Phi nodes within the body of a for loop require back filling.
/// Are the merge nodes corresponding to the Phi nodes forcibly generated
/// by a for loop always LoopBegin?
///
void IRGenerator::record_phi_need_fill(const weak_ptr<AbstractMergeNode>& loop_begin,
                                       const shared_ptr<VarSymbol>& var_sym,
                                       const weak_ptr<PhiNode>& phi_node,
                                       const weak_ptr<AbstractBeginNode>& flow)
{
    /// reference is necessary.
    auto &loop_need_fill = this->phi_need_backfill[loop_begin];

    auto pair = make_pair(flow, phi_node);

    if (loop_need_fill.contains(var_sym)) {
        loop_need_fill[var_sym].push_back(pair);
    }
    else {
        loop_need_fill[var_sym] = {pair};
    }
}


shared_ptr<VarProxy> IRGenerator::gen_phi_node(const weak_ptr<AbstractMergeNode> &merge_node,
                                               const weak_ptr<AbstractBeginNode> &attached_flow,
                                               const shared_ptr<VarSymbol> &var_sym,
                                               vector<weak_ptr<DataProducerNode> > data_inputs,
                                               bool need_back_fill)
{
    weak_ptr<AbstractMergeNode> phi_merge_w = merge_node.lock();
    uint32_t merge_index = merge_node.lock()->get_next_phi_idx();

    const auto phi_node = make_shared<PhiNode>(phi_merge_w, merge_index, data_inputs); // data_inputs is null

    graphs_being_building.back()->add_node(phi_node);

    phi_node->post_construct();

    auto var_proxy = graphs_being_building.back()->add_var_definition(
        var_sym, dynamic_pointer_cast<DataProducerNode>(phi_node));

    set_VarProxy_for_flow(attached_flow, var_sym, var_proxy);

    if (need_back_fill) {
        this->record_phi_need_fill(merge_node, var_sym, phi_node, attached_flow);
    }

    return var_proxy;
}

void IRGenerator::walk_merge_for_varProxy(const shared_ptr<AbstractMergeNode> &merge_node,
                                          const shared_ptr<VarSymbol> &var_symbol,
                                          const vector<weak_ptr<AbstractBeginNode> > &visited_begins,
                                          const weak_ptr<AbstractBeginNode> &end_node,
                                          vector<weak_ptr<DataProducerNode> > &data_inputs,
                                          vector<shared_ptr<VarProxy> > &var_proxies)
{
    for (const auto &_end_node: merge_node->merged_flows) {
        auto endBeMerged = _end_node.lock();

        const bool is_loop_end = (dynamic_pointer_cast<LoopEnd>(endBeMerged) != nullptr);

        weak_ptr<AbstractBeginNode> branchBegin = endBeMerged->get_begin_node();

        /// get varproxy function may modify the vector of visited begins
        /// We make a copy of the vector before using it to avoid interference from the previous for-loop iteration.
        auto visited_begins_dup = visited_begins;
        auto var_proxy = get_VarProxy_from_flow(branchBegin, var_symbol, visited_begins_dup, end_node);

        /// If the merge node is a loop begin, we search backward along both the 'end' and 'loop-end' branches.
        /// To avoid infinite loops, the search on the loop-end branch stops when reaching the loop begin.
        /// Since the loop body may not assign a value to the var symbol, the var proxy might not be found on that path.
        /// If the loop begin being queried is not the one currently being traversed by the IR generator
        /// (i.e., we're not inside its loop body), there's no need to forcibly create a phi node.
        /// In this case, the var proxy remains null during this iteration.
        ///
        if (var_proxy != nullptr) {
            var_proxies.push_back(var_proxy);

            weak_ptr<DataProducerNode> data_node = graphs_being_building.back()->varProxy2node.find(var_proxy)->second;

            assert_or_throw_js2graph(data_node.lock() != nullptr,
                ErrorMsgsJS2Graph::handleError(ErrorCodeJS2Graph::VarProxyHasNode));

            data_inputs.push_back(data_node);
        }
        else if (is_loop_end && this->loop_begins_should_gen_phi.contains(merge_node)) {
            ///
            /// If the current branch is a loop end, the queried var proxy must be inside the loop,
            /// since there is a mechanism to prevent loops from forming at loop begin.
            ///
            /// If no value is found in the loop-end branch, decide whether to force phi creation
            /// based on whether we're currently traversing the loop body of the corresponding loop begin.
            /// If we are, a phi node must be created and patched later,
            /// using a fake data node as one of its inputs.
            ///
            data_inputs.push_back(this->fake_data_node);
        }
    }
}

shared_ptr<VarProxy> IRGenerator::extract_varProxy_from_merge(const shared_ptr<AbstractMergeNode>& merge_node,
                                                              const weak_ptr<AbstractBeginNode>& attached_flow,
                                                              const shared_ptr<VarSymbol>& var_symbol,
                                                              vector<weak_ptr<DataProducerNode>> data_inputs,
                                                              vector<shared_ptr<VarProxy>> &var_proxies)
{
    if (data_inputs.empty()) {
        /// Due to the presence of loops and the loop prevention mechanism at LoopBegin,
        /// it is possible that neither branch of a merge can find a matching proxy.
        return nullptr;
    }

    if (data_inputs.size() == 1) {
        if (dynamic_pointer_cast<FakeDataProducerNode>(data_inputs[0].lock())) {
            /// If one branch of the merge returns nothing and the other returns a placeholder (fake) value to be backfilled,
            /// there is no need to generate a loop phi node.
            return nullptr;
        }

        /// If only one of the two flows returns a result, it must be from the LoopEnd branch,
        /// indicating the variable was newly declared inside the loop body.
        /// If it's not found before the EndNode, it means a unique var proxy was created within the loop body.
        return var_proxies[0];
    }

    if (data_inputs.size() == 2 && is_same_element(data_inputs)) {
        return var_proxies[0];
    }

    bool need_back_fill = false;

    /// During loop processing, the retrieved data_node may be a temporary placeholder (FakeDataNode).
    /// This indicates that the loop is currently being converted from JS to graph and has not yet completed.
    ///
    if (dynamic_pointer_cast<LoopBegin>(merge_node)) {
        for (auto &inp: data_inputs) {
            if (inp.lock() == this->fake_data_node) {
                need_back_fill = true;
            }
        }
    }

    auto var_proxy = gen_phi_node(merge_node, attached_flow, var_symbol, data_inputs, need_back_fill);
    return var_proxy;
}

/// Only query at the beginning node itself, without recursion.
shared_ptr<VarProxy> IRGenerator::varProxy_at_begin(const weak_ptr<AbstractBeginNode> &begin_node,
                                                    const shared_ptr<VarSymbol> &var_sym)
{
    shared_ptr<VarProxy> var_proxy = nullptr;

    auto inside_map_itr = this->flow2varProxies.find(begin_node);

    if (inside_map_itr != this->flow2varProxies.end()) {
        auto &inside_map = inside_map_itr->second;
        auto proxy_itr = inside_map.find(var_sym);
        if (proxy_itr != inside_map.end()) {
            var_proxy = proxy_itr->second.top();
        }
    }

    return var_proxy;
}

/// Starting from a flow node (corresponding to AbstractBegin class),
/// searches for the var proxy associated with a given var symbol.
///
/// If the target var is bound to this flow node, returns it immediately.
/// Otherwise, continues searching upstream along the control flow.
///
/// Note: The search is guaranteed to succeed theoretically, as failure
/// would indicate referencing an undeclared/uninitialized variable.
///
/// The returned var proxy always represents the last assignment to
/// this variable in the control flow, i.e., the most recent one.
/// When end_node is nullptr, the search continues until the variable is found (no termination node restriction).
///
shared_ptr<VarProxy> IRGenerator::get_VarProxy_from_flow(weak_ptr<AbstractBeginNode> begin_node,
                                                         const shared_ptr<VarSymbol>& var_sym,
                                                         vector<weak_ptr<AbstractBeginNode> > &visited_begins,
                                                         const weak_ptr<AbstractBeginNode>& search_end)
{
    /// prevent search loop
    if (dynamic_pointer_cast<LoopBegin>(begin_node.lock())) {
        const auto visited_loop_begin_pos =
                std::find_if(visited_begins.begin(), visited_begins.end(),
                             [&begin_node](const std::weak_ptr<AbstractBeginNode> &ptr1) {
                                 return ptr1.lock() == begin_node.lock();
                             });

        if (visited_loop_begin_pos != visited_begins.end()) {
            return nullptr;
        }
    }

    /// Record the visited begin node to prevent loops at the LoopBegin node
    visited_begins.push_back(begin_node);

    shared_ptr<VarProxy> var_proxy = varProxy_at_begin(begin_node, var_sym);
    if (var_proxy != nullptr) {
        return var_proxy;
    }

    /// When the begin node coincides with the graph head, the query results in failure.
    if (auto start_node = dynamic_pointer_cast<FunctionHeadNode>(begin_node.lock())) {
        return nullptr;
    }

    /// The proxies on the "search end" node are within the search scope.
    if (search_end.lock() != nullptr) {
        if (begin_node.lock() == search_end.lock()) {
            /// If we reach the search end, the recursion stops.
            return nullptr;
        }
    }

    /// If no var proxy is found at current begin node, we can recursively search upward.

    if (dynamic_pointer_cast<CatchNode>(begin_node.lock()) != nullptr) {
        return nullptr;
    }
    if (dynamic_pointer_cast<FinallyNode>(begin_node.lock()) != nullptr) {
        return nullptr;
    }

    /// 1. current begin has a predecessor
    if (begin_node.lock()->predecessor.use_count() > 0) {
        /// If the current begin node has predecessor (MergeNode has no predecessor)
        /// we should recursively query the pred node.
        ///
        /// If the current begin node is a branch of If, now we can search the node before If.
        weak_ptr<AbstractBeginNode> preceding_begin =
                begin_node.lock()->predecessor.lock()->get_begin_node();

        /// When traversing backward through control flow, watch for potential loops
        /// (e.g., LoopBegin → LoopEnd → ... → LoopBegin).
        ///
        /// If the previous node is LoopBegin, check if it already exists in visited nodes.
        /// If found, this indicates we've reached the start of a loop cycle,
        /// meaning we're in a merge branch - in this case, return nullptr.
        ///
        if (dynamic_pointer_cast<LoopBegin>(preceding_begin.lock())) {
            const auto visited_loop_begin_pos =
                    std::find_if(visited_begins.begin(), visited_begins.end(),
                                 [&preceding_begin](
                             const std::weak_ptr<AbstractBeginNode> &ptr1) {
                                     return ptr1.lock() == preceding_begin.lock();
                                 });

            if (visited_loop_begin_pos != visited_begins.end()) {
                return nullptr;
            }
        }

        /// recursive
        var_proxy = get_VarProxy_from_flow(preceding_begin, var_sym, visited_begins, search_end);
        return var_proxy;
    }
    else {
        /// 2. current begin has no predecessor. It is a merge node.
        auto merge_node = dynamic_pointer_cast<AbstractMergeNode>(begin_node.lock());

        if (merge_node == nullptr) {
            assert_or_throw_js2graph(false,
                                   "Failed to find var proxy, while the begin node has no predecessor and is not AbstractMerge");
        }

        /// receive the return values by parameters.
        vector<weak_ptr<DataProducerNode> > data_inputs;
        vector<shared_ptr<VarProxy> > var_proxies;

        walk_merge_for_varProxy(merge_node, var_sym, visited_begins, search_end, data_inputs, var_proxies);

        /// All phi nodes generated at AbstractMerge nodes (including LoopBegin)
        /// should have their var proxies bound to the merge flow.
        /// Since phi nodes are created due to merging, any lookup that passes through
        /// a merge node should ultimately resolve to the corresponding phi.
        ///
        /// For LoopBegin nodes, if the generated phi (denoted as phi-x) is instead
        /// bound to the BeginNode flow, future lookups will still traverse both
        /// branches of the LoopBegin. As a result, two separate values may be found
        /// from the EndNode and LoopEnd branches, which would then trigger the
        /// creation of a new phi node. That new phi will be identical to phi-x,
        /// leading to its reuse — because phi-x was originally created from this merge scenario.
        ///
        const weak_ptr<AbstractBeginNode>& attached_merge = begin_node;
        auto _var_proxy =
                extract_varProxy_from_merge(merge_node, attached_merge, var_sym, data_inputs, var_proxies);

        return _var_proxy;
    }
}

shared_ptr<DataProducerNode> IRGenerator::get_variable_node(const shared_ptr<VarSymbol>& var_symbol)
{
    check_last_uni();

    const weak_ptr<AbstractBeginNode> begin_node = last_unisuccessor->get_begin_node();

    vector<weak_ptr<AbstractBeginNode> > visited_begin;
    const shared_ptr<AbstractBeginNode> null_end;

    if (const shared_ptr<VarProxy> var_proxy = get_VarProxy_from_flow(begin_node, var_symbol, visited_begin, null_end)) {
        cout << "In get variable, we have found the var_proxy: " << var_proxy->get_label() << std::endl;

        /// return the data node when successfully queried the var proxy
        shared_ptr<DataProducerNode> ret_node = dynamic_pointer_cast<DataProducerNode>(
            graphs_being_building.back()->varProxy2node.find(var_proxy)->second.lock());

        return ret_node;
    }

    /// If the get var proxy function failed,
    /// we try to find the var symbol in builtin and global data flows.
    /// We only search the builtin symbols after the query on begin chains,
    /// because the seed may update the builtin symbols.
    ///
    if (this->builtin_var_symbols.contains(var_symbol)) {
        auto _builtin_node = this->builtin_varSym2node[var_symbol];
        graphs_being_building.back()->add_node(_builtin_node);
        return _builtin_node;
    }

    if (auto global_data_opt = this->query_producer_in_main(var_symbol);
        global_data_opt.has_value())
    {
        /// This is a global data flow
        auto global_data_node = make_shared<GlobalVarNode>(var_symbol->name);

        graphs_being_building.back()->add_node(global_data_node);

        return global_data_node;
    }

    for (const auto& function_symbol : this->function_symbols) {
        if (function_symbol->name == var_symbol->name) {
            auto global_function_node = make_shared<GlobalFunctionNode>(var_symbol->name);
            graphs_being_building.back()->add_node(global_function_node);
            return global_function_node;
        }
    }

    /// TODO: ChakraCore_test_AsmJs_fgpeepsbug.js triggers this assertion
    const string err_msg = "Failed to find the data producer node for given var symbol";
    cerr << err_msg << ": " << var_symbol->name << std::endl;
    throw JS2GraphError(err_msg);

    return {};
}

/// todo: why not get variable node?
/// get variable node in cur graph
shared_ptr<DataProducerNode> IRGenerator::get_variable_node_in_cur_graph(const shared_ptr<VarSymbol> &var_symbol)
{
    check_last_uni();

    const weak_ptr<AbstractBeginNode> begin_node = last_unisuccessor->get_begin_node();
    vector<weak_ptr<AbstractBeginNode> > visited_begin;
    const shared_ptr<AbstractBeginNode> null_end;

    const shared_ptr<VarProxy> var_proxy =
        get_VarProxy_from_flow(begin_node, var_symbol, visited_begin, null_end);

    if (var_proxy != nullptr) {
        const weak_ptr<DataProducerNode> node = graphs_being_building.back()->varProxy2node[var_proxy];
        return node.lock();
    }

    assert_or_throw_js2graph(false,
                           "get identifier node failed");

    return nullptr;
}

optional<shared_ptr<DataProducerNode>> IRGenerator::query_producer_in_main(const shared_ptr<VarSymbol>& var_symbol) const
{
    assert_or_throw_js2graph((! graphs_being_building.empty()),
                           "IRGenerator without any graph");

    auto main_graph = graphs_being_building.front();

    for (const auto &[proxy, node]: main_graph->varProxy2node) {
        if (proxy->var_symbol == var_symbol) {
            return node.lock();
        }
    }

    return {};
}

bool IRGenerator::is_same_element(const vector<weak_ptr<DataProducerNode>> &nodes)
{
    /// Check if all the nodes are equal: each node must be equal to the first node.
    shared_ptr<DataProducerNode> producer = dynamic_pointer_cast<DataProducerNode>(nodes[0].lock());

    if (producer != nullptr) {
        for (auto &node1_w: nodes) {
            shared_ptr<DataProducerNode> node1 = dynamic_pointer_cast<DataProducerNode>(node1_w.lock());
            if (node1 == nullptr) {
                return false;
            }

            if (producer != node1) {
                return false;
            }
        }
        return true;
    }

    return false;
}

void IRGenerator::gen_builtin_nodes(const set<shared_ptr<Symbol> >& builtinSymbols)
{
    for (auto &sym: builtinSymbols) {
        if (auto var_sym = dynamic_pointer_cast<VarSymbol>(sym)) {
            auto _builtin_node = make_shared<BuiltinNode>(var_sym->name);

            this->builtin_var_symbols.insert(var_sym);
            this->builtin_nodes.insert(_builtin_node);
            this->builtin_varSym2node.insert({var_sym, _builtin_node});
        }
    }
}

void IRGenerator::check_last_uni() const
{
    assert_or_throw_js2graph(last_unisuccessor != nullptr,
        ErrorMsgsJS2Graph::handleError(ErrorCodeJS2Graph::LastUniSuccessorIsNull));
}

void IRGenerator::check_reset_current_flow(const shared_ptr<UniSuccessorNode> &new_uni_node)
{
    /// update control chain
    assert_or_throw_js2graph(last_unisuccessor != nullptr,
        ErrorMsgsJS2Graph::handleError(ErrorCodeJS2Graph::LastUniSuccessorIsNull));

    last_unisuccessor->set_next(new_uni_node);

    last_unisuccessor = new_uni_node;
}

std::any IRGenerator::visitProgram(JavaScriptParser::ProgramContext *ctx)
{
    /// Prepare BuiltinNodes
    auto builtin_symbols = ctx->builtin_symbols;
    this->gen_builtin_nodes(builtin_symbols);

    /// The main script corresponds to a graph.
    auto top_graph = make_shared<Graph>();
    this->program.graphs.push_back(top_graph);
    graphs_being_building.push_back(top_graph);

    /// Create the Function Head Node
    /// The 'next' member of this node is temporarily set to a fake ctrl node
    /// for placeholder purposes, and will be populated with an actual node subsequently.
    vector<weak_ptr<ParameterNode> > params;
    auto function_node = make_shared<FunctionHeadNode>("__main__", params, fake_ctrl_node);
    function_node->post_construct();
    top_graph->add_node(function_node);

    /// Go on traversing
    last_unisuccessor = function_node;
    std::any visit_ret = this->JavaScriptParserBaseVisitor::visitProgram(ctx);

    /// Check if the 'next' for the start node is set.
    /// If not, it indicates that a Return/EndProgram node needs to be created.
    if (dynamic_pointer_cast<FakeCtrlNode>(function_node->next())) {
        const auto return_node = make_shared<EndProgramNode>();
        function_node->set_next(return_node);
        top_graph->add_node(return_node);
    }

    if (auto uni_node = dynamic_pointer_cast<UniSuccessorNode>(last_unisuccessor);
        uni_node != nullptr && dynamic_pointer_cast<FakeCtrlNode>(uni_node->next()))
    {
        const auto return_node = make_shared<EndProgramNode>();
        uni_node->set_next(return_node);
        top_graph->add_node(return_node);
    }

    graphs_being_building.pop_back();

    return visit_ret;
}

std::any IRGenerator::visitFunctionDeclaration(JavaScriptParser::FunctionDeclarationContext *ctx)
{
    /// A function definition matches a graph.
    auto cur_graph = make_shared<Graph>();
    cur_graph->set_outer_graph(graphs_being_building.back());
    graphs_being_building.push_back(cur_graph);
    this->program.graphs.push_back(cur_graph);

    /// record the parsing context to judge whether we need an unwind.
    this->now_in_function_decls.push(ctx);

    string func_name = ctx->identifier()->getText();
    this->function_symbols.push_back(make_shared<VarSymbol>(func_name));

    const auto last_flow_node = last_unisuccessor;

    /// Create the graph head.
    vector<weak_ptr<ParameterNode>> param_nodes;
    const auto function_head_node = make_shared<FunctionHeadNode>(func_name, param_nodes, fake_ctrl_node);
    cur_graph->add_node(function_head_node);
    last_unisuccessor = function_head_node;

    /// Go on traversing the function body.
    /// this call will invoke visitFormalParameter...
    std::any visit_ret = this->JavaScriptParserBaseVisitor::visitFunctionDeclaration(ctx);

    /// Now we create the parameter nodes.
    if (ctx->formalParameterList() != nullptr) {
        vector<JavaScriptParser::FormalParameterArgContext *> param_list =
                ctx->formalParameterList()->formalParameterArg();

        for (const auto arg_context: param_list) {
            const string arg_name = arg_context->assignable()->identifier()->getText();
            weak_ptr<ParameterNode> param_node = cur_graph->get_parameter_node(arg_name);
            function_head_node->inputs.push_back(param_node);
        }
    }

    /// Check whether the 'next' property of Function Head Node has been set.
    if (dynamic_pointer_cast<FakeCtrlNode>(function_head_node->next())) {
        const auto return_node = make_shared<ReturnNode>();
        function_head_node->set_next(return_node);
        cur_graph->add_node(return_node);
    }

    function_head_node->post_construct();

    auto uni_node = dynamic_pointer_cast<UniSuccessorNode>(last_unisuccessor);
    if (uni_node != nullptr && dynamic_pointer_cast<FakeCtrlNode>(uni_node->next())) {
        auto return_node = make_shared<ReturnNode>();
        uni_node->set_next(return_node);
        cur_graph->add_node(return_node);
    }

    /// Restore the context.
    last_unisuccessor = last_flow_node;

    graphs_being_building.pop_back();
    this->now_in_function_decls.pop();

    return visit_ret;
}

std::any IRGenerator::visitFunctionExpression(JavaScriptParser::FunctionExpressionContext *ctx)
{
    throw JS2GraphError("unsupported function expression");
    return nullptr;
}

std::any IRGenerator::visitStatementList(JavaScriptParser::StatementListContext *ctx)
{
    for (auto stmt: ctx->statement()) {
        visit(stmt);

        if (stmt->throwStatement() != nullptr) {
            break;
        }

        if (stmt->returnStatement() != nullptr) {
            break;
        }
    }

    return nullptr;
}

///
/// We handle the formal param like VarDecl.
/// The data node will be created, and the var proxy will be set.
///
std::any IRGenerator::visitFormalParameterList(JavaScriptParser::FormalParameterListContext *ctx)
{
    vector<JavaScriptParser::FormalParameterArgContext *> param_list =
            ctx->formalParameterArg();

    for (auto arg_cxt: param_list) {
        /// todo: the formal param name?
        string arg_name = arg_cxt->assignable()->identifier()->getText();

        auto param_node = make_shared<ParameterNode>(arg_name);
        graphs_being_building.back()->add_node(param_node);

        shared_ptr<VarSymbol> var_symbol = dynamic_pointer_cast<VarSymbol>(
            arg_cxt->assignable()->identifier()->symbol);
        auto proxy = graphs_being_building.back()->add_var_definition(var_symbol, param_node);

        check_last_uni();

        weak_ptr<AbstractBeginNode> w_begin_node = last_unisuccessor->get_begin_node();
        this->set_VarProxy_for_flow(w_begin_node, var_symbol, proxy);
    }

    return nullptr;
}

std::any IRGenerator::visitLiteral(JavaScriptParser::LiteralContext *ctx)
{
    auto visit_ret = std::any();

    /// StringLiteral does not matches AST node. We need to parse it through Literal node.
    string literal_text;

    if (ctx->BooleanLiteral() != nullptr) {
        literal_text = ctx->BooleanLiteral()->getText();
        bool bool_val;

        if (literal_text == "true") {
            bool_val = true;
        }
        else if (literal_text == "false") {
            bool_val = false;
        }
        else {
            throw JS2GraphError("Wrong bool literal");
        }

        auto bool_node = make_shared<LiteralBoolNode>(bool_val);
        graphs_being_building.back()->add_node(bool_node);

        return bool_node;
    }

    if (ctx->StringLiteral() != nullptr) {
        literal_text = ctx->StringLiteral()->getText();
        shared_ptr<LiteralStringNode> str_node = make_shared<LiteralStringNode>(literal_text, true);
        graphs_being_building.back()->add_node(str_node);
        return str_node;
    }

    if (ctx->numericLiteral() != nullptr) {
        visit_ret = this->visitNumericLiteral(ctx->numericLiteral());
        return visit_ret;
    }

    if (ctx->NullLiteral() != nullptr) {
        // TODO
    }

    return {};
}

std::any IRGenerator::visitNumericLiteral(JavaScriptParser::NumericLiteralContext *ctx)
{
    /// In JS, there is no distinction between int, float, and double,
    /// hence only the Decimal Literal item exists in the AST.
    std::any visit_ret = this->JavaScriptParserBaseVisitor::visitNumericLiteral(ctx);

    double value = 0.0;

    if (const auto node = ctx->DecimalLiteral()) {
        string s = node->getText();

        if (s.find("e") == std::string::npos) {
            value = std::stof(s);
        } else {
            // Compared to std::stof, this approach can handle scientific notation.
            // However, it lacks sufficient precision. For example, in the test case
            // gecko-dev_js_src_jit-test_tests_jaeger_bug625757.js, the number 5e-324
            // is processed as 0 using this method.
            // TODO: Should we retain the original number representation from the JS code instead?
            std::istringstream os(s);
            os >> value;
        }
    }
    else if (const auto hex_int_node = ctx->HexIntegerLiteral()) {
        const string s = hex_int_node->getText();
        value = std::stoull(s, 0, 16);
    }
    else if (auto octal_int_node = ctx->OctalIntegerLiteral()) {
        const string s = octal_int_node->getText();
        value = std::stoull(s, 0, 8);
    }
    else if (auto binary_int_node = ctx->BinaryIntegerLiteral()) {
        const string s = binary_int_node->getText();
        value = std::stoull(s, 0, 2);
    }

    auto float_node = make_shared<LiteralFloatNode>(value);
    graphs_being_building.back()->add_node(float_node);

    return float_node;
}

///
/// returnStatement
///    : Return ({this->notLineTerminator()}? expressionSequence)? eos
///    ;
///
std::any IRGenerator::visitReturnStatement(JavaScriptParser::ReturnStatementContext *ctx)
{
    /// The only subtree needed to traverse is the return value: expressionSequence
    shared_ptr<DataProducerNode> ret_value = nullptr;

    if (ctx->expressionSequence() != nullptr) {
        vector<JavaScriptParser::SingleExpressionContext *> expr_list =
                ctx->expressionSequence()->singleExpression();

        if (expr_list.empty()) {
            cout << "return value length is 0" << std::endl;
        }
        else if (expr_list.size() > 1) {
            /// When the return value expression sequences contains more than one expr,
            /// the evaluation result is the last expr.
            /// Therefore, the real return value is the last expr.
            /// However, such case is rare.
            throw JS2GraphError("The length of return value expression sequence is more than 1");
        }
        else {
            /// When there is only 1 expression in the sequences
            JavaScriptParser::SingleExpressionContext *expr = expr_list[0];
            ret_value = any2DataProducer(this->JavaScriptParserBaseVisitor::visit(expr));
        }
    }

    shared_ptr<ReturnNode> return_node = nullptr;
    if (ret_value == nullptr) {
        return_node = make_shared<ReturnNode>();
    }
    else {
        return_node = make_shared<ReturnNode>(ret_value);
    }

    /// handle the uses members
    return_node->post_construct();

    graphs_being_building.back()->add_node(return_node);

    /// The predecessor of ReturnNode must be UniSuccessorNode
    last_unisuccessor->set_next(return_node);

    /// return can only be a statement. It won't be expression in other statements.
    /// We do not need to return the data node.
    return nullptr;
}

///
/// ifStatement
///     : If '(' expressionSequence ')' statement (Else statement)?
///     ;
///
/// The evaluation result of expression sequence is the result of last expr.
///
std::any IRGenerator::visitIfStatement(JavaScriptParser::IfStatementContext *ctx)
{
    shared_ptr<DataProducerNode> condition_node = nullptr;

    JavaScriptParser::ExpressionSequenceContext *condition_expr = ctx->expressionSequence();

    /// If there is any sequential operation node with side effect generated in
    /// condition expression, the sequential chain will be set.
    /// New operation node will be attached after the last uni while before the If Node.
    vector<JavaScriptParser::SingleExpressionContext *> single_expr_list = condition_expr->singleExpression();
    for (auto &single_expr: single_expr_list) {
        std::any node_any = visit(single_expr);
        /// After the loop, the condition node will matches the last expr.
        condition_node = any2DataProducer(node_any);
    }

    /// create the true and false branch
    auto begin_true = make_shared<BeginNode>(this->fake_ctrl_node);
    graphs_being_building.back()->add_node(begin_true);

    auto begin_false = make_shared<BeginNode>(this->fake_ctrl_node);
    graphs_being_building.back()->add_node(begin_false);

    /// create the If node
    const auto if_node = make_shared<IfNode>(condition_node, begin_true, begin_false);
    if_node->post_construct();
    graphs_being_building.back()->add_node(if_node);

    /// Control flow continuation
    /// IfNode is not a uni successor node thus can not be the curretn flow node.
    auto uni_node = dynamic_pointer_cast<UniSuccessorNode>(this->last_unisuccessor);
    assert_or_throw_js2graph(uni_node != nullptr,
                           "The current flow node must be UniSuccessorNode");
    uni_node->set_next(if_node);

    /// traverse the true branch
    last_unisuccessor = begin_true;

    vector<JavaScriptParser::StatementContext *> stmts = ctx->statement();
    if (!stmts.empty()) {
        /// ctx.statement() returns the list of statements.
        /// The element at pos:0 is the 'if' branch，
        /// The element at pos:1 is the 'else' branch，
        visit(stmts[0]);
    }

    /// If the branch ends with a throw, the control flow of that branch
    /// jumps to catch or finally, and there is no continuing control flow afterwards.
    shared_ptr<EndNode> end_true = nullptr;
    bool true_end_with_throw = false;

    if (dynamic_pointer_cast<UnwindNode>(this->last_unisuccessor->next())) {
        true_end_with_throw = true;
    }
    else {
        end_true = make_shared<EndNode>();
        graphs_being_building.back()->add_node(end_true);

        check_last_uni();
        uni_node = dynamic_pointer_cast<UniSuccessorNode>(this->last_unisuccessor);

        if (uni_node->next() != begin_true) {
            uni_node->set_next(end_true);
        }
        else {
            begin_true->set_next(end_true);
        }
    }

    /// traverse the false branch
    last_unisuccessor = begin_false;

    if (stmts.size() > 1) {
        visit(stmts[1]);
    }

    /// If the branch ends with a throw, the control flow of that branch jumps to the catch
    /// or finally node, and there is no continuing control flow afterward.
    shared_ptr<EndNode> end_false = nullptr;
    bool false_end_with_throw = false;

    if (dynamic_pointer_cast<UnwindNode>(this->last_unisuccessor->next())) {
        false_end_with_throw = true;
    }
    else {
        /// Create the EndNode of false branch
        end_false = make_shared<EndNode>();
        graphs_being_building.back()->add_node(end_false);

        check_last_uni();
        uni_node = dynamic_pointer_cast<UniSuccessorNode>(this->last_unisuccessor);
        if (uni_node->next() != begin_true) {
            uni_node->set_next(end_false);
        } else {
            begin_false->set_next(end_false);
        }
    }

    /// A MergeNode needs to be generated only when both the true
    /// and false branches normally end without being terminated by a throw.
    if ((!true_end_with_throw) && (!false_end_with_throw)) {
        vector<weak_ptr<EndMayMergeNode> > merged_ends;
        merged_ends.push_back(end_true);
        merged_ends.push_back(end_false);
        const auto merge_node = make_shared<MergeNode>(merged_ends, this->fake_ctrl_node, MergeType::If);
        merge_node->post_construct();
        graphs_being_building.back()->add_node(merge_node);

        last_unisuccessor = merge_node;
    }
    else if (true_end_with_throw && false_end_with_throw) {
        /// If both branches ends with throw statements, the if-else won't proceed normally - control flow will jump to catch/finally.
        /// The false branch's current flow node (now processed) will be marked as throw, which subsequent code can check.
    }
    else {
        /// When a branch contains throw, no MergeNode is created - the if-else terminates control flow abnormally
        ///
        /// Normally: BeginNode starts branches, EndNode terminates them, then MergeNode joins both EndNodes
        ///
        /// Without MergeNode, EndNode can't simply terminate - we need to connect subsequent control flow
        ///
        /// CtrlRelayNode serves as this continuation point
        shared_ptr<EndNode> single_branch_end = nullptr;

        if (true_end_with_throw) {
            single_branch_end = end_false;
        }
        else if (false_end_with_throw) {
            single_branch_end = end_true;
        }

        auto relay_node = make_shared<CtrlRelayNode>(single_branch_end, this->fake_ctrl_node);
        relay_node->post_construct();
        graphs_being_building.back()->add_node(relay_node);

        last_unisuccessor = relay_node;
    }

    return nullptr;
}

void IRGenerator::remove_loop_phi(vector<pair<weak_ptr<AbstractBeginNode>,
                                              weak_ptr<PhiNode>>> &flow_and_phi_nodes,
                                  const shared_ptr<VarProxy>& var_proxy)
{
    ///
    /// The var proxy parameter represents the last var proxy found during loop analysis.
    /// Note: This may not necessarily be the proxy associated with the loop phi node.
    ///

    for (auto &[flow, phi_node]: flow_and_phi_nodes) {
        auto &symbol2proxies = this->flow2varProxies[flow];

        auto loop_phi_proxy = symbol2proxies[var_proxy->var_symbol].top();

        /// Remove the loop_phi_proxy entry from both varProxy2node and flow2varProxies.
        for (auto it = graphs_being_building.back()->varProxy2node.begin();
             it != graphs_being_building.back()->varProxy2node.end(); it++) {

            if (it->first == loop_phi_proxy) {
                graphs_being_building.back()->varProxy2node.erase(it);
                break;
            }
        }

        symbol2proxies[var_proxy->var_symbol].pop();
        if (symbol2proxies[var_proxy->var_symbol].empty()) {
            symbol2proxies.erase(var_proxy->var_symbol);
        }
    }

    for (auto &[flow, phi_node]: flow_and_phi_nodes) {
        ///
        /// Cleans up connections related to loop phi nodes.
        /// Any proxies in varProxy2node pointing to loop phis will be redirected
        /// to their corresponding real data nodes.
        ///
        phi_node.lock()->remove_unnecessary_loop_phi(graphs_being_building.back()->varProxy2node);

        /// remove phi node from graph
        ///
        auto &graph_nodes = graphs_being_building.back()->nodes;

        auto pos = std::find(graph_nodes.begin(),
                             graph_nodes.end(),
                             phi_node.lock());

        graph_nodes.erase(pos);
    }
}

std::any IRGenerator::visitForStatement(JavaScriptParser::ForStatementContext *ctx)
{
    check_last_uni();

    /// End the previous control flow uni node
    auto end_node = make_shared<EndNode>();
    graphs_being_building.back()->add_node(end_node);

    /// Create LoopBegin
    vector<weak_ptr<EndMayMergeNode>> begin_inputs;
    begin_inputs.push_back(end_node);
    auto loop_begin = make_shared<LoopBegin>(begin_inputs, fake_ctrl_node);
    graphs_being_building.back()->add_node(loop_begin);

    /// Create LoopEnd and LoopExit
    /// LoopEnd is an merging src of LoopBegin (Merge node), which means that
    /// after the loop body is executed once (meeting the continuation conditions),
    /// it returns to the beginning of the loop.
    ///
    /// The LoopBegin is the input of LoopEnd, indicating that the loop body may not be executed?
    auto loop_end = make_shared<LoopEnd>(loop_begin);
    graphs_being_building.back()->add_node(loop_end);
    loop_begin->merged_flows.push_back(loop_end);

    /// Maintain the reverse edge of the LoopBegin inputs edge
    /// Add LoopBegin to the uses of EndNode and LoopEnd
    loop_begin->post_construct();

    auto loop_exit = make_shared<LoopExit>(fake_ctrl_node);
    graphs_being_building.back()->add_node(loop_exit);

    /// Extract loop conditions

    /// To differentiate the expr
    unsigned long semi_0_index = ctx->SemiColon(0)->getSymbol()->getTokenIndex();
    unsigned long semi_1_index = ctx->SemiColon(1)->getSymbol()->getTokenIndex();

    JavaScriptParser::VariableDeclarationListContext *var_decls = nullptr;
    JavaScriptParser::ExpressionSequenceContext *init = nullptr;
    JavaScriptParser::ExpressionSequenceContext *condition = nullptr;
    JavaScriptParser::ExpressionSequenceContext *increment = nullptr;

    if (ctx->variableDeclarationList() != nullptr) {
        /// handling the init part
        var_decls = ctx->variableDeclarationList();

        vector<JavaScriptParser::ExpressionSequenceContext *> exprs = ctx->expressionSequence();
        for (auto &expr: exprs) {
            unsigned long expr_index = expr->start->getTokenIndex();
            if ((expr_index > semi_0_index) && (expr_index < semi_1_index)) {
                condition = expr;
            }
            else if (expr_index > semi_1_index) {
                increment = expr;
            }
            else {
                cout << "Failed at decide the for expr" << std::endl;
            }
        }
    }
    else {
        vector<JavaScriptParser::ExpressionSequenceContext *> exprs = ctx->expressionSequence();
        for (auto &expr: exprs) {
            size_t expr_index = expr->start->getTokenIndex();
            if (expr_index < semi_0_index) {
                init = expr;
            }
            else if ((expr_index > semi_0_index) && (expr_index < semi_1_index)) {
                condition = expr;
            }
            else if (expr_index > semi_1_index) {
                increment = expr;
            }
            else {
                cout << "Failed at deciding the for expr" << std::endl;
            }
        }
    }

    /// In the loop initialization section, there may be sequential operation nodes such as LoadNode.
    /// New uni node may be generated.
    /// The declared variable' proxies will be attached to the uni node before LoopBegin
    /// So we keep the last uni node as before.

    /// The situation of loop initialization (1).
    /// `for(a ; b ; c){}` a is variableDeclarationList
    ///

    /// There maybe fixed node in the var declaration or init part
    /// e.g.,
    /// for (i = -5; i < 100; i++)
    ///
    if (var_decls != nullptr) {
        visit(var_decls);
    }

    /// The situation of loop initialization (2).
    ///  `for(a ; b ; c) {}` a is expressionSequence
    if (init != nullptr) {
        visit(init);
    }

    last_unisuccessor->set_next(end_node);

    /// The possible fixed node in the init part
    /// Control flow node for loop initialization positioned before LoopBegin in the graph.
    ///
    /// After processing the initialization block:
    /// 1. New control flow nodes may be added
    /// 2. The last unified node (last_uni) gets updated
    ///
    /// Therefore, we set last_uni's successor to the end node only after completing the initialization block traversal.
    last_unisuccessor = loop_begin;

    /// Create the BeginNode for the loop body
    auto work_begin_node = make_shared<BeginNode>(fake_ctrl_node);
    graphs_being_building.back()->add_node(work_begin_node);
    last_unisuccessor = work_begin_node;

    /// Temporarily set the successor of the begin node to the loop end.
    /// If new uni nodes are added in subsequent parsing of loop body,
    /// they will be inserted in between.
    work_begin_node->set_next(loop_end);

    /// The loop condition may generate new var proxies!
    ///
    /// The loop condition is an `expressionSequence`, which may contain expressions that create var proxies.
    /// For example: `while (a--, a--, a--, a > 0) statement`
    /// In this case, the expression sequence generates new var proxies for `a`.
    ///
    /// A new var proxy created in the loop condition may affect the loop body,
    /// and the loop body may modify variables used in the condition.
    /// No matter which part is processed first, it cannot predict the changes made by the other.
    ///
    /// – If the loop condition is processed first, and the loop body modifies a variable,
    ///   then a PHI node is needed in the condition.
    /// – If the loop body is processed first, and the condition modifies a variable,
    ///   then a PHI node is needed in the loop body.
    ///
    /// Therefore, backfilling must be deferred until both parts are fully processed.
    ///

    /// When traversing the loop body,
    /// forcibly generate a loop phi for each variable that is used.
    this->loop_begins_should_gen_phi.insert(loop_begin);

    /// the map of loop phi nodes that need to be back filled for the current loop.
    /// This map will be pushed onto the stack.
    map<shared_ptr<VarSymbol>,
        vector<pair<weak_ptr<AbstractBeginNode>,
                    weak_ptr<PhiNode>>>> loop_need_fill;

    /// The LoopBegin node itself is used as the key
    this->phi_need_backfill.insert_or_assign(loop_begin, loop_need_fill);

    /// First, parse the loop body, then parse the loop condition.
    /// The var proxy created within the loop body affects the loop condition.

    /// When parsing the loop body, first set the next of loop_begin to the BeginNode of
    /// the loop body (which will later be changed to IfNode or others).
    /// During data flow analysis, the query will backtrack in the order of
    /// BeginNode -> LoopBegin.
    loop_begin->set_next(work_begin_node);

    /// Parse the loop body.
    /// The var proxy would be attached to the BeginNode.
    /// Note that after analyzing the loop body, the last uni node may have changed.
    visit(ctx->statement());

    /// Record the last unit after parsing the loop body.
    /// We use this variable name to explicitly show the current flow changing.
    auto loop_body_end_flow = last_unisuccessor;

    /// The incrementing part can be regarded as the code block executed after the loop body,
    /// so we also regard the incrementing part as the loop body.
    /// (the loop increment will only be executed if the loop body is executed first).
    ///
    /// We take the latest last uni after traversing the loop body as the last uni node
    /// so as to reflect the sequence relationship.
    /// That is, the newly generated var proxy in the loop increment is bound to
    /// loop_body_end_flow.
    /// The reason why cur flow node needs to be reassigned is because the variable may
    /// have been updated in the loop body.
    ///
    last_unisuccessor = loop_body_end_flow;
    if (increment != nullptr) {
        visit(increment);
    }

    /// There may be cfg nodes in the incremental part.
    /// So, after visiting the incremental part, we need to check the latest last uni node,
    /// its `next` property may be fake ctrl node to be replaced.
    /// The `next` property should be set to the LoopEnd.
    last_unisuccessor->set_next(loop_end);

    /// The `var proxy` within the for-loop body has been determined,
    /// and all loop phi nodes are bound to the `LoopBegin` node.
    ///
    /// All phi nodes needing backfilling are recorded in `phi_need_backfill`.
    /// For each, locate its corresponding variable symbol, then search backward
    /// from `LoopEnd` to `LoopBegin` to find a `var proxy` with the same name.
    /// If the found proxy is not a phi node awaiting backfill, use it to backfill the phi node.
    ///
    /// If no matching `var proxy` is found in the `BeginNode`, it means the variable
    /// is not assigned within the loop body. In this case, the loop phi node to be backfilled is removed,
    /// and its single child node is used as a replacement.
    ///
    /// If the only matching node found is the phi node itself (which only happens at `LoopBegin`),
    /// it is treated as redundant and removed similarly.
    /// (This cannot happen if the search endpoint is set to `BeginNode`.)
    ///
    auto &nodes_fill = this->phi_need_backfill[loop_begin];

    for (auto &[var_symbol, flow_phi_pairs]: nodes_fill) {
        /// When backfilling loop PHI nodes, we need to check if a var proxy is generated within the loop body.
        /// The search must be limited by a specific end point in the flow.
        /// The starting point of the search is the uni node right before the loop end.
        auto &search_end = loop_begin;
        vector<weak_ptr<AbstractBeginNode>> visited_begins;

        shared_ptr<VarProxy> var_proxy = get_VarProxy_from_flow(loop_end->get_begin_node(), var_symbol, visited_begins, search_end);

        if (var_proxy == nullptr) {
            /// If there is no proxy for this symbol within the loop body,
            /// the phi condition is invalid.
            ///
            /// This situation occurs when the query endpoint is BeginNode instead of
            /// LoopBegin.
            /// At this point, the loop phi nodes are bound to the LoopBegin node.
            /// When the query endpoint is LoopBegin, this branch does not occur.
            assert_or_throw_js2graph(false,
                                   "No var proxy in loop body, but there is a loop phi node");
        }
        else {
            for (auto &[flow, phi_node]: flow_phi_pairs) {

                auto real_node = graphs_being_building.back()->varProxy2node[var_proxy];

                if (auto real_phi = dynamic_pointer_cast<PhiNode>(real_node.lock()))
                {
                    if (real_phi->need_back_fill()) {
                        /// If the proxy found in the flow is still a phi node that needs to be filled,
                        /// the phi condition is invalid.
                        /// This situation does not occur when the query endpoint is set to the BeginNode.
                        remove_loop_phi(flow_phi_pairs, var_proxy);
                    }
                    else {
                        /// The existence of the phi node is established.
                        phi_node.lock()->back_fill(real_node);
                    }
                }
                else {
                    /// The existence of the phi node is established.
                    phi_node.lock()->back_fill(real_node);
                }
            }
        }
    }

    /// When traversing the loop condition, the flow should be set to the LoopBegin node.
    ///
    /// Loop conditions differ from loop bodies (including the increment step).
    /// It can be reached both before entering the loop and after executing the loop body.
    ///
    /// The loop body uses the BeginNode as its flow root. While traversing the body,
    /// if a var proxy is found in the BeginNode, it can be used directly—
    /// there's no need to consider branches before the loop.
    /// This is because accesses to variables defined before the loop,
    /// when made *inside* the loop body, do not go through a merge.
    /// Any necessary merges (loop PHI nodes) are already attached to the LoopBegin node.
    ///
    /// Setting the flow to LoopBegin allows direct access to all loop PHI nodes attached to it.
    /// These PHI nodes are the result of merging values from:
    /// – the EndNode (which reflects pre-loop code that may affect the condition), and
    /// – the LoopEnd (which reflects loop-body code that may also affect the condition),
    /// matching the semantics of the loop condition.
    ///
    /// Why not use BeginNode as the flow root?
    /// 1. The loop condition is evaluated even before the loop body executes,
    ///    so BeginNode is not appropriate.
    /// 2. Even if a var proxy is found in the BeginNode, it cannot be used directly
    ///    without merging—it effectively acts as the first statement inside the loop body.
    ///
    /// Attaching loop PHI nodes to the LoopBegin instead of the BeginNode
    /// also avoids redundant PHI construction for loop conditions.

    last_unisuccessor = loop_begin;

    ///
    /// When processing the loop condition, since the loop body has already been handled,
    /// PHI nodes can be created as needed without forced insertion or later backfilling.
    ///
    this->loop_begins_should_gen_phi.erase(loop_begin);

    shared_ptr<DataProducerNode> condition_node;
    if (condition != nullptr) {
        condition_node = any2DataProducer(visit(condition));
        //graphs_being_building.back()->add_node(condition_node);
    }
    else {
        /// If the loop condition is empty, it indicates an infinite loop.
        /// This test case should be abandoned.
        throw JS2GraphError("Unlimited loop. Drop this test case.");

        auto bool_node = make_shared<LiteralBoolNode>(true);
        graphs_being_building.back()->add_node(bool_node);
        condition_node = bool_node;
    }

    /// record the latest last uni in the condition.
    auto condition_end_flow_node = last_unisuccessor;

    auto loop_if_node = make_shared<LoopIf>(condition_node, work_begin_node, loop_exit);
    loop_if_node->post_construct();
    graphs_being_building.back()->add_node(loop_if_node);

    if (condition_end_flow_node != work_begin_node) {
        /// If there is any fixed operation node in conditional expression,
        /// its successor must be if node.
        condition_end_flow_node->set_next(loop_if_node);
    }
    else {
        /// Otherwise, the successor of loop begin is the loop if node.
        loop_begin->set_next(loop_if_node);
    }

    /// Whether the loop begin and loop if are neighborhoods,
    /// the loop begin has a member pointing to loop if.
    loop_begin->set_loop_if(loop_if_node);

    last_unisuccessor = loop_exit;

    return nullptr;
}

std::any IRGenerator::visitWhileStatement(JavaScriptParser::WhileStatementContext *ctx)
{
    /// end the preceding control flow
    shared_ptr<EndNode> end_node = make_shared<EndNode>();
    graphs_being_building.back()->add_node(end_node);
    last_unisuccessor->set_next(end_node);

    /// create LoopBegin
    vector<weak_ptr<EndMayMergeNode>> begin_inputs;
    begin_inputs.push_back(end_node);
    shared_ptr<LoopBegin> loop_begin = make_shared<LoopBegin>(begin_inputs, fake_ctrl_node);
    graphs_being_building.back()->add_node(loop_begin);
    last_unisuccessor = loop_begin;

    /// create LoopEnd
    shared_ptr<LoopEnd> loop_end = make_shared<LoopEnd>(loop_begin);
    graphs_being_building.back()->add_node(loop_end);
    loop_begin->merged_flows.push_back(loop_end);

    /// maintain the merge_node edge between LoopBegin and nodes be merged
    loop_begin->post_construct();

    shared_ptr<LoopExit> loop_exit = make_shared<LoopExit>(fake_ctrl_node);
    graphs_being_building.back()->add_node(loop_exit);

    JavaScriptParser::ExpressionSequenceContext *condition = ctx->expressionSequence();

    /// create the the BeginNode in loop body
    shared_ptr<BeginNode> work_begin_node = make_shared<BeginNode>(fake_ctrl_node);
    graphs_being_building.back()->add_node(work_begin_node);
    last_unisuccessor = work_begin_node;

    /// Temporarily set the successor of the begin node to the loop end.
    /// Subsequent control flow nodes within the loop body,
    /// ifany, will be inserted in between.
    work_begin_node->set_next(loop_end);

    /// When traversing the loop condition and loop body,
    /// a loop phi is explicitly generated for each variable that is used.
    this->loop_begins_should_gen_phi.insert(loop_begin);

    /// Phi nodes to be filled of this loop
    map<shared_ptr<VarSymbol>,
        vector<pair<weak_ptr<AbstractBeginNode>,
               weak_ptr<PhiNode>>>> loop_need_fill;

    this->phi_need_backfill.insert_or_assign(loop_begin, loop_need_fill);

    /// When processing the loop body, initially set LoopBegin's `next` to the body's BeginNode
    /// (this will later be updated to an IfNode).
    /// When querying a var proxy, the lookup will backtrack in the order: BeginNode -> LoopBegin.
    loop_begin->set_next(work_begin_node);

    /// Parse the loop condition first, then the loop body.
    /// Both the condition and the body may generate var proxies.
    /// The condition is processed first.

    /// When traversing the loop condition, set the flow to the LoopBegin node.
    /// Fixed nodes within the loop condition are attached after the LoopBegin node.
    /// Note: At this point, the predecessor of the condition's BeginNode is still LoopBegin.
    last_unisuccessor = loop_begin;

    shared_ptr<DataProducerNode> condition_node;
    if (condition != nullptr) {
        /// eval the expr sequence returns the the eval result of the last expr
        condition_node = any2DataProducer(visit(condition));
    }
    else {
        assert_or_throw_js2graph(false, "Infinite loop detected. Drop the test case.");
        return nullptr;
    }

    auto condition_end_flow_node = last_unisuccessor;

    /// Traverse the loop body.
    /// Var proxies should be added to the BeginNode.
    /// Note: The current flow node may change during traversal of the loop body.
    last_unisuccessor = work_begin_node;
    visit(ctx->statement());

    auto loop_body_end_flow = last_unisuccessor;
    assert_or_throw_js2graph(loop_body_end_flow != nullptr, "Loop body ends normal");
    loop_body_end_flow->set_next(loop_end);

    ///
    /// back fill the loop phi nodes
    ///
    auto &nodes_fill = this->phi_need_backfill[loop_begin];

    for (auto &[var_sym, flow_phi_pairs]: nodes_fill)
    {
        auto search_end = loop_begin;
        vector<weak_ptr<AbstractBeginNode> > visited_begins;
        shared_ptr<VarProxy> var_proxy = get_VarProxy_from_flow(loop_end->get_begin_node(), var_sym, visited_begins,search_end);

        if (var_proxy != nullptr)
        {
            for (auto &[flow, phi_node]: flow_phi_pairs)
            {
                auto real_node = graphs_being_building.back()->varProxy2node[var_proxy];

                if (auto real_phi = dynamic_pointer_cast<PhiNode>(real_node.lock()))
                {
                    if (real_phi->need_back_fill())
                    {
                        remove_loop_phi(flow_phi_pairs, var_proxy);

                        shared_ptr<DataProducerNode> real_data_node;

                        for (int i = 0; i < real_phi->inputs.size(); i++) {
                            if (!dynamic_pointer_cast<FakeDataProducerNode>(real_phi->inputs[i].lock())) {
                                real_data_node = dynamic_pointer_cast<DataProducerNode>(real_phi->inputs[i].lock());
                            }
                        }

                        if (real_phi == condition_node) {
                            condition_node = real_data_node;
                        }
                    }
                    else {
                        /// phi is established
                        phi_node.lock()->back_fill(real_node);
                    }
                }
                else {
                    /// phi is established
                    phi_node.lock()->back_fill(real_node);
                }
            }
        }
        else {
            assert_or_throw_js2graph(false,
                       "No var proxy in loop body, but there is a loop phi node");
        }
    }

    /// Loop if node
    auto loop_if_node = make_shared<LoopIf>(condition_node, work_begin_node, loop_exit);
    loop_if_node->post_construct();
    graphs_being_building.back()->add_node(loop_if_node);

    loop_begin->set_loop_if(loop_if_node);

    /// If the loop condition contains fixed nodes, the last fixed node should point to the IfNode.
    /// If there is no control flow in the condition, LoopBegin should directly connect to the LoopIf.
    if (condition_end_flow_node != work_begin_node) {
        condition_end_flow_node->set_next(loop_if_node);
    }
    else {
        loop_begin->set_next(loop_if_node);
    }

    last_unisuccessor = loop_exit;

    this->loop_begins_should_gen_phi.erase(loop_begin);

    return nullptr;
}

///
/// variableDeclaration
///    : assignable ('=' singleExpression)? // ECMAScript 6: Array & Object Matching
///    ;
///
/// assignable
///      : identifier
///      | arrayLiteral
///      | objectLiteral
///      ;
///
std::any IRGenerator::visitVariableDeclaration(JavaScriptParser::VariableDeclarationContext *ctx)
{
    shared_ptr<DataProducerNode> data_node = nullptr;

    if (ctx->assignable()->identifier() == nullptr) {
        throw JS2GraphError("assignable is not identifier");
    }

    string var_name = ctx->assignable()->identifier()->getText();

    if (ctx->Assign() != nullptr) {
        /// var definition
        data_node = any2DataProducer(this->visit(ctx->singleExpression()));
    }
    else {
        /// var decl in for-in loop
        //const auto prop_name_node = make_shared<ForInPropName>(var_name);
        //graphs_being_building.back()->add_node(prop_name_node);
        //data_node = prop_name_node;
    }

    /// declaration generates the first var proxy
    if (data_node != nullptr) {
        const shared_ptr<VarSymbol> var_symbol = ctx->var_symbol;

        const auto proxy = graphs_being_building.back()->add_var_definition(var_symbol, data_node);

        check_last_uni();
        const weak_ptr<AbstractBeginNode> begin_node = last_unisuccessor->get_begin_node();
        this->set_VarProxy_for_flow(begin_node, var_symbol, proxy);
    }

    return data_node;
}

shared_ptr<LiteralStringNode> IRGenerator::identifier_as_property_name(const string &property_name) const
{
    auto str_node = make_shared<LiteralStringNode>(property_name, false);
    graphs_being_building.back()->add_node(str_node);
    return str_node;
}

std::any IRGenerator::visitIdentifier(JavaScriptParser::IdentifierContext *ctx)
{
    /// The identifier in Function declaration does not need parsing
    if (dynamic_cast<JavaScriptParser::FunctionDeclarationContext *>(ctx->parent)) {
        return nullptr;
    }

    const string id_name = ctx->Identifier()->getText();

    /// When identifier is used as property name, we extract its string literal
    /// as a data flow node
    if (this->is_property_name && this->is_identifier_name) {
        return identifier_as_property_name(id_name);
    }

    shared_ptr<VarSymbol> var_symbol = dynamic_pointer_cast<VarSymbol>(ctx->symbol);
    assert_or_throw_js2graph(var_symbol != nullptr,
        "The identifier node has no VarSymbol");

    /// For lvalue, we return the var symbol
    if (ctx->is_left_value) {
        return var_symbol;
    }

    /// For rvalue, we return a data producer node.
    /// The data node matches the last var definition.
    /// We need to query the data node through var symbol.
    shared_ptr<DataProducerNode> variable_node = get_variable_node(var_symbol);

    return variable_node;
}

///
/// singleExpression:
///     singleExpression arguments # ArgumentsExpression
///
std::any IRGenerator::visitArgumentsExpression(JavaScriptParser::ArgumentsExpressionContext *ctx)
{
    /// handle function args
    vector<weak_ptr<DataProducerNode> > arg_nodes;

    vector<JavaScriptParser::ArgumentContext *> arguments = ctx->arguments()->argument();

    for (JavaScriptParser::ArgumentContext *arg: arguments) {
        if (arg->identifier() != nullptr) {
            shared_ptr<DataProducerNode> node = any2DataProducer(visit(arg->identifier()));
            arg_nodes.push_back(node);
        }
        else if (arg->singleExpression() != nullptr) {
            const auto visit_ret = visit(arg->singleExpression());
            shared_ptr<DataProducerNode> node = any2DataProducer(visit_ret);
            arg_nodes.push_back(node);
        }
    }

    if (const auto id_expr = dynamic_cast<JavaScriptParser::IdentifierExpressionContext *>(ctx->singleExpression())) {
        /// 1. function call
        JavaScriptParser::IdentifierContext *id_ctx = id_expr->identifier();

        const string id_name = id_ctx->getText();

        if (const auto function_symbol = dynamic_pointer_cast<VarSymbol>(id_ctx->symbol)) {

            /// Create the invoke node
            const auto invoke_node = make_shared<InvokeNode>(function_symbol->name, arg_nodes, fake_ctrl_node, InvokeType::CallFunction);
            invoke_node->post_construct();
            graphs_being_building.back()->add_node(invoke_node);

            this->check_reset_current_flow(invoke_node);

            /// Visiting the function call expression returns the return value node.
            /// The invoke represents the call return value
            return invoke_node;
        }
    }
    else if (const auto member_dot_expr =
        dynamic_cast<JavaScriptParser::MemberDotExpressionContext *>(ctx->singleExpression())) {
        /// 2. method call
        auto visit_ret_any = this->visit(member_dot_expr);

        shared_ptr<VarSymbol> var_sym;
        shared_ptr<DataProducerNode> load_node;

        if (visit_ret_any.type() == typeid(pair<shared_ptr<VarSymbol>,
                                                weak_ptr<DataProducerNode>>)) {
            auto var_sym_node = any_cast<pair<shared_ptr<VarSymbol>,
                                              weak_ptr<DataProducerNode>>>(visit_ret_any);
            var_sym = var_sym_node.first;
            load_node = var_sym_node.second.lock();
        }
        else if (visit_ret_any.type() == typeid(shared_ptr<LoadNode>)) {
            load_node = any2DataProducer(visit_ret_any);
        }

        if (auto load_field = dynamic_pointer_cast<LoadNode>(load_node); load_field != nullptr)
        {
            auto invoke_node = make_shared<InvokeMethodNode>(load_field, arg_nodes, fake_ctrl_node);
            invoke_node->post_construct();

            graphs_being_building.back()->add_node(invoke_node);
            this->check_reset_current_flow(invoke_node);

            return invoke_node;
        }

        assert_or_throw_js2graph(false, "Load node is invalid");
    }

    return nullptr;
}

///
/// The grammar of AssignmentExpression:
///
/// singleExpression:
/// | <assoc=right> singleExpression '=' singleExpression # AssignmentExpression
///
std::any IRGenerator::visitAssignmentExpression(JavaScriptParser::AssignmentExpressionContext *ctx)
{
    /// Visiting the second singleExpression will returns a data producer node
    auto node = visit(ctx->singleExpression(1));
    shared_ptr<DataProducerNode> right_node = any2DataProducer(node);

    /// handle the left part of the assignment
    JavaScriptParser::SingleExpressionContext *assign_target = ctx->singleExpression(0);

    if (dynamic_cast<JavaScriptParser::IdentifierExpressionContext *>(assign_target)) {
        /// When the left of assignment is an Identifier, it matches a VarSymbol.
        /// Now a new var proxy would be generated.
        const auto left = this->visit(assign_target);
        const auto left_sym = any_cast<shared_ptr<VarSymbol>>(left);

        const auto proxy = graphs_being_building.back()->add_var_definition(left_sym, right_node);

        check_last_uni();
        const auto begin_node = last_unisuccessor->get_begin_node();
        this->set_VarProxy_for_flow(begin_node, left_sym, proxy);
    }
    else if (const auto member_dot =
        dynamic_cast<JavaScriptParser::MemberDotExpressionContext *>(assign_target)) {
        /// MemberDotExpressionContext used as assignment target
        const auto visit_object_access_ret = this->visitMemberDotExpression(member_dot);

        auto object_field = any_cast<pair<weak_ptr<DataProducerNode>,
                                          weak_ptr<DataProducerNode>>>(visit_object_access_ret);

        auto [object_node, property_name_node] = object_field;

        const auto store_node = make_shared<StoreNode>(
            fake_ctrl_node, object_node, property_name_node, right_node, ObjectAccessType::field);
        store_node->post_construct();

        graphs_being_building.back()->add_node(store_node);
        this->check_reset_current_flow(store_node);
    }
    else if (const auto member_index =
        dynamic_cast<JavaScriptParser::MemberIndexExpressionContext *>(assign_target)) {

        auto visit_object_access_ret = this->visitMemberIndexExpression(member_index);

        auto object_field = any_cast<pair<weak_ptr<DataProducerNode>,
                                          weak_ptr<DataProducerNode>>>(visit_object_access_ret);

        auto [object_node, property_name_node] = object_field;

        const auto store_node = make_shared<StoreNode>(
            fake_ctrl_node, object_node, property_name_node, right_node, ObjectAccessType::index);
        store_node->post_construct();

        graphs_being_building.back()->add_node(store_node);
        this->check_reset_current_flow(store_node);
    }
    else {
        /// TODO:
        /// WebKit_JSTests_es6_destructuring_chained_object_destructuring.js
        throw JS2GraphError("The assignment target is not supported");

        return nullptr;
    }

    /// The value of an assignment expression is the value of the right-side operand.
    return right_node;
}

///
/// singleExpression:
///     Delete singleExpression # DeleteExpression
///
std::any IRGenerator::visitDeleteExpression(JavaScriptParser::DeleteExpressionContext *ctx)
{
    /// Visiting DeleteExpression returns a data node.
    /// The data node is either true or false.
    /// Delete success returns true，otherwise return false
    /// delete node matches a return data node likes Invoke node (CallTargetNode).

    auto del_tgt_node = any2DataProducer(
        visit(ctx->singleExpression()));

    /// create delete node
    auto delete_node = make_shared<DeleteNode>(fake_ctrl_node, del_tgt_node);
    delete_node->post_construct();
    graphs_being_building.back()->add_node(delete_node);

    this->check_reset_current_flow(delete_node);

    return delete_node;
}

///
/// PostIncrement and PostDecrement share the same logic except for the operator.
/// Likewise, PreIncrement and PreDecrement differ only in the operator.
/// PostX and PreX differ only in the return value; the rest is identical.
///
/// This function extracts the common logic.
///
/// @param expr The target expression of Post/Pre increment or decrement.
/// @param op   '+' for increment, '-' for decrement.
///
std::any IRGenerator::handle_postfix_prefix(JavaScriptParser::SingleExpressionContext *expr,
                                            shared_ptr<LanguageOperator> op,
                                            const SelfAssignmentType self_assignment_type)
{
    auto right_data_node = make_shared<LiteralFloatNode>(1);
    graphs_being_building.back()->add_node(right_data_node);

    /// Handle the `expr++` / `expr--` expressions.
    /// `expr` is an l-value.
    /// If `expr` is an identifier, it should return a var symbol when accessed.
    /// At the same time, `expr` is also used as an r-value input to the binary operation node.
    /// This behavior is similar to assignment operators, but different from assignment expressions.
    ///
    if (const auto member_dot = dynamic_cast<JavaScriptParser::MemberDotExpressionContext *>(expr))
    {
        auto data_node = gen_store4BinaryOp(
            member_dot, right_data_node, op, ObjectAccessType::field, self_assignment_type);
        return data_node;
    }

    if (const auto member_index = dynamic_cast<JavaScriptParser::MemberIndexExpressionContext *>(expr))
    {
        auto data_node = gen_store4BinaryOp(
            member_index, right_data_node, op, ObjectAccessType::index, self_assignment_type);
        return data_node;
    }

    if (const auto identifier_expr = dynamic_cast<JavaScriptParser::IdentifierExpressionContext *>(expr))
    {
        /// When the left side of an assignment is an Identifier, it should correspond to a VarSymbol.
        /// In this case, the assignment will generate a new variable proxy.
        const auto left = visit(identifier_expr);

        const auto left_sym = any_cast<shared_ptr<VarSymbol>>(left);

        weak_ptr<DataProducerNode> left_data_node = get_variable_node(left_sym);

        auto binary_op = make_shared<BinaryOpNode>(fake_ctrl_node, left_data_node, right_data_node, op);
        graphs_being_building.back()->add_node(binary_op);
        binary_op->post_construct();

        const auto proxy = graphs_being_building.back()->add_var_definition(left_sym, binary_op);

        check_last_uni();
        const auto begin_node = last_unisuccessor->get_begin_node();

        this->set_VarProxy_for_flow(begin_node, left_sym, proxy);

        check_reset_current_flow(binary_op);

        if (self_assignment_type == SelfAssignmentType::POST) {
            return left_data_node.lock();
        }
        else {
            return binary_op;
        }
    }

    /// TODO:
    /// WebKit_JSTests_es6_destructuring_chained_object_destructuring.js
    throw JS2GraphError("unsupported expression type for post decrease");

    return nullptr;
}

///
/// The return values of PostX and PreX nodes differ.
/// The node returned by PreX corresponds to the binary operation node,
/// which reflects the state after the increment/decrement operation is performed.
/// On the other hand, the node returned by PostX corresponds to the expression
/// node, representing the state before the increment/decrement operation is executed.

std::any IRGenerator::visitPostIncrementExpression(JavaScriptParser::PostIncrementExpressionContext *ctx)
{
    /// An increment operation requires a left value.
    const string add_op = "Add(+)";
    const string op_code = OperatorPairs::label2code(add_op);
    auto op = LanguageOperatorFactory::instance().get(add_op, op_code);

    /// For identifier expressions: return a var symbol
    /// For MemberDot/MemberIndex: generate a StoreNode
    const auto expr = ctx->singleExpression();

    auto node = this->handle_postfix_prefix(expr, op, SelfAssignmentType::POST);
    return node;
}

std::any IRGenerator::visitPostDecreaseExpression(JavaScriptParser::PostDecreaseExpressionContext *ctx)
{
    /// X-- requires that X must be a lvalue.
    const string minus_op = "Minus(-)";
    const string op_code = OperatorPairs::label2code(minus_op);
    auto op = LanguageOperatorFactory::instance().get(minus_op, op_code);

    auto expr = ctx->singleExpression();

    auto node_before_op = this->handle_postfix_prefix(expr, op, SelfAssignmentType::POST);
    return node_before_op;
}

std::any IRGenerator::visitPreIncrementExpression(JavaScriptParser::PreIncrementExpressionContext *ctx)
{
    const string add_op = "Add(+)";
    const string op_code = OperatorPairs::label2code(add_op);
    auto op = LanguageOperatorFactory::instance().get(add_op, op_code);

    const auto expr = ctx->singleExpression();

    auto node_after_op = this->handle_postfix_prefix(expr, op, SelfAssignmentType::PRE);
    return node_after_op;
}

std::any IRGenerator::visitPreDecreaseExpression(JavaScriptParser::PreDecreaseExpressionContext *ctx)
{
    const string minus_op = "Minus(-)";
    const string op_code = OperatorPairs::label2code(minus_op);
    auto op = LanguageOperatorFactory::instance().get(minus_op, op_code);

    const auto expr = ctx->singleExpression();

    auto node_after_op = this->handle_postfix_prefix(expr, op, SelfAssignmentType::PRE);
    return node_after_op;
}

/**
 * The following six expressions are unary operations, each with a single operand expression.
 *
 * Void singleExpression                                                 # VoidExpression
 * Typeof singleExpression                                               # TypeofExpression
 * '+' singleExpression                                                  # UnaryPlusExpression
 * '-' singleExpression                                                  # UnaryMinusExpression
 * '~' singleExpression                                                  # BitNotExpression
 * '!' singleExpression                                                  # NotExpression
 */

/**
 * void is a unary operator that appears before its single operand, which may be of any type.
 * This operator is unusual and infrequently used; it evaluates its operand, then
 * discards the value and returns undefined. Since the operand value is discarded, using
 * the void operator makes sense only if the operand has side effects.
 */
///
/// singleExpression:
///     Void singleExpression # VoidExpression
///
std::any IRGenerator::visitVoidExpression(JavaScriptParser::VoidExpressionContext *ctx)
{
    const string void_op = "void";
    const string op_code = OperatorPairs::label2code(void_op);
    auto op = LanguageOperatorFactory::instance().get(void_op, op_code);

    /// get the data node
    JavaScriptParser::SingleExpressionContext *data = ctx->singleExpression();
    shared_ptr<DataProducerNode> data_node = any2DataProducer(visit(data));

    auto void_node = make_shared<UnaryOpNode>(fake_ctrl_node, data_node, op);
    void_node->post_construct();

    graphs_being_building.back()->add_node(void_node);

    check_reset_current_flow(void_node);
    return void_node;
}

std::any IRGenerator::visitTypeofExpression(JavaScriptParser::TypeofExpressionContext *ctx)
{
    const string typeof_op = "typeof";
    const string op_code = OperatorPairs::label2code(typeof_op);
    auto op = LanguageOperatorFactory::instance().get(typeof_op, op_code);

    /// get the data node
    JavaScriptParser::SingleExpressionContext *data = ctx->singleExpression();
    shared_ptr<DataProducerNode> data_node = any2DataProducer(visit(data));

    auto typeof_node = make_shared<UnaryOpNode>(fake_ctrl_node, data_node, op);
    typeof_node->post_construct();

    graphs_being_building.back()->add_node(typeof_node);

    check_reset_current_flow(typeof_node);
    return typeof_node;
}

std::any IRGenerator::visitUnaryPlusExpression(JavaScriptParser::UnaryPlusExpressionContext *ctx)
{
    const string plus_op = "UnaryPlus(+)";
    const string op_code = OperatorPairs::label2code(plus_op);
    auto op = LanguageOperatorFactory::instance().get(plus_op, op_code);

    /// get the data node
    JavaScriptParser::SingleExpressionContext *data = ctx->singleExpression();
    shared_ptr<DataProducerNode> data_node = any2DataProducer(visit(data));

    auto plus_node = make_shared<UnaryOpNode>(fake_ctrl_node, data_node, op);
    plus_node->post_construct();

    graphs_being_building.back()->add_node(plus_node);

    check_reset_current_flow(plus_node);
    return plus_node;
}

std::any IRGenerator::visitUnaryMinusExpression(JavaScriptParser::UnaryMinusExpressionContext *ctx)
{
    const string plus_op = "UnaryMinus(-)";
    const string op_code = OperatorPairs::label2code(plus_op);
    auto op = LanguageOperatorFactory::instance().get(plus_op, op_code);

    /// get the data node
    JavaScriptParser::SingleExpressionContext *data = ctx->singleExpression();
    shared_ptr<DataProducerNode> data_node = any2DataProducer(visit(data));

    auto minus_node = make_shared<UnaryOpNode>(fake_ctrl_node, data_node, op);
    minus_node->post_construct();

    graphs_being_building.back()->add_node(minus_node);

    check_reset_current_flow(minus_node);
    return minus_node;
}

std::any IRGenerator::visitBitNotExpression(JavaScriptParser::BitNotExpressionContext *ctx)
{
    /// get the data node
    JavaScriptParser::SingleExpressionContext *data = ctx->singleExpression();
    shared_ptr<DataProducerNode> data_node = any2DataProducer(visit(data));

    const string op_label = "BitNot(~)";
    const string op_code = OperatorPairs::label2code(op_label);
    auto op = LanguageOperatorFactory::instance().get(op_label, op_code);

    auto bitnot_node = make_shared<UnaryOpNode>(fake_ctrl_node, data_node, op);

    bitnot_node->post_construct();

    graphs_being_building.back()->add_node(bitnot_node);

    check_reset_current_flow(bitnot_node);
    return bitnot_node;
}

std::any IRGenerator::visitNotExpression(JavaScriptParser::NotExpressionContext *ctx)
{
    /// get the data node
    JavaScriptParser::SingleExpressionContext *data = ctx->singleExpression();
    shared_ptr<DataProducerNode> data_node = any2DataProducer(visit(data));

    const string op_label = "Not(!)";
    const string op_code = OperatorPairs::label2code(op_label);
    auto op = LanguageOperatorFactory::instance().get(op_label, op_code);

    auto not_node = make_shared<UnaryOpNode>(fake_ctrl_node, data_node, op);
    not_node->post_construct();

    graphs_being_building.back()->add_node(not_node);

    check_reset_current_flow(not_node);
    return not_node;
}

std::any IRGenerator::visitPowerExpression(JavaScriptParser::PowerExpressionContext *ctx)
{
    JavaScriptParser::SingleExpressionContext *left = ctx->singleExpression(0);
    JavaScriptParser::SingleExpressionContext *right = ctx->singleExpression(1);

    const string op_label = "Power(**)";
    const string op_code = OperatorPairs::label2code(op_label);
    auto op = LanguageOperatorFactory::instance().get(op_label, op_code);

    shared_ptr<DataProducerNode> left_data_node = any2DataProducer(visit(left));

    auto ret = visit(right);
    shared_ptr<DataProducerNode> right_data_node = any2DataProducer(ret);

    auto power_node = make_shared<BinaryOpNode>(fake_ctrl_node, left_data_node, right_data_node, op);
    power_node->post_construct();

    graphs_being_building.back()->add_node(power_node);

    check_reset_current_flow(power_node);
    return power_node;
}

///
/// The following are various instances of singleExpression.
///

/**
 * relational expression
 *
 * singleExpression ('<' | '>' | '<=' | '>=') singleExpression
 */
std::any IRGenerator::visitRelationalExpression(JavaScriptParser::RelationalExpressionContext *ctx)
{
    JavaScriptParser::SingleExpressionContext *left = ctx->singleExpression(0);
    JavaScriptParser::SingleExpressionContext *right = ctx->singleExpression(1);

    string op_label;

    /**
     * 4 relation '<' | '>' | '<=' | '>='
     */
    if (ctx->MoreThan() != nullptr) {
        op_label = ">";
    }
    else if (ctx->LessThan() != nullptr) {
        op_label = "<";
    }
    else if (ctx->GreaterThanEquals() != nullptr) {
        op_label = ">=";
    }
    else if (ctx->LessThanEquals() != nullptr) {
        op_label = "<=";
    }
    else {
        cout << "Error in relational operator." << std::endl;
    }

    const string op_code = OperatorPairs::label2code(op_label);
    auto op = LanguageOperatorFactory::instance().get(op_label, op_code);

    shared_ptr<DataProducerNode> left_data_node = any2DataProducer(visit(left));
    shared_ptr<DataProducerNode> right_data_node = any2DataProducer(visit(right));

    auto relational_node = make_shared<BinaryOpNode>(fake_ctrl_node, left_data_node, right_data_node, op);
    relational_node->post_construct();

    graphs_being_building.back()->add_node(relational_node);

    check_reset_current_flow(relational_node);
    return relational_node;
}

std::any IRGenerator::visitInstanceofExpression(JavaScriptParser::InstanceofExpressionContext *ctx)
{
    JavaScriptParser::SingleExpressionContext *left = ctx->singleExpression(0);
    JavaScriptParser::SingleExpressionContext *right = ctx->singleExpression(1);

    const string op_label = "instanceof";
    const string op_code = OperatorPairs::label2code(op_label);
    auto op = LanguageOperatorFactory::instance().get(op_label, op_code);

    shared_ptr<DataProducerNode> left_data_node = any2DataProducer(visit(left));

    auto ret = visit(right);
    shared_ptr<DataProducerNode> right_data_node = any2DataProducer(ret);

    auto instanceof_node = make_shared<BinaryOpNode>(fake_ctrl_node,
                                                     left_data_node,
                                                     right_data_node,
                                                     op);

    graphs_being_building.back()->add_node(instanceof_node);
    instanceof_node->post_construct();

    check_reset_current_flow(instanceof_node);
    return instanceof_node;
}

std::any IRGenerator::visitInExpression(JavaScriptParser::InExpressionContext *ctx)
{
    JavaScriptParser::SingleExpressionContext *left = ctx->singleExpression(0);
    JavaScriptParser::SingleExpressionContext *right = ctx->singleExpression(1);

    const string op_label = "in";
    const string op_code = OperatorPairs::label2code(op_label);
    auto op = LanguageOperatorFactory::instance().get(op_label, op_code);

    shared_ptr<DataProducerNode> left_data_node = any2DataProducer(visit(left));

    auto ret = visit(right);
    shared_ptr<DataProducerNode> right_data_node = any2DataProducer(ret);

    auto in_node = make_shared<BinaryOpNode>(fake_ctrl_node,
                                             left_data_node,
                                             right_data_node,
                                             op);
    in_node->post_construct();

    graphs_being_building.back()->add_node(in_node);

    check_reset_current_flow(in_node);
    return in_node;
}


/**
 * singleExpression ('+' | '-') singleExpression
 */
std::any IRGenerator::visitAdditiveExpression(JavaScriptParser::AdditiveExpressionContext *ctx)
{
    JavaScriptParser::SingleExpressionContext *left = ctx->singleExpression(0);
    JavaScriptParser::SingleExpressionContext *right = ctx->singleExpression(1);

    string op_label;

    if (ctx->Plus() != nullptr) {
        op_label = "Add(+)";
    }
    else if (ctx->Minus() != nullptr) {
        op_label = "Minus(-)";
    }
    else {
        assert_or_throw_js2graph(false, "Error type in additive operator");
    }

    const string op_code = OperatorPairs::label2code(op_label);
    auto op = LanguageOperatorFactory::instance().get(op_label, op_code);

    shared_ptr<DataProducerNode> left_data_node = any2DataProducer(visit(left));

    auto ret = visit(right);
    shared_ptr<DataProducerNode> right_data_node = any2DataProducer(ret);

    auto add_node = make_shared<BinaryOpNode>(fake_ctrl_node, left_data_node, right_data_node, op);
    add_node->post_construct();

    graphs_being_building.back()->add_node(add_node);

    check_reset_current_flow(add_node);
    return add_node;
}

/**
 * singleExpression ('*' | '/' | '%') singleExpression
 */
std::any IRGenerator::visitMultiplicativeExpression(JavaScriptParser::MultiplicativeExpressionContext *ctx)
{
    JavaScriptParser::SingleExpressionContext *left = ctx->singleExpression(0);
    JavaScriptParser::SingleExpressionContext *right = ctx->singleExpression(1);

    string op_label;
    if (ctx->Multiply() != nullptr) {
        op_label = "Mul(*)";
    }
    else if (ctx->Divide() != nullptr) {
        op_label = "Div(/)";
    }
    else if (ctx->Modulus() != nullptr) {
        op_label = "Mod(%)";
    }
    else {
        cout << "Error in multiplicative operator." << std::endl;
    }

    const string op_code = OperatorPairs::label2code(op_label);
    auto op = LanguageOperatorFactory::instance().get(op_label, op_code);

    shared_ptr<DataProducerNode> left_data_node = any2DataProducer(visit(left));
    shared_ptr<DataProducerNode> right_data_node = any2DataProducer(visit(right));

    auto mul_node = make_shared<BinaryOpNode>(fake_ctrl_node, left_data_node, right_data_node, op);
    mul_node->post_construct();

    graphs_being_building.back()->add_node(mul_node);

    check_reset_current_flow(mul_node);
    return mul_node;
}

/**
 * singleExpression ('<<' | '>>' | '>>>') singleExpression               # BitShiftExpression
 */
std::any IRGenerator::visitBitShiftExpression(JavaScriptParser::BitShiftExpressionContext *ctx)
{
    JavaScriptParser::SingleExpressionContext *left = ctx->singleExpression(0);
    JavaScriptParser::SingleExpressionContext *right = ctx->singleExpression(1);

    string op_label;
    if (ctx->LeftShiftArithmetic() != nullptr) {
        op_label = "<<";
    }
    else if (ctx->RightShiftArithmetic() != nullptr) {
        op_label = ">>";
    }
    else if (ctx->RightShiftLogical() != nullptr) {
        op_label = ">>>";
    }
    else {
        throw JS2GraphError("Error in recognize BitShiftExpression operator");
    }

    const string op_code = OperatorPairs::label2code(op_label);
    auto op = LanguageOperatorFactory::instance().get(op_label, op_code);

    shared_ptr<DataProducerNode> left_data_node = any2DataProducer(visit(left));

    auto ret = visit(right);
    shared_ptr<DataProducerNode> right_data_node = any2DataProducer(ret);

    auto shift_node = make_shared<BinaryOpNode>(fake_ctrl_node, left_data_node, right_data_node, op);
    shift_node->post_construct();

    graphs_being_building.back()->add_node(shift_node);

    check_reset_current_flow(shift_node);
    return shift_node;
}

/**
 * singleExpression:
 * singleExpression ('==' | '!=' | '===' | '!==') singleExpression       # EqualityExpression
 */
std::any IRGenerator::visitEqualityExpression(JavaScriptParser::EqualityExpressionContext *ctx)
{
    JavaScriptParser::SingleExpressionContext *left = ctx->singleExpression(0);
    JavaScriptParser::SingleExpressionContext *right = ctx->singleExpression(1);

    string op_label;

    if (ctx->Equals_() != nullptr) {
        op_label = "==";
    } else if (ctx->NotEquals() != nullptr) {
        op_label = "!=";
    } else if (ctx->IdentityEquals() != nullptr) {
        op_label = "===";
    } else if (ctx->IdentityNotEquals() != nullptr) {
        op_label = "!==";
    } else {
        cout << "Error in equality operator." << std::endl;
    }

    const string op_code = OperatorPairs::label2code(op_label);
    auto op = LanguageOperatorFactory::instance().get(op_label, op_code);

    shared_ptr<DataProducerNode> left_data_node = any2DataProducer(visit(left));
    shared_ptr<DataProducerNode> right_data_node = any2DataProducer(visit(right));

    auto equality_node = make_shared<BinaryOpNode>(fake_ctrl_node, left_data_node, right_data_node, op);
    equality_node->post_construct();

    graphs_being_building.back()->add_node(equality_node);

    check_reset_current_flow(equality_node);
    return equality_node;
}

/**
 * singleExpression '&' singleExpression # BitAndExpression
 */
std::any IRGenerator::visitBitAndExpression(JavaScriptParser::BitAndExpressionContext *ctx)
{
    JavaScriptParser::SingleExpressionContext *left = ctx->singleExpression(0);
    JavaScriptParser::SingleExpressionContext *right = ctx->singleExpression(1);

    const string op_label = "&";
    const string op_code = OperatorPairs::label2code(op_label);
    auto op = LanguageOperatorFactory::instance().get(op_label, op_code);

    shared_ptr<DataProducerNode> left_data_node = any2DataProducer(visit(left));
    shared_ptr<DataProducerNode> right_data_node = any2DataProducer(visit(right));

    auto bin_node = make_shared<BinaryOpNode>(fake_ctrl_node, left_data_node, right_data_node, op);
    bin_node->post_construct();

    graphs_being_building.back()->add_node(bin_node);

    check_reset_current_flow(bin_node);
    return bin_node;
}

/**
 * singleExpression '&' singleExpression # BitAndExpression
 */
std::any IRGenerator::visitBitXOrExpression(JavaScriptParser::BitXOrExpressionContext *ctx)
{
    JavaScriptParser::SingleExpressionContext *left = ctx->singleExpression(0);
    JavaScriptParser::SingleExpressionContext *right = ctx->singleExpression(1);

    const string op_label = "^";
    const string op_code = OperatorPairs::label2code(op_label);
    auto op = LanguageOperatorFactory::instance().get(op_label, op_code);

    shared_ptr<DataProducerNode> left_data_node = any2DataProducer(visit(left));
    shared_ptr<DataProducerNode> right_data_node = any2DataProducer(visit(right));

    auto bin_node = make_shared<BinaryOpNode>(fake_ctrl_node, left_data_node, right_data_node, op);
    bin_node->post_construct();

    graphs_being_building.back()->add_node(bin_node);

    check_reset_current_flow(bin_node);
    return bin_node;
}

/**
 * singleExpression '|' singleExpression # BitOrExpression
 */
std::any IRGenerator::visitBitOrExpression(JavaScriptParser::BitOrExpressionContext *ctx)
{
    JavaScriptParser::SingleExpressionContext *left = ctx->singleExpression(0);
    JavaScriptParser::SingleExpressionContext *right = ctx->singleExpression(1);

    const string op_label = "|";
    const string op_code = OperatorPairs::label2code(op_label);
    auto op = LanguageOperatorFactory::instance().get(op_label, op_code);

    shared_ptr<DataProducerNode> left_data_node = any2DataProducer(visit(left));
    shared_ptr<DataProducerNode> right_data_node = any2DataProducer(visit(right));

    auto bin_node = make_shared<BinaryOpNode>(fake_ctrl_node, left_data_node, right_data_node, op);
    bin_node->post_construct();

    graphs_being_building.back()->add_node(bin_node);
    check_reset_current_flow(bin_node);

    return bin_node;
}

/**
 * singleExpression '&&' singleExpression # LogicalAndExpression
 */
std::any IRGenerator::visitLogicalAndExpression(JavaScriptParser::LogicalAndExpressionContext *ctx)
{
    JavaScriptParser::SingleExpressionContext *left = ctx->singleExpression(0);
    JavaScriptParser::SingleExpressionContext *right = ctx->singleExpression(1);

    const string op_label = "&&";
    const string op_code = OperatorPairs::label2code(op_label);
    auto op = LanguageOperatorFactory::instance().get(op_label, op_code);

    shared_ptr<DataProducerNode> left_data_node = any2DataProducer(visit(left));
    shared_ptr<DataProducerNode> right_data_node = any2DataProducer(visit(right));

    auto logical_node = make_shared<BinaryOpNode>(fake_ctrl_node, left_data_node, right_data_node, op);
    logical_node->post_construct();

    graphs_being_building.back()->add_node(logical_node);

    check_reset_current_flow(logical_node);
    return logical_node;
}

/**
 * singleExpression '||' singleExpression # LogicalOrExpression
 */
std::any IRGenerator::visitLogicalOrExpression(JavaScriptParser::LogicalOrExpressionContext *ctx)
{
    JavaScriptParser::SingleExpressionContext *left = ctx->singleExpression(0);
    JavaScriptParser::SingleExpressionContext *right = ctx->singleExpression(1);

    const string op_label = "||";
    const string op_code = OperatorPairs::label2code(op_label);
    auto op = LanguageOperatorFactory::instance().get(op_label, op_code);

    shared_ptr<DataProducerNode> left_data_node = any2DataProducer(visit(left));
    shared_ptr<DataProducerNode> right_data_node = any2DataProducer(visit(right));

    auto logical_node = make_shared<BinaryOpNode>(fake_ctrl_node, left_data_node, right_data_node, op);
    logical_node->post_construct();

    graphs_being_building.back()->add_node(logical_node);

    check_reset_current_flow(logical_node);
    return logical_node;
}

/**
 * Only TernaryExpression is TernaryOpNode
 *
 * The conditional operator is the only ternary operator (three operands) in JavaScript
 * and is sometimes actually called the ternary operator.
 */
std::any IRGenerator::visitTernaryExpression(JavaScriptParser::TernaryExpressionContext *ctx)
{
    JavaScriptParser::SingleExpressionContext *operand_1 = ctx->singleExpression(0);
    JavaScriptParser::SingleExpressionContext *operand_2 = ctx->singleExpression(1);
    JavaScriptParser::SingleExpressionContext *operand_3 = ctx->singleExpression(2);

    shared_ptr<DataProducerNode> operand_1_node = any2DataProducer(visit(operand_1));
    shared_ptr<DataProducerNode> operand_2_node = any2DataProducer(visit(operand_2));
    shared_ptr<DataProducerNode> operand_3_node = any2DataProducer(visit(operand_3));

    shared_ptr<TernaryOpNode> ternary_node = make_shared<TernaryOpNode>(operand_1_node,
                                                                        operand_2_node,
                                                                        operand_3_node);
    ternary_node->post_construct();

    graphs_being_building.back()->add_node(ternary_node);
    return ternary_node;
}

///
/// The following is support for objects
///

std::any IRGenerator::visitObjectLiteral(JavaScriptParser::ObjectLiteralContext *ctx)
{
    vector<JavaScriptParser::PropertyAssignmentContext *> property_assignments = ctx->propertyAssignment();

    /// We construct ObjectLiteralNode first, because when visiting FunctionProperty we need
    /// to know which ObjectLiteralNode we are in.
    /// A vector is used as stack to keep the currently processing object literal
    auto object_literal_node = make_shared<ObjectLiteralNode>();
    this->current_object_literals.push_back(object_literal_node);

    /// Production rule:
    ///   propertyAssignment -> PropertyExpressionAssignment
    ///   propertyAssignment -> ComputedPropertyExpression
    vector<weak_ptr<PropExprAssignNode>> prop_assigns;

    /// Production rule:
    ///   propertyAssignment -> FunctionProperty
    vector<weak_ptr<FunctionPropertyNode> > prop_funcs;

    for (auto &prop_assign: property_assignments)
    {
        if (dynamic_cast<JavaScriptParser::PropertyExpressionAssignmentContext *>(prop_assign)
            || dynamic_cast<JavaScriptParser::ComputedPropertyExpressionAssignmentContext *>(prop_assign))
        {
            weak_ptr<DataProducerNode> prop_node_float = any2DataProducer(this->visit(prop_assign));
            auto prop_node = dynamic_pointer_cast<PropExprAssignNode>(prop_node_float.lock());
            prop_assigns.push_back(prop_node);
        }
        else if (dynamic_cast<JavaScriptParser::FunctionPropertyContext *>(prop_assign)) {
            auto node_any = this->visit(prop_assign);
            if (node_any.type() == typeid(shared_ptr<FunctionPropertyNode>)) {
                auto func_node = std::any_cast<shared_ptr<FunctionPropertyNode> >(node_any);
                prop_funcs.push_back(func_node);
            }
        }
        else {
            /// failed test: WebKit_JSTests_stress_proxy-getOwnPropertySlots-exceptionChecks.js
            throw JS2GraphError("Not supported PropertyAssignment type");
        }
    }

    /// Now, we know the inputs of objectLiteralNode.
    /// Meanwhile, when visiting MethodNode, we know which objectLiteral we are in.
    object_literal_node->post_construct(prop_assigns, prop_funcs);

    graphs_being_building.back()->add_node(object_literal_node);
    return object_literal_node;
}

std::any IRGenerator::visitPropertyName(JavaScriptParser::PropertyNameContext *ctx)
{
    ///
    /// Production rule:
    ///   propertyName -> '[' singleExpression ']'
    ///
    if (ctx->singleExpression() != nullptr) {
        /*
         * In this case, PropertyName(AST node) has three "children": OpenBracket, singleExpression and CloseBracket
         * If we visit the nodes by
         * `return this->JavaScriptParserBaseVisitor::visitPropertyName(ctx);`
         * AbstractParseTreeVisitor's aggregateResult function will be called. Due to the default implementation
         * of aggregateResult, the return value is always the last result. As a result, the return value is an
         * empty std::any.
         *
         * We can override the aggregateResult function, but the influence is large.
         * A more simple solution is to only visit the useful child : singleExpression.
         * We ignore the OpenBracket and CloseBracket.
         *
         * This is a simple way.
         */
        return this->JavaScriptParserBaseVisitor::visit(ctx->singleExpression());
    }

    ///
    /// Production rule:
    ///   propertyName -> StringLiteral
    ///
    if (auto string_literal = ctx->StringLiteral()) {
        /// Since `StringLiteral` has no corresponding AST node, directly calling
        /// `this->JavaScriptParserBaseVisitor::visitPropertyName(ctx)`
        /// will have no effect—this class does not override the method, so no processing will occur.
        /// Therefore, it must be handled separately by directly extracting the literal's text.
        ///
        string literal_text = string_literal->getText();

        shared_ptr<LiteralStringNode> str_node = make_shared<LiteralStringNode>(literal_text, true);
        graphs_being_building.back()->add_node(str_node);

        return str_node;
    }

    /*
     * Production rule:
     *   propertyName -> identifierName
     *   propertyName -> StringLiteral
     *   propertyName -> numericLiteral
     */
    this->is_property_name = true;
    auto visit_ret = this->JavaScriptParserBaseVisitor::visitPropertyName(ctx);
    this->is_property_name = false;

    return visit_ret;

}

///
/// When an identifier is used as a PropertyName, the identifier node is always under an identifierName node.
///
std::any IRGenerator::visitIdentifierName(JavaScriptParser::IdentifierNameContext *ctx)
{
    /// Set the is_identifier_name flag. When encountering an identifier node,
    /// check both the is_identifier_name and is_property_name flags.
    /// If both flags are set, the identifier is considered a property name.
    bool under_property_name = false;

    if (dynamic_cast<JavaScriptParser::PropertyNameContext *>(ctx->parent) != nullptr
        || dynamic_cast<JavaScriptParser::MemberDotExpressionContext *>(ctx->parent) != nullptr)
    {
        this->is_identifier_name = true;
        under_property_name = true;
    }

    auto visit_ret = this->JavaScriptParserBaseVisitor::visitIdentifierName(ctx);

    if (under_property_name == true) {
        this->is_identifier_name = false;
    }

    return visit_ret;
}

std::any IRGenerator::visitPropertyExpressionAssignment(JavaScriptParser::PropertyExpressionAssignmentContext *ctx)
{
    // property name
    JavaScriptParser::PropertyNameContext *prop_name = ctx->propertyName();
    weak_ptr<DataProducerNode> property_name = any2DataProducer(this->visit(prop_name));
    weak_ptr<DataProducerNode> property_value = any2DataProducer(this->visit(ctx->singleExpression()));

    auto prop_node = make_shared<PropExprAssignNode>(property_name, property_value);
    prop_node->post_construct();

    graphs_being_building.back()->add_node(prop_node);
    return prop_node;
}

std::any IRGenerator::visitComputedPropertyExpressionAssignment(
    JavaScriptParser::ComputedPropertyExpressionAssignmentContext *ctx)
{
    weak_ptr<DataProducerNode> property_name = any2DataProducer(this->visit(ctx->singleExpression(0)));
    weak_ptr<DataProducerNode> property_value = any2DataProducer(this->visit(ctx->singleExpression(1)));

    auto prop_node = make_shared<PropExprAssignNode>(property_name, property_value);
    prop_node->post_construct();

    graphs_being_building.back()->add_node(prop_node);
    return prop_node;
}

std::any IRGenerator::visitFunctionProperty(JavaScriptParser::FunctionPropertyContext *ctx)
{
    /// The property name is not necessarily a string, it may also be an expression to be calculated
    weak_ptr<DataProducerNode> prop_name = any2DataProducer(this->visit(ctx->propertyName()));

    /// create a new graph for the object's method
    auto cur_graph = make_shared<Graph>();
    graphs_being_building.push_back(cur_graph);
    this->program.graphs.push_back(cur_graph);

    auto last_flow_node = last_unisuccessor;

    /// save the graph in objectLiteralNode
    auto object_literal_node = this->current_object_literals.back();
    //object_literal_node->propName2graph.insert_or_assign(prop_name, cur_graph);

    /// build the new graph
    /// create the function node
    vector<weak_ptr<ParameterNode> > param_nodes;
    auto function_head_node = make_shared<FunctionHeadNode>("this_is_a_method", param_nodes, fake_ctrl_node);
    cur_graph->add_node(function_head_node);

    last_unisuccessor = function_head_node;

    /// visit the childs
    std::any visit_ret = this->JavaScriptParserBaseVisitor::visitFunctionProperty(ctx);

    /// get the parameters

    if (ctx->formalParameterList() != nullptr) {
        vector<JavaScriptParser::FormalParameterArgContext *> param_list = ctx->formalParameterList()->
                formalParameterArg();
        for (const auto arg_context: param_list) {
            const string arg_name = arg_context->assignable()->identifier()->getText();

            weak_ptr<ParameterNode> param_node = cur_graph->get_parameter_node(arg_name);
            function_head_node->inputs.push_back(param_node);
        }
    }

    /// If the start node hasn't set a valid next node, it means that a Return/End is needed
    if (dynamic_pointer_cast<FakeCtrlNode>(function_head_node->next())) {
        auto return_node = make_shared<ReturnNode>();
        function_head_node->set_next(return_node);
        cur_graph->add_node(return_node);
    }

    function_head_node->post_construct();

    if (auto uni_node = dynamic_pointer_cast<UniSuccessorNode>(last_unisuccessor);
        uni_node != nullptr && dynamic_pointer_cast<FakeCtrlNode>(uni_node->next()))
    {
        const auto return_node = make_shared<ReturnNode>();
        uni_node->set_next(return_node);
        cur_graph->add_node(return_node);
    }

    /// restore the context
    graphs_being_building.pop_back();
    last_unisuccessor = last_flow_node;

    /// create the FunctionPropertyNode inside ObjectLiteralNode
    auto func_prop_node = make_shared<FunctionPropertyNode>(prop_name, cur_graph);

    func_prop_node->post_construct();

    /// Add FunctionPropertyNode to the graph where ObjectLiteralNode is located.
    /// The deduplication is performed at the graph. This means that if there is
    /// the same function property in other ObjectLiteral, it will be reused.
    graphs_being_building.back()->add_node(func_prop_node); /// todo

    /// set the return value to FunctionPropertyNode, which will be used as the a input of
    /// object literal node
    return func_prop_node;
}

weak_ptr<DataProducerNode> IRGenerator::get_object_node(JavaScriptParser::SingleExpressionContext *object_expr)
{
    weak_ptr<DataProducerNode> object_node;

    if (const auto id_as_object = dynamic_cast<JavaScriptParser::IdentifierExpressionContext *>(object_expr)) {
        /// If the object part is an identifier, the return value of visit could either be the var symbol
        /// corresponding to an l-value or the data node corresponding to an r-value.

        /// A MemberDotExpression node without a set l-value property may contain an Identifier node with a set l-value property.
        /// When accessing the Identifier, a var symbol object will be returned.
        /// This case occurs when the MemberDotExpression node constructs a LoadField node.
        /// Therefore, instead of relying on the l-value property in ctx to determine the type of the var symbol,
        /// the type is directly checked and processed accordingly.
        if (const auto id_node = this->visitIdentifierExpression(id_as_object);
            id_node.type() == typeid(shared_ptr<VarSymbol>))
        {
            const auto var_symbol = any_cast<shared_ptr<VarSymbol>>(id_node);

            assert_or_throw_js2graph(var_symbol != nullptr,
                "When the object expr is an identifier, the visit result is not a var symbol");

            object_node = this->get_variable_node(var_symbol);
        }
        else {
            object_node = any2DataProducer(id_node);
        }
    }
    else if (dynamic_cast<JavaScriptParser::MemberDotExpressionContext *>(object_expr) != nullptr
               || dynamic_cast<JavaScriptParser::MemberIndexExpressionContext *>(object_expr) != nullptr)
    {
        const auto load_node = visit(object_expr);

        assert_or_throw_js2graph(load_node.type() == typeid(shared_ptr<LoadNode>),
            "");

        object_node = any2DataProducer(load_node);
    }
    else if (const auto call_expr = dynamic_cast<JavaScriptParser::ArgumentsExpressionContext *>(object_expr))
    {
        const auto call_node = visitArgumentsExpression(call_expr);

        object_node = any2DataProducer(call_node);
    }
    else if (const auto this_expr = dynamic_cast<JavaScriptParser::ThisExpressionContext *>(object_expr))
    {
        /// todo
        /// Use `this` to refer to the object in the constructor, e.g., `this.name`.
        /// What type of object node should be returned in this case?
        const auto this_node = visitThisExpression(this_expr);
        object_node = any2DataProducer(this_node);
    }
    else {
        /// TODO:
        /// test case WebKit_JSTests_microbenchmarks_array-prototype-sort-large-array-comparator.js
        /// The test case reflects a scenario where an array literal can also be used as an object expression.
        throw JS2GraphError("The object field is unknown");
    }

    return object_node;
}

std::any IRGenerator::gen_load_node(const weak_ptr<DataProducerNode>& object_node,
                                    const weak_ptr<DataProducerNode>& field_node,
                                    ObjectAccessType loadType)
{
    auto load_node = make_shared<LoadNode>(
        object_node, field_node, fake_ctrl_node, loadType);

    load_node->post_construct();

    graphs_being_building.back()->add_node(load_node);

    this->check_reset_current_flow(load_node);

    return load_node;
}

/**
 * Production rule:
 *   singleExpression -> singleExpression '?'? '.' '#'? identifierName
 */
std::any IRGenerator::visitMemberDotExpression(JavaScriptParser::MemberDotExpressionContext *ctx)
{
    /// handle the object part
    const auto object_expr = ctx->singleExpression();
    const weak_ptr<DataProducerNode> object_node = get_object_node(object_expr);

    /// handle the field part
    this->is_property_name = true;

    const auto field_node = any2DataProducer(visit(ctx->identifierName()));

    this->is_property_name = false;

    /*
     * We only know the object and property name info from this node
     * no matter this node constructs a store behaviour or load behaviour
     */
    if (ctx->is_left_value) {
        pair<weak_ptr<DataProducerNode>,
             weak_ptr<DataProducerNode>> object_field = make_pair(object_node, field_node);

        return object_field;
    }

    return gen_load_node(object_node, field_node, ObjectAccessType::field);
}

/**
 * Production rule:
 *   singleExpression -> singleExpression '[' expressionSequence ']'
 * where
 *   expressionSequence -> singleExpression (',' singleExpression)*
 */
std::any IRGenerator::visitMemberIndexExpression(JavaScriptParser::MemberIndexExpressionContext *ctx)
{
    /// The MemberIndexExpression node supports both accessing object members using []
    /// and accessing array elements using [].

    const auto object_expr = ctx->singleExpression();
    weak_ptr<DataProducerNode> object_node = this->get_object_node(object_expr);

    /// The field part is a sequence of expressions, with the last expression in the sequence being the actual member field.
    /// The expressions in the earlier part of the sequence must also be visited to generate nodes, as they may influence the final expression.
    /// The last expression must return a data node, which will serve as the field node.
    vector<JavaScriptParser::SingleExpressionContext *> exprs = ctx->expressionSequence()->singleExpression();
    const auto last_expr = exprs.back();
    exprs.pop_back();

    for (const auto &expr: exprs) {
        visit(expr);
    }

    /// Visiting the last expression in expr sequence must return a data producer node as the field index
    auto field_node = any2DataProducer(visit(last_expr));

    if (ctx->is_left_value) {
        pair<weak_ptr<DataProducerNode>,
             weak_ptr<DataProducerNode>> object_field = make_pair(object_node, field_node);

        return object_field;
    }

    return gen_load_node(object_node, field_node, ObjectAccessType::index);
}

std::any IRGenerator::visitArrayLiteral(JavaScriptParser::ArrayLiteralContext *ctx)
{
    vector<weak_ptr<DataProducerNode>> elements;

    for (vector<JavaScriptParser::ArrayElementContext *> element_list = ctx->elementList()->arrayElement();
        const auto &array_element: element_list)
    {
        /// Any array element should correspond to a r-value,
        /// so the visit function should return a data node.
        const auto visit_ret_any = this->visit(array_element->singleExpression());

        auto data_node = any2DataProducer(visit_ret_any);
        elements.push_back(data_node);
    }

    auto array_literal_node = make_shared<ArrayLiteralNode>(elements);
    array_literal_node->post_construct();

    graphs_being_building.back()->add_node(array_literal_node);
    return array_literal_node;
}

std::any IRGenerator::visitNewExpression(JavaScriptParser::NewExpressionContext *ctx)
{
    JavaScriptParser::SingleExpressionContext *call_expr = ctx->singleExpression();

    vector<weak_ptr<DataProducerNode>> arg_nodes;

    if (const auto args_ctx = ctx->arguments()) {
        for (vector<JavaScriptParser::ArgumentContext *> args = args_ctx->argument(); const auto &arg: args) {
            const auto visit_arg = visit(arg);
            auto arg_node = any2DataProducer(visit_arg);
            arg_nodes.push_back(arg_node);
        }
    }

    /// 1. normal function call
    if (const auto id_expr = dynamic_cast<JavaScriptParser::IdentifierExpressionContext *>(call_expr))
    {
        JavaScriptParser::IdentifierContext *id_ctx = id_expr->identifier();

        string id_name = id_ctx->getText();

        if (auto function_sym = dynamic_pointer_cast<VarSymbol>(id_ctx->symbol)) {
            auto new_node = make_shared<InvokeNode>(id_name, arg_nodes, fake_ctrl_node, InvokeType::NewInstance);
            new_node->post_construct();
            graphs_being_building.back()->add_node(new_node);

            this->check_reset_current_flow(new_node);

            return new_node;
        }

        assert("NewInstance failed to find the FunctionSymbol of an identifier" && false);
    }

    /// 2. member call
    if (dynamic_cast<JavaScriptParser::MemberDotExpressionContext *>(call_expr) != nullptr
               || dynamic_cast<JavaScriptParser::MemberIndexExpressionContext *>(call_expr) != nullptr)
    {
        const auto visit_ret_any = visit(call_expr);

        if (const auto base = any_cast<shared_ptr<LoadNode>>(&visit_ret_any))
        {
            shared_ptr<DataProducerNode> call_node = any2DataProducer(visit_ret_any);

            if (auto load_node = dynamic_pointer_cast<LoadNode>(call_node)) {
                auto invoke_node = make_shared<InvokeMethodNode>(load_node, arg_nodes, fake_ctrl_node);
                invoke_node->post_construct();

                graphs_being_building.back()->add_node(invoke_node);
                this->check_reset_current_flow(invoke_node);
                return invoke_node;
            }
        }
    }
    else {
        /// WebKit_JSTests_wasm_v8_regress_regress-1215808.js triggers
        //assert_or_throw_js2son(false, "Unimplemented path in visitNewInstance");
        cout << "Unimplemented path in visitNewInstance\n";
        return nullptr;
    }

    return nullptr;
}

std::any IRGenerator::visitThisExpression(JavaScriptParser::ThisExpressionContext *ctx)
{
    auto this_node = make_shared<ThisNode>();
    graphs_being_building.back()->add_node(this_node);
    return this_node;
}

/**
 * Visiting the expr sequences returns the evaluation result of the last expr.
 *
 * expressionSequence
 *   : singleExpression (',' singleExpression)*
 */
std::any IRGenerator::visitExpressionSequence(JavaScriptParser::ExpressionSequenceContext *ctx)
{
    vector<JavaScriptParser::SingleExpressionContext *> exprs = ctx->singleExpression();

    /// keep the last return value of exprs
    std::any the_last_expr_node;

    for (const auto &expr: exprs) {
        the_last_expr_node = visit(expr);
    }

    return the_last_expr_node;
}

///
/// When visiting a ParenthesizedExpression that needs to return a floating node,
/// the functions in the parent class of ANTLR aggregate the visit results for
/// the three children: `(`, `expressionSequence`, and `)`, resulting in an empty std::any being returned.
/// By overriding this behavior, we ensure that the result of expressionSequence is returned instead.
///
std::any IRGenerator::visitParenthesizedExpression(JavaScriptParser::ParenthesizedExpressionContext *ctx)
{
    auto ret = visit(ctx->expressionSequence());
    return ret;
}

///
/// When a MemberDot or MemberIndex expression is used in a post/pre-increment/decrement
/// or assignment operator, it requires generating a Store node, a Load node, and a BinaryOp node.
/// One input of the BinaryOp is the Load result.
///
/// This function is responsible for creating these three nodes.
/// Which node is returned depends on the semantics of the operation:
///
/// - For post-increment/decrement (`x++` / `x--`), return the original data node (before the BinaryOp).
/// - For pre-increment/decrement (`++x` / `--x`) and assignment operators, return the BinaryOp node (after computation).
///
shared_ptr<DataProducerNode> IRGenerator::gen_store4BinaryOp(JavaScriptParser::SingleExpressionContext *member_expr,
                                                             shared_ptr<DataProducerNode> binary_right_node,
                                                             shared_ptr<LanguageOperator> op,
                                                             ObjectAccessType access_type,
                                                             const SelfAssignmentType self_assignment_type)
{
    // MemberDotExpressionContext used as assignment target
    if (const auto visit_object_access_ret = this->visit(member_expr);
        visit_object_access_ret.type() == typeid(pair<weak_ptr<DataProducerNode>,
                                                      weak_ptr<DataProducerNode>>))
    {
        shared_ptr<DataProducerNode> left_data_node;
        auto object_field = any_cast<pair<weak_ptr<DataProducerNode>,
                                          weak_ptr<DataProducerNode>>>(visit_object_access_ret);

        auto [object_node, property_name_node] = object_field;

        if (auto ret_any = gen_load_node(object_node, property_name_node, access_type);
            ret_any.type() == typeid(shared_ptr<LoadNode>))
        {
            left_data_node = any_cast<shared_ptr<LoadNode>>(ret_any);
        }
        else {
            throw JS2GraphError("The return value of gen_load_node is not a load node");
        }

        const auto binary_node = make_shared<BinaryOpNode>(fake_ctrl_node, left_data_node, binary_right_node, op);
        binary_node->post_construct();

        graphs_being_building.back()->add_node(binary_node);
        check_reset_current_flow(binary_node);

        auto store_node = make_shared<StoreNode>(
            fake_ctrl_node, object_node, property_name_node, binary_node, access_type);
        store_node->post_construct();

        graphs_being_building.back()->add_node(store_node);
        this->check_reset_current_flow(store_node);

        if (self_assignment_type == SelfAssignmentType::POST) {
            return left_data_node;
        }
        else {
            /// PreIncrement, PreDecrement, and the assignment operator all fall into this category.
            /// Semantically, PreX returns the data after the binary operation, and similarly,
            /// the assignment operator also returns the data after the binary operation is performed.
            return binary_node;
        }
    }

    assert_or_throw_js2graph(false,
        "When the assignment target is a MemberDotExpressionContext, the visit result is not a tuple or pair");

    return nullptr;
}

///
/// singleExpression:
///     singleExpression assignmentOperator singleExpression # AssignmentOperatorExpression
///
/*
 * assignmentOperator
    : '*='
    | '/='
    | '%='
    | '+='
    | '-='
    | '<<='
    | '>>='
    | '>>>='
    | '&='
    | '^='
    | '|='
    | '**='
    ;
 */
std::any IRGenerator::visitAssignmentOperatorExpression(JavaScriptParser::AssignmentOperatorExpressionContext *ctx)
{
    /**
     * Visiting the assignment operator expression node returns a BinaryOp node
        > a = {x: 1024};
        { x: 1024 }
        > a.x += 1;
        1025
        > a
        { x: 1025 }
        > (a.x += 1).x
        undefined
        > (a.x += 1)
        1027
     */
    const auto assign_op = ctx->assignmentOperator();

    string op_label;

    if (assign_op->MultiplyAssign() != nullptr) {
        op_label = "*=";
    } else if (assign_op->DivideAssign() != nullptr) {
        op_label = "/=";
    } else if (assign_op->ModulusAssign() != nullptr) {
        op_label = "%=";
    } else if (assign_op->PlusAssign() != nullptr) {
        op_label = "+=";
    } else if (assign_op->MinusAssign() != nullptr) {
        op_label = "-=";
    } else if (assign_op->LeftShiftArithmeticAssign() != nullptr) {
        op_label = "<<=";
    } else if (assign_op->RightShiftArithmeticAssign() != nullptr) {
        op_label = ">>=";
    } else if (assign_op->RightShiftLogicalAssign() != nullptr) {
        op_label = ">>>=";
    } else if (assign_op->BitAndAssign() != nullptr) {
        op_label = "&=";
    } else if (assign_op->BitXorAssign() != nullptr) {
        op_label = "^=";
    } else if (assign_op->BitOrAssign() != nullptr) {
        op_label = "|=";
    } else if (assign_op->PowerAssign() != nullptr) {
        op_label = "**=";
    }

    const string op_code = OperatorPairs::label2code(op_label);
    auto op = LanguageOperatorFactory::instance().get(op_label, op_code);

    /// handle right side
    shared_ptr<DataProducerNode> right_data_node = any2DataProducer(
        visit(ctx->singleExpression(1)));

    /// Handle the assignment target: left side
    JavaScriptParser::SingleExpressionContext *assign_target = ctx->singleExpression(0);

    if (const auto member_dot = dynamic_cast<JavaScriptParser::MemberDotExpressionContext *>(assign_target)) {
        auto new_binary_node = gen_store4BinaryOp(
            member_dot, right_data_node, op, ObjectAccessType::field, SelfAssignmentType::POST);
        return new_binary_node;
    }

    if (const auto member_index = dynamic_cast<JavaScriptParser::MemberIndexExpressionContext *>(assign_target)) {
        auto new_binary_node = gen_store4BinaryOp(
            member_index, right_data_node, op, ObjectAccessType::index, SelfAssignmentType::PRE);
        return new_binary_node;
    }

    if (dynamic_cast<JavaScriptParser::IdentifierExpressionContext *>(assign_target)) {
        /// When the assignment target is an Identifier, it corresponds to a VarSymbol,
        /// and at this point, the assignment will generate a new var proxy.
        const auto left = visit(ctx->singleExpression(0));
        const auto left_sym = any_cast<shared_ptr<VarSymbol>>(left);

        weak_ptr<DataProducerNode> left_data_node = get_variable_node(left_sym);

        auto binary_node = make_shared<BinaryOpNode>(fake_ctrl_node, left_data_node, right_data_node, op);
        binary_node->post_construct();

        graphs_being_building.back()->add_node(binary_node);

        const auto proxy = graphs_being_building.back()->add_var_definition(left_sym, binary_node);

        check_last_uni();

        const auto begin_node = last_unisuccessor->get_begin_node();
        this->set_VarProxy_for_flow(begin_node, left_sym, proxy);

        check_reset_current_flow(binary_node);

        return binary_node;
    }

    /// TODO: WebKit_JSTests_es6_destructuring_chained_object_destructuring.js
    assert_or_throw_js2graph(false, "The assignment target is not supported");

    return nullptr;
}

///
/// tryStatement
///     :
///     Try block(catchProduction finallyProduction? | finallyProduction);
///
std::any IRGenerator::visitTryStatement(JavaScriptParser::TryStatementContext *ctx)
{
    const auto catch_production = ctx->catchProduction();
    shared_ptr<CatchNode> catch_node = nullptr;

    if (catch_production != nullptr) {
        catch_node = make_shared<CatchNode>(fake_ctrl_node);
        graphs_being_building.back()->add_node(catch_node);
    }

    const auto finally_production = ctx->finallyProduction();
    shared_ptr<FinallyNode> finally_node = nullptr;

    if (finally_production != nullptr) {
        finally_node = make_shared<FinallyNode>(fake_ctrl_node);
        graphs_being_building.back()->add_node(finally_node);
    }

    /// The catch and finally node may be nullptr
    const auto try_node = make_shared<TryNode>(fake_ctrl_node, catch_node, finally_node);
    graphs_being_building.back()->add_node(try_node);

    this->check_reset_current_flow(try_node);

    /// handle try block
    visit(ctx->block());
    check_last_uni();

    bool try_terminate_with_throw = false;
    bool catch_terminate_with_throw = false;

    shared_ptr<UniSuccessorNode> try_last_uni;
    shared_ptr<UniSuccessorNode> catch_last_uni;

    if (dynamic_pointer_cast<UnwindNode>(last_unisuccessor->next())) {
        try_terminate_with_throw = true;
    }
    else {
        try_last_uni = last_unisuccessor;
    }

    ///
    /// catchProduction
    ///     :
    ///     Catch('(' assignable ? ')') ? block;
    ///

    /// handle catch assignable
    if (catch_production != nullptr) {

        last_unisuccessor = catch_node;

        if (const auto assignable = catch_production->assignable()) {
            ///
            /// assignable
            ///     : identifier
            ///     | arrayLiteral
            ///     | objectLiteral
            ///     ;
            ///
            /// The current implementation only supports cases where the parentheses after catch contain an identifier.
            if (const auto identifier = assignable->identifier()) {

                const auto visit_ret = visit(identifier);

                assert_or_throw_js2graph(visit_ret.type() == typeid(shared_ptr<VarSymbol>),
                    ErrorMsgsJS2Graph::handleError(ErrorCodeJS2Graph::VisitLeftValueId));

                const auto var_sym = any_cast<shared_ptr<VarSymbol>>(visit_ret);

                const auto catch_id = make_shared<CatchIdNode>(var_sym->name);
                graphs_being_building.back()->add_node(catch_id);

                const auto var_proxy = graphs_being_building.back()->add_var_definition(var_sym, catch_id);
                set_VarProxy_for_flow(catch_node, var_sym, var_proxy);

                catch_node->set_catch_id(catch_id);
            }
        }

        /// handle catch block
        if (catch_production->block() != nullptr) {
            visit(catch_production->block());
        }

        ///
        /// There are several scenarios for the end of the catch block:
        ///
        /// First Scenario:
        /// The catch block ends with an unconditional throw. In this case, no catch end or try exit is needed.
        /// There are various sub-cases to consider, such as how the try block ends or whether there is a finally block,
        /// but these do not need to be addressed here.
        ///
        /// Second Scenario:
        /// The try block ends normally, and there is no unconditional throw in the catch.
        /// In this case, the catch ends the control flow with a normal end.
        /// An end node is required here because a merge node will be needed later to combine the two normal ends.
        ///
        /// Third Scenario:
        /// The try block unconditionally throws into the catch, and there is no unconditional throw in the catch.
        /// If there is a finally block, the end of the catch is merged with the finally block.
        /// In this case, the finally block has only one control flow input, which is the end of the catch.
        ///
        /// Fourth Scenario:
        /// The try block unconditionally throws into the catch, and there is no unconditional throw in the catch,
        /// and no finally block is present.
        /// The catch block becomes the only exit for the control flow.
        /// In this case, to clearly define the boundary of the catch block, a try exit node is needed.
        ///
        if (dynamic_pointer_cast<UnwindNode>(last_unisuccessor->next())) {
            /// First scenario
            catch_terminate_with_throw = true;
        }
        else {
            /// Second and third scenario
            catch_last_uni = last_unisuccessor;
        }
    }

    ///
    /// finallyProduction
    ///     :
    ///     Finally block;
    ///
    if (finally_production != nullptr) {
        /// The finally block is the unique exit of the try statement.
        last_unisuccessor = finally_node;

        /// Since a `finally` block exists, there’s no need to insert a try-exit in the try or catch blocks.
        /// Therefore, the end node can be safely and definitively added here.
        /// Create end node for try/catch node.
        if ( !try_terminate_with_throw) {
            const auto try_end = make_shared<EndNode>();
            graphs_being_building.back()->add_node(try_end);
            try_last_uni->set_next(try_end);
        }

        if (catch_production != nullptr) {
            if ( !catch_terminate_with_throw) {
                const auto catch_end = make_shared<EndNode>();
                graphs_being_building.back()->add_node(catch_end);
                catch_last_uni->set_next(catch_end);
            }
        }

        /// handle finally block
        visit(finally_production);

        check_last_uni();

        /// If there is an unconditional throw inside the finally block, the Try exit is not needed.
        /// unconditional throw in finally block is unwind.
        if (dynamic_pointer_cast<UnwindNode>(last_unisuccessor->next())) {
            /// Since the finally block is a mandatory path, and now that there is an unconditional throw
            /// within the finally block, the control flow terminates.
            return nullptr;
        }

        /// finally end with exit
        const auto finally_exit = make_shared<TryExit>(fake_ctrl_node);
        graphs_being_building.back()->add_node(finally_exit);
        this->check_reset_current_flow(finally_exit);
    }
    else {
        /// If there is no finally block, there must be a catch node.

        /// merge the try end and catch end
        if (!try_terminate_with_throw && !catch_terminate_with_throw) {

            const auto try_end = make_shared<EndNode>();
            graphs_being_building.back()->add_node(try_end);
            try_last_uni->set_next(try_end);

            const auto catch_end = make_shared<EndNode>();
            graphs_being_building.back()->add_node(catch_end);
            catch_last_uni->set_next(catch_end);

            vector<weak_ptr<EndMayMergeNode>> merge_inputs;
            merge_inputs.push_back(try_end);
            merge_inputs.push_back(catch_end);

            const auto merge_node = make_shared<MergeNode>(merge_inputs, fake_ctrl_node, MergeType::Try);
            merge_node->post_construct();
            graphs_being_building.back()->add_node(merge_node);

            last_unisuccessor = merge_node;
        }
        else if (!try_terminate_with_throw && catch_terminate_with_throw) {
            /// try end with exit
            const auto try_exit = make_shared<TryExit>(fake_ctrl_node);
            graphs_being_building.back()->add_node(try_exit);
            try_last_uni->set_next(try_exit);
            last_unisuccessor = try_exit;
        }
        else if (try_terminate_with_throw && !catch_terminate_with_throw) {
            /// catch end with exit
            const auto catch_exit = make_shared<TryExit>(fake_ctrl_node);
            graphs_being_building.back()->add_node(catch_exit);
            catch_last_uni->set_next(catch_exit);
            last_unisuccessor = catch_exit;
        }
        else {
            /// Both try and catch block throw unconditionally
            /// The control flow ends.
        }
    }

    return nullptr;
}

///
/// throwStatement
///     : Throw {this->notLineTerminator()}? expressionSequence eos
///     ;
///
/// Throw is a statement without evaluation result.
///
std::any IRGenerator::visitThrowStatement(JavaScriptParser::ThrowStatementContext *ctx)
{
    const auto expr_seq_ret = this->visit(ctx->expressionSequence());

    shared_ptr<DataProducerNode> exception_node = any2DataProducer(expr_seq_ret);

    const auto unwind_node = make_shared<UnwindNode>(exception_node);
    graphs_being_building.back()->add_node(unwind_node);
    unwind_node->post_construct();

    check_last_uni();
    last_unisuccessor->set_next(unwind_node);

    return nullptr;
}

///
/// A for/in loop looks a lot like a for/of loop, with the `of` keyword changed to `in`.
/// While a for/of loop requires an iterable object after the of, a for/in loop works with
/// any object after the in.
/// The for/of loop is new in ES6, but for/in has been part of JavaScript since the
/// very beginning (which is why it has the more natural sounding syntax).
///
/// The for/in statement loops through the property names of a specified object.
///
/// iterationStatement
///    : For '(' (singleExpression | variableDeclarationList) In expressionSequence ')' statement # ForInStatement
///
std::any IRGenerator::visitForInStatement(JavaScriptParser::ForInStatementContext *ctx)
{
    /// end the preceding control flow
    check_last_uni();

    auto end_node = make_shared<EndNode>();
    graphs_being_building.back()->add_node(end_node);

    last_unisuccessor->set_next(end_node);

    /// create LoopBegin
    vector<weak_ptr<EndMayMergeNode>> begin_inputs;
    begin_inputs.push_back(end_node);
    auto loop_begin = make_shared<LoopBegin>(begin_inputs, fake_ctrl_node);
    graphs_being_building.back()->add_node(loop_begin);
    last_unisuccessor = loop_begin;

    /// create LoopEnd
    auto loop_end = make_shared<LoopEnd>(loop_begin);
    graphs_being_building.back()->add_node(loop_end);
    loop_begin->merged_flows.push_back(loop_end);

    /// maintain the reverse edges for LoopBegin's inputs
    /// append LoopBegin to EndNode and LoopEnd's uses
    loop_begin->post_construct();

    /// create LoopExit
    auto loop_exit = make_shared<LoopExit>(fake_ctrl_node);
    graphs_being_building.back()->add_node(loop_exit);

    /// create BeginNode for loop body
    auto work_begin_node = make_shared<BeginNode>(fake_ctrl_node);
    graphs_being_building.back()->add_node(work_begin_node);

    last_unisuccessor = work_begin_node;

    /// Temporarily set the successor of begin node to loop end
    /// If there is a new control flow in the subsequent loop body, it will be inserted into the middle
    work_begin_node->set_next(loop_end);

    /// When traversing the loop body, loop phi is forced to be generated for each var proxy queried.
    /// There is no loop condition in the For-in loop, only the enumerated prop name.
    /// The prop name does not involve quering the data flow through var proxy.
    /// The prop name is essentially a variable declared at the beginning of each loop iteration,
    /// with no influence from the previous loop affecting the current iteration.
    /// Therefore there is no need to generate phi nodes for prop name
    ///
    /// The enumeration target object that may be assigned within the loop body.
    /// Requires generation of a loop phi node for this object.
    this->loop_begins_should_gen_phi.insert(loop_begin);

    /// push the loop phi nodes that need backfilling for this level of loop to the stack
    map<shared_ptr<VarSymbol>,
        vector<pair<weak_ptr<AbstractBeginNode>,
                    weak_ptr<PhiNode>>>> loop_need_fill;

    /// the LoopBegin is used as the key when quering the nodes need fill map
    this->phi_need_backfill.insert_or_assign(loop_begin, loop_need_fill);

    /// When traversing the loop body, set the `next` of LoopBegin to the BeginNode
    /// of the loop body initially. It will be modified to ForInEnum later.
    /// When querying with get var proxy, we backtrack the search in the order of BeginNode -> LoopBegin.
    loop_begin->set_next(work_begin_node);

    /// parse the loop enum

    /// parse prop name
    string prop_name;

    shared_ptr<ForInPropName> prop_name_node;

    if (auto var_list = ctx->variableDeclarationList(); var_list != nullptr) {
        auto decl_vec = var_list->variableDeclaration();

        if (decl_vec.size() != 1) {
            assert_or_throw_js2graph(false, "Uncommon for/in syntax.");
        }

        if (auto assignable = decl_vec[0]->assignable(); assignable->identifier() == nullptr) {
            assert_or_throw_js2graph(false, "Uncommon for/in syntax.");
        }
        else {
            prop_name = assignable->identifier()->getText();
        }

        /// call visitVariableDecl to establish the varProxy and attach it to flow
        prop_name_node = dynamic_pointer_cast<ForInPropName>(
            any2DataProducer(this->visit(decl_vec[0])));
    }
    else {
        throw JS2GraphError("Uncommon for/in syntax.");
    }

    /// parse object node
    /// generate loop phi node for object
    shared_ptr<DataProducerNode> object_node;

    if (auto exprs = ctx->expressionSequence()->singleExpression(); exprs.size() == 1) {
        object_node = any2DataProducer(this->visit(exprs[0]));
    }
    else {
        throw JS2GraphError("Uncommon for/in syntax.");
    }

    /// parse loop body

    /// var proxy should be attached to BeginNode
    /// Note that in the loop body, the current flow node may change
    last_unisuccessor = work_begin_node;
    this->visit(ctx->statement());

    auto loop_body_end_flow = last_unisuccessor;

    /// Establish the control flow.
    /// During backfilling, backtrack according to the flow.
    /// At the end of the loop body, there should be a UniSuccessorNode.
    check_last_uni();
    loop_body_end_flow->set_next(loop_end);

    auto &nodes_fill = this->phi_need_backfill[loop_begin];

    for (auto &[var_sym, flow_phi_pairs]: nodes_fill)
    {
        auto search_end = loop_begin;
        vector<weak_ptr<AbstractBeginNode> > visited_begins;
        shared_ptr<VarProxy> var_proxy = get_VarProxy_from_flow(loop_end->get_begin_node(), var_sym, visited_begins, search_end);

        if (var_proxy == nullptr) {
            assert(false && "No var proxy in loop body, but there is a loop phi node");
            remove_loop_phi(flow_phi_pairs, var_proxy);
        }

        for (auto &[flow, phi_node]: flow_phi_pairs)
        {
            auto real_node = graphs_being_building.back()->varProxy2node[var_proxy];

            if (auto real_phi = dynamic_pointer_cast<PhiNode>(real_node.lock()))
            {
                if (real_phi->need_back_fill())
                {
                    remove_loop_phi(flow_phi_pairs, var_proxy);

                    shared_ptr<DataProducerNode> real_data_node;
                    for (int i = 0; i < real_phi->inputs.size(); i++) {
                        if (!dynamic_pointer_cast<FakeDataProducerNode>(real_phi->inputs[i].lock())) {
                            real_data_node = dynamic_pointer_cast<DataProducerNode>(real_phi->inputs[i].lock());
                        }
                    }
                    if (real_phi == object_node) {
                        object_node = real_data_node;
                    }
                }
                else {
                    /// The existence of the phi node is established.
                    phi_node.lock()->back_fill(real_node);
                }
            }
            else {
                /// real data node is not a phi
                /// The existence of the phi node is established.
                phi_node.lock()->back_fill(real_node);
            }
        }
    }

    /// create ForInEnum
    auto enum_node = make_shared<ForInEnum>(prop_name_node, object_node, work_begin_node, loop_exit);

    enum_node->post_construct();
    graphs_being_building.back()->add_node(enum_node);
    loop_begin->set_next(enum_node);

    /// Remove the current loop begin from the list of nodes needed to be backfilled.
    this->loop_begins_should_gen_phi.erase(loop_begin);

    last_unisuccessor = loop_exit;

    return nullptr;
}

} /// end of namespace
