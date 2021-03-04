#include <tokenizer/tokenizer.h>

#include <catch_amalgamated.hpp>

TEST_CASE("Unquoted", "Tokenizer") {
    std::string s = "abc a b d\n";
    Tokenizer tok(fmemopen(s.data(), s.size(), "r"));

    tok.Next();
    REQUIRE(std::get<ExpressionToken>(tok.GetToken()).expression == "abc");
    REQUIRE(!tok.IsEnd());
    tok.Next();
    REQUIRE(std::holds_alternative<SpaceToken>(tok.GetToken()));
    tok.Next();
    REQUIRE(!tok.IsEnd());
    REQUIRE(std::get<ExpressionToken>(tok.GetToken()).expression == "a");
    REQUIRE(!tok.IsEnd());
    tok.Next();
    REQUIRE(std::holds_alternative<SpaceToken>(tok.GetToken()));
    tok.Next();
    REQUIRE(!tok.IsEnd());
    REQUIRE(std::get<ExpressionToken>(tok.GetToken()).expression == "b");
    REQUIRE(!tok.IsEnd());
    tok.Next();
    REQUIRE(std::holds_alternative<SpaceToken>(tok.GetToken()));
    tok.Next();
    REQUIRE(!tok.IsEnd());
    REQUIRE(std::get<ExpressionToken>(tok.GetToken()).expression == "d");
    REQUIRE(!tok.IsEnd());
    tok.Next();
    REQUIRE(std::holds_alternative<NewLineToken>(tok.GetToken()));
    REQUIRE(!tok.IsEnd());
    tok.Next();
    REQUIRE(tok.IsEnd());
}

TEST_CASE("Quotes", "Tokenizer") {
    std::string s = "x\"abc\"y\nc'a'b\n";
    Tokenizer tok(fmemopen(s.data(), s.size(), "r"));

    tok.Next();
    REQUIRE(std::get<ExpressionToken>(tok.GetToken()).expression == "x");
    tok.Next();
    REQUIRE(std::get<ExpressionToken>(tok.GetToken()).expression == "abc");
    tok.Next();
    REQUIRE(std::get<ExpressionToken>(tok.GetToken()).expression == "y");
    tok.Next();
    REQUIRE(std::holds_alternative<NewLineToken>(tok.GetToken()));
    tok.Next();
    REQUIRE(std::get<ExpressionToken>(tok.GetToken()).expression == "c");
    tok.Next();
    REQUIRE(std::get<ConstantToken>(tok.GetToken()).value == "a");
    tok.Next();
    REQUIRE(std::get<ExpressionToken>(tok.GetToken()).expression == "b");
    tok.Next();
    REQUIRE(std::holds_alternative<NewLineToken>(tok.GetToken()));
    tok.Next();
    REQUIRE(tok.IsEnd());
}

TEST_CASE("Escape", "Tokenizer") {
    std::string s = "\"\\\"\"\\ '\\'\n";
    Tokenizer tok(fmemopen(s.data(), s.size(), "r"));
    tok.Next();
    REQUIRE(std::get<ExpressionToken>(tok.GetToken()).expression == "\"");
    tok.Next();
    REQUIRE(std::get<ExpressionToken>(tok.GetToken()).expression == " ");
    tok.Next();
    REQUIRE(std::get<ConstantToken>(tok.GetToken()).value == "\\");
    tok.Next();
    REQUIRE(std::holds_alternative<NewLineToken>(tok.GetToken()));
    tok.Next();
    REQUIRE(tok.IsEnd());
}

TEST_CASE("Space", "Tokenizer") {
    std::string s = "x   y \t z\t \n";
    Tokenizer tok(fmemopen(s.data(), s.size(), "r"));

    tok.Next();
    REQUIRE(std::get<ExpressionToken>(tok.GetToken()).expression == "x");
    tok.Next();
    REQUIRE(std::holds_alternative<SpaceToken>(tok.GetToken()));
    tok.Next();
    REQUIRE(std::get<ExpressionToken>(tok.GetToken()).expression == "y");
    tok.Next();
    REQUIRE(std::holds_alternative<SpaceToken>(tok.GetToken()));
    tok.Next();
    REQUIRE(std::get<ExpressionToken>(tok.GetToken()).expression == "z");
    tok.Next();
    REQUIRE(std::holds_alternative<SpaceToken>(tok.GetToken()));
    tok.Next();
    REQUIRE(std::holds_alternative<NewLineToken>(tok.GetToken()));
    tok.Next();
    REQUIRE(tok.IsEnd());
}

TEST_CASE("Pipes", "Tokenizer") {
    std::string s = "x| y |z | u\n";
    Tokenizer tok(fmemopen(s.data(), s.size(), "r"));

    tok.Next();
    REQUIRE(std::get<ExpressionToken>(tok.GetToken()).expression == "x");
    tok.Next();
    REQUIRE(std::holds_alternative<PipeToken>(tok.GetToken()));
    tok.Next();
    REQUIRE(std::holds_alternative<SpaceToken>(tok.GetToken()));
    tok.Next();
    REQUIRE(std::get<ExpressionToken>(tok.GetToken()).expression == "y");
    tok.Next();
    REQUIRE(std::holds_alternative<SpaceToken>(tok.GetToken()));
    tok.Next();
    REQUIRE(std::holds_alternative<PipeToken>(tok.GetToken()));
    tok.Next();
    REQUIRE(std::get<ExpressionToken>(tok.GetToken()).expression == "z");
    tok.Next();
    REQUIRE(std::holds_alternative<SpaceToken>(tok.GetToken()));
    tok.Next();
    REQUIRE(std::holds_alternative<PipeToken>(tok.GetToken()));
    tok.Next();
    REQUIRE(std::holds_alternative<SpaceToken>(tok.GetToken()));
    tok.Next();
    REQUIRE(std::get<ExpressionToken>(tok.GetToken()).expression == "u");
    tok.Next();
    REQUIRE(std::holds_alternative<NewLineToken>(tok.GetToken()));
    tok.Next();
    REQUIRE(tok.IsEnd());
}