#include "coord.h"
#include "grid.h"
#include "lib.h"
#include "read.h"

#include <chrono>
#include <print>
#include <queue>
#include <unordered_set>

using Puzzle = aoc::grid<char>;

Puzzle parse_stdin() {
    std::vector<std::vector<char>> v;

    auto lines = aoc::readlines();

    for (auto &line : lines) {
        auto row = std::vector<char>();

        for (auto c : line) {
            row.push_back(c);
        }

        v.push_back(row);
    }

    return Puzzle(v);
}

using Region = std::unordered_set<aoc::Coord, aoc::CoordHasher>;
Region fill(Puzzle &p, aoc::Coord start) {
    Region r;

    char c = *p[start];

    auto q = std::queue<aoc::Coord>();
    q.push(start);

    while (!q.empty()) {
        auto next = q.front();
        q.pop();

        if (r.contains(next)) {
            continue;
        }

        auto dirs = {next.north(), next.south(), next.east(), next.west()};
        for (auto &d : dirs) {
            if (p[d] == c) {
                q.push(d);
            }
        }

        r.insert(next);
    }

    return r;
}

int perimeter(Region &r) {
    int perim = 0;
    for (auto &c : r) {
        auto dirs = {c.north(), c.south(), c.east(), c.west()};

        for (auto &n : dirs) {
            if (!r.contains(n)) {
                perim++;
            }
        }
    }
    return perim;
}

int sides(Region &r) {
    int corners = 0;
    for (auto &c : r) {
        auto vertical = {c.north(), c.south()};
        auto horizontal = {c.east(), c.west()};

        for (auto v : vertical) {
            for (auto h : horizontal) {
                if (!r.contains(v) && !r.contains(h)) {
                    corners++;
                }

                if (r.contains(v) && r.contains(h) && !r.contains({h.x, v.y})) {
                    corners++;
                }
            }
        }
    }

    return corners;
}

int main() {
    auto data = parse_stdin();

    auto start = std::chrono::high_resolution_clock::now();

    auto part1 = 0;
    auto part2 = 0;

    auto seen = Region();
    auto regions = std::vector<Region>();

    for (int x = 0; x < data.w; x++) {
        for (int y = 0; y < data.h; y++) {
            if (seen.contains({x, y})) {
                continue;
            }

            auto region = fill(data, {x, y});
            regions.push_back(region);
            seen.insert(region.begin(), region.end());
        }
    }

    for (auto region : regions) {
        part1 += region.size() * perimeter(region);
        part2 += region.size() * sides(region);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto dur =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::print("part 1: {} ({})\n", part1, part1 == 1494342);
    std::print("part 2: {} ({})\n", part2, part2 == 893676);
    std::print("dur:    {}us\n", dur.count());
}
