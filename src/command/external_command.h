#pragma once

#include <string>
#include <vector>

#include "command.h"
class ExternalCommand : public ICommand {
public:
    ExternalCommand(const std::vector<std::string> &args);
    void Run() override;

private:
    std::vector<std::string> args_;
    std::vector<char *> argv_;
};