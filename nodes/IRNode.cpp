#include "IRNode.h"
#include "FixedNode.h"

#include "../js2graph/Graph.h"
#include "../visitors/GraphVisitor.h"

namespace FuzzFlow {

const string IRNode::label = "IRNode";

void IRNode::accept(GraphVisitor &visitor)
{
    shared_ptr<IRNode> node_self = shared_from_this();

    visitor.visit(node_self);
}

void IRNode::compute_hash_next()
{
    string tokens = node_hash_current;

    bool updated = false;

    if (auto consumer = dynamic_cast<DataConsumerNode *>(this); consumer != nullptr) {
        tokens += consumer->get_neighbor_hash();
        updated = true;
    }

    if (auto fixed = dynamic_cast<FixedNode *>(this); fixed != nullptr) {
        tokens += fixed->get_neighbor_hash();
        updated = true;
    }

    if (updated) {
        this->node_hash_next = std::to_string(std::hash<std::string>{}(tokens));
    }
}

} /// end of namespace
