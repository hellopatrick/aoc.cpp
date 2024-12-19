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

std::vector<std::string> split(const std::string &s,
                               const std::string &delimiter) {
    auto start = 0;
    auto end = 0;
    auto len = delimiter.length();

    std::string token;
    std::vector<std::string> res;

    while ((end = s.find(delimiter, start)) != std::string::npos) {
        token = s.substr(start, end - start);
        start = end + len;
        res.push_back(token);
    }

    res.push_back(s.substr(start));

    return res;
}
} // namespace aoc
