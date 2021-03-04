#pragma once

#include <string>
#include <vector>

#include "command.h"

class PwdCommand : public ICommand {
public:
    PwdCommand(const std::vector<std::string> &argv);
    void Run() override;
};