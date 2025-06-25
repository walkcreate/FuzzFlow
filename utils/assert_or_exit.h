#ifndef FUZZFLOW_REPORT_ERROR_H
#define FUZZFLOW_REPORT_ERROR_H

#include <string>
#include <iostream>

using std::string;
using std::cerr;

#define ASSERT_OR_EXIT(cond) \
    assert_or_exit((cond), __FILE__, __LINE__)

void assert_or_exit(bool condition,
                    const char* file,
                    int line);

#endif //FUZZFLOW_REPORT_ERROR_H
