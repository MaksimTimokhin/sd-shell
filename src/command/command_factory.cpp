#include "command_factory.h"

std::shared_ptr<ICommand> CommandFactory::CreateCommand(const std::vector<std::string> &argv) {
    if (argv.empty()) {
        throw std::runtime_error("empty argv");
    }
    if (argv[0] == "echo") {
        return std::make_shared<EchoCommand>(argv);
    }
    if (argv[0] == "exit") {
        return std::make_shared<ExitCommand>(argv);
    }
    if (argv[0] == "pwd") {
        return std::make_shared<PwdCommand>(argv);
    }
    if (argv[0] == "cat") {
        return std::make_shared<CatCommand>(argv);
    }
    if (argv[0] == "wc") {
        return std::make_shared<WcCommand>(argv);
    }
    return std::make_shared<ExternalCommand>(argv);
}