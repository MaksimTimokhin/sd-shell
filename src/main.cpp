#include <runner/runner.h>

#include <iostream>
int main() {
    Runner runner(stdin);
    runner.Go();
    // Tokenizer tok(stdin);
    // do {
    //     tok.Next();
    //     if (tok.IsEnd()) {
    //         break;
    //     }
    //     auto token = tok.GetToken();
    //     if (std::holds_alternative<SpaceToken>(token)) {
    //         std::cout << "<Space> ";
    //     }
    //     if (std::holds_alternative<NewLineToken>(token)) {
    //         std::cout << "<NewLine>\n";
    //     }
    //     if (std::holds_alternative<PipeToken>(token)) {
    //         std::cout << "<Pipe> ";
    //     }
    //     if (auto constant = std::get_if<ConstantToken>(&token); constant) {
    //         std::cout << "<Constant " << constant->value << "> ";
    //     }
    //     if (auto constant = std::get_if<ExpressionToken>(&token); constant) {
    //         std::cout << "<Expression " << constant->expression << "> ";
    //     }
    // } while (true);
    return 0;
}