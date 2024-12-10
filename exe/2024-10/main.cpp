#include "lib.h"

#include <chrono>
#include <print>
#include <queue>
#include <unordered_set>
#include <vector>

using Puzzle = std::vector<std::vector<int>>;

Puzzle parse_stdin() {
    Puzzle p;

    auto lines = aoc::readlines();

    for (int y = 0; y < lines.size(); y++) {
        auto line = lines.at(y);

        auto row = std::vector<int>(line.size());
        for (int x = 0; x < line.size(); x++) {
            row[x] = (line[x] - '0');
        }

        p.push_back(row);
    }

    return p;
}

auto solve(Puzzle const &p, bool uniq) -> int {
    auto sum = 0;

    auto height = p.size();
    auto width = p[0].size();

    for (int y = 0; y < height; y++) {
        auto row = p[y];

        for (int x = 0; x < width; x++) {
            if (row[x] != 0) {
                continue;
            }

            std::unordered_set<aoc::Coord, aoc::CoordHasher> v;

            std::queue<aoc::Coord> q;
            q.emplace(x, y);

            while (!q.empty()) {
                auto pt = q.front();
                q.pop();

                if (uniq) {
                    if (v.contains(pt)) {
                        continue;
                    }

                    v.insert(pt);
                }

                auto val = p[pt.y][pt.x];

                if (val == 9) {
                    sum++;
                    continue;
                }

                if (pt.y > 0 && val + 1 == p[pt.y - 1][pt.x]) {
                    q.emplace(pt.x, pt.y - 1);
                }
                if (pt.x > 0 && val + 1 == p[pt.y][pt.x - 1]) {
                    q.emplace(pt.x - 1, pt.y);
                }
                if (pt.y < height - 1 && val + 1 == p[pt.y + 1][pt.x]) {
                    q.emplace(pt.x, pt.y + 1);
                }
                if (pt.x < width - 1 && val + 1 == p[pt.y][pt.x + 1]) {
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

    std::print("part 1: {}\n", p1);
    std::print("part 2: {}\n", p2);
    std::print("dur:    {}us\n", dur.count());
}
