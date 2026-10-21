#include <iostream>
#include <cstdint>

int main() {
    __uint128_t x = 1;
    x <<= 100;

    std::cout << "Success! 2^100 was calculated.\n";
    std::cout << "Value: " << (unsigned long long)(x >> 64)
              << " (upper 64 bits)\n";
}
