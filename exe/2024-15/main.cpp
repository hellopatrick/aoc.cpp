#include "coord.h"
#include "grid.h"
#include "lib.h"

#include <chrono>
#include <iostream>
#include <print>
#include <vector>

using Puzzle = std::pair<aoc::grid<char>, std::vector<aoc::Coord>>;

Puzzle parse_stdin() {
    auto lines = aoc::readlines();

    auto i = lines.begin();
    auto g = std::vector<std::vector<char>>();

    while (i != lines.end()) {
        auto line = *i;

        auto row = std::vector<char>();

        if (line.empty()) {
            i++;
            break;
        }

        for (auto c : line) {
            row.push_back(c);
        }

        g.push_back(row);
        i++;
    }

    auto map = aoc::grid<char>(g);

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

    return {map, dirs};
}

aoc::Coord push(aoc::grid<char> &g, aoc::Coord robot, aoc::Coord d) {
    aoc::Coord next = {robot.x + d.x, robot.y + d.y};

    auto found_free = false;

    int shoves = 0;

    while (g[next] != '#') {
        if (g[next] == '.') {
            found_free = true;
            break;
        }

        next = {next.x + d.x, next.y + d.y};
        shoves++;
    }

    if (!found_free) {
        return robot;
    }

    next = {robot.x + d.x, robot.y + d.y};

    g.g[next.y][next.x] = '.';

    for (int i = 0; i < shoves; i++) {
        next = {next.x + d.x, next.y + d.y};
        g.g[next.y][next.x] = 'O';
    }

    return {robot.x + d.x, robot.y + d.y};
}

void simulate(aoc::grid<char> &g, std::vector<aoc::Coord> dirs) {
    auto robot = g.find('@').value();

    std::println("{}, {}", robot.x, robot.y);

    g.g[robot.y][robot.x] = '.';

    for (auto &d : dirs) {
        aoc::Coord next = {robot.x + d.x, robot.y + d.y};

        if (g[next] == '#') {
        } else if (g[next] == '.') {
            robot = next;
        } else if (g[next] == 'O') {
            robot = push(g, robot, d);
        }

        for (int y = 0; y < g.h; y++) {
            for (int x = 0; x < g.w; x++) {
                if (x == robot.x && y == robot.y) {
                    std::cout << '@';
                } else {
                    std::cout << g.g[y][x];
                }
            }
            std::cout << std::endl;
        }
    }
}

int main() {
    auto [map, dirs] = parse_stdin();

    auto start = std::chrono::high_resolution_clock::now();

    simulate(map, dirs);

    int64_t part1 = 0;

    for (int64_t y = 0; y < map.h; y++) {
        for (int64_t x = 0; x < map.w; x++) {
            if (map[{x, y}] == 'O') {
                part1 += (100L * y) + x;
            }
        }
    }

    auto part2 = 0;

    auto end = std::chrono::high_resolution_clock::now();
    auto dur =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::print("part 1: {}\n", part1);
    std::print("part 2: {}\n", part2);
    std::print("dur:    {}us\n", dur.count());
}
