#include "external_command.h"

#include <unistd.h>
#include <wait.h>

#include <iostream>

ExternalCommand::ExternalCommand(const std::vector<std::string> &args)
    : args_(args), argv_(args.size() + 1) {
    for (size_t i = 0; i < args.size(); ++i) {
        argv_[i] = args_[i].data();
    }
    argv_[args.size()] = nullptr;
}

void ExternalCommand::Run() {
    int pid = fork();
    if (pid == 0) {
        if (execvp(argv_[0], argv_.data()) < 0) {
            std::cerr << "command not found: " << argv_[0] << std::endl;
        }
    } else if (pid > 0) {
        waitpid(pid, 0, 0);
    } else {
        perror("fork");
    }
}