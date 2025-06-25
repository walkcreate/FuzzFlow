#include "./assert_or_throw.h"

namespace FuzzFlow {

void dbg_assert_or_release_throw(bool expect_true, const string& msg)
{
    if (!expect_true) {
        std::cerr << "Assertion error: " << msg << std::endl;
    }

    /// crashes in debug mode
    assert(expect_true);

    /// throw the exception in release mode
    if (!expect_true) {
        throw std::runtime_error(msg);
    }
}

void assert_or_throw_js2graph(bool expect_true, const std::string_view& msg)
{
    if (!expect_true) {
        std::cerr << "Assertion error: " << msg << std::endl;
    }

    /// crashes in debug mode
    assert(expect_true);

    /// throw the exception in release mode
    if (! expect_true) {
        throw JS2GraphError(std::string(msg));
    }
}

void assert_or_throw_graph2js(bool expect_true, const string& msg)
{
    if (!expect_true) {
        std::cerr << "Assertion error: " << msg << std::endl;
    }

    assert(expect_true);

    if (!expect_true) {
        throw LiftError(msg);
    }
}

void assert_or_throw_mutate(bool expect_true, const string& msg)
{
    if (!expect_true) {
        std::cerr << "Assertion error: " << msg << std::endl;
    }

    assert(expect_true);

    if (!expect_true) {
        throw MutateError(msg);
    }
}

} /// end of namespace FuzzFlow