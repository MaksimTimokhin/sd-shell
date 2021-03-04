#pragma once

#include <parser/parser.h>

class Runner {
public:
    Runner(FILE *in);
    void Go();

private:
    Parser parser_;
};