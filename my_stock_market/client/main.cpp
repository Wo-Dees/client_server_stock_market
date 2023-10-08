#include <assistant.hpp>
#include <iostream>

int main() {
    Assistant assistant(std::cout, std::cin, {"127.0.0.1", 5555});
    return assistant.Run();
}