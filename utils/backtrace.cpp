#include "backtrace.h"

/// Add the following line will lead to compilation error.
//#define BOOST_STACKTRACE_LINK

#define BOOST_STACKTRACE_USE_BACKTRACE
#include <boost/stacktrace.hpp>

#include <signal.h>
#include <stdlib.h>
#include <iostream>

namespace FuzzFlow {

void signalHandler(int signal)
{
    std::cerr << "Error: signal " << signal << " caught.\n";
    std::cerr << boost::stacktrace::stacktrace();
    exit(1);
}

void registerStackTrace()
{
    signal(SIGSEGV, signalHandler);
    signal(SIGABRT, signalHandler);
}

} /// end of namespace