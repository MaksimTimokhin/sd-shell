#pragma once

#include <istream>
#include <string>
#include <vector>

#include "command.h"

class WcCommand : public ICommand {
public:
    WcCommand(const std::vector<std::string> &argv);
    void Run() override;

private:
    struct Stat {
        size_t lines;
        size_t words;
        size_t bytes;
    };

private:
    Stat ReadStream(std::istream &in);

private:
    std::vector<std::string> argv_;
};