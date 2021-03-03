#pragma once

#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

struct ConstantToken {
    std::string value;
};

struct ExpressionToken {
    std::string expression;
};

struct SpaceToken {};

struct PipeToken {};

struct NewLineToken {};

using Token = std::variant<ConstantToken, ExpressionToken, SpaceToken, PipeToken, NewLineToken>;