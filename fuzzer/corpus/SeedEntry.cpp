#include "SeedEntry.h"
#include "../../translator.h"

#include "../environment/material/MaterialV8.h"
#include "../environment/material/MaterialSpiderMonkey.h"
#include "../environment/material/MaterialJSC.h"

namespace FuzzFlow {

string SeedEntry::merge_graphs_code()
{
    this->newly_js_code.clear();

    /// The first graph is the __main__ program, we put code in __main__ at last
    for (int i = 1; i < this->graph_codes.size(); i++) {
        this->newly_js_code += this->graph_codes[i];
    }

    this->newly_js_code += this->graph_codes[0];

    return this->newly_js_code;
}

string SeedEntry::merge_mutated_code(const uint32_t mutated_idx, const string& mutated_code) const
{
    string full_js_code;

    /// The first graph is the __main__ program, we put code in __main__ at last
    for (int i = 1; i < this->graph_codes.size(); i++) {
        if (i == mutated_idx) {
            full_js_code += mutated_code;
        }
        else {
            full_js_code += this->graph_codes[i];
        }
    }

    if (mutated_idx == 0) {
        full_js_code += mutated_code;
    }
    else {
        full_js_code += this->graph_codes[0];
    }

    return full_js_code;
}

unique_ptr<SeedEntry> SeedEntry::clone_from_mutation()
{
    vector<shared_ptr<Graph>> js_graphs;
    vector<string> graph_codes;

    for (int i = 0; i < this->js_graphs.size(); i++) {
        shared_ptr<Graph> new_graph;
        string graph_code;

        if (this->mutated_idx2code.contains(i)) {
            /// If a graph has been mutated, we call walk copy
            /// to generate a new graph from mutated graph
            new_graph = this->js_graphs[i]->clone_mutated_graph();
            graph_code = this->mutated_idx2code[i];

            bool debug = false;

            if (debug) {
                /// test the clone
                string dot_save_name = "clone.dot";
                string content = GraphPainter::to_dot(new_graph, true);
                write_text_file(dot_save_name, content);
                cout << "save clone.dot\n";

                string new_code = singleGraph2js(new_graph);

                cout << "code before clone: \n";
                cout << graph_code;

                cout << "code after clone: \n";
                cout << new_code;
            }
        }
        else {
            new_graph = this->js_graphs[i]->clone_non_mutated_graph();
            graph_code = this->graph_codes[i];
        }

        js_graphs.push_back(new_graph);
        graph_codes.push_back(graph_code);
    }

    auto new_seed = make_unique<SeedEntry>(this->initial_name,
                                           this->initial_code,
                                           js_graphs,
                                           graph_codes,
                                           this->mutators_for_child());
    return std::move(new_seed);
}

uint32_t SeedEntry::program_size() const
{
    uint32_t nodes_num = 0;
    for (auto &graph : this->js_graphs) {
        nodes_num += graph->nodes.size();
    }
    return nodes_num;
}

void SeedEntry::append_newly_mutator(const MutatorEnum mutator)
{
    this->newly_mutators.push_back(mutator);
}

void SeedEntry::clear_newly_mutator()
{
    this->newly_mutators.clear();
}

uint32_t SeedEntry::query_generation() const
{
    return this->done_mutators.size();
}

vector<MutatorEnum> SeedEntry::mutators_for_child()
{
    vector<MutatorEnum> full_mutate_trace;

    for (auto& mutator : this->done_mutators) {
        full_mutate_trace.push_back(mutator);
    }

    for (auto& mutator : this->newly_mutators) {
        full_mutate_trace.push_back(mutator);
    }

    return full_mutate_trace;
}

} /// end of namespace