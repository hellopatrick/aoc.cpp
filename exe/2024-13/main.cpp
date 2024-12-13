#include "scn/scan.h"

#include <chrono>
#include <cstdint>
#include <cstdio>
#include <numeric>
#include <print>
#include <vector>

struct Button {
    int64_t dx, dy;
};

struct Machine {
    Button a, b;
    int64_t px, py;
};

using Puzzle = std::vector<Machine>;

Puzzle parse_stdin() {
    Puzzle p;

    while (true) {
        auto result =
            scn::scan<int64_t, int64_t>(stdin, "Button A: X+{}, Y+{}\n");
        if (!result.has_value()) {
            break;
        }

        auto [ax, ay] = result->values();
        Button a = {ax, ay};

        result = scn::scan<int64_t, int64_t>(stdin, "Button B: X+{}, Y+{}\n");
        auto [bx, by] = result->values();
        Button b = {bx, by};

        result = scn::scan<int64_t, int64_t>(stdin, "Prize: X={}, Y={}\n");
        auto [px, py] = result->values();
        Machine m = {a, b, px, py};

        p.push_back(m);
    }

    return p;
}

int64_t simulate(Machine &m, int64_t offset) {
    auto px = m.px + offset;
    auto py = m.py + offset;

    auto determinant = (m.a.dx * m.b.dy) - (m.a.dy * m.b.dx);
    if (determinant == 0) {
        return 0;
    }

    if ((px * m.b.dy - py * m.b.dx) % determinant != 0 ||
        (py * m.a.dx - px * m.a.dy) % determinant != 0) {
        return 0;
    }

    auto a = (px * m.b.dy - py * m.b.dx) / determinant;
    auto b = (py * m.a.dx - px * m.a.dy) / determinant;

    return (3 * a) + b;
}

int main() {
    auto data = parse_stdin();

    auto start = std::chrono::high_resolution_clock::now();

    int64_t part1 =
        std::transform_reduce(data.begin(), data.end(), 0L, std::plus{},
                              [](Machine &m) { return simulate(m, 0); });

    int64_t part2 = std::transform_reduce(
        data.begin(), data.end(), 0L, std::plus{},
        [](Machine &m) { return simulate(m, 10000000000000); });

    auto end = std::chrono::high_resolution_clock::now();
    auto dur =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::print("part 1: {}\n", part1);
    std::print("part 2: {}\n", part2);
    std::print("dur:    {}us\n", dur.count());
}
