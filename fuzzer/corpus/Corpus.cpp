#include "Corpus.h"
#include "../../translator.h"

namespace FuzzFlow {

void Corpus::initialize()
{
}

shared_ptr<SeedEntry> Corpus::build_seed(const std::filesystem::path& seed_js_path,
                                         const shared_ptr<SubGraphPool>& sub_graph_pool)
{
    string initial_name = seed_js_path.filename();

    std::ifstream ifs(seed_js_path);
    std::ostringstream ss;
    ss << ifs.rdbuf();
    string initial_code = ss.str();

    auto graphs = js2multiGraphs(seed_js_path);

    for (const auto& graph : graphs) {
        sub_graph_pool->extract(graph);
        sub_graph_pool->pool_operation_sequence.extract(graph);
    }

    auto graphs_code = multiGraphs2js(graphs);

    auto seed_entry = make_shared<SeedEntry>(initial_name, initial_code, graphs, graphs_code);

    return seed_entry;
}

} /// end of namespace FuzzFlow
