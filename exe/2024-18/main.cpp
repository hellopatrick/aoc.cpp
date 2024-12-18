#include "coord.h"
#include "grid.h"
#include "lib.h"
#include "read.h"
#include "scn/scan.h"

#include <chrono>
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

auto walk(aoc::grid<char> &g)
    -> std::unordered_map<aoc::Coord, int64_t, aoc::CoordHasher> {
    std::unordered_map<aoc::Coord, int64_t, aoc::CoordHasher> dists;

    auto cmp = [](const std::pair<aoc::Coord, int64_t> &a,
                  const std::pair<aoc::Coord, int64_t> &b) {
        return a.second > b.second;
    };

    std::priority_queue<std::pair<aoc::Coord, int64_t>,
                        std::vector<std::pair<aoc::Coord, int64_t>>,
                        decltype(cmp)>
        pq(cmp);

    dists[{0, 0}] = 0;
    pq.push({{0, 0}, 0});

    while (!pq.empty()) {
        auto [curr, d] = pq.top();
        pq.pop();

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

    return dists;
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

    auto dists = walk(grid);
    auto part1 = dists[{70, 70}];

    auto i = 1024;
    aoc::Coord part2;

    while (i < data.size()) {
        auto block = data[i];
        grid[block] = '#';

        auto dists = walk(grid);
        if (!dists.contains({70, 70})) {
            part2 = block;
            break;
        }

        i++;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto dur =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::print("part 1: {}\n", part1);
    std::print("part 2: {},{}\n", part2.x, part2.y);
    std::print("dur:    {}us\n", dur.count());
}
