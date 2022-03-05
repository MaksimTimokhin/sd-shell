#include "cat_command.h"

#include <fstream>
#include <iostream>

CatCommand::CatCommand(const std::vector<std::string> &argv) : argv_(argv) {
}

void CatCommand::Run() {
    if (argv_.size() == 1) {
        ReadStream(std::cin);
        return;
    }
    for (size_t i = 1; i < argv_.size(); ++i) {
        std::ifstream file(argv_[i]);
        if (!file.is_open()) {
            std::cerr << argv_[0] << ": couldn't open file: " << argv_[i] << std::endl;
            continue;
        }
        ReadStream(file);
    }
}

void CatCommand::ReadStream(std::istream &in) {
    int c = in.get();
    while (c != EOF) {
        std::cout << char(c);
        c = in.get();
    }
}