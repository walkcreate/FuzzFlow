#ifndef FUZZFLOW_SONSTATISTICS_H
#define FUZZFLOW_SONSTATISTICS_H

#include <stdint.h>

namespace FuzzFlow {

/// Some statistics only used in FuzzFlow project
class FuzzFlowStatistics {
public:
    //// The number of samples failed at translate. Not necessary. translate is only needed at seed preparing.
    uint64_t js2son_failed_samples = 0;

    //// The number of samples failed at graph2js
    uint64_t son2js_failed_samples = 0;

    //// The number of independent dataflow subgraphs
    uint32_t dataflow_pool_size = 0;
};

} /// end of namespace

#endif //FUZZFLOW_SONSTATISTICS_H
