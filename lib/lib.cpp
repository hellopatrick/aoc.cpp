#include "lib.h"

#include <iostream>

namespace aoc {
std::vector<std::string> readlines() {
    using namespace std;

    vector<string> lines;
    string line;

    while (getline(cin, line)) {
        lines.push_back(line);
    }

    return lines;
}

bool Coord::operator==(const Coord &c) const { return x == c.x && y == c.y; }

size_t CoordHasher::operator()(const Coord &k) const {
    std::hash<int> inthash;

    return inthash(k.x) ^ (inthash(k.y) << 1);
}
} // namespace aoc
