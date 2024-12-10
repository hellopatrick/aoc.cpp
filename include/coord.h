#pragma once

#include <cstddef>

namespace aoc {
struct Coord {
    int x, y;

    bool operator==(const Coord &p) const;
};

struct CoordHasher {
    size_t operator()(const Coord &k) const;
};
} // namespace aoc
