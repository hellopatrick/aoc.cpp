#include "lib.h"

#include <chrono>

int parse_stdin() { return 0; }

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    auto data = parse_stdin();

    auto part1 = 0;
    auto part2 = 0;

    auto end = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::printf("part 1: %d\n", part1);
    std::printf("part 2: %d\n", part2);
    std::printf("dur:    %lldus\n", dur.count());
}
