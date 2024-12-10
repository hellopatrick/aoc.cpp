#include "read.h"

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
} // namespace aoc
