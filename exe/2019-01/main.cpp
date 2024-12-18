#include "lib.h"
#include "read.h"

#include <chrono>
#include <cstdlib>
#include <numeric>
#include <print>
#include <vector>

using Puzzle = std::vector<int>;

Puzzle parse_stdin() {
    Puzzle p;

    for (auto &l : aoc::readlines()) {
        p.emplace_back(std::atoi(l.c_str()));
    }

    return p;
}

int main() {
    auto data = parse_stdin();

    auto start = std::chrono::high_resolution_clock::now();

    auto part1 = std::transform_reduce(data.begin(), data.end(), 0, std::plus{},
                                       [](int mass) { return mass / 3 - 2; });

    auto part2 = std::transform_reduce(data.begin(), data.end(), 0, std::plus{},
                                       [](int mass) {
                                           auto fuel = 0;
                                           auto payload = mass / 3 - 2;

                                           while (payload > 0) {
                                               fuel += payload;
                                               payload = payload / 3 - 2;
                                           }

                                           return fuel;
                                       });

    auto end = std::chrono::high_resolution_clock::now();
    auto dur =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::print("part 1: {}\n", part1);
    std::print("part 2: {}\n", part2);
    std::print("dur:    {}us\n", dur.count());
}
