#include "echo_command.h"

#include <iostream>

EchoCommand::EchoCommand(const std::vector<std::string> &argv) : argv_(argv) {
}

void EchoCommand::Run() {
    for (size_t i = 1; i < argv_.size(); ++i) {
        std::cout << argv_[i];
        if (i + 1 != argv_.size()) {
            std::cout << ' ';
        }
    }
    std::cout << std::endl;
}