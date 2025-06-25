#ifndef FUZZFLOW_JS2GRAPH_UTILS_H
#define FUZZFLOW_JS2GRAPH_UTILS_H

#include "../utils/common_using.h"

#include "../nodes/AllNodesInclude.h"

#include "../nodes/DataProducerNode.h"

namespace FuzzFlow {

shared_ptr<DataProducerNode> any2DataProducer(std::any node_any);

} /// end of namespace

#endif //FUZZFLOW_JS2GRAPH_UTILS_H
