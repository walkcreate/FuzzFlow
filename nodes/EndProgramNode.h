#ifndef FUZZFLOW_ENDPROGRAMNODE_H
#define FUZZFLOW_ENDPROGRAMNODE_H

#include "../utils/common_using.h"

#include "AbstractEndNode.h"

namespace FuzzFlow {

///
/// Why do we need this node?
/// FlowIR operates at function level. For script code not belonging to any function,
/// we treat it as a __main__ function. This main function has no return node.
///
/// While adding a return node to __main__ would work during translation and graph2js,
/// the generated test cases would fail when executed by the V8 engine.
///
/// Therefore, __main__ cannot have a return node, but we still need a way to indicate program termination.
/// Hence the EndProgramNode - it marks the end of the entire test case in main.
///
/// During the Lift phase, encountering EndProgramNode means we should simply return,
/// indicating no further node traversal is needed.
///
class EndProgramNode final : public AbstractEndNode {
    static const string label;
public:
    EndProgramNode() = default;

    string get_label() override
    {
        return EndProgramNode::label;
    }

    shared_ptr<IRNode> clone() override
    {
        return make_shared<EndProgramNode>();
    }

    void accept(GraphVisitor &visitor) override
    {
        auto node = dynamic_pointer_cast<EndProgramNode>(shared_from_this());
        visitor.visit(node);
    }
};

} /// end of namespace

#endif //FUZZFLOW_ENDPROGRAMNODE_H
