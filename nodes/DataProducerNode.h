#ifndef FUZZFLOW_DATAPRODUCERNODE_H
#define FUZZFLOW_DATAPRODUCERNODE_H

#include "../utils/common_using.h"

#include "IRNode.h"

namespace FuzzFlow {

class DataConsumerNode;

class JavaScriptLifter;

class DataProducerNode : virtual public IRNode {
public:
    vector<weak_ptr<DataConsumerNode>> uses;

    virtual string get_producer_expr(JavaScriptLifter &visitor)
    {
        return "";
    }
};

}

#endif //FUZZFLOW_DATAPRODUCERNODE_H
