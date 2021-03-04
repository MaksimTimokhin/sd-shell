#include "runner.h"

#include <unistd.h>
#include <wait.h>

#include <iostream>

Runner::Runner(FILE *in) : parser_(in) {
}

void Runner::Go() {
    for (;;) {
        auto line = parser_.ParseLine();
        if (line.empty()) {
            continue;
        }

        if (line.size() == 1) {
            line[0]->Run();
            continue;
        }

        std::vector<std::vector<int>> pipes(line.size() + 1, std::vector<int>(2));
        pipes[0][0] = 0;
        pipes[line.size()][1] = 1;
        for (size_t i = 1; i < line.size(); ++i) {
            if (pipe(pipes[i].data()) < 0) {
                perror("pipe");
                exit(1);
            }
        }

        std::vector<int> pids(line.size());
        for (size_t i = 0; i < line.size(); ++i) {
            int pid = fork();
            if (pid == 0) {
                dup2(pipes[i][0], 0);
                dup2(pipes[i + 1][1], 1);
                line[i]->Run();
                exit(0);
            } else if (pid > 0) {
                pids[i] = pid;
                if (i != 0) {
                    close(pipes[i][0]);
                }
                if (i != line.size() - 1) {
                    close(pipes[i + 1][1]);
                }
            } else {
                perror("fork");
                exit(1);
            }
        }

        for (int pid : pids) {
            waitpid(pid, 0, 0);
        }
    }
}