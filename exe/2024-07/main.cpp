#include "lib.h"
#include "scn/scan.h"

#include <chrono>
#include <iterator>
#include <print>
#include <ranges>
#include <vector>

std::vector<std::pair<long, std::vector<long>>> parse_stdin() {
    std::vector<std::pair<long, std::vector<long>>> puzzle;

    auto lines = aoc::readlines();

    for (auto &line : lines) {
        auto res = scn::scan<long>(line, "{}:");

        auto n = res->value();
        auto remaining = res->range();

        std::vector<long> vs;
        while (auto res = scn::scan<long>(remaining, "{}")) {
            auto v = res->value();
            vs.emplace_back(v);
            remaining = res->range();
        }

        puzzle.emplace_back(n, vs);
    }

    return puzzle;
}

long concatable(long target, long digits) {
    long div = 10;
    while (div < digits) {
        div *= 10;
    }

    return (target % div == digits) ? target / div : 0;
}

template <std::input_iterator iter>
bool is_ok(auto target, iter start, iter end, bool allow_concat) {
    if (start == end) {
        return target == 1;
    }

    auto n = *start;

    if (target % n == 0 && is_ok(target / n, start + 1, end, allow_concat)) {
        return true;
    }

    if (allow_concat) {
        auto v = concatable(target, n);
        if (v > 0 && is_ok(v, start + 1, end, allow_concat)) {
            return true;
        }
    }

    return is_ok(target - n, start + 1, end, allow_concat);
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    auto data = parse_stdin();

    auto part1 = 0l;
    auto part2 = 0l;

    for (auto [n, row] : data) {
        if (is_ok(n, row.rbegin(), row.rend(), false)) {
            part1 += n;
        }
        if (is_ok(n, row.rbegin(), row.rend(), true)) {
            part2 += n;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto dur =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::print("part 1: {} ({})\n", part1, part1 == 3598800864292);
    std::print("part 2: {} ({})\n", part2, part2 == 340362529351427);
    std::print("dur:    {}us\n", dur.count());
}
