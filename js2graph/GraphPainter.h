#ifndef FUZZFLOW_GRAPHPAINTER_H
#define FUZZFLOW_GRAPHPAINTER_H

#include "../utils/common_using.h"

#include "../nodes/AllNodesInclude.h"

#include "Graph.h"

namespace FuzzFlow {

class GraphPainter {
public:
    static string to_dot(shared_ptr<Graph> graph, bool rescheduling_index=false);
};

} /// end of namespace

#endif //FUZZFLOW_GRAPHPAINTER_H
