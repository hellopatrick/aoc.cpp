#include "lib.h"

#include <chrono>
#include <print>
#include <vector>

using puzzle_t = std::vector<int>;

puzzle_t parse_stdin() {
    puzzle_t puzzle;

    return puzzle;
}

int main() {
    auto data = parse_stdin();

    auto start = std::chrono::high_resolution_clock::now();

    auto part1 = 0;
    auto part2 = 0;

    auto end = std::chrono::high_resolution_clock::now();
    auto dur =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::print("part 1: {}\n", part1);
    std::print("part 2: {}\n", part2);
    std::print("dur:    {}us\n", dur.count());
}
