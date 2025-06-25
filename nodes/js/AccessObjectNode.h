#ifndef FUZZFLOW_ACCESSOBJECTNODE_H
#define FUZZFLOW_ACCESSOBJECTNODE_H

#include "../DataConsumerNode.h"
#include "../DataProducerNode.h"

namespace FuzzFlow {

enum class ObjectAccessType {
    field,
    index
};

class AccessObjectNode : public DataConsumerNode {
private:

public:
    ObjectAccessType access_type;

    // StoreField/Index LoadField/Index all have an object child
    shared_ptr<DataProducerNode> object() const
    {
        return this->inputs[0].lock();
    }

    void set_object(const weak_ptr<DataProducerNode> &obj)
    {
        this->inputs.clear();
        this->inputs[0] = obj;
    }

    shared_ptr<DataProducerNode> property() const
    {
        return this->inputs[1].lock();
    }
};

} /// end of namespace

#endif //FUZZFLOW_ACCESSOBJECTNODE_H
