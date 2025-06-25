#ifndef FUZZFLOW_JS2GRAPHERRORS_H
#define FUZZFLOW_JS2GRAPHERRORS_H

#include "../utils/common_using.h"

namespace FuzzFlow {

enum class ErrorCodeJS2Graph {
    LastUniSuccessorIsNull = 0,
    PhiIndexNotMatchMerge,
    VarProxyHasNode,
    VisitLeftValueId
};

class ErrorMsgsJS2Graph {
public:
    static const unordered_map<ErrorCodeJS2Graph, string> messages;

    static string handleError(const ErrorCodeJS2Graph code)
    {
        const auto it = ErrorMsgsJS2Graph::messages.find(code);

        string msg;

        if (it != ErrorMsgsJS2Graph::messages.end()) {
            msg = "Error(JS2Graph): " + it->second + "\n";
        }
        else {
            msg = "Unknown JS2Graph error occurred.\n";
        }

        return msg;
    }
};

} /// end of namespace

#endif //FUZZFLOW_JS2GRAPHERRORS_H
