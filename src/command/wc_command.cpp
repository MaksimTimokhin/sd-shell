#include "wc_command.h"

#include <fstream>
#include <iostream>

WcCommand::WcCommand(const std::vector<std::string> &argv) : argv_(argv) {
}

void WcCommand::Run() {
    if (argv_.size() == 1) {
        auto stat = ReadStream(std::cin);
        std::cout << stat.lines << '\t' << stat.words << '\t' << stat.bytes << std::endl;
        return;
    }

    size_t total_lines = 0, total_words = 0, total_bytes = 0;
    for (size_t i = 1; i < argv_.size(); ++i) {
        std::ifstream file(argv_[i]);
        if (!file.is_open()) {
            std::cerr << argv_[0] << ": couldn't open file: " << argv_[i] << std::endl;
            continue;
        }
        auto stat = ReadStream(file);
        std::cout << stat.lines << '\t' << stat.words << '\t' << stat.bytes << '\t' << argv_[i]
                  << std::endl;
        total_lines += stat.lines;
        total_words += stat.words;
        total_bytes += stat.bytes;
    }
    std::cout << total_lines << '\t' << total_words << '\t' << total_bytes << "\ttotal"
              << std::endl;
}

WcCommand::Stat WcCommand::ReadStream(std::istream &in) {
    Stat result{0, 0, 0};
    int prev_char = ' ';
    for (int curr_char = in.get(); curr_char != EOF; curr_char = in.get()) {
        ++result.bytes;
        if (isspace(curr_char) && !isspace(prev_char)) {
            ++result.words;
        }
        if (curr_char == '\n') {
            ++result.lines;
        }
        prev_char = curr_char;
    }
    if (!isspace(prev_char)) {
        ++result.words;
    }
    return result;
}