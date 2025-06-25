#ifndef FUZZFLOW_TERMINALNODE_H
#define FUZZFLOW_TERMINALNODE_H

#include "IRNode.h"

#include "DataConsumerNode.h"
#include "DataProducerNode.h"

namespace FuzzFlow {

class TerminalNode : virtual public DataProducerNode {
public:

};

} /// end of namespace

#endif //FUZZFLOW_TERMINALNODE_H
