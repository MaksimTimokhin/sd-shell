#include "pwd_command.h"

#include <limits.h>
#include <unistd.h>

#include <iostream>

PwdCommand::PwdCommand(const std::vector<std::string> &argv){};

void PwdCommand::Run() {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd))) {
        std::cout << cwd << std::endl;
    } else {
        perror("getcwd");
    }
}