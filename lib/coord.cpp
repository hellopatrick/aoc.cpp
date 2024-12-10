#include "coord.h"

#include <functional>

namespace aoc {
bool Coord::operator==(const Coord &c) const { return x == c.x && y == c.y; }

size_t CoordHasher::operator()(const Coord &k) const {
    std::hash<int> inthash;

    return inthash(k.x) ^ (inthash(k.y) << 2);
}
} // namespace aoc
