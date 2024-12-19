#include "intcode.h"
#include "split.h"
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <print>
#include <string>

aoc::vm parse_stdin() {
    std::string line;
    std::getline(std::cin, line);

    auto prog = aoc::split(line, ",");

    std::vector<int> data;

    std::transform(prog.begin(), prog.end(), std::back_inserter(data),
                   [](std::string c) { return std::atoi(c.c_str()); });

    return aoc::vm(data);
}

int main() {
    auto vm = parse_stdin();

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
