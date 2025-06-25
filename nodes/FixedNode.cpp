#include "FixedNode.h"

#include "IfNode.h"
#include "AbstractBeginNode.h"

#include "../utils/assert_or_throw.h"
#include "js/ForInEnum.h"

namespace FuzzFlow {

weak_ptr<AbstractBeginNode> FixedNode::get_begin_node()
{
    if (const auto _cur_node = dynamic_cast<AbstractBeginNode *>(this); _cur_node != nullptr) {
        const auto node_self = dynamic_pointer_cast<AbstractBeginNode>(shared_from_this());
        return node_self;
    }

    /// The predecessor of a FixedNode is either a UniSuccessor or a IfNode
    /// AbstractEnd and FakeCtrl has no successors thus can not be predecessor of others.
    if (dynamic_pointer_cast<UniSuccessorNode>(this->predecessor.lock()) != nullptr) {
        return this->predecessor.lock()->get_begin_node();
    }

    if (dynamic_pointer_cast<IfNode>(this->predecessor.lock()) != nullptr) {
        /// Loop exit predecessor: IfNode (non-UniSuccessorNode)
        return this->predecessor.lock()->get_begin_node();
    }

    assert_or_throw_js2graph(false, "Error in get_begin_node");
    /// use a braced initializer list
    return {};
}

string FixedNode::get_neighbor_hash()
{
    if (const auto node = dynamic_cast<UniSuccessorNode *>(this); node != nullptr) {
        return node->successor.lock()->node_hash_current;
    }

    if (const auto node = dynamic_cast<IfNode *>(this); node != nullptr) {
        string current =  node->branch_true()->node_hash_current;
        current += node->branch_false()->node_hash_current;
        return current;
    }

    if (const auto node = dynamic_cast<ForInEnum *>(this); node != nullptr) {
        string current =  node->branch_true()->node_hash_current;
        current += node->branch_false()->node_hash_current;
        return current;
    }

    /// abstract end node
    return {};
}

} /// end of namespace