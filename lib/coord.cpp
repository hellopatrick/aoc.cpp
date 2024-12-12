#include "coord.h"

#include <functional>

namespace aoc {
bool Coord::operator==(const Coord &c) const { return x == c.x && y == c.y; }

Coord Coord::north() const { return {x, y - 1}; };
Coord Coord::east() const { return {x + 1, y}; };
Coord Coord::south() const { return {x, y + 1}; };
Coord Coord::west() const { return {x - 1, y}; };

size_t CoordHasher::operator()(const Coord &k) const {
    std::hash<int> inthash;

    return inthash(k.x) ^ (inthash(k.y) << 2);
}
} // namespace aoc
