#include <tokenizer/tokenizer.h>

#include <iostream>
#include <sstream>

int main() {
    std::stringstream s("");
    std::cout << std::cin.good() << std::endl
              << std::cin.peek() << std::endl
              << std::cin.good() << std::endl;
    return 0;
}