#include "lib.h"

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <ostream>
#include <print>
#include <utility>
#include <vector>

using Block = std::tuple<int64_t, int64_t, int64_t>;
using Puzzle = std::vector<Block>;

Puzzle parse_stdin() {
    Puzzle p;

    auto lines = aoc::readlines();
    auto line = lines[0];

    int64_t i = 0;
    int64_t offset = 0;
    for (auto const c : line) {
        int64_t size = c - '0';

        auto id = (i % 2 == 0) ? i / 2 : -1;

        p.emplace_back(id, offset, size);

        offset += size;
        i++;
    }

    return p;
}

auto part1(Puzzle &p) -> int64_t {
    int64_t total_size = 0;
    for (auto [_id, _offset, size] : p) {
        total_size += size;
    }

    std::vector<int64_t> disk(total_size);

    for (auto [id, offset, size] : p) {
        for (int64_t j = 0; j < size; j++) {
            disk[offset + j] = id;
        }
    }

    auto forward = disk.begin();
    auto backward = disk.rbegin();

    while (true) {
        while (backward != disk.rend() && *backward == -1) {
            backward++;
        }

        if (backward == disk.rend()) {
            break;
        }

        while (forward != disk.end() && *forward != -1) {
            forward++;
        }

        if (forward == disk.end()) {
            break;
        }

        if (forward < backward.base()) {
            std::swap(*forward, *backward);
        } else {
            break;
        }
    }

    int64_t sum = 0;
    for (int64_t i = 0; i < disk.size(); i++) {
        auto id = disk[i];
        if (id == -1) {
            continue;
        }

        sum += (id * i);
    }

    return sum;
}

auto part2(Puzzle &p) -> int64_t {
    int64_t total_size = 0;
    for (auto [_id, _offset, size] : p) {
        total_size += size;
    }

    std::vector<int64_t> disk(total_size);

    for (auto [id, offset, size] : p) {
        for (int64_t j = 0; j < size; j++) {
            disk[offset + j] = id;
        }
    }

    auto file = p.rbegin();
    while (file != p.rend()) {

        auto [id, offset, size] = *file;
        file++;

        if (id == -1) {
            continue;
        }

        auto i = 0;
    loop:
        while (i < disk.size() && i < offset) {
            if (disk[i] != -1) {
                i++;
                continue;
            }

            for (auto j = 0; j < size; j++) {
                if (disk[i + j] != -1) {
                    i += (j + 1);
                    goto loop;
                }
            }

            for (auto k = 0; k < size; k++) {
                disk[i + k] = disk[offset + k];
                disk[offset + k] = -1;
            }

            break;
        }
    }

    // for (auto id : disk) {
    //     std::cout << id << " ";
    // }
    // std::cout << std::endl;

    int64_t sum = 0;
    for (int64_t i = 0; i < disk.size(); i++) {
        auto id = disk[i];
        if (id == -1) {
            continue;
        }

        sum += (id * i);
    }

    return sum;
}

auto main() -> int {
    auto data = parse_stdin();

    auto start = std::chrono::high_resolution_clock::now();

    auto p1 = part1(data);
    auto p2 = part2(data);

    auto end = std::chrono::high_resolution_clock::now();
    auto dur =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::print("part 1: {} ({})\n", p1, p1 == 6385338159127);
    std::print("part 2: {} ({})\n", p2, p2 == 6415163624282);
    std::print("dur:    {}us\n", dur.count());
}
