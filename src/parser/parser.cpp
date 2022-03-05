#include "parser.h"

#include <iostream>

Parser::Parser(FILE *in) : tokenizer_(in) {
}

std::vector<std::shared_ptr<ICommand>> Parser::ParseLine() {
    std::vector<Token> line;
    do {
        std::cout << "$ " << std::flush;
        line.clear();
        tokenizer_.Next();
        if (tokenizer_.IsEnd()) {
            return {CommandFactory::CreateCommand({"exit"})};
        }

        for (;; tokenizer_.Next()) {
            auto token = tokenizer_.GetToken();
            if (std::holds_alternative<NewLineToken>(token)) {
                break;
            }
            line.push_back(token);
        }
    } while (TryAssignVariable(line));

    bool has_non_empty_expr = false;
    std::string current_value;
    std::vector<std::string> argv;
    std::vector<std::shared_ptr<ICommand>> pipe;
    for (const auto &token : line) {
        if (std::holds_alternative<SpaceToken>(token)) {
            if (current_value.empty()) {
                continue;
            }
            if (!argv.empty() || !expander_.ParseVariableAssignment(current_value)) {
                argv.push_back(current_value);
            }
            current_value.clear();
            continue;
        }
        if (std::holds_alternative<PipeToken>(token)) {
            if (!has_non_empty_expr) {
                std::cout << "bad pipe" << std::endl;
                return {};
            }
            if (!argv.empty()) {
                pipe.push_back(CommandFactory::CreateCommand(argv));
                argv.clear();
            }
            has_non_empty_expr = false;
            continue;
        }
        if (auto constant = std::get_if<ConstantToken>(&token); constant) {
            current_value += constant->value;
        }
        if (auto expr = std::get_if<ExpressionToken>(&token); expr) {
            current_value += expander_.ExpandExpression(expr->expression);
        }
        if (!current_value.empty()) {
            has_non_empty_expr = true;
        }
    }
    if (!current_value.empty() &&
        (!argv.empty() || !expander_.ParseVariableAssignment(current_value))) {
        argv.push_back(current_value);
    }
    if (!argv.empty()) {
        pipe.push_back(CommandFactory::CreateCommand(argv));
    }

    return pipe;
}

bool Parser::TryAssignVariable(const std::vector<Token> &line) {
    bool ready = false;
    std::string current_value;
    for (const auto &token : line) {
        if (std::holds_alternative<SpaceToken>(token)) {
            if (!current_value.empty()) {
                ready = true;
            }
            continue;
        }
        if (ready || std::holds_alternative<PipeToken>(token)) {
            return false;
        }
        if (auto constant = std::get_if<ConstantToken>(&token); constant) {
            if (!current_value.empty() || expander_.ParseVariableAssignment(constant->value)) {
                current_value += constant->value;
            } else {
                return false;
            }
        }
        if (auto expr = std::get_if<ExpressionToken>(&token); expr) {
            if (!current_value.empty() || expander_.ParseVariableAssignment(expr->expression)) {
                current_value += expander_.ExpandExpression(expr->expression);
            } else {
                return false;
            }
        }
    }
    auto assignment = expander_.ParseVariableAssignment(current_value);
    if (!assignment) {
        return false;
    }
    expander_.SetVariable(*assignment);
    return true;
}