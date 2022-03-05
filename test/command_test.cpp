#include <command/command_factory.h>
#include <unistd.h>
#include <wait.h>

#include <catch_amalgamated.hpp>
#include <iostream>

std::pair<int, std::string> RunCommand(ICommand *command, bool err) {
    int out_pipe[2];
    int err_pipe[2];
    pipe(out_pipe);
    pipe(err_pipe);
    int pid = fork();
    if (pid == 0) {
        dup2(out_pipe[1], 1);
        dup2(err_pipe[1], 2);
        command->Run();
        exit(0);
    } else {
        int status;
        waitpid(pid, &status, 0);
        char buf[1024];
        size_t size = read(err ? err_pipe[0] : out_pipe[0], buf, 1024);
        close(out_pipe[1]);
        close(err_pipe[1]);
        close(err_pipe[0]);
        close(out_pipe[0]);
        return std::make_pair(WEXITSTATUS(status), std::string(buf, size));
    }
    return std::make_pair(0, "");
}

TEST_CASE("External", "Command") {
    std::vector<std::string> argv{"echo", "abc", "kek"};
    auto comm = CommandFactory::CreateCommand(argv);
    REQUIRE(RunCommand(comm.get(), false).second == "abc kek\n");

    argv = {"kek"};
    comm = comm = CommandFactory::CreateCommand(argv);
    REQUIRE(RunCommand(comm.get(), true).second == "command not found: kek\n");
}

TEST_CASE("Exit", "Command") {
    std::vector<std::string> argv{"exit", "1", "2"};
    auto comm = CommandFactory::CreateCommand(argv);
    REQUIRE(RunCommand(comm.get(), true).second == "exit: too many arguments\n");

    argv = {"exit", "3s"};
    comm = CommandFactory::CreateCommand(argv);
    REQUIRE(RunCommand(comm.get(), true).second == "exit: 3s: numeric argument required\n");

    argv = {"exit", "3"};
    comm = CommandFactory::CreateCommand(argv);
    REQUIRE(RunCommand(comm.get(), false).first == 3);
}

TEST_CASE("Echo", "Command") {
    std::vector<std::string> argv{"echo", "a", "b", "x\ny"};
    auto comm = CommandFactory::CreateCommand(argv);
    REQUIRE(RunCommand(comm.get(), false).second == "a b x\ny\n");
}

TEST_CASE("Pwd", "Command") {
    std::vector<std::string> argv{"pwd"};
    auto comm = CommandFactory::CreateCommand(argv);
    std::cout << RunCommand(comm.get(), false).second << std::endl;
}

TEST_CASE("Cat", "Command") {
    std::vector<std::string> argv{"cat", "../test/test_file"};
    auto comm = CommandFactory::CreateCommand(argv);
    REQUIRE(RunCommand(comm.get(), false).second == "abc\n\ndef \nxxxxx");
}

TEST_CASE("Wc", "Command") {
    std::vector<std::string> argv{"wc", "../test/test_file", "../test/test_file"};
    auto comm = CommandFactory::CreateCommand(argv);
    REQUIRE(RunCommand(comm.get(), false).second ==
            "3\t3\t15\t../test/test_file\n3\t3\t15\t../test/test_file\n6\t6\t30\ttotal\n");
}