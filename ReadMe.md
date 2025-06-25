
# FuzzFlow v0.2

## Changelog

Compared to v0.1, FuzzFlow v0.2 has undergone substantial refactoring to improve code clarity and maintainability. 

The key improvements include:

1. Code Normalization Using Babel.
To reduce complexity and eliminate redundant code in JS2Graph and Graph2JS modules, we implemented Babel-based normalization for initial seed sets. 
This process removes syntactic sugar (such as arrow functions and class declarations) and standardizes various syntax forms (e.g., unifying different loop constructs).
The removal of syntactic sugar and syntax normalization has, to some extent, reduced the exploration of state in the JS engine's frontend. 
However, given the near absence of software defects in the frontend and the significant improvement in maintainability this upgrade brings to both JS2Graph and Graph2JS, 
we believe this trade-off is justified.

2. Node Consolidation
We merged several node types to reduce overall node and edge counts, such as:
- Combining CallTargetNode into InvokeNode
- Merging DeleteTargetNode with DeleteNode
- Unifying StoreFieldNode and StoreNode

3. Refactored Inheritance Hierarchy for Data Flow Nodes
The original FloatingNode class has been replaced with two specialized types: DataProducerNode and DataConsumerNode.
Data flow nodes can now inherit from either type individually or both simultaneously, providing clearer semantic representation.

4. Enhanced Node Type Representation
Certain data flow nodes now inherit from both FixedNode and DataXNode classes to better reflect their dual characteristics in data flow and side effect behaviors.

5. Graph2JS Module Rewrite
The Graph2JS module has been completely redesigned using the interpreter pattern for improved performance and maintainability.

6. Edge Optimization
We removed low-value mutation edges, such as:
- Connections between LoopEnd and LoopBegin nodes
- Links between ThrowNode and CatchNode/Finally nodes

7. Mutation Component Refactoring
The mutation component has been restructured to accommodate the new node inheritance architecture.

8. Memory Optimization
Node classes have been upgraded to reduce memory allocation overhead.

## Dependencies

- C++-20
- Boost 1.86.0
- Antlr 4.9.3 (with a little patch)
- cmake
- NodeJS, Babel

## Build

```shell
git clone this_project

cd js_normalize

npm install

cd ..

mkdir build && cd build

cmake ..

cmake --build . 
```

## Usage

```shell
./FuzzFlow --help

# Set the absolute path to js_normalize/main.js using environment variables
NORMALIZER=/path/to/js_normalize/main.js ./FuzzFlow --jsPath /path/to/js_engine_executable --profile=v8/spidermonkey/jsc --storagePath /path/to/storage --inputDir /path/to/js_seeds --exportStatistics=true --statisticsExportInterval=10
```

## Development Plan

1. mutation operator scheduling
2. more mutation operators
3. supporting more language features

v0.3 is on its way!
