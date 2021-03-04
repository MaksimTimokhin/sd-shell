#pragma once

#include <string>
#include <vector>

#include "command.h"

class ExitCommand : public ICommand {
public:
    ExitCommand(const std::vector<std::string> &argv);
    void Run() override;

private:
    std::vector<std::string> argv_;
};