#include <expander/expander.h>

#include <catch_amalgamated.hpp>

TEST_CASE("No vars", "Expander") {
    Expander exp;
    REQUIRE(exp.ExpandExpression("") == "");
    REQUIRE(exp.ExpandExpression("abc") == "abc");
    REQUIRE(exp.ExpandExpression("a$'") == "a$'");
    REQUIRE(exp.ExpandExpression("a$") == "a$");
}

TEST_CASE("Expand vars", "Expander") {
    Expander exp;
    exp.SetVariable(Expander::VariableAssignment{"a", "bcd"});
    exp.SetVariable(Expander::VariableAssignment{"1", "acd"});
    REQUIRE(exp.ExpandExpression("$a") == "bcd");
    REQUIRE(exp.ExpandExpression("ab$a$1x$c") == "abbcdacdx");
}

TEST_CASE("Parse assignment", "Expander") {
    Expander exp;
    exp.SetVariable(Expander::VariableAssignment{"0", "bcd"});
    auto res = exp.ParseVariableAssignment("a1=bcd");
    REQUIRE(res->name == "a1");
    REQUIRE(res->value == "bcd");
    res = exp.ParseVariableAssignment("a=xdc'$0d'tu");
    REQUIRE(res->name == "a");
    REQUIRE(res->value == "xdc'bcdd'tu");
}

TEST_CASE("Bad assignment", "Expander") {
    Expander exp;
    REQUIRE(!exp.ParseVariableAssignment("a'$5qsf"));
    REQUIRE(!exp.ParseVariableAssignment("a'=5"));
    REQUIRE(!exp.ParseVariableAssignment("5a=6"));
}