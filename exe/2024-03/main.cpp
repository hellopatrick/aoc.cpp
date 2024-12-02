#include "lib.h"

#include <chrono>
#include <print>

int parse_stdin() { return 0; }

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    auto data = parse_stdin();

    auto part1 = 0;
    auto part2 = 0;

    auto end = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::print("part 1: {}\n", part1);
    std::print("part 2: {}\n", part2);
    std::print("dur:    {}us\n", dur.count());
}
