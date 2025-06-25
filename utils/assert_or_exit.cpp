#include "assert_or_exit.h"

void assert_or_exit(const bool condition,
                    const char* file,
                    const int line)
{
    if (!condition) {
        cerr << "[Check Failed] \n"
             << "File: " << file << ", Line: " << line << "\n";

        std::exit(EXIT_FAILURE);
    }
}