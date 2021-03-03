#include "tokenizer.h"

#include <iostream>
#include <stdexcept>

template <typename UnaryPredicate>
std::string ReadUntil(FILE *in, UnaryPredicate predicate) {
    std::string result;
    int current_char = fgetc(in);
    for (; !predicate(current_char); current_char = getc(in)) {
        if (current_char == EOF) {
            clearerr(in);
        }
        result.push_back(current_char);
    }
    ungetc(current_char, in);
    return result;
}

bool IsSpace(int c) {
    return isspace(c) && c != '\n';
}

Tokenizer::Tokenizer(FILE *in) : in_(in) {
    Next();
}

bool Tokenizer::IsEnd() const {
    return is_end_;
}

void Tokenizer::Next() {
    int current_char = fgetc(in_);
    if (current_char == EOF && std::holds_alternative<NewLineToken>(current_token_)) {
        is_end_ = true;
        return;
    }
    ungetc(current_char, in_);

    if (std::holds_alternative<SpaceToken>(current_token_)) {
        ReadUntil(in_, [](int c) { return c != EOF && !IsSpace(c); });
    }
    ReadUntil(in_, [](int c) { return c != EOF; });

    current_char = fgetc(in_);
    if (IsSpace(current_char)) {
        current_token_ = SpaceToken{};
        return;
    }

    switch (current_char) {
        case '|':
            current_token_ = PipeToken{};
            return;

        case '\n':
            current_token_ = NewLineToken{};
            return;

        case '\'':
            current_token_ = ConstantToken{ReadUntil(in_, [](int c) { return c == '\''; })};
            fgetc(in_);
            return;

        case '"': {
            std::string expression = ReadUntil(in_, [](int c) { return c == '"'; });
            while (expression.back() == '\\') {
                expression.back() = fgetc(in_);
                expression += ReadUntil(in_, [](int c) { return c == '"'; });
            }
            fgetc(in_);
            current_token_ = ExpressionToken{expression};
            return;
        }

        default: {
            auto stop_criterion = [](int c) {
                return c == '\'' || c == '"' || c == '|' || isspace(c);
            };
            ungetc(current_char, in_);
            std::string expression = ReadUntil(in_, stop_criterion);
            while (expression.back() == '\\') {
                expression.back() = fgetc(in_);
                expression += ReadUntil(in_, stop_criterion);
            }
            current_token_ = ExpressionToken{expression};
            return;
        }
    }
}

Token Tokenizer::GetToken() const {
    return current_token_;
}