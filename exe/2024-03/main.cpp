#include "lib.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <ostream>
#include <print>
#include <scn/scan.h>

std::string parse_stdin() {
    std::ostringstream buffer;
    buffer << std::cin.rdbuf();
    return buffer.str();
}

const std::string_view mult_pattern = "mul(";
const std::string_view do_pattern = "do()";
const std::string_view dont_pattern = "don't()";

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    auto data = parse_stdin();

    auto part1 = 0;
    auto part2 = 0;

    bool enabled = true;
    auto range = scn::ranges::subrange{data};
    auto last = range.begin();

    while (!range.empty()) {
        auto result = scn::scan<int, int>(range, "mul({},{})");

        if (result.has_value()) {
            auto [first, second] = result->values();
            range = result->range();
            auto mul = first * second;

            part1 += mul;
            if (enabled) {
                part2 += mul;
            }
        } else {
            auto pos = std::search(range.begin() + 1, range.end(),
                                   mult_pattern.begin(), mult_pattern.end());

            auto do_pos = std::search(range.begin(), range.end(),
                                      do_pattern.begin(), do_pattern.end());

            auto dont_pos =
                std::search(range.begin(), range.end(), dont_pattern.begin(),
                            dont_pattern.end());

            auto next = range.begin();
            if (dont_pos < pos && dont_pos < do_pos && last != dont_pos) {
                enabled = false;
                next = dont_pos;
            } else if (do_pos < pos && do_pos < dont_pos && last != do_pos) {
                enabled = true;
                next = do_pos;
            } else {
                next = pos;
            }

            last = next;
            range = scn::ranges::subrange{next, range.end()};
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto dur =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::print("part 1: {}\n", part1);
    std::print("part 2: {}\n", part2);
    std::print("dur:    {}us\n", dur.count());
}
