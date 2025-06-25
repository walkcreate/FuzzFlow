#ifndef MUTATOR_OUTSIDE_GRAPH_H
#define MUTATOR_OUTSIDE_GRAPH_H

#include "../utils/common_using.h"

#include "../fuzzer/CmdOptions.h"
#include "../fuzzer/Fuzzer.h"
#include "../fuzzer/corpus/SeedEntry.h"

namespace FuzzFlow {

class MutatorOutsideGraph {
public:
    explicit MutatorOutsideGraph (const TargetEngine target_engine)
    {
        this->target_engine = target_engine;
    }

    [[nodiscard]] string mutate_concat(const shared_ptr<SeedEntry> &seed_entry) const;

private:
    TargetEngine target_engine;
};

} // FuzzFlow

#endif //MUTATOR_OUTSIDE_GRAPH_H
