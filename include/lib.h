#include <string>
#include <vector>

namespace aoc {
struct Coord {
    int x, y;

    bool operator==(const Coord &p) const;
};

struct CoordHasher {
    size_t operator()(const Coord &k) const;
};

std::vector<std::string> readlines();
} // namespace aoc
