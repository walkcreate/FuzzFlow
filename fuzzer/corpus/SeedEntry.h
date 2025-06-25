#ifndef FUZZFLOW_SEEDENTRY_H
#define FUZZFLOW_SEEDENTRY_H

// use boost's uuid
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

// used to string representation
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <utility>

#include "../../utils/common_using.h"

#include "../../mutate/MutatorInsideGraph.h"
#include "../../js2graph/Graph.h"
#include "../../mutate/MutatorEnum.h"

namespace FuzzFlow {

class SeedEntry {
public:
    string initial_name;
    string initial_code;

    string header_comments;
    string footer_comments;

    /// access graphs_being_building with index
    vector<shared_ptr<Graph>> js_graphs;

    /// access function code with index
    vector<string> graph_codes;

    /// bundle of graphs_being_building code
    string newly_js_code;

    /// The map of indexes of mutated graph to newly lifted graph code
    /// todo std::list better?
    map<uint32_t, string> mutated_idx2code;

    /// record the mutation operator, we will use it when undoing mutate
    unique_ptr<MutatorInsideGraph> last_mutator;

    unsigned int age = 0;

    SeedEntry(string initial_name,
              string initial_code,
              vector<shared_ptr<Graph>> js_graphs,
              vector<string> graph_codes)
    {
        this->initial_name = std::move(initial_name);
        this->initial_code = std::move(initial_code);

        /// The constructor only initialize the js_graphs.
        /// The funcName2code and full_js_code will be initialized after the first lift
        this->js_graphs = std::move(js_graphs);

        this->graph_codes = std::move(graph_codes);
    }

    SeedEntry(string initial_name,
              string initial_code,
              const vector<shared_ptr<Graph>> &js_graphs,
              const vector<string> &graph_codes,
              const vector<MutatorEnum> &done_mutators)
    {
        this->initial_name = std::move(initial_name);
        this->initial_code = std::move(initial_code);

        /// The constructor only initialize the js_graphs.
        /// The funcName2code and full_js_code will be initialized after the first lift
        this->js_graphs = js_graphs;

        this->graph_codes = graph_codes;

        // copy the vector
        this->done_mutators = done_mutators;
    }

    [[nodiscard]] string uuid2str() const
    {
        auto uuid = boost::lexical_cast<std::string>(id);
        return uuid;
    }

    /// merge code among graphs_being_building to construct a full js test case
    string merge_graphs_code();

    [[nodiscard]] string merge_mutated_code(uint32_t mutated_idx, const string &mutated_code) const;

    unique_ptr<SeedEntry> clone_from_mutation();

    [[nodiscard]] uint32_t program_size() const;

    /// record the mutation operator
    void append_newly_mutator(MutatorEnum mutator);

    void clear_newly_mutator();

    /// Obtain the mutation generation of the seed
    /// (which generation did the seed mutate from?
    /// The original seed is considered as the 0th generation).
    [[nodiscard]] uint32_t query_generation() const;

private:
    boost::uuids::uuid id = boost::uuids::random_generator()();

    /// mutation trace
    vector<MutatorEnum> done_mutators;
    vector<MutatorEnum> newly_mutators;

    /// When interesting seed occurred, we construct the full mutation trace as constructor parameter for child seed.
    vector<MutatorEnum> mutators_for_child();
};

} /// end of namespace

#endif //FUZZFLOW_SEEDENTRY_H
