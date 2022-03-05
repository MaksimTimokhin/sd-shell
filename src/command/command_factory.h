#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "cat_command.h"
#include "echo_command.h"
#include "exit_command.h"
#include "external_command.h"
#include "pwd_command.h"
#include "wc_command.h"

class CommandFactory {
public:
    static std::shared_ptr<ICommand> CreateCommand(const std::vector<std::string> &argv);
};