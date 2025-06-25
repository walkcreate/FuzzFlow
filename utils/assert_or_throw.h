#ifndef FUZZFLOW_ASSERT_OR_THROW_H
#define FUZZFLOW_ASSERT_OR_THROW_H

#include <iostream>
#include <cassert>
#include <string>

#include "../exceptions/JS2GraphError.h"
#include "../exceptions/LiftError.h"
#include "../exceptions/MutateError.h"

using std::string;

namespace FuzzFlow {

void dbg_assert_or_release_throw(bool expect_true, const string& msg);

void assert_or_throw_js2graph(bool expr, const std::string_view& msg);

void assert_or_throw_graph2js(bool expr, const string& msg);

void assert_or_throw_mutate(bool expr, const string& msg);

} /// end of namespace FuzzFlow

#endif //FUZZFLOW_ASSERT_OR_THROW_H
