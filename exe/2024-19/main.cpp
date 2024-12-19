#include "read.h"
#include <chrono>
#include <functional>
#include <numeric>
#include <print>
#include <unordered_map>
#include <vector>

using Puzzle = std::pair<std::vector<std::string>, std::vector<std::string>>;

Puzzle parse_stdin() {
    Puzzle p;

    auto lines = aoc::readlines();

    auto towels = aoc::split(lines[0], ", ");
    auto patterns = std::vector<std::string>(lines.begin() + 2, lines.end());

    return {towels, patterns};
}

auto cache = std::unordered_map<std::string_view, int64_t>();

int64_t combinations(const std::string_view &pattern,
                     const std::vector<std::string> &towels) {
    if (pattern.size() == 0) {
        return 1;
    }

    if (auto a = cache.find(pattern); a != cache.end()) {
        return a->second;
    }

    int64_t total = 0;

    for (auto &towel : towels) {
        total += pattern.starts_with(towel)
                     ? combinations(pattern.substr(towel.size()), towels)
                     : 0;
    }

    return cache[pattern] = total;
}

int main() {
    auto [towels, patterns] = parse_stdin();

    auto start = std::chrono::high_resolution_clock::now();

    int64_t part1 = std::transform_reduce(
        patterns.begin(), patterns.end(), 0L, std::plus{},
        [&](std::string &a) { return combinations(a, towels) > 0 ? 1 : 0; });

    int64_t part2 = std::transform_reduce(
        patterns.begin(), patterns.end(), 0L, std::plus{},
        [&](std::string &a) { return combinations(a, towels); });

    auto end = std::chrono::high_resolution_clock::now();
    auto dur =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::print("part 1: {}\n", part1);
    std::print("part 2: {}\n", part2);
    std::print("dur:    {}us\n", dur.count());
}
