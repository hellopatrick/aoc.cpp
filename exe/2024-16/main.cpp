#include "coord.h"
#include "grid.h"
#include "lib.h"

#include <chrono>
#include <complex>
#include <cstdint>
#include <functional>
#include <iostream>
#include <print>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using Maze = aoc::grid<char>;

Maze parse_stdin() {
    std::vector<std::vector<char>> p;

    auto lines = aoc::readlines();
    for (auto line : lines) {
        auto row = std::vector<char>();

        for (auto c : line) {
            row.push_back(c);
        }

        p.push_back(row);
    }

    return aoc::grid<char>(p);
}

using Path = std::pair<aoc::Coord, std::complex<int64_t>>;

std::vector<std::pair<Path, int>> neighbors(Maze m, Path p) {
    std::vector<std::pair<Path, int>> ns;

    auto [pt, f] = p;

    aoc::Coord fn = {pt.x + f.real(), pt.y + f.imag()};
    if (m.get(fn) == '.') {
        ns.push_back({{fn, f}, 1});
    }

    auto l = f * std::complex<int64_t>(0, 1);
    aoc::Coord ln = {pt.x + l.real(), pt.y + l.imag()};
    if (m.get(ln) == '.') {
        ns.push_back({{ln, l}, 1001});
    }

    auto r = f * std::complex<int64_t>(0, -1);
    aoc::Coord rn = {pt.x + r.real(), pt.y + r.imag()};
    if (m.get(rn) == '.') {
        ns.push_back({{rn, r}, 1001});
    }

    return ns;
}

struct PathHasher {
    size_t operator()(const Path &p) const {
        auto h = aoc::CoordHasher{};
        auto inthash = std::hash<int64_t>();

        return h(p.first) ^ (inthash(p.second.real()) << 2) ^
               (inthash(p.second.imag()) << 4);
    }
};

std::pair<int64_t, int64_t> walk(Maze m, aoc::Coord start, aoc::Coord end) {
    std::unordered_map<Path, int64_t, PathHasher> dist;

    std::unordered_map<Path, std::unordered_set<Path, PathHasher>, PathHasher>
        paths;

    auto cmp = [](const std::pair<Path, int64_t> &a,
                  const std::pair<Path, int64_t> &b) {
        return a.second > b.second;
    };

    std::priority_queue<std::pair<Path, int64_t>,
                        std::vector<std::pair<Path, int64_t>>, decltype(cmp)>
        pq(cmp);

    pq.push({Path{start, {1, 0}}, 0});

    paths[Path{start, {1, 0}}] = std::unordered_set<Path, PathHasher>();

    while (!pq.empty()) {
        auto [path, d] = pq.top();
        pq.pop();

        auto [pt, f] = path;

        auto ns = neighbors(m, path);

        for (auto [next, cost] : ns) {
            if (!paths.contains(next)) {
                paths[next] = std::unordered_set<Path, PathHasher>{};
            }

            if (dist.contains(next)) {
                if (dist[next] > d + cost) {
                    dist[next] = d + cost;
                    paths[next] = std::unordered_set<Path, PathHasher>{path};
                } else if (dist[next] == d + cost) {
                    paths[next].emplace(path);
                    continue;
                } else {
                    continue;
                }
            } else {
                dist[next] = d + cost;
                paths[next].emplace(path);
            }

            pq.push({next, d + cost});
        }
    }

    auto tiles = std::unordered_set<aoc::Coord, aoc::CoordHasher>();
    auto queue = std::queue<Path>();

    auto min = INT64_MAX;

    for (auto [k, v] : dist) {
        auto [pt, _] = k;

        if (pt.x == end.x && pt.y == end.y) {
            if (v < min) {
                min = v;
            }
        }
    }

    for (auto [k, v] : dist) {
        auto [pt, _] = k;

        if (pt.x == end.x && pt.y == end.y) {
            if (v == min) {
                queue.push(k);
            }
        }
    }

    while (!queue.empty()) {
        auto p = queue.front();
        auto [pt, _] = p;
        queue.pop();

        tiles.insert(pt);

        auto s = paths[p];

        queue.push_range(s);
    }

    for (int y = 0; y < m.h; y++) {
        for (int x = 0; x < m.w; x++) {
            std::cout << (tiles.contains({x, y}) ? 'O' : m[{x, y}]);
        }
        std::cout << std::endl;
    }

    return {min, tiles.size()};
}

int main() {
    auto data = parse_stdin();

    auto start = std::chrono::high_resolution_clock::now();

    auto sp = data.find('S').value();
    data[sp] = '.';

    auto ep = data.find('E').value();
    data[ep] = '.';

    auto [part1, part2] = walk(data, sp, ep);

    auto end = std::chrono::high_resolution_clock::now();
    auto dur =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::print("part 1: {} -> {}\n", part1, part1 == 101492);
    std::print("part 2: {} -> {}\n", part2, part2 == 543);
    std::print("dur:    {}us\n", dur.count());
}
