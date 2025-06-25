#ifndef FUZZFLOW_MUOPINSERTSTORENODE_H
#define FUZZFLOW_MUOPINSERTSTORENODE_H

#include "MuOp.h"
#include "../nodes/js/StoreNode.h"

namespace FuzzFlow {

class MuOpInsertStore final : public MuOp {
public:
    explicit MuOpInsertStore(const shared_ptr<StoreNode> &node)
    {
        this->_store_node = node;
    }

    void undo() override
    {
        const auto prev_node = this->_store_node->predecessor.lock();
        const auto post_node = this->_store_node->next();
        ASSERT_OR_EXIT(prev_node != nullptr && post_node != nullptr);

        const auto prev_uni_node = dynamic_pointer_cast<UniSuccessorNode>(prev_node);
        ASSERT_OR_EXIT(prev_uni_node != nullptr);

        prev_uni_node->successor = post_node;
        post_node->predecessor = prev_uni_node;

        for ( auto &_input_w: this->_store_node->inputs) {
            auto _input = _input_w.lock();

            auto it = std::find_if((_input->uses).begin(), (_input->uses).end(),
                            [this](const weak_ptr<DataConsumerNode> &item) {
                            return this->_store_node == item.lock();
                        });

            if (it != _input->uses.end()) {
                _input->uses.erase(it);
            }
            else {
                ASSERT_OR_EXIT(false);
            }
        }
    }

private:
    shared_ptr<StoreNode> _store_node;
};

} /// end of namespace

#endif //FUZZFLOW_MUOPINSERTSTORENODE_H
