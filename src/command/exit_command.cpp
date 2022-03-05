#include "exit_command.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>

ExitCommand::ExitCommand(const std::vector<std::string> &argv) : argv_(argv) {
}

void ExitCommand::Run() {
    int code = 0;
    if (argv_.size() > 2) {
        std::cerr << argv_[0] << ": too many arguments" << std::endl;
    } else if (argv_.size() > 1) {
        if (std::find_if_not(argv_[1].begin(), argv_[1].end(), isdigit) != argv_[1].end()) {
            std::cerr << argv_[0] << ": " << argv_[1] << ": numeric argument required" << std::endl;
        } else {
            code = std::atoi(argv_[1].data());
        }
    }
    std::cout << "exit" << std::endl;
    exit(code);
}