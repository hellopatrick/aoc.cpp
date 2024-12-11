#include "lib.h"
#include "scn/scan.h"

#include <chrono>
#include <cstdint>
#include <functional>
#include <numeric>
#include <print>
#include <unordered_map>
#include <vector>

using Puzzle = std::vector<int64_t>;

Puzzle parse_stdin() {
    auto p = aoc::readlines();

    std::vector<int64_t> q;

    auto input = scn::ranges::subrange{p[0]};

    while (auto result = scn::scan<int64_t>(input, "{}")) {
        q.push_back(result->value());
        input = result->range();
    }

    return q;
}

int64_t powi(int64_t i, int64_t e) {
    int64_t res = 1;

    for (int k = 0; k < e; k++) {
        res *= i;
    }

    return res;
}

std::unordered_map<aoc::Coord, int64_t, aoc::CoordHasher> cache;

int64_t solve(int64_t n, int64_t steps) {
    if (cache.contains({n, steps})) {
        return cache[{n, steps}];
    }

    if (steps == 0) {
        cache[{n, steps}] = 1;
        return cache[{n, steps}];
    }

    if (n == 0) {
        cache[{n, steps}] = solve(1, steps - 1);
        return cache[{n, steps}];
    }

    int64_t digits = 1;
    int64_t size = 10;
    while (size <= n) {
        digits++;
        size *= 10;
    }

    if (digits % 2 == 0) {
        digits /= 2;
        size = powi(10, digits);

        cache[{n, steps}] =
            solve(n / size, steps - 1) + solve(n % size, steps - 1);
        return cache[{n, steps}];
    }

    cache[{n, steps}] = solve(n * 2024, steps - 1);

    return cache[{n, steps}];
}

int main() {
    auto data = parse_stdin();

    auto start = std::chrono::high_resolution_clock::now();

    auto part1 =
        std::transform_reduce(data.begin(), data.end(), int64_t(0), std::plus{},
                              [](int64_t n) { return solve(n, 25); });
    auto part2 =
        std::transform_reduce(data.begin(), data.end(), int64_t(0), std::plus{},
                              [](int64_t n) { return solve(n, 75); });

    auto end = std::chrono::high_resolution_clock::now();
    auto dur =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::print("part 1: {}\n", part1);
    std::print("part 2: {}\n", part2);
    std::print("dur:    {}us\n", dur.count());
}
