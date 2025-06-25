#include "MutatorOutsideGraph.h"

#include "../fuzzer/environment/material/MaterialV8.h"
#include "../fuzzer/environment/material/MaterialSpiderMonkey.h"
#include "../fuzzer/environment/material/MaterialJSC.h"

namespace FuzzFlow {

string MutatorOutsideGraph::mutate_concat(const shared_ptr<SeedEntry> &seed_entry) const
{
    string full_js_code;

    for (int i = 0; i < seed_entry->graph_codes.size(); i++) {
        if (seed_entry->js_graphs[i]->get_function_name() == "__main__") {
            continue;
        }

        full_js_code += seed_entry->graph_codes[i];
    }

    switch (target_engine) {
        case TargetEngine::V8: {
            full_js_code += MaterialV8::prefix_suffix_pairs[0].first;
            break;
        }
        case TargetEngine::SM: {
            full_js_code += MaterialSpiderMonkey::prefix_suffix_pairs[0].first;
            break;
        }
        case TargetEngine::JSC: {
            full_js_code += MaterialJSC::prefix_suffix_pairs[0].first;
            break;
        }
        default: {
            return {};
        }
    }

    for (int i = 0; i < seed_entry->graph_codes.size(); i++) {

        if (seed_entry->js_graphs[i]->get_function_name() != "__main__") {
            continue;
        }

        full_js_code += seed_entry->graph_codes[i];
    }

    switch (target_engine) {
        case TargetEngine::V8: {
            full_js_code += MaterialV8::prefix_suffix_pairs[0].second;
            break;
        }
        case TargetEngine::SM: {
            full_js_code += MaterialSpiderMonkey::prefix_suffix_pairs[0].second;
            break;
        }
        case TargetEngine::JSC: {
            full_js_code += MaterialJSC::prefix_suffix_pairs[0].second;
            break;
        }
        default: {
            return {};
        }
    }

    return full_js_code;
}

} // FuzzFlow