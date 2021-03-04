#pragma once

#include <istream>
#include <string>
#include <vector>

#include "command.h"

class CatCommand : public ICommand {
public:
    CatCommand(const std::vector<std::string> &argv);
    void Run() override;

private:
    void ReadStream(std::istream &in);

private:
    std::vector<std::string> argv_;
};