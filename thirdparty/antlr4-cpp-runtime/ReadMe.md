
This directory contains ANTLR4 C++ runtime (commit 70b2edc) built and installed from other directories for easier project deployment.

Note:
- This version is between releases 4.9.3 and 4.10.
- Though named "antlr-cpp-runtime", it's functionally equivalent to an installation directory of the runtime.

# How to build/install antlr-cpp-runtime

antlr4 commit: 70b2edc

Install the dependencies:
```
sudo apt install libssl-dev
sudo apt install uuid
sudo apt install uuid-dev
sudo apt install openjdk-8-jre-headless
```

Get the antlr4:
```
mkdir antlr4
git clone https://github.com/antlr/antlr4.git
mv antlr4 4.9.3-70b2ed
cd 4.9.3-70b2ed
git reset --hard 70b2edcf98eb612a92d3dbaedb2ce0b69533b0cb
```

Prepare the build dir:
```
cd runtime/Cpp
mkdir build-70b2edc
```

Prepare the install dir:
```
cd runtime/Cpp
mkdir install-70b2edc
```

Build antlr-cpp-runtime:
```
cd antlr4

wget https://github.com/antlr/website-antlr4/blob/gh-pages/download/antlr-4.9.3-complete.jar

cmake .. -DANTLR_JAR_LOCATION=/path_to/antlr-4.9.3-complete.jar -DCMAKE_INSTALL_PREFIX=/path_to/antlr4/4.9.3-70b2ed/runtime/Cpp/install-70b2edc -DWITH_DEMO=True

make -j 6

make install
```

# Usage:

In the CMake configuration file, specify:
- Header file directory: `include` subdirectory
- Library search path: `lib` subdirectory