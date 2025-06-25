#include "MutatorInsideGraph.h"

#include "../mutationOperator/MuOpBinaryOp.h"
#include "../mutationOperator/MuOpLiteralFloat.h"
#include "../mutationOperator/MuOpConsumerInput.h"
#include "../mutationOperator/MuOpSwapIfBranches.h"
#include "../mutationOperator/MuOpInsertStore.h"
#include "../mutationOperator/MuOpInsertInvoke.h"
#include "../mutationOperator/MuOpInsertOperationSequence.h"
#include "../mutationOperator/MuOpDeleteSequentialOperation.h"
#include "../mutationOperator/MuOpMoveSequentialOperation.h"
#include "../mutationOperator/MuOpMoveCtrlGroup.h"
#include "../mutationOperator/MuOpSplice.h"

#include "../fuzzer/corpus/Corpus.h"

namespace FuzzFlow {

/// To improve performance, mutation is applied directly to the seed instead of creating a full copy.
/// Therefore, the seed must be restored after mutation.
///
void MutatorInsideGraph::undo_mutate()
{
    for (const auto& applied_mutator : this->applied_mutation_operators) {
        applied_mutator->undo();
    }
}

bool MutatorInsideGraph::mutate()
{
    bool has_mutated = false;

    this->preprocess();

    /// todo:
    /// We can mutate a seed multiple times during once mutation.
    /// The following switch statement can be placed inside a loop.
    if (this->supported_mutators.empty()) {
        return false;
    }

    auto selected_mutator = random_set_element(this->supported_mutators);

    //selected_mutator = MutatorEnum::INSERT_SEQUENCES;
    //selected_mutator = MutatorEnum::SPLICE;

    switch (selected_mutator) {
        case MutatorEnum::MUTATE_INPUTS:
            if (! this->nodes_mutable_consumer.empty()) {
                const weak_ptr<DataConsumerNode> node = random_set_element(this->nodes_mutable_consumer);
                has_mutated = this->mutate_consumer_inputs(node);
            }
            break;

        case MutatorEnum::MUTATE_FLOAT:
            if (! this->_nodes_float.empty()) {
                const weak_ptr<LiteralFloatNode> float_node = random_set_element(this->_nodes_float);
                has_mutated = this->mutate_literal_float(float_node);
            }
            break;

        case MutatorEnum::MUTATE_BINARY_OP:
            if (! this->_nodes_binary_op.empty()) {
                const weak_ptr<BinaryOpNode> node = random_set_element(this->_nodes_binary_op);
                has_mutated = this->mutate_binary_operator(node);
            }
            break;

        case MutatorEnum::SWAP_IF_BRANCHES:
            if (! this->_nodes_if.empty()) {
                const weak_ptr<IfNode> node = random_set_element(this->_nodes_if);
                has_mutated = this->mutate_swap_if_branches(node);
            }
            break;

        case MutatorEnum::MOVE_SEQ_OPERATION:
            if ((! this->_operations_could_move.empty()) && (! this->move_target_pos.empty())) {
                shared_ptr<SequentialOperationNode> node_to_mv = random_set_element(this->_operations_could_move).lock();

                has_mutated = this->mutate_move_sequential_operation(node_to_mv);
            }
            break;

        case MutatorEnum::MOVE_CTRL_GROUP:
            has_mutated = this->mutate_move_ctrl_group();
            break;

        case MutatorEnum::DEL_STORE_NODE:
            if (! this->_nodes_store.empty()) {
                weak_ptr<StoreNode> store_node_w = random_set_element(this->_nodes_store);
                has_mutated = this->mutate_delete_store(store_node_w);
            }
            break;

        case MutatorEnum::DEL_INVOKE_NODE:
            if (! this->_nodes_invoke.empty()) {
                weak_ptr<InvokeNode> invoke_node_w = random_set_element(this->_nodes_invoke);
                if (invoke_node_w.lock()->uses.empty()) {
                    has_mutated = this->mutate_delete_invoke(invoke_node_w);
                }
            }
            break;

        case MutatorEnum::DEL_DELETE_NODE:
            if (! this->_nodes_delete.empty()) {
                weak_ptr<DeleteNode> delete_node_w = random_set_element(this->_nodes_delete);
                if (delete_node_w.lock()->uses.empty()) {
                    has_mutated = this->mutate_delete_delete(delete_node_w);
                }
            }
            break;

        case MutatorEnum::INSERT_STORE:
            if (! this->_nodes_object_literal.empty()) {
                has_mutated = this->mutate_insert_store();
            }
            break;

        case MutatorEnum::INSERT_INVOKE:
            mutate_insert_invoke();
            has_mutated = true;
            break;

        case MutatorEnum::INSERT_SEQUENCES:
            has_mutated = this->mutate_insert_operation_sequence();
            break;

        case MutatorEnum::SPLICE:
            has_mutated = this->mutate_splice();
            break;

        default:
            throw MutateError("Unsupported MutatorEnum");
    }

    this->done_mutators.push_back(selected_mutator);

    return has_mutated;
}

///
/// Which consumer's inputs could not be mutated?
///
///     FunctionHeadNode<- parameter node
///     PhiNode         <- branch flow
///     AccessObject    <- object
///     ForInEnum       <- object
///     UnwindNode      <- exception node
///     InvokeMethod    <- load node
///
bool MutatorInsideGraph::is_mutable_consumer(const weak_ptr<DataConsumerNode>& node_w)
{
    const auto node = node_w.lock();

    /// Blacklist

    if (auto _node = dynamic_pointer_cast<FunctionHeadNode>(node)) {
        return false;
    }

    if (auto _node = dynamic_pointer_cast<PhiNode>(node)) {
        return false;
    }

    if (auto _node = dynamic_pointer_cast<ForInEnum>(node)) {
        return false;
    }

    if (auto _node = dynamic_pointer_cast<UnwindNode>(node)) {
        return false;
    }

    if (auto _node = dynamic_pointer_cast<ObjectLiteralNode>(node)) {
        return false;
    }

    /// Store and Load
    if (auto _node = dynamic_pointer_cast<AccessObjectNode>(node)) {
        return false;
    }

    return true;
}

/// Analysis the seed to verify the usable mutators
void MutatorInsideGraph::preprocess()
{
    for (auto& node : this->graph->nodes)
    {
        this->supported_mutators.insert(MutatorEnum::INSERT_INVOKE);

        if (auto producer = dynamic_pointer_cast<DataProducerNode>(node); producer != nullptr) {
            this->_nodes_producer.insert(producer);

            if (producer->uses.empty()) {
                /// dead code elimination
                this->_nodes_dead.insert(producer);
            }
            else if (auto float_node = dynamic_pointer_cast<LiteralFloatNode>(node)) {
                /// do not mutate float literal which is used as BinaryOp's input
                if (! float_node->uses.empty()) {
                    bool used_as_binary = false;

                    for (const auto& use : float_node->uses) {
                        if (dynamic_pointer_cast<BinaryOpNode>(use.lock()) != nullptr)
                        {
                            used_as_binary = true;
                            break;
                        }
                    }

                    if (used_as_binary) {
                        continue;
                    }
                }

                this->_nodes_float.insert(float_node);
                this->supported_mutators.insert(MutatorEnum::MUTATE_FLOAT);
            }
            else if (auto bin_op_node = dynamic_pointer_cast<BinaryOpNode>(node)) {
                this->_nodes_binary_op.insert(bin_op_node);
                this->supported_mutators.insert(MutatorEnum::MUTATE_BINARY_OP);
            }
            else if (auto obj_literal_node = dynamic_pointer_cast<ObjectLiteralNode>(node)) {
                this->_nodes_object_literal.insert(obj_literal_node);
                this->supported_mutators.insert(MutatorEnum::INSERT_STORE);
            }
        }

        if (auto consumer = dynamic_pointer_cast<DataConsumerNode>(node);
            (consumer != nullptr) && is_mutable_consumer(consumer))
        {
            if (dynamic_pointer_cast<ObjectLiteralNode>(consumer) == nullptr) {
                this->nodes_mutable_consumer.insert(consumer);
                this->supported_mutators.insert(MutatorEnum::MUTATE_INPUTS);
            }
        }

        if (auto if_node = dynamic_pointer_cast<IfNode>(node)) {
            /// LoopIf's two branches can not be swapped
            if (dynamic_pointer_cast<LoopIf>(if_node)) {
                continue;
            }

            this->_nodes_if.insert(if_node);
            this->supported_mutators.insert(MutatorEnum::SWAP_IF_BRANCHES);
            this->supported_mutators.insert(MutatorEnum::MOVE_CTRL_GROUP);
        }

        if (auto loop_begin = dynamic_pointer_cast<LoopBegin>(node)) {
            this->_nodes_loop.insert(loop_begin);
            this->supported_mutators.insert(MutatorEnum::MOVE_CTRL_GROUP);
        }

        if (auto store_node = dynamic_pointer_cast<StoreNode>(node)) {
            this->_nodes_store.insert(store_node);
            this->_operations_could_move.insert((store_node));
            this->supported_mutators.insert(MutatorEnum::INSERT_STORE);
            this->supported_mutators.insert(MutatorEnum::DEL_STORE_NODE);
        }

        if (auto invoke_node = dynamic_pointer_cast<InvokeNode>(node)) {
            this->_nodes_invoke.insert(invoke_node);
            this->_operations_could_move.insert((invoke_node));
            this->supported_mutators.insert(MutatorEnum::DEL_INVOKE_NODE);
        }

        if (auto delete_node = dynamic_pointer_cast<DeleteNode>(node)) {
            this->_nodes_delete.insert(delete_node);
            this->_operations_could_move.insert((delete_node));
            this->supported_mutators.insert(MutatorEnum::DEL_DELETE_NODE);
        }

        if (auto uni_node = dynamic_pointer_cast<UniSuccessorNode>(node)) {
            /// The successor of LoopBegin is typically a BinaryOp. Breaking this edge serves no purpose.
            if (dynamic_pointer_cast<LoopBegin>(uni_node) == nullptr) {
                this->move_target_pos.insert(uni_node);
                this->supported_mutators.insert(MutatorEnum::INSERT_SEQUENCES);
            }
        }

        if (! _nodes_producer.empty()) {
            this->supported_mutators.insert(MutatorEnum::INSERT_INVOKE);
        }
    }
}

bool MutatorInsideGraph::mutate_consumer_inputs(const weak_ptr<DataConsumerNode>& node)
{
    /// When mutating the data flow, what factors should be considered?
    /// For example: The Object input of a StoreNode should not be arbitrarily mutated; otherwise, semantic errors may occur.
    /// It should only point to nodes like ObjectLiteral and LoadNode.
    ///
    shared_ptr<DataConsumerNode> consumer = node.lock();

    unsigned int input_index = 0;
    if (consumer->inputs.empty()) {
        return false;
    }

    if (consumer->inputs.size() == 1) {
        if (dynamic_pointer_cast<InvokeMethodNode>(consumer) != nullptr) {
            return false;
        }

        if (dynamic_pointer_cast<StoreNode>(consumer) != nullptr) {
            return false;
        }

        if (dynamic_pointer_cast<LoadNode>(consumer) != nullptr) {
            return false;
        }

        input_index = 0;
    }
    else {
        unsigned int valid_index = 0;
        if (dynamic_pointer_cast<InvokeMethodNode>(consumer) != nullptr) {
            valid_index = 1;
        }
        else if (dynamic_pointer_cast<StoreNode>(consumer) != nullptr) {
            valid_index = 1;
        }
        else if (dynamic_pointer_cast<LoadNode>(consumer) != nullptr) {
            valid_index = 1;
        }

        input_index = random_between_integer(valid_index, consumer->inputs.size()-1);
    }

    const shared_ptr<SubGraph> sub_graph = this->sub_graph_pool->random_sub_graph();

    /// Using the head node here ensures the longest possible data flow.
    weak_ptr new_input = random_vector_element(sub_graph->nodes);

    auto pre_input = consumer->inputs[input_index];
    auto mu_op_consumer_input = make_unique<MuOpConsumerInput>(consumer, input_index, pre_input, new_input);
    this->applied_mutation_operators.push_back(std::move(mu_op_consumer_input));

    /// setup new edges
    consumer->inputs[input_index] = new_input;
    new_input.lock()->uses.push_back(consumer);

    return true;
}

bool MutatorInsideGraph::mutate_binary_operator(const weak_ptr<BinaryOpNode>& node)
{
    const auto bin_op_node = node.lock();

    if (const string label = bin_op_node->op->label; OperatorPairs::arithmetic_op.contains(label)) {
        auto [op_label, op_code] = random_unordered_map_element(OperatorPairs::arithmetic_op, label);

        auto mu_op_binary_op = make_unique<MuOpBinaryOp>(node, bin_op_node->op);
        this->applied_mutation_operators.push_back(std::move(mu_op_binary_op));

        bin_op_node->op = make_unique<LanguageOperator>(op_label, op_code);

        return true;
    }

    return false;
}

bool MutatorInsideGraph::mutate_literal_float(const weak_ptr<LiteralFloatNode>& node)
{
    const auto float_node = node.lock();

    const int rand_integer = random_between_integer(0, 100);
    const float random_float = random_set_element(this->js_environment->interesting_floats);

    auto mu_op_constant_float = make_unique<MuOpLiteralFloat>(node, float_node->value);
    this->applied_mutation_operators.push_back(std::move(mu_op_constant_float));

    const float rand_value = probability(0.5) ? random_float : rand_integer;

    float_node->value = rand_value;
    return true;
}

bool MutatorInsideGraph::mutate_swap_if_branches(const weak_ptr<IfNode>& node)
{
    const auto if_node = node.lock();

    const auto if_prev = dynamic_pointer_cast<UniSuccessorNode>(if_node->predecessor.lock());
    assert_or_throw_mutate((if_prev != nullptr) && (if_prev->next() == if_node),
        "error in swap if branches");

    if_node->swap_branches();

    /// The order of phi inputs associated with MergeNode affects which branch they're lifted to
    /// However, we can't directly obtain the MergeNode from the if node here
    /// Therefore, we don't rearrange the inputs of potentially existing phi nodes associated with MergeNode
    ///
    auto mu_op_if_branches = make_unique<MuOpSwapIfBranches>(node);
    this->applied_mutation_operators.push_back(std::move(mu_op_if_branches));

    return true;
}

bool MutatorInsideGraph::mutate_move_sequential_operation(const shared_ptr<SequentialOperationNode>& node_to_mv)
{
    /// 1. find a position as moving target
    shared_ptr<UniSuccessorNode> new_predecessor;

    constexpr unsigned int try_times = 10;
    for (int i = 0; i < try_times; i++) {
        new_predecessor = random_set_element(this->move_target_pos).lock();

        // Constraint: Cannot move a node to its original position.
        // This would waste computational resources and could cause logical errors.
        if (node_to_mv->predecessor.lock() != new_predecessor) {
            break;
        }

        new_predecessor = nullptr;
    }

    if (new_predecessor == nullptr) {
        /// mutate failed
        return false;
    }

    const auto orig_prev = node_to_mv->predecessor.lock();
    const auto orig_post = node_to_mv->next();

    /// 2. establish the connection at the original position of the node to mv.
    ///
    /// node_to_mv cannot be a BeginNode, so its predecessor cannot be an IfNode.
    /// Only Uni nodes and IfNodes can have successors.
    /// Therefore, node_to_mv's predecessor must be a Uni node.
    auto orig_prev_uni= dynamic_pointer_cast<UniSuccessorNode>(orig_prev);
    if (orig_prev_uni != nullptr) {
        orig_prev_uni->successor = orig_post;
    }
    else {
        const string msg = "In moving sequential operation, the prev is not a uni";
        cerr << msg << std::endl;
        throw MutateError(msg);
    }
    orig_post->predecessor = orig_prev;

    /// 3. establish the connection at the new position of the node to mv.
    const auto new_post = new_predecessor->next();
    node_to_mv->predecessor = new_predecessor;
    new_predecessor->successor = node_to_mv;

    new_post->predecessor = node_to_mv;
    node_to_mv->successor = new_post;

    auto mu_op = make_unique<MuOpMoveSequentialOperation>(node_to_mv,
                                              orig_prev_uni,
                                              new_predecessor);
    this->applied_mutation_operators.push_back(std::move(mu_op));

    return true;
}

///
/// TODO: Try group
///
bool MutatorInsideGraph::mutate_move_ctrl_group()
{
    auto func_head = dynamic_pointer_cast<FunctionHeadNode>(this->graph->nodes[0]);
    ASSERT_OR_EXIT(func_head != nullptr);

    shared_ptr<FixedNode> walk_start = func_head;

    /// 1. Find all the ctrl groups in a seed.
    auto walker = RecognizeCtrlGroup(walk_start);
    walker.walk();

    auto loop_tail_body = walker.loop_tail_body;
    auto if_tail_body = walker.if_tail_body;

    bool move_loop = probability(0.5);
    if (if_tail_body.empty()) {
        move_loop = true;
    }

    weak_ptr<FixedNode> group_head;
    weak_ptr<UniSuccessorNode> group_tail;
    // group_inners only stores uni-successor nodes between head and tail, not all nodes.
    // There may be other nodes (e.g., IfNode) in between, but non-uni nodes cannot be
    // valid move targets, so the walker skips them.
    set<weak_ptr<UniSuccessorNode>,
        std::owner_less<>> group_inners;

    pair<weak_ptr<UniSuccessorNode>,
         set<weak_ptr<UniSuccessorNode>,
             std::owner_less<>>> tail_body;

    /// 2. Identify the head, tail, and inner uni-successor nodes of the control group to be moved.
    if (move_loop && ! loop_tail_body.empty()) {
        auto [loop_begin, _tail_body] = random_map_element(loop_tail_body);

        /// The EndNode before LoopBegin is the real head.
        group_head = loop_begin.lock()->merged_flows[0];
        group_tail = _tail_body.first;
        group_inners = _tail_body.second;

        assert_or_throw_mutate(dynamic_pointer_cast<EndNode>(group_head.lock()) != nullptr,
            "The ctrl group head of a Loop is an EndNode");
    }
    else if (! if_tail_body.empty()) {
        auto [if_node, _tail_body] = random_map_element(if_tail_body);

        group_head = if_node;
        group_tail = _tail_body.first;
        group_inners = _tail_body.second;

        assert_or_throw_mutate(dynamic_pointer_cast<IfNode>(group_head.lock()) != nullptr,
            "The ctrl group head of if is an IfNode");
    }
    else {
        /// mutation failed
        return false;
    }
    assert_or_throw_mutate(group_tail.lock() != nullptr,
        "The CtrlGroup's tail node should not be nullptr");

    /// 3. Find a valid target position to move to.
    /// The inner uni nodes and the tail node can not be the new prev.
    set<weak_ptr<UniSuccessorNode>,
        std::owner_less<>> invalid_new_prev = group_inners;
    invalid_new_prev.insert(group_tail);

    // Compute set difference between all uni nodes and selected ctrl group's uni nodes for movable targets
    set<weak_ptr<UniSuccessorNode>,
        std::owner_less<>> possible_new_prev;

    std::set_difference(this->move_target_pos.begin(), this->move_target_pos.end(),
                        invalid_new_prev.begin(), invalid_new_prev.end(),
                        std::inserter(possible_new_prev, possible_new_prev.begin()),
                        [](auto& a, auto& b)
                                {return a.lock() < b.lock();}
                        );

    if (possible_new_prev.empty()) {
        cout << "There are no insertion pos outside the chosen ctrl group" << std::endl;
        return false;
    }

    shared_ptr<UniSuccessorNode> new_prev_node;

    for (int i = 0; i < possible_new_prev.size(); i++) {
        new_prev_node = random_set_element(possible_new_prev).lock();

        if (new_prev_node->next() == group_head.lock()) {
            /// Attention! If the chosen new previous node is exactly the previous of the head node
            /// the mutation will be error!
            /// mutator.undo will fail!
            new_prev_node = nullptr;
            continue;
        }
    }

    if (new_prev_node == nullptr) {
        //cout << "Failed to select valid insertion pos" << std::endl;
        return false;
    }

    /// 4. Remove the ctrl group from the original position
    ///
    auto orig_prev = group_head.lock()->predecessor;
    auto orig_post = group_tail.lock()->next();

    auto orig_prev_uni = dynamic_pointer_cast<UniSuccessorNode>(orig_prev.lock());
    if (orig_prev_uni != nullptr) {
        /// If we don't check whether the new prev node is the predecessor of the head node,
        /// and prev_uni happens to be the new prev node, modifying `successor` here will affect
        /// the value of new_prev_node->successor below, leading to incorrect logic.
        orig_prev_uni->successor = orig_post;
    }
    else {
        string msg = "In mutate_MoveCtrlGroup, the prev of head node is not a uni";
        cout << msg << std::endl;
        throw MutateError(msg);
    }

    orig_post->predecessor = orig_prev;

    auto new_post = new_prev_node->next();

    /// 5. Move to the new position
    /// Update edge connections between nodes at the new position
    group_head.lock()->predecessor = new_prev_node;
    new_prev_node->successor = group_head;

    new_post->predecessor = group_tail;
    group_tail.lock()->successor = new_post;

    auto mu_op = make_unique<MuOpMoveCtrlGroup>(group_head,
                                                group_tail,
                                                orig_prev_uni,
                                                new_prev_node);

    this->applied_mutation_operators.push_back(std::move(mu_op));

    return true;
}

bool MutatorInsideGraph::delete_sequential_operation(const weak_ptr<SequentialOperationNode>& node_w)
{
    const auto sequential_operation = node_w.lock();

    const auto prev_node = sequential_operation->predecessor;
    const auto post_node = sequential_operation->next();

    /// The predecessor of a uni node isn't necessarily another uni node - it could be an IfNode.
    /// However, sequential operations always have uni nodes as predecessors,
    /// since IfNode can only be followed by BeginNode.
    const shared_ptr<UniSuccessorNode> prev_uni_node = dynamic_pointer_cast<UniSuccessorNode>(
            prev_node.lock());

    if (prev_uni_node == nullptr) {
        const string msg = "In reducing operation, the prev of prev is not a uni";
        cerr << msg << std::endl;
        throw MutateError(msg);
    }

    prev_uni_node->successor = post_node;
    post_node->predecessor = prev_uni_node;

    auto mu_op = make_unique<MuOpDeleteSequentialOperation>(node_w);
    this->applied_mutation_operators.push_back(std::move(mu_op));

    return true;
}

bool MutatorInsideGraph::mutate_delete_store(const weak_ptr<StoreNode>& node)
{
    return this->delete_sequential_operation(node);
}

bool MutatorInsideGraph::mutate_delete_invoke(const weak_ptr<InvokeNode>& node)
{
    return this->delete_sequential_operation(node);
}

bool MutatorInsideGraph::mutate_delete_delete(const weak_ptr<DeleteNode>& node)
{
    return this->delete_sequential_operation(node);
}

bool MutatorInsideGraph::mutate_insert_store()
{
    auto obj_literal_node = random_set_element(this->_nodes_object_literal);
    auto prop_expr_assignments = obj_literal_node.lock()->prop_expr_assignments();

    if (prop_expr_assignments.empty()) {
        return false;
    }
    auto prop_expr_node = random_vector_element(prop_expr_assignments);
    auto prop_name = prop_expr_node->property_name();

    weak_ptr<DataProducerNode> new_prop_val = this->sub_graph_pool->random_producer_from_pool();

    auto insert_after = random_set_element(this->move_target_pos);

    auto next = insert_after.lock()->next();

    auto store_node = make_shared<StoreNode>(next, obj_literal_node, prop_name, new_prop_val, ObjectAccessType::field);

    store_node->predecessor = insert_after;
    insert_after.lock()->successor = store_node;
    store_node->post_construct();

    /// Sets the node's owner to MuOp (stores the shared_ptr in MuOp)
    /// Note: MuOp's lifetime is tied to the Mutator object
    ///       It will be released after cloning the mutated subgraph
    ///
    auto mu_op = make_unique<MuOpInsertStore>(store_node);
    this->applied_mutation_operators.push_back(std::move(mu_op));

    return true;
}

bool MutatorInsideGraph::mutate_insert_invoke()
{
    if (_nodes_producer.empty()) {
        cerr << "No data producer in the given seed\n";
        return false;
    }

    /// insert to where
    auto insert_after = random_set_element(this->move_target_pos);

    auto next = insert_after.lock()->next();

    /// insert what
    BuiltInObject builtin_object = random_vector_element(this->js_environment->built_in_objects);

    StaticMethod static_method = random_set_element(builtin_object.static_methods);

    string function_name = builtin_object.name + "." + static_method.name;
    unsigned int parameter_num = random_vector_element(static_method.param_count);

    vector<weak_ptr<DataProducerNode>> arg_nodes;
    for (unsigned int i = 0; i < parameter_num; i++) {
        auto arg_node = random_set_element(_nodes_producer);
        arg_nodes.push_back(arg_node);
    }

    auto invoke_node = make_shared<InvokeNode>(function_name, arg_nodes, next, InvokeType::CallFunction);

    /// perform insertion
    invoke_node->predecessor = insert_after;
    insert_after.lock()->successor = invoke_node;
    invoke_node->post_construct();

    auto mu_op = make_unique<MuOpInsertInvoke>(invoke_node);
    this->applied_mutation_operators.push_back(std::move(mu_op));

    return true;
}

bool MutatorInsideGraph::mutate_insert_operation_sequence()
{
    if (sub_graph_pool->pool_operation_sequence.sequences.empty()) {
        return false;
    }

    auto seq = random_set_element(sub_graph_pool->pool_operation_sequence.sequences);
    auto init_prev = seq->nodes.front()->predecessor;
    auto init_post = seq->nodes.back()->successor;

    auto insert_after = random_set_element(this->move_target_pos);

    auto orig_next = insert_after.lock()->next();

    insert_after.lock()->successor = seq->nodes.front();
    seq->nodes.front()->predecessor = insert_after;

    seq->nodes.back()->successor = orig_next;
    orig_next->predecessor = insert_after;

    auto mu_op = make_unique<MuOpInsertOperationSequence>(seq, init_prev, init_post);
    this->applied_mutation_operators.push_back(std::move(mu_op));

    return true;
}

bool MutatorInsideGraph::mutate_splice()
{
    auto splice_prev = random_set_element(this->move_target_pos).lock();
    auto splice_post = splice_prev->next();

    unsigned int try_times = 10;

    shared_ptr<FixedNode> graph_b_head;
    shared_ptr<FixedNode> graph_b_tail;
    shared_ptr<UniSuccessorNode> graph_b_tail_uni;

    for (int i = 0; i < try_times; i++) {
        auto seed = this->corpus->random_element_for_mutating();

        auto graph_b = random_vector_element(seed->js_graphs);
        graph_b = seed->js_graphs[0];

        if (graph_b == this->graph) {
            continue;
        }

        if (graph_b->nodes.size() < 5) {
            continue;
        }

        for (const auto& _node: graph_b->nodes) {
            if (auto end_program = dynamic_pointer_cast<EndProgramNode>(_node);
                end_program != nullptr)
            {
                graph_b_tail = end_program->predecessor.lock();
                graph_b_tail_uni = dynamic_pointer_cast<UniSuccessorNode>(graph_b_tail);
            }
        }

        if (dynamic_pointer_cast<FunctionHeadNode>(graph_b_tail) != nullptr) {
            /// FunctionHeadNode -> EndProgramNode
            continue;
        }

        if (graph_b_tail_uni == nullptr) {
            continue;
        }

        auto function_head = dynamic_pointer_cast<FunctionHeadNode>(graph_b->nodes.front());
        graph_b_head = function_head->successor.lock();

        ASSERT_OR_EXIT(graph_b_head != nullptr);
        ASSERT_OR_EXIT(graph_b_tail_uni != nullptr);

        /// copy the map
        this->graph->splice_graph_varProxy2node = graph_b->varProxy2node;

        break;
    }

    /// find graph b failed
    if (graph_b_head == nullptr) {
        return false;
    }

    auto graph_b_head_prev = dynamic_pointer_cast<UniSuccessorNode>(graph_b_head->predecessor.lock());
    auto graph_b_tail_post = graph_b_tail_uni->successor.lock();

    ASSERT_OR_EXIT(graph_b_head_prev != nullptr);
    ASSERT_OR_EXIT(graph_b_tail_post != nullptr);

    splice_prev->successor = graph_b_head;
    graph_b_head->predecessor = splice_prev;

    splice_post->predecessor = graph_b_tail_uni;
    graph_b_tail_uni->successor = splice_post;

    auto mu_op = make_unique<MuOpSplice>(graph_b_head, graph_b_head_prev, graph_b_tail_uni, graph_b_tail_post);
    this->applied_mutation_operators.push_back(std::move(mu_op));

    return true;
}

} /// end of namespace