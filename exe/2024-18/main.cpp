#include "coord.h"
#include "grid.h"
#include "lib.h"
#include "read.h"
#include "scn/scan.h"

#include <chrono>
#include <optional>
#include <print>
#include <unordered_map>
#include <vector>

using Puzzle = std::vector<aoc::Coord>;

Puzzle parse_stdin() {
    Puzzle p;

    for (auto &l : aoc::readlines()) {
        if (auto c = scn::scan<int, int>(l, "{},{}")) {
            auto [x, y] = c->values();
            p.emplace_back(x, y);
        }
    }

    return p;
}

auto cmp = [](const std::pair<aoc::Coord, int64_t> &a,
              const std::pair<aoc::Coord, int64_t> &b) {
    return a.second > b.second;
};

using PriorityQueue =
    std::priority_queue<std::pair<aoc::Coord, int64_t>,
                        std::vector<std::pair<aoc::Coord, int64_t>>,
                        decltype(cmp)>;

auto walk(aoc::grid<char> &g) -> std::optional<int> {
    std::unordered_map<aoc::Coord, int64_t, aoc::CoordHasher> dists;

    PriorityQueue pq(cmp);

    dists[{0, 0}] = 0;
    pq.push({{0, 0}, 0});

    while (!pq.empty()) {
        auto [curr, d] = pq.top();
        pq.pop();

        // exit early, doesn't help much?
        if (curr.x == 70 && curr.y == 70) {
            break;
        }

        auto nexts = {curr.east(), curr.west(), curr.north(), curr.south()};

        for (auto next : nexts) {
            if (g.get(next) != '.') {
                continue;
            }

            if (dists.contains(next)) {
                if (d + 1 < dists[next]) {
                    dists[next] = d + 1;
                    pq.push({next, d + 1});
                }
            } else {
                dists[next] = d + 1;
                pq.push({next, d + 1});
            }
        }
    }

    if (dists.contains({70, 70})) {
        return dists[{70, 70}];
    }

    return std::nullopt;
}

int main() {
    auto data = parse_stdin();

    auto start = std::chrono::high_resolution_clock::now();

    auto h = 71;
    auto rows = std::vector<std::vector<char>>();
    auto w = 71;
    for (int i = 0; i < h; i++) {
        rows.push_back(std::vector<char>(w, '.'));
    }

    auto grid = aoc::grid<char>(rows);

    for (auto i = 0; i < 1024; i++) {
        auto c = data[i];
        grid[c] = '#';
    }

    auto part1 = walk(grid);

    auto p = 1024; // know 1024 is okay from part1
    auto q = data.size() - 1;

    while (p + 1 < q) {
        auto mp = (p + q) / 2;

        for (int i = 0; i < data.size(); i++) {
            grid[data[i]] = i <= mp ? '#' : '.';
        }

        auto dist = walk(grid);

        if (dist.has_value()) {
            p = mp;
        } else {
            q = mp;
        }
    }

    aoc::Coord part2 = data[q];

    auto end = std::chrono::high_resolution_clock::now();
    auto dur =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::print("part 1: {}\n", part1.value());
    std::print("part 2: {},{}\n", part2.x, part2.y);
    std::print("dur:    {}us\n", dur.count());
}
