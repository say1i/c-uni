#include <iostream>

int value = 100;

int main() {
    int value = 10;
    std::cout << "local value: " << value << std::endl;
    std::cout << "global value: " << ::value << std::endl;
    return 0;
}
