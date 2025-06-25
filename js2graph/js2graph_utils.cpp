#include "js2graph_utils.h"

#include <cxxabi.h>

#include "../exceptions/JS2GraphError.h"

namespace FuzzFlow {

using std::any_cast;

///
/// cast the std::any type (return value of AST visitor) to DDGNode
///
shared_ptr<DataProducerNode> any2DataProducer(std::any node_any)
{
    shared_ptr<DataProducerNode> node = nullptr;

    if (node_any.type() == typeid(shared_ptr<DataProducerNode>)) {
        node = any_cast<shared_ptr<DataProducerNode>>(node_any);
    }

    if (node_any.type() == typeid(shared_ptr<PhiNode>)) {
        node = any_cast<shared_ptr<PhiNode>>(node_any);
    }

    if (node_any.type() == typeid(shared_ptr<ParameterNode>)) {
        node = any_cast<shared_ptr<ParameterNode>>(node_any);
    }

    if (node_any.type() == typeid(shared_ptr<LiteralFloatNode>)) {
        node = any_cast<shared_ptr<LiteralFloatNode>>(node_any);
    }

    if (node_any.type() == typeid(shared_ptr<LiteralStringNode>)) {
        node = any_cast<shared_ptr<LiteralStringNode>>(node_any);
    }

    if (node_any.type() == typeid(shared_ptr<LiteralBoolNode>)) {
        node = any_cast<shared_ptr<LiteralBoolNode>>(node_any);
    }

    if (node_any.type() == typeid(shared_ptr<BinaryOpNode>)) {
        node = any_cast<shared_ptr<BinaryOpNode>>(node_any);
    }

    if (node_any.type() == typeid(shared_ptr<UnaryOpNode>)) {
        node = any_cast<shared_ptr<UnaryOpNode>>(node_any);
    }

    if (node_any.type() == typeid(shared_ptr<TernaryOpNode>)) {
        node = any_cast<shared_ptr<TernaryOpNode>>(node_any);
    }

    if (node_any.type() == typeid(shared_ptr<ObjectLiteralNode>)) {
        node = any_cast<shared_ptr<ObjectLiteralNode>>(node_any);
    }

    if (node_any.type() == typeid(shared_ptr<PropExprAssignNode>)) {
        node = any_cast<shared_ptr<PropExprAssignNode>>(node_any);
    }

    if (node_any.type() == typeid(shared_ptr<ComputedPropExprAssignNode>)) {
        node = any_cast<shared_ptr<ComputedPropExprAssignNode>>(node_any);
    }

    if (node_any.type() == typeid(shared_ptr<FunctionPropertyNode>)) {
        node = any_cast<shared_ptr<FunctionPropertyNode>>(node_any);
    }

    if (node_any.type() == typeid(shared_ptr<ArrayLiteralNode>)) {
        node = any_cast<shared_ptr<ArrayLiteralNode>>(node_any);
    }

    if (node_any.type() == typeid(shared_ptr<ThisNode>)) {
        node = any_cast<shared_ptr<ThisNode>>(node_any);
    }

    if (node_any.type() == typeid(shared_ptr<BuiltinNode>)) {
        node = any_cast<shared_ptr<BuiltinNode>>(node_any);
    }

    if (node_any.type() == typeid(shared_ptr<GlobalVarNode>)) {
        node = any_cast<shared_ptr<GlobalVarNode>>(node_any);
    }

    if (node_any.type() == typeid(shared_ptr<GlobalFunctionNode>)) {
        node = any_cast<shared_ptr<GlobalFunctionNode>>(node_any);
    }

    if (node_any.type() == typeid(shared_ptr<ForInPropName>)) {
        node = any_cast<shared_ptr<ForInPropName>>(node_any);
    }

    if (node_any.type() == typeid(shared_ptr<InvokeNode>)) {
        node = any_cast<shared_ptr<InvokeNode>>(node_any);
    }

    if (node_any.type() == typeid(shared_ptr<InvokeMethodNode>)) {
        node = any_cast<shared_ptr<InvokeMethodNode>>(node_any);
    }

    if (node_any.type() == typeid(shared_ptr<LoadNode>)) {
        node = any_cast<shared_ptr<LoadNode>>(node_any);
    }

    if (node_any.type() == typeid(shared_ptr<DeleteNode>)) {
        node = any_cast<shared_ptr<DeleteNode>>(node_any);
    }

    if (node != nullptr) {
        return node;
    }

    int status = 0;
    cout << "Not supported Producer subclass: "
         << __cxxabiv1::__cxa_demangle(node_any.type().name(), nullptr, nullptr, &status)
         << std::endl;

    /// WebKit_JSTests_stress_reverse-with-immutable-butterfly.js triggers this assertion
    throw JS2GraphError("Not supported Producer subclass");
    return nullptr;
}

} /// end of namespace