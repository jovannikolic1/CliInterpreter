#include <iostream>

#include "core/Interpreter.h"

int main() {
    std::ios::sync_with_stdio(false);
    cli::Interpreter interpreter(std::cin, std::cout, std::cerr);
    interpreter.run();
    return 0;
}
