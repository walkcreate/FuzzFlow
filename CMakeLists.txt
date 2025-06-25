cmake_minimum_required(VERSION 3.19)
project(FuzzFlow CXX C)

set(CMAKE_CXX_STANDARD 20)

# Release version or not?
set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_BUILD_TYPE Debug)

# use boost
set(Boost_ROOT
    /path_to/boost_1_86_0_install)

find_package(Boost 1.86
    REQUIRED COMPONENTS
    json
    program_options
    stacktrace_backtrace
)

include_directories(${Boost_ROOT}/include)
link_directories(${Boost_ROOT}/lib)

# antlr version: 4.9.3, 70b2edc
# set antlr runtime install path
include_directories("thirdparty/antlr4-cpp-runtime/include/antlr4-runtime")
link_directories(${CMAKE_SOURCE_DIR}/thirdparty/antlr4-cpp-runtime/lib)

# for antlr
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# some sources appeared in executable and library
set(FuzzFlow_node_sources
    ${CMAKE_SOURCE_DIR}/nodes/IRNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/DataProducerNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/DataConsumerNode.cpp

    ${CMAKE_SOURCE_DIR}/nodes/FakeDataProducerNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/AbstractMergeNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/FixedNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/UniSuccessorNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/LoopBegin.cpp
    ${CMAKE_SOURCE_DIR}/nodes/MergeNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/InvokeNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/InvokeMethodNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/IfNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/LoopIf.cpp
    ${CMAKE_SOURCE_DIR}/nodes/PhiNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/FunctionHeadNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/EndNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/LiteralNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/LiteralStringNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/LiteralFloatNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/LiteralBoolNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/BinaryOpNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/BeginNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/ParameterNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/LoopEnd.cpp
    ${CMAKE_SOURCE_DIR}/nodes/LoopExit.cpp
    ${CMAKE_SOURCE_DIR}/nodes/ReturnNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/UnaryOpNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/EndProgramNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/CtrlRelayNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/TerminalNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/TernaryOpNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/GlobalVarNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/GlobalFunctionNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/AbstractEndNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/SequentialOperationNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/SequentialOperationNode.h

    ${CMAKE_SOURCE_DIR}/nodes/js/ThisNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/js/StoreNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/js/PropExprAssignNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/js/FunctionPropertyNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/js/ObjectLiteralNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/js/LoadNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/js/FunctionPropertyNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/js/BuiltinNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/js/ArrayLiteralNode.cpp

    ${CMAKE_SOURCE_DIR}/nodes/js/TryNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/js/CatchNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/js/FinallyNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/js/UnwindNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/js/TryExit.cpp
    ${CMAKE_SOURCE_DIR}/nodes/js/DeleteNode.cpp
    ${CMAKE_SOURCE_DIR}/nodes/js/ForInPropName.cpp
    ${CMAKE_SOURCE_DIR}/nodes/js/ForInEnum.cpp
    ${CMAKE_SOURCE_DIR}/nodes/js/CatchIdNode.cpp
)

set(FuzzFlow_translate_sources
    ${FuzzFlow_node_sources}

    ${CMAKE_SOURCE_DIR}/utils/util_rand.cpp
    ${CMAKE_SOURCE_DIR}/utils/util_time.cpp
    ${CMAKE_SOURCE_DIR}/utils/assert_or_throw.cpp
    ${CMAKE_SOURCE_DIR}/utils/assert_or_exit.cpp
    ${CMAKE_SOURCE_DIR}/utils/backtrace.cpp

    ${CMAKE_SOURCE_DIR}/translator.cpp
    ${CMAKE_SOURCE_DIR}/visitors/RefResolver.cpp

    ${CMAKE_SOURCE_DIR}/thirdparty/antlr4/JavaScriptLexer.cpp
    ${CMAKE_SOURCE_DIR}/thirdparty/antlr4/JavaScriptParser.cpp
    ${CMAKE_SOURCE_DIR}/thirdparty/antlr4/JavaScriptLexerBase.cpp
    ${CMAKE_SOURCE_DIR}/thirdparty/antlr4/JavaScriptParserBase.cpp
    ${CMAKE_SOURCE_DIR}/thirdparty/antlr4/JavaScriptParserBaseVisitor.cpp

    ${CMAKE_SOURCE_DIR}/semantic/Scope.cpp

    ${CMAKE_SOURCE_DIR}/js2graph/TestVisit.cpp
    ${CMAKE_SOURCE_DIR}/js2graph/IRGenerator.cpp
    ${CMAKE_SOURCE_DIR}/js2graph/GraphPainter.cpp
    ${CMAKE_SOURCE_DIR}/js2graph/OperatorPairs.cpp
    ${CMAKE_SOURCE_DIR}/js2graph/Graph.cpp
    ${CMAKE_SOURCE_DIR}/js2graph/js2graph_utils.cpp
    ${CMAKE_SOURCE_DIR}/js2graph/JS2GraphErrorMsgs.cpp
    ${CMAKE_SOURCE_DIR}/js2graph/LanguageOperatorFactory.cpp
    ${CMAKE_SOURCE_DIR}/js2graph/LanguageOperatorFactory.h

    ${CMAKE_SOURCE_DIR}/graph2js/JavaScriptLifter.cpp
    ${CMAKE_SOURCE_DIR}/graph2js/ScriptWriter.cpp
    ${CMAKE_SOURCE_DIR}/graph2js/RegionSingle.cpp
    ${CMAKE_SOURCE_DIR}/graph2js/Region.cpp

    ${CMAKE_SOURCE_DIR}/mutate/SubGraphPool.cpp
    ${CMAKE_SOURCE_DIR}/mutate/SubGraph.cpp
    ${CMAKE_SOURCE_DIR}/mutate/LiteralPool.cpp
    ${CMAKE_SOURCE_DIR}/mutate/OperationSequencePool.cpp
)

set(FuzzFlow_mutate_sources
    ${CMAKE_SOURCE_DIR}/exceptions/MutateError.cpp

    ${CMAKE_SOURCE_DIR}/mutate/MutatorInsideGraph.cpp
    ${CMAKE_SOURCE_DIR}/mutate/MutatorOutsideGraph.cpp

    ${CMAKE_SOURCE_DIR}/mutate/WalkCtrlFlow.cpp
    ${CMAKE_SOURCE_DIR}/mutate/RecognizeCtrlGroup.cpp
    ${CMAKE_SOURCE_DIR}/mutate/WalkCopyGraph.cpp
    ${CMAKE_SOURCE_DIR}/mutate/OperationSequence.cpp
    ${CMAKE_SOURCE_DIR}/mutate/ExtractOperationSequence.cpp

    ${CMAKE_SOURCE_DIR}/mutationOperator/MuOp.cpp
    ${CMAKE_SOURCE_DIR}/mutationOperator/MuOpSwapIfBranches.cpp
    ${CMAKE_SOURCE_DIR}/mutationOperator/MuOpInsertStore.cpp
    ${CMAKE_SOURCE_DIR}/mutationOperator/MuOpInsertInvoke.cpp
    ${CMAKE_SOURCE_DIR}/mutationOperator/MuOpDeleteSequentialOperation.cpp
    ${CMAKE_SOURCE_DIR}/mutationOperator/MuOpMoveSequentialOperation.cpp
    ${CMAKE_SOURCE_DIR}/mutationOperator/MuOpInsertOperationSequence.cpp
    ${CMAKE_SOURCE_DIR}/mutationOperator/MuOpSplice.cpp
    ${CMAKE_SOURCE_DIR}/mutationOperator/MuOpConcat.cpp

    ${CMAKE_SOURCE_DIR}/fuzzer/environment/JSEnvironment.cpp
    ${CMAKE_SOURCE_DIR}/fuzzer/environment/BuiltInObject.cpp
    ${CMAKE_SOURCE_DIR}/fuzzer/environment/Constructor.cpp
    ${CMAKE_SOURCE_DIR}/fuzzer/environment/StaticMethod.cpp
    ${CMAKE_SOURCE_DIR}/fuzzer/environment/InstanceMethod.cpp

    ${CMAKE_SOURCE_DIR}/fuzzer/environment/material/MaterialV8.cpp
    ${CMAKE_SOURCE_DIR}/fuzzer/environment/material/MaterialSpiderMonkey.cpp
    ${CMAKE_SOURCE_DIR}/fuzzer/environment/material/MaterialJSC.cpp
)

# some sources appeared in executable and library
set(FuzzFlow_main_sources
    ${FuzzFlow_translate_sources}
    ${FuzzFlow_mutate_sources}
)

set(FuzzFlow_fuzzer_sources
    ${CMAKE_SOURCE_DIR}/fuzzer/execution/REPRL.cpp
    ${CMAKE_SOURCE_DIR}/fuzzer/execution/Execution.cpp
    ${CMAKE_SOURCE_DIR}/fuzzer/execution/ExecutionOutcome.cpp
    ${CMAKE_SOURCE_DIR}/fuzzer/execution/REPRLExecution.cpp
    ${CMAKE_SOURCE_DIR}/fuzzer/evaluation/CovEdgeSet.cpp
    ${CMAKE_SOURCE_DIR}/fuzzer/evaluation/ProgramCoverageEvaluator.cpp
    ${CMAKE_SOURCE_DIR}/fuzzer/corpus/Corpus.cpp
    ${CMAKE_SOURCE_DIR}/fuzzer/corpus/SeedEntry.cpp
    ${CMAKE_SOURCE_DIR}/fuzzer/corpus/SeedComments.cpp
    ${CMAKE_SOURCE_DIR}/fuzzer/protobuf/ExportStatistics.cpp
    ${CMAKE_SOURCE_DIR}/fuzzer/Util/MovingAverage.cpp

    ${CMAKE_SOURCE_DIR}/fuzzer/CmdOptions.cpp
    ${CMAKE_SOURCE_DIR}/fuzzer/Storage.cpp
    ${CMAKE_SOURCE_DIR}/fuzzer/MovingStatistics.cpp
    ${CMAKE_SOURCE_DIR}/fuzzer/Fuzzer.cpp
    ${CMAKE_SOURCE_DIR}/fuzzer/TerminalUI.cpp

    ${CMAKE_SOURCE_DIR}/fuzzer/profiles/V8Profile.cpp
    ${CMAKE_SOURCE_DIR}/fuzzer/profiles/SpidermonkeyProfile.cpp
    ${CMAKE_SOURCE_DIR}/fuzzer/profiles/ChakraProfile.cpp
    ${CMAKE_SOURCE_DIR}/fuzzer/profiles/JSCProfile.cpp
    ${CMAKE_SOURCE_DIR}/fuzzer/profiles/JerryProfile.cpp
    ${CMAKE_SOURCE_DIR}/fuzzer/profiles/QjsProfile.cpp

    ${CMAKE_SOURCE_DIR}/fuzzer/events/Subject.cpp
    ${CMAKE_SOURCE_DIR}/fuzzer/events/Event.cpp
    ${CMAKE_SOURCE_DIR}/fuzzer/events/Observer.cpp
)

add_library(reprl
    STATIC
    ${CMAKE_SOURCE_DIR}/fuzzer/libreprl/libreprl-posix.c
)

add_library(coverage
    STATIC
    ${CMAKE_SOURCE_DIR}/fuzzer/libcoverage/coverage.c
)

add_executable(FuzzFlow
    FuzzerCli.cpp
    ${FuzzFlow_main_sources}
    ${FuzzFlow_fuzzer_sources}
)

target_link_libraries(FuzzFlow
    Threads::Threads

    reprl
    coverage

    /lib/x86_64-linux-gnu/librt.a

    ${CMAKE_SOURCE_DIR}/thirdparty/antlr4-cpp-runtime/lib/libantlr4-runtime.a

    ## statically link boost
    ${Boost_ROOT}/lib/libboost_json.a
    ${Boost_ROOT}/lib/libboost_program_options.a
    ${Boost_ROOT}/lib/libboost_process.a

    # libs stacktrace
    backtrace
    -rdynamic
    # Although we link statically, we use `dl`
    # The dl must be put after the stacktrace lib
    dl
)

add_executable(Translate
    EvalTranslate.cpp
    ${FuzzFlow_main_sources}
)

target_link_libraries(Translate
    Threads::Threads
    ${CMAKE_SOURCE_DIR}/thirdparty/antlr4-cpp-runtime/lib/libantlr4-runtime.a
    backtrace
    -rdynamic
    dl
)
