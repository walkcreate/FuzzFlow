#include "util_rand.h"

namespace FuzzFlow {

/**
 * Produces random floating-point values x, uniformly distributed on the interval [a, b)
 */
double random_between_real(const double lower,
                           const double upper)
{
    assert("The upper should be greater than lower"
           && (upper > lower));

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(lower, upper);

    double random_real = dist(mt);
    return random_real;
}

/// Both upper and lower bounds are closed intervals
unsigned int random_between_integer(const unsigned int lower,
                                    const unsigned int upper)
{
    assert("The upper should be greater than 1"
           && (upper >= 1));

    /// Produces random integer values i, uniformly distributed on the closed interval [a, b]
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(lower, upper);

    const unsigned int random_index = dist(mt);
    return random_index;
}

bool probability(const double prob)
{
    assert(prob >= 0 && prob <= 1.0);
    return prob == 1.0 || random_between_real(0.0, 1.0) < prob;
}

unsigned int random_container_index(const unsigned int upper)
{
    if (upper == 1) {
        return 0u;
    }
    return random_between_integer(0, upper-1);
}

} /// end of namespace