#pragma once

#include <cstdio>

#include "token.h"

class Tokenizer {
public:
    Tokenizer(FILE *in);
    bool IsEnd() const;
    void Next();
    Token GetToken() const;

private:
    FILE *in_;
    Token current_token_ = NewLineToken{};
    bool is_end_ = false;
};