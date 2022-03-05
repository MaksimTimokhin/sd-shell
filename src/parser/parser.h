#pragma once

#include <command/command_factory.h>
#include <expander/expander.h>
#include <tokenizer/tokenizer.h>

class Parser {
public:
    Parser(FILE *in);
    std::vector<std::shared_ptr<ICommand>> ParseLine();

private:
    bool TryAssignVariable(const std::vector<Token> &line);

private:
    Tokenizer tokenizer_;
    Expander expander_;
};