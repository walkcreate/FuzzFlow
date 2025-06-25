#ifndef FUZZFLOW_COMMON_USING_H
#define FUZZFLOW_COMMON_USING_H

#include <optional>
using std::optional;

#include <string>
using std::string;

#include <string_view>
using std::string_view;

#include <format>

#include <iostream>
using std::cout;
using std::cin;
using std::cerr;
using std::ifstream;
using std::ofstream;

#include <filesystem>
/// Namespace aliases: Namespace aliases allow the programmer to define an alternate name for a namespace.
/// namespace-alias-definition: makes name a synonym for another namespace: see namespace alias
namespace fs = std::filesystem;

#include <memory>
using std::shared_ptr;
using std::unique_ptr;
using std::weak_ptr;
using std::static_pointer_cast;
using std::dynamic_pointer_cast;
using std::make_shared;
using std::make_unique;
using std::enable_shared_from_this;

#include <vector>
#include <set>
#include <map>
#include <stack>
using std::vector;
using std::set;
using std::map;
using std::stack;

#include <unordered_map>
using std::unordered_map;

#include <unordered_set>
using std::unordered_set;

#include <utility>
using std::pair;
using std::make_pair;

#include <tuple>
using std::tuple;

#include <deque>
using std::deque;

/// for assert
#include <cassert>

#include <cstdint>

#include <algorithm>

#endif //FUZZFLOW_COMMON_USING_H
