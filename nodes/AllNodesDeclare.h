#ifndef FUZZFLOW_DECLAREALLNODES_H
#define FUZZFLOW_DECLAREALLNODES_H

namespace FuzzFlow {

class AbstractMergeNode;
class BeginNode;
class BinaryOpNode;
class LiteralNode;
class LiteralBoolNode;
class LiteralFloatNode;
class LiteralStringNode;
class CtrlRelayNode;
class EndNode;
class EndProgramNode;

class FunctionHeadNode;
class GlobalVarNode;
class GlobalFunctionNode;
class IfNode;
class InvokeMethodNode;
class InvokeNode;
class LoopBegin;
class LoopEnd;
class LoopExit;
class LoopIf;
class MergeNode;
class ParameterNode;
class PhiNode;
class ReturnNode;
class StartNode;
class TerminalNode;
class TernaryOpNode;
class UnaryOpNode;
class UniSuccessorNode;

class FakeCtrlNode;
class FixedNode;
class IRNode;

class AccessObjectNode;
class ArrayLiteralNode;
class BuiltinNode;
class CatchIdNode;
class CatchNode;
class ComputedPropExprAssignNode;
class DeleteNode;
class FinallyNode;
class ForInEnum;
class ForInPropName;
class FunctionPropertyNode;
class LoadNode;
class NewInstanceNode;
class ObjectLiteralNode;
class PropExprAssignNode;
class StoreNode;
class ThisNode;
class ThrowNode;
class TryExit;
class TryNode;
class UnwindNode;

class EndMayMergeNode;

}

#endif //FUZZFLOW_DECLAREALLNODES_H
