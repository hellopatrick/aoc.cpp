#include "coord.h"
#include "grid.h"
#include "lib.h"

#include <chrono>
#include <print>
#include <vector>

using Puzzle =
    std::tuple<aoc::grid<char>, aoc::grid<char>, std::vector<aoc::Coord>>;

Puzzle parse_stdin() {
    auto lines = aoc::readlines();

    auto i = lines.begin();
    auto g1 = std::vector<std::vector<char>>();
    auto g2 = std::vector<std::vector<char>>();

    while (i != lines.end()) {
        auto line = *i;

        auto row1 = std::vector<char>();
        auto row2 = std::vector<char>();

        if (line.empty()) {
            i++;
            break;
        }

        for (auto c : line) {
            row1.push_back(c);

            if (c == '#') {
                row2.push_back('#');
                row2.push_back('#');
            } else if (c == 'O') {
                row2.push_back('[');
                row2.push_back(']');
            } else if (c == '@') {
                row2.push_back('@');
                row2.push_back('.');
            } else if (c == '.') {
                row2.push_back('.');
                row2.push_back('.');
            }
        }

        g1.push_back(row1);
        g2.push_back(row2);
        i++;
    }

    auto dirs = std::vector<aoc::Coord>();

    while (i != lines.end()) {
        auto line = *i;

        for (auto c : line) {
            if (c == '<') {
                dirs.push_back({-1, 0});
            } else if (c == '>') {
                dirs.push_back({+1, 0});
            } else if (c == '^') {
                dirs.push_back({0, -1});
            } else if (c == 'v') {
                dirs.push_back({0, +1});
            }
        }

        i++;
    }

    return {aoc::grid<char>(g1), aoc::grid<char>(g2), dirs};
}

bool can_move(aoc::grid<char> &g, aoc::Coord pt, aoc::Coord d) {
    aoc::Coord next = {pt.x + d.x, pt.y + d.y};

    auto space = g[next];

    if (space == '#') {
        return false;
    } else if (space == '.') {
        return true;
    } else if (space == 'O') {
        return can_move(g, next, d);
    } else if (space == '[') {
        if (d.x == 0) {
            return can_move(g, next, d) && can_move(g, next.east(), d);
        } else {
            return can_move(g, next, d);
        }
    } else if (space == ']') {
        if (d.x == 0) {
            return can_move(g, next.west(), d) && can_move(g, next, d);
        } else {
            return can_move(g, next, d);
        }
    }

    return false;
};

void push(aoc::grid<char> &g, aoc::Coord pt, aoc::Coord d) {
    aoc::Coord next = {pt.x + d.x, pt.y + d.y};
    auto space = g[next];

    if (space == '#') {
        return;
    }

    if (space == 'O') {
        push(g, next, d);
    } else if (space == '[') {
        if (d.x == 0) {
            push(g, next, d);
            push(g, next.east(), d);
        } else {
            push(g, next, d);
        }
    } else if (space == ']') {
        if (d.x == 0) {
            push(g, next.west(), d);
            push(g, next, d);
        } else {
            push(g, next, d);
        }
    }

    g.g[next.y][next.x] = g.g[pt.y][pt.x];
    g.g[pt.y][pt.x] = '.';
}

void simulate(aoc::grid<char> &g, std::vector<aoc::Coord> dirs) {
    auto robot = g.find('@').value();

    g.g[robot.y][robot.x] = '.';

    for (auto &d : dirs) {
        if (can_move(g, robot, d)) {
            push(g, robot, d);
            robot = {robot.x + d.x, robot.y + d.y};
        }
    }
}

int main() {
    auto [simple, expanded, dirs] = parse_stdin();

    auto start = std::chrono::high_resolution_clock::now();

    auto part1 = 0;
    simulate(simple, dirs);

    for (auto y = 0; y < simple.h; y++) {
        for (auto x = 0; x < simple.w; x++) {
            if (simple[{x, y}] == 'O') {
                part1 += (100L * y) + x;
            }
        }
    }

    auto part2 = 0;
    simulate(expanded, dirs);

    for (auto y = 0; y < expanded.h; y++) {
        for (auto x = 0; x < expanded.w; x++) {
            if (expanded[{x, y}] == '[') {
                part2 += (100L * y) + x;
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto dur =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::print("part 1: {}\n", part1);
    std::print("part 2: {}\n", part2);
    std::print("dur:    {}us\n", dur.count());
}
