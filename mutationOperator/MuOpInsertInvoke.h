#ifndef FUZZFLOW_MUOPINSERTINVOKE_H
#define FUZZFLOW_MUOPINSERTINVOKE_H

#include <algorithm>

#include "../utils/common_using.h"

#include "MuOp.h"

#include "../nodes/InvokeNode.h"

namespace FuzzFlow {

class MuOpInsertInvoke final : public MuOp {
private:
    shared_ptr<InvokeNode> _invoke_node;

public:
    explicit MuOpInsertInvoke(const shared_ptr<InvokeNode> &node)
    {
        _invoke_node = node;
    }

    void undo() override
    {
        const auto prev_node = this->_invoke_node->predecessor.lock();
        const auto post_node = this->_invoke_node->next();
        ASSERT_OR_EXIT(prev_node != nullptr && post_node != nullptr);

        const auto prev_uni_node = dynamic_pointer_cast<UniSuccessorNode>(prev_node);
        ASSERT_OR_EXIT(prev_uni_node != nullptr);

        prev_uni_node->successor = post_node;
        post_node->predecessor = prev_uni_node;

            for ( auto &_input_w: this->_invoke_node->inputs) {
                auto _input = _input_w.lock();

                auto it = std::find_if((_input->uses).begin(), (_input->uses).end(),
                                [this](const weak_ptr<DataConsumerNode> &item) {
                                return this->_invoke_node == item.lock();
                            });

                if (it != _input->uses.end()) {
                    _input->uses.erase(it);
                }
                else {
                    ASSERT_OR_EXIT(false);
                }
            }
    }
};

} /// end of namespace

#endif //FUZZFLOW_MUOPINSERTINVOKE_H
