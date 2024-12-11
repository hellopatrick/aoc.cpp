#pragma once

#include <cstddef>
#include <cstdint>

namespace aoc {
struct Coord {
    int64_t x, y;

    bool operator==(const Coord &p) const;
};

struct CoordHasher {
    size_t operator()(const Coord &k) const;
};
} // namespace aoc
