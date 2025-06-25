#ifndef FUZZFLOW_MUTATOR_INSIDE_GRAPH_H
#define FUZZFLOW_MUTATOR_INSIDE_GRAPH_H

#include "../utils/common_using.h"
#include "../utils/util_rand.h"

#include "../nodes/AllNodesInclude.h"

#include "../js2graph/Graph.h"
#include "../js2graph/OperatorPairs.h"
#include "../mutationOperator/MuOp.h"

#include "SubGraphPool.h"
#include "RecognizeCtrlGroup.h"
#include "MutatorEnum.h"
#include "OperationSequencePool.h"

#include "../exceptions/MutateError.h"
//#include "../fuzzer/corpus/Corpus.h"
#include "../fuzzer/environment/JSEnvironment.h"

namespace FuzzFlow {

class Corpus;

class MutatorInsideGraph {
public:
    /// Record the implemented mutation operators for review purposes,
    /// rather than for undo functionality.
    vector<MutatorEnum> done_mutators;

    MutatorInsideGraph(const shared_ptr<Graph> &graph,
                       const shared_ptr<JSEnvironment> &js_environment,
                       const shared_ptr<SubGraphPool> &sub_graph_pool,
                       const shared_ptr<Corpus> &corpus)
    {
        this->graph = graph;
        this->sub_graph_pool = sub_graph_pool;
        this->js_environment = js_environment;
        this->corpus = corpus;
    }

    bool mutate();

    void undo_mutate();

private:
    shared_ptr<Corpus> corpus;

    shared_ptr<Graph> graph;

    shared_ptr<JSEnvironment> js_environment;

    shared_ptr<SubGraphPool> sub_graph_pool;

    /// To leverage polymorphism, pointers were the only option.
    vector<unique_ptr<MuOp>> applied_mutation_operators;

    /// non-leave nodes
    set<weak_ptr<DataConsumerNode>,
        std::owner_less<>> nodes_mutable_consumer;

    /// leave nodes in the graph
    set<weak_ptr<LiteralFloatNode>,
        std::owner_less<>> _nodes_float;
    set<weak_ptr<BinaryOpNode>,
        std::owner_less<>> _nodes_binary_op;
    set<weak_ptr<ObjectLiteralNode>,
        std::owner_less<>> _nodes_object_literal;
    set<weak_ptr<IfNode>,
        std::owner_less<>> _nodes_if;
    set<weak_ptr<LoopBegin>,
        std::owner_less<>> _nodes_loop;
    set<weak_ptr<StoreNode>,
        std::owner_less<>> _nodes_store;
    set<weak_ptr<InvokeNode>,
        std::owner_less<>> _nodes_invoke;
    set<weak_ptr<DeleteNode>,
        std::owner_less<>> _nodes_delete;
    set<weak_ptr<DataProducerNode>,
        std::owner_less<>> _nodes_dead;
    set<weak_ptr<DataProducerNode>,
        std::owner_less<>> _nodes_producer;

    set<weak_ptr<SequentialOperationNode>,
        std::owner_less<>> _operations_could_move;

    /// The node is used as target predecessor
    set<weak_ptr<UniSuccessorNode>,
        std::owner_less<>> move_target_pos;

    set<MutatorEnum> supported_mutators;

    void preprocess();

    static bool is_mutable_consumer(const weak_ptr<DataConsumerNode>& node_w);

    /// The return value of mutate_xxx indicates whether the mutation really performed.
    /// 1. The following are mutators on DDG.

    /// 1.1 Change the data dependency between nodes
    bool mutate_consumer_inputs(const weak_ptr<DataConsumerNode>& node);

    /// 1.2 Change the existing data operator
    // todo
    // bool mutate_UnaryOp(const weak_ptr<UnaryOpNode>& node);
    bool mutate_binary_operator(const weak_ptr<BinaryOpNode>& node);

    /// 1.3 Change the literal itself
    bool mutate_literal_float(const weak_ptr<LiteralFloatNode>& node);
    /// todo
    /// bool mutate_literal_string

    /// 2. The following are mutators on CFG

    /// 2.1 Re-scheduling
    bool mutate_swap_if_branches(const weak_ptr<IfNode>& node);

    /// todo
    // bool mutate_LoopRolling(const weak_ptr<LoopBegin>& node) const;

    bool mutate_move_sequential_operation(const shared_ptr<SequentialOperationNode>& node_to_mv);

    bool mutate_move_ctrl_group();

    /// todo
    /// 2.3 Insertion
    /// The return value indicates whether the mutation is finished

    /// 2.3.1 Insertion of sequential operation node
    bool mutate_insert_store();

    bool mutate_insert_invoke();

    bool mutate_insert_operation_sequence();

    bool mutate_splice();

    bool mutate_concat();

    /// todo: 2.3.2 Insertion of ctrl group nodes

    /// 2.4 Deletion
    bool delete_sequential_operation(const weak_ptr<SequentialOperationNode>& node_w);

    bool mutate_delete_store(const weak_ptr<StoreNode>& node);

    bool mutate_delete_invoke(const weak_ptr<InvokeNode>& node);

    bool mutate_delete_delete(const weak_ptr<DeleteNode>& node);

    // todo: delete ctrl group
};

} /// end of namespace

#endif //FUZZFLOW_MUTATOR_INSIDE_GRAPH_H
