#ifndef FUZZFLOW_UTIL_TIME_H
#define FUZZFLOW_UTIL_TIME_H

#include <iostream>
#include <memory>
#include <string>
#include <chrono>
#include <iomanip>

using std::cout;
using std::shared_ptr;
using std::string;

string format_date();

string format_seconds_duration(long seconds);

#endif //FUZZFLOW_UTIL_TIME_H
