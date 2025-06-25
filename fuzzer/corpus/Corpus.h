#ifndef FUZZFLOW_CORPUS_H
#define FUZZFLOW_CORPUS_H

#include "../../utils/common_using.h"

#include "SeedEntry.h"
#include "../evaluation/CovEdgeSet.h"

namespace FuzzFlow {

class Corpus {
public:
    /// The current set of interesting programs used for mutations.
    set<shared_ptr<SeedEntry>> seeds;

    explicit Corpus(const uint32_t min_size=128,
                    const uint32_t max_size=4096,
                    const uint32_t min_mutations_per_sample=32)
    {
        this->min_size = min_size;
        this->max_size = max_size;

        this->min_mutations_per_sample = min_mutations_per_sample;
        this->seeds = {};
    }

    void initialize();

    [[nodiscard]] uint32_t count() const
    {
        return seeds.size();
    }

    void add(const shared_ptr<SeedEntry>& seed, unique_ptr<ProgramAspects> aspects)
    {
        this->seeds.insert(seed);
    }

    [[nodiscard]] shared_ptr<SeedEntry> random_element_for_mutating() const
    {
        const unsigned int index = random_container_index(this->count());
        auto it = seeds.begin();
        std::advance(it, index);
        return *it;
    }

    void export_state();

    void import_state();

    void cleanup();

    static shared_ptr<SeedEntry> build_seed(const std::filesystem::path& seed_js_path,
                                            const shared_ptr<SubGraphPool>& sub_graph_pool=nullptr);

private:
    /// The minimum number of samples that should be kept in the corpus.
    uint32_t min_size = 0;
    uint32_t max_size = 0;
    uint32_t min_mutations_per_sample;
};

} /// end of namespace


#endif //FUZZFLOW_CORPUS_H
