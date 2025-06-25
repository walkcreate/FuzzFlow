#ifndef FUZZFLOW_JSENVIRONMENT_H
#define FUZZFLOW_JSENVIRONMENT_H

#include <limits>
#include <climits>

#include "../../utils/common_using.h"

#include "BuiltInObject.h"

namespace FuzzFlow {

class JSEnvironment {
public:
    JSEnvironment()
    {
        init_built_in_objects();
    }

    ~JSEnvironment() = default;

    set<int64_t> interesting_integers {
        LLONG_MIN,                                                // -9223372036854775808
        -9223372036854775807,                                     // LLONG_MIN + 1. The most negative signed integer literal that can be safely written directly in C++
        -9007199254740992, -9007199254740991, -9007199254740990,  // Smallest integer value that is still precisely representable by a double
        -4294967297, -4294967296, -4294967295,                    // Negative Uint32 max
        -2147483649, -2147483648, -2147483647,                    // Int32 min
        -1073741824, -536870912, -268435456,                      // -2**32 / {4, 8, 16}
        -65537, -65536, -65535,                                   // -2**16
        -4096, -1024, -256, -128,                                 // Other powers of two
        -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 16, 64,         // Numbers around 0
        127, 128, 129,                                            // 2**7
        255, 256, 257,                                            // 2**8
        512, 1000, 1024, 4096, 10000,                             // Misc numbers
        65535, 65536, 65537,                                      // 2**16
        268435439, 268435440, 268435441,                          // V8 String kMaxLength (32-bit)
        536870887, 536870888, 536870889,                          // V8 String kMaxLength (64-bit)
        268435456, 536870912, 1073741824,                         // 2**32 / {4, 8, 16}
        1073741823, 1073741824, 1073741825,                       // 2**30
        2147483647, 2147483648, 2147483649,                       // Int32 max
        4294967295, 4294967296, 4294967297,                       // Uint32 max
        9007199254740990, 9007199254740991, 9007199254740992,     // Biggest integer value that is still precisely representable by a double
        9223372036854775807,
    };

    set<double> interesting_floats {
        -std::numeric_limits<double>::infinity(),
        -std::numeric_limits<double>::max(),
        -1e-15, -1e12, -1e9, -1e6, -1e3, -5.0, -4.0, -3.0, -2.0, -1.0,
        -std::numeric_limits<double>::epsilon(),
        -std::numeric_limits<double>::min(),
        -0.0, 0.0,
        std::numeric_limits<double>::min(),
        std::numeric_limits<double>::epsilon(),
        1.0, 2.0, 3.0, 4.0, 5.0, 1e3, 1e6, 1e9, 1e12, 1e-15,
        std::numeric_limits<double>::max(),
        std::numeric_limits<double>::infinity(),
        std::numeric_limits<double>::quiet_NaN(),
    };

    set<string> interesting_strings {};

    set<string> interesting_regExps {};

    vector<BuiltInObject> built_in_objects;

    void init_built_in_objects();
};

}

#endif //FUZZFLOW_JSENVIRONMENT_H
