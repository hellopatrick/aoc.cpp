#include "coord.h"
#include "lib.h"

#include <chrono>
#include <print>
#include <queue>
#include <unordered_set>
#include <vector>

using Puzzle = aoc::grid<int>;

Puzzle parse_stdin() {
    auto lines = aoc::readlines();

    std::vector<std::vector<int>> p;
    for (int y = 0; y < lines.size(); y++) {
        auto line = lines.at(y);

        auto row = std::vector<int>(line.size());
        for (int x = 0; x < line.size(); x++) {
            row[x] = (line[x] - '0');
        }

        p.push_back(row);
    }

    return Puzzle(p);
}

auto solve(Puzzle const &p, bool uniq) -> int {
    auto sum = 0;

    for (int y = 0; y < p.h; y++) {
        for (int x = 0; x < p.w; x++) {
            auto a = p[{x, y}];

            if (*a != 0) {
                continue;
            }

            std::unordered_set<aoc::Coord, aoc::CoordHasher> v;

            std::queue<aoc::Coord> q;
            q.push({x, y});

            while (!q.empty()) {
                auto pt = q.front();
                q.pop();

                if (uniq) {
                    if (v.contains(pt)) {
                        continue;
                    }

                    v.insert(pt);
                }

                auto val = *p[pt];

                if (val == 9) {
                    sum++;
                    continue;
                }

                if (val + 1 == p[{pt.x, pt.y - 1}]) {
                    q.emplace(pt.x, pt.y - 1);
                }
                if (val + 1 == p[{pt.x - 1, pt.y}]) {
                    q.emplace(pt.x - 1, pt.y);
                }
                if (val + 1 == p[{pt.x, pt.y + 1}]) {
                    q.emplace(pt.x, pt.y + 1);
                }
                if (val + 1 == p[{pt.x + 1, pt.y}]) {
                    q.emplace(pt.x + 1, pt.y);
                }
            }
        }
    }

    return sum;
}

int main() {
    auto data = parse_stdin();

    auto start = std::chrono::high_resolution_clock::now();

    auto p1 = solve(data, true);
    auto p2 = solve(data, false);

    auto end = std::chrono::high_resolution_clock::now();
    auto dur =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::print("part 1: {} ({})\n", p1, p1 == 638);
    std::print("part 2: {} ({})\n", p2, p2 == 1289);
    std::print("dur:    {}us\n", dur.count());
}
