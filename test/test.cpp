#include <src/test.h>

#include <catch_amalgamated.hpp>

TEST_CASE("simple", "sum") {
    REQUIRE(sum(1, 2) == 3);
}