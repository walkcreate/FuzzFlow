#ifndef FUZZFLOW_IRGENERATOR_H
#define FUZZFLOW_IRGENERATOR_H

#include <any>
#include "../utils/common_using.h"
#include "../utils/assert_or_throw.h"
#include "../thirdparty/antlr4/JavaScriptParserBaseVisitor.h"

#include "../nodes/AllNodesInclude.h"
#include "../semantic/FunctionSymbol.h"
#include "../semantic/VarSymbol.h"
#include "../semantic/Scope.h"
#include "FullProgram.h"

#include "LanguageOperator.h"
#include "LanguageOperatorFactory.h"

#include "OperatorPairs.h"
#include "antlr4-runtime.h"
#include "js2graph_utils.h"
#include "JS2GraphErrorMsgs.h"

using antlr4::ParserRuleContext;

namespace FuzzFlow {

enum class SelfAssignmentType {
    POST,
    PRE
};

class IRGenerator final : public JavaScriptParserBaseVisitor,
                          public std::enable_shared_from_this<IRGenerator>
{
public:
    FullProgram program;

    /// Who owns graph? FullProgram.
    ///
    /// Who owns function symbol?
    /// IRGenerator has functions_syms, FullProgram has func2graph.
    ///
    /// IRGenerator->graphs_being_building does not keep graphs.
    /// It just acts as a stack. After Js2Graph, the vector becomes empty.
    vector<shared_ptr<Graph>> graphs_being_building;

    IRGenerator()
    {
        fake_ctrl_node = make_shared<FakeCtrlNode>();
        fake_data_node = make_shared<FakeDataProducerNode>();
    }

private: // implementation

    /// fake node for placeholder
    shared_ptr<FakeCtrlNode> fake_ctrl_node;
    shared_ptr<FakeDataProducerNode> fake_data_node;

    vector<shared_ptr<VarSymbol>> function_symbols;

    vector<shared_ptr<ObjectLiteralNode>> current_object_literals;

    shared_ptr<UniSuccessorNode> last_unisuccessor;

    /// flow2varProxies is used to look up the corresponding varProxy for a variable (right-hand side),
    /// and then further query its data producer node via varProxy2Node.
    ///
    /// When querying a var symbol in flow, it should always return the latest var proxy
    /// (as subsequent code uses the most recently assigned value of the var).
    ///
    /// Due to the need to remove invalid loop phi, the corresponding var proxy for phi must be deleted.
    /// Therefore, each flow cannot simply store the last proxy; a stack is used to track them.
    /// If this requirement is not present, the second-level map does not need a stack and can
    /// just store the most recent proxy.
    map<weak_ptr<const AbstractBeginNode>,
        map<shared_ptr<VarSymbol>,
            stack<
                shared_ptr<VarProxy>>,
            std::owner_less<>>,
        std::owner_less<>> flow2varProxies;

    /// Due to the special control flow of loops, Phi nodes must be forcibly created during the first traversal
    /// of the loop body (or loop condition, depends on which one is processed first).
    /// After traversal, loop Phi nodes are either backfilled or removed.
    ///
    /// We track the loop Phi nodes that need backfilling.
    ///
    /// When removing an invalid Phi node (failed Phi), the corresponding var proxy must be restored.
    /// To do this, the previous var proxy (proxy_{i-1}) of the failed Phi's var proxy (proxy_i) needs to be found.
    /// This requires querying from flow2varProxies, so the flow to which the loop Phi is attached must also be recorded.
    ///

    /// Phi nodes that need to be backfilled cannot be managed using a stack structure.
    /// The issue arises from a potential scenario where, during the traversal of an inner for loop,
    /// the data flow search encounters the position of a previous (or outer) for loop.
    /// In this case, a Phi node is generated in the LoopBegin flow of the outer for loop.
    /// If the stack is accessed at this point, only the nodes needing backfill for the current for loop will be accessed,
    /// resulting in incorrect storage of the Phi node at the wrong location.
    ///
    map<weak_ptr<AbstractMergeNode>,
        map<shared_ptr<VarSymbol>,
            vector<pair<weak_ptr<AbstractBeginNode>,
                     weak_ptr<PhiNode>>>>,
        std::owner_less<>
    > phi_need_backfill;

    /// When performing data flow queries, if a loop begin node is encountered, we need to consider whether to force
    /// the creation of a Phi for variables inside the loop body.
    /// If a var symbol is not found in the loop end branch within the loop body, a loop phi should be generated,
    /// and the branch will prepare a fake data node.
    ///
    /// Loops can be nested, so determining whether the current merge node needs to generate a phi
    /// depends on whether we are inside the body of a loop begin. Each time a loop body is entered,
    /// the corresponding loop begin is added to a set.
    ///
    /// We may be inside multiple loop bodies, but the current loop begin being processed is always determined.
    ///
    /// A stack cannot be used here because, when traversing the end node branches before the loop begin,
    /// we might encounter outer loops. If the outer loop's loop end branch also doesn't have the required var symbol,
    /// a loop phi must still be generated. Therefore, a set is used.
    set<weak_ptr<AbstractMergeNode>,
        std::owner_less<>> loop_begins_should_gen_phi;

    /// Maybe nested, stack is used
    stack<JavaScriptParser::FunctionDeclarationContext *> now_in_function_decls;

    /// identifierName as propertyName
    bool is_property_name = false;
    bool is_identifier_name = false;

    set<shared_ptr<Symbol>> builtin_symbols;
    set<shared_ptr<VarSymbol>> builtin_var_symbols;
    set<shared_ptr<BuiltinNode>> builtin_nodes;
    map<shared_ptr<VarSymbol>,
        shared_ptr<BuiltinNode>,
        std::owner_less<>> builtin_varSym2node;

    enum class FuncTry {
        FUNCTION_DECL,
        TRY
    };

    vector<FuncTry> func_and_try;

    /// When failing to search the dataflow in current graph, query the __main__ graph
    /// The var symbol may be a global variable
    std::optional<shared_ptr<DataProducerNode>> query_producer_in_main(const shared_ptr<VarSymbol>& var_symbol) const;

    void set_VarProxy_for_flow(const weak_ptr<AbstractBeginNode>& begin_node,
                               shared_ptr<VarSymbol> var_sym,
                               const shared_ptr<VarProxy>& proxy);

    shared_ptr<VarProxy> get_VarProxy_from_flow(weak_ptr<AbstractBeginNode> begin_node,
                                                const shared_ptr<VarSymbol>& var_sym,
                                                vector<weak_ptr<AbstractBeginNode>> &visited_begin,
                                                const weak_ptr<AbstractBeginNode>& end_node);

    shared_ptr<DataProducerNode> get_variable_node(const shared_ptr<VarSymbol>& var_symbol);

    shared_ptr<DataProducerNode> get_variable_node_in_cur_graph(const shared_ptr<VarSymbol> &var_symbol);

    static bool is_same_element(const vector<weak_ptr<DataProducerNode>> &nodes);

    shared_ptr<DataProducerNode> any_to_floating_node(std::any node_any);

    void record_phi_need_fill(const weak_ptr<AbstractMergeNode>& merge_node,
                              const shared_ptr<VarSymbol>& var_sym,
                              const weak_ptr<PhiNode>& phi_node,
                              const weak_ptr<AbstractBeginNode>& flow);

    void remove_loop_phi(vector<pair<weak_ptr<AbstractBeginNode>,
                                     weak_ptr<PhiNode>>> &flow_and_phi_nodes,
                         const shared_ptr<VarProxy>& var_proxy);

    shared_ptr<VarProxy> gen_phi_node(const weak_ptr<AbstractMergeNode>& merge_node,
                                      const weak_ptr<AbstractBeginNode>& begin_node,
                                      const shared_ptr<VarSymbol>& var_sym,
                                      vector<weak_ptr<DataProducerNode>> data_inputs,
                                      bool need_back_fill);

    shared_ptr<VarProxy> varProxy_at_begin(const weak_ptr<AbstractBeginNode>& begin_node,
                                           const shared_ptr<VarSymbol>& var_sym);

    void walk_merge_for_varProxy(const shared_ptr<AbstractMergeNode>& merge_node,
                                 const shared_ptr<VarSymbol>& var_symbol,
                                 const vector<weak_ptr<AbstractBeginNode>> &visited_begins,
                                 const weak_ptr<AbstractBeginNode>& end_node,
                                 vector<weak_ptr<DataProducerNode>> &data_inputs,
                                 vector<shared_ptr<VarProxy>> &var_proxies);

    shared_ptr<VarProxy> extract_varProxy_from_merge(const shared_ptr<AbstractMergeNode>& merge_node,
                                                     const weak_ptr<AbstractBeginNode>& attached_flow,
                                                     const shared_ptr<VarSymbol>& var_symbol,
                                                     vector<weak_ptr<DataProducerNode>> data_inputs,
                                                     vector<shared_ptr<VarProxy>> &var_proxies);

    void gen_builtin_nodes(const set<shared_ptr<Symbol>>& builtinSymbols);

    void check_last_uni() const;
    void check_reset_current_flow(const shared_ptr<UniSuccessorNode>& new_uni_node);

    std::any visitProgram(JavaScriptParser::ProgramContext *ctx) override;

    std::any visitFunctionDeclaration(JavaScriptParser::FunctionDeclarationContext *ctx) override;

    std::any visitFunctionExpression(JavaScriptParser::FunctionExpressionContext *ctx) override;

    std::any visitStatementList(JavaScriptParser::StatementListContext *ctx) override;

    std::any visitFormalParameterList(JavaScriptParser::FormalParameterListContext *ctx) override;

    std::any visitNumericLiteral(JavaScriptParser::NumericLiteralContext *ctx) override;

    std::any visitLiteral(JavaScriptParser::LiteralContext *ctx) override;

    std::any visitReturnStatement(JavaScriptParser::ReturnStatementContext *ctx) override;

    std::any visitIfStatement(JavaScriptParser::IfStatementContext *ctx) override;

    std::any visitWhileStatement(JavaScriptParser::WhileStatementContext *ctx) override;

    std::any visitForStatement(JavaScriptParser::ForStatementContext *ctx) override;

    std::any visitVariableDeclaration(JavaScriptParser::VariableDeclarationContext *ctx) override;

    std::any visitIdentifier(JavaScriptParser::IdentifierContext *ctx) override;

    std::any visitArgumentsExpression(JavaScriptParser::ArgumentsExpressionContext *ctx) override;

    std::any visitAssignmentExpression(JavaScriptParser::AssignmentExpressionContext *ctx) override;

    std::any visitDeleteExpression(JavaScriptParser::DeleteExpressionContext *ctx) override;

    std::any handle_postfix_prefix(JavaScriptParser::SingleExpressionContext *expr,
                           shared_ptr<LanguageOperator> op,
                           const SelfAssignmentType self_assignment_type);

    std::any visitPostIncrementExpression(JavaScriptParser::PostIncrementExpressionContext *ctx) override;

    std::any visitPostDecreaseExpression(JavaScriptParser::PostDecreaseExpressionContext *ctx) override;

    std::any visitPreIncrementExpression(JavaScriptParser::PreIncrementExpressionContext *ctx) override;

    std::any visitPreDecreaseExpression(JavaScriptParser::PreDecreaseExpressionContext *ctx) override;

    std::any visitVoidExpression(JavaScriptParser::VoidExpressionContext *ctx) override;

    std::any visitTypeofExpression(JavaScriptParser::TypeofExpressionContext *ctx) override;

    std::any visitUnaryPlusExpression(JavaScriptParser::UnaryPlusExpressionContext *ctx) override;

    std::any visitUnaryMinusExpression(JavaScriptParser::UnaryMinusExpressionContext *ctx) override;

    std::any visitBitNotExpression(JavaScriptParser::BitNotExpressionContext *ctx) override;

    std::any visitNotExpression(JavaScriptParser::NotExpressionContext *ctx) override;

    std::any visitPowerExpression(JavaScriptParser::PowerExpressionContext *ctx) override;

    std::any visitRelationalExpression(JavaScriptParser::RelationalExpressionContext *ctx) override;

    std::any visitInstanceofExpression(JavaScriptParser::InstanceofExpressionContext *ctx) override;

    std::any visitInExpression(JavaScriptParser::InExpressionContext *ctx) override;

    std::any visitAdditiveExpression(JavaScriptParser::AdditiveExpressionContext *ctx) override;

    std::any visitMultiplicativeExpression(JavaScriptParser::MultiplicativeExpressionContext *ctx) override;

    std::any visitBitShiftExpression(JavaScriptParser::BitShiftExpressionContext *ctx) override;

    std::any visitEqualityExpression(JavaScriptParser::EqualityExpressionContext *ctx) override;

    std::any visitBitAndExpression(JavaScriptParser::BitAndExpressionContext *ctx) override;

    std::any visitBitXOrExpression(JavaScriptParser::BitXOrExpressionContext *ctx) override;

    std::any visitBitOrExpression(JavaScriptParser::BitOrExpressionContext *ctx) override;

    std::any visitLogicalAndExpression(JavaScriptParser::LogicalAndExpressionContext *ctx) override;

    std::any visitLogicalOrExpression(JavaScriptParser::LogicalOrExpressionContext *ctx) override;

    std::any visitTernaryExpression(JavaScriptParser::TernaryExpressionContext *ctx) override;

    std::any visitObjectLiteral(JavaScriptParser::ObjectLiteralContext *ctx) override;

    std::any visitPropertyName(JavaScriptParser::PropertyNameContext *ctx) override;

    std::any visitIdentifierName(JavaScriptParser::IdentifierNameContext *ctx) override;

    shared_ptr<LiteralStringNode> identifier_as_property_name(const string& property_name) const;

    std::any visitPropertyExpressionAssignment(JavaScriptParser::PropertyExpressionAssignmentContext *ctx) override;

    std::any visitComputedPropertyExpressionAssignment(
        JavaScriptParser::ComputedPropertyExpressionAssignmentContext *ctx) override;

    std::any visitFunctionProperty(JavaScriptParser::FunctionPropertyContext *ctx) override;

    weak_ptr<DataProducerNode> get_object_node(JavaScriptParser::SingleExpressionContext *object_expr);

    void gen_store_node(const std::any &visit_object_access_ret,
                        const shared_ptr<DataProducerNode> &new_prop_value_node,
                        const ObjectAccessType access_type);

    std::any gen_load_node(const weak_ptr<DataProducerNode> &object_node,
                           const weak_ptr<DataProducerNode> &field_node,
                           ObjectAccessType loadType);

    std::any visitMemberIndexExpression(JavaScriptParser::MemberIndexExpressionContext *ctx) override;

    std::any visitMemberDotExpression(JavaScriptParser::MemberDotExpressionContext *ctx) override;

    std::any visitArrayLiteral(JavaScriptParser::ArrayLiteralContext *ctx) override;

    std::any visitNewExpression(JavaScriptParser::NewExpressionContext *ctx) override;

    std::any visitThisExpression(JavaScriptParser::ThisExpressionContext *ctx) override;

    std::any visitExpressionSequence(JavaScriptParser::ExpressionSequenceContext *ctx) override;

    std::any visitParenthesizedExpression(JavaScriptParser::ParenthesizedExpressionContext *ctx) override;

    shared_ptr<DataProducerNode> gen_store4BinaryOp(JavaScriptParser::SingleExpressionContext *member_expr,
                                                      shared_ptr<DataProducerNode> binary_right_node,
                                                      shared_ptr<LanguageOperator> op, ObjectAccessType access_type,
                                                      SelfAssignmentType self_assignment_type);

    std::any visitAssignmentOperatorExpression(JavaScriptParser::AssignmentOperatorExpressionContext *ctx) override;

    std::any visitTryStatement(JavaScriptParser::TryStatementContext *ctx) override;

    //std::any visitCatchProduction(JavaScriptParser::CatchProductionContext *ctx) override;

    //std::any visitFinallyProduction(JavaScriptParser::FinallyProductionContext *ctx) override;

    std::any visitThrowStatement(JavaScriptParser::ThrowStatementContext *ctx) override;

    //std::any visitSourceElements(JavaScriptParser::SourceElementsContext *ctx) override;

    std::any visitForInStatement(JavaScriptParser::ForInStatementContext *ctx) override;
};

} /// end of namespace

#endif //FUZZFLOW_IRGENERATOR_H
