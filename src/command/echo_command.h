#pragma once

#include <string>
#include <vector>

#include "command.h"

class EchoCommand : public ICommand {
public:
    EchoCommand(const std::vector<std::string> &argv);
    void Run() override;

private:
    std::vector<std::string> argv_;
};