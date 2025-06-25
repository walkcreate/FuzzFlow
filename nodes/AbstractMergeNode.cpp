#include "AbstractMergeNode.h"
#include "PhiNode.h"

namespace FuzzFlow {

vector<weak_ptr<PhiNode>> AbstractMergeNode::phi_nodes()
{
    vector<weak_ptr<PhiNode>> merge_phi_nodes;

    /// Due to force-loop-phi mechanism, idx2phis may contain gaps in phi node indices.
    /// Example: After translating 4 phis, index2 might be removed as unnecessary,
    /// leaving only keys 0, 1, 3 in LoopBegin's idx2phis map.
    ///
    /// When iterating with range-based for (auto& [k,v] : map), C++ sorts by key,
    /// ensuring merge_phi_nodes returns phis in correct original order.
    ///
    for (auto &[idx, node]: this->idx2phis) {
        if (shared_ptr<PhiNode> phi_node = dynamic_pointer_cast<PhiNode>(node.lock())) {
            merge_phi_nodes.push_back(phi_node);
        }
        else {
            cout << "node label: " << node.lock()->get_label() << std::endl;
            assert("Merge use node is not PhiNode" && false);
        }
    }

    return merge_phi_nodes;
}

} /// end of namespace