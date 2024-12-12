#pragma once

#include <cstddef>
#include <cstdint>

namespace aoc {
struct Coord {
    int64_t x, y;

    bool operator==(const Coord &p) const;

    Coord north() const;
    Coord east() const;
    Coord south() const;
    Coord west() const;
};

struct CoordHasher {
    size_t operator()(const Coord &k) const;
};
} // namespace aoc
