#include "lib.h"

#include <chrono>
#include <print>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using Coords = std::unordered_set<aoc::Coord, aoc::CoordHasher>;
using Puzzle = std::unordered_map<char, std::vector<aoc::Coord>>;

std::tuple<Puzzle, int, int> parse_stdin() {
    Puzzle p;

    auto lines = aoc::readlines();

    auto y = 0;
    for (auto &line : lines) {
        auto x = 0;

        for (auto c : line) {
            if (c == '.') {
                x++;
                continue;
            }
            p[c].emplace_back(x, y);
            x++;
        }

        y++;
    }

    return {p, lines[0].size(), lines.size()};
}

auto solve_part1(Puzzle p, int width, int height) -> Coords {
    auto res = Coords();

    for (auto [k, pts] : p) {
        for (auto p = pts.begin(); p != pts.end(); p++) {
            for (auto q = p + 1; q != pts.end(); q++) {
                auto [px, py] = *p;
                auto [qx, qy] = *q;

                auto dx = px - qx;
                auto dy = py - qy;

                auto nx = px + dx;
                auto ny = py + dy;

                if (0 <= nx && nx < width && 0 <= ny && ny < width) {
                    res.emplace(nx, ny);
                }

                nx = qx - dx;
                ny = qy - dy;

                if (0 <= nx && nx < width && 0 <= ny && ny < width) {
                    res.emplace(nx, ny);
                }
            }
        }
    }

    return res;
}

auto solve_part2(Puzzle &p, const int width, const int height) -> Coords {
    auto res = Coords();

    for (auto [k, pts] : p) {
        for (auto p = pts.begin(); p != pts.end(); p++) {
            for (auto q = p + 1; q != pts.end(); q++) {
                auto [px, py] = *p;
                auto [qx, qy] = *q;

                auto dx = px - qx;
                auto dy = py - qy;

                auto nx = px;
                auto ny = py;

                while (0 <= nx && nx < width && 0 <= ny && ny < width) {
                    res.emplace(nx, ny);
                    nx += dx;
                    ny += dy;
                }

                nx = qx;
                ny = qy;

                while (0 <= nx && nx < width && 0 <= ny && ny < width) {
                    res.emplace(nx, ny);
                    nx -= dx;
                    ny -= dy;
                }
            }
        }
    }

    return res;
}

int main() {
    auto [data, width, height] = parse_stdin();

    auto start = std::chrono::high_resolution_clock::now();

    auto part1 = solve_part1(data, width, height);
    auto part2 = solve_part2(data, width, height);

    auto end = std::chrono::high_resolution_clock::now();
    auto dur =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::print("part 1: {}\n", part1.size());
    std::print("part 2: {}\n", part2.size());
    std::print("dur:    {}us\n", dur.count());
}
