#include "lib.h"

#include <algorithm>
#include <chrono>
#include <complex>
#include <print>
#include <unordered_map>
#include <unordered_set>

template <typename T>
using coord_map = std::unordered_map<aoc::Coord, T, aoc::CoordHasher>;

std::pair<coord_map<char>, aoc::Coord> parse_stdin() {
    coord_map<char> map;
    aoc::Coord start;

    auto lines = aoc::readlines();

    for (int y = 0; y < lines.size(); y++) {
        auto line = lines[y];

        for (int x = 0; x < line.size(); x++) {
            auto c = line.at(x);
            map[aoc::Coord{x, y}] = c;

            if (c == '^') {
                start.x = x;
                start.y = y;
            }
        }
    }

    return {map, start};
}

using coord_set = std::unordered_set<aoc::Coord, aoc::CoordHasher>;

std::pair<bool, coord_set> travel(coord_map<char> &m, aoc::Coord sp) {
    coord_set set;
    coord_map<std::vector<std::complex<int>>> visited;

    aoc::Coord at = sp;

    bool was_loop = false;

    std::complex<int> facing(0, -1);

    while (m.contains(at)) {
        auto dirs = visited[at];

        if (std::find(dirs.begin(), dirs.end(), facing) != dirs.end()) {
            was_loop = true;
            break;
        }

        set.insert(at);
        visited[at].emplace_back(facing);

        auto next = at;
        next.x += facing.real();
        next.y += facing.imag();

        if (m.find(next) != m.end() && m[next] == '#') {
            facing *= std::complex<int>(0, 1);
        } else {
            at = next;
        }
    }

    return {was_loop, set};
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    auto [map, sp] = parse_stdin();

    auto [_, seen] = travel(map, sp);

    auto part1 = seen.size();
    auto part2 = 0;
    for (auto &pt : seen) {
        if (sp == pt) {
            continue;
        }

        coord_map<char> modified_map(map);
        modified_map[pt] = '#';

        auto [was_loop, _] = travel(modified_map, sp);

        part2 += was_loop;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto dur =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::print("part 1: {}\n", part1);
    std::print("part 2: {}\n", part2);
    std::print("dur:    {}us\n", dur.count());
}
