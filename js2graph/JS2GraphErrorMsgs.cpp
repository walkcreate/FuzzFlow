#include "JS2GraphErrorMsgs.h"

namespace FuzzFlow {

const std::unordered_map<ErrorCodeJS2Graph, std::string> ErrorMsgsJS2Graph::messages =
{
    {ErrorCodeJS2Graph::LastUniSuccessorIsNull,
        "Invalid argument provided."},
    {ErrorCodeJS2Graph::PhiIndexNotMatchMerge,
        "The index of PhiNode does not match the content in MergeNode."},
    {ErrorCodeJS2Graph::VarProxyHasNode,
        "The var proxy node does not exist."},
    {ErrorCodeJS2Graph::VisitLeftValueId,
        "Visiting a left value identifier returns VarSymbol."},
};

} /// end of namespace