#include <runner/runner.h>

#include <iostream>
int main() {
    Runner runner(stdin);
    runner.Go();
    return 0;
}