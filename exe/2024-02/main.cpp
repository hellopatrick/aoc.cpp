#include "lib.h"

#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<vector<int>> parse_stdin() {
    string line;
    vector<vector<int>> reports;

    while (getline(cin, line)) {
        vector<int> report;

        istringstream stream(line);
        int s;

        while (stream >> s) {
            report.push_back(s);
        }

        reports.push_back(report);
    }

    return reports;
}

bool is_safe(vector<int> report) {
    int sign = 0;

    for (int i = 0; i + 1 < report.size(); i++) {
        auto diff = report[i + 1] - report[i];

        if (diff == 0 || abs(diff) > 3) {
            return false;
        }

        int s = copysign(1, diff);

        if (sign == 0) {
            sign = s;
        }

        if (s != sign) {
            return false;
        }
    }

    return true;
}

bool could_be_safe(vector<int> report) {
    for (int i = 0; i < report.size(); i++) {
        vector<int> adjusted_report;

        adjusted_report.reserve(report.size() - 1);
        adjusted_report.insert(adjusted_report.end(), report.begin(),
                               report.begin() + i);
        adjusted_report.insert(adjusted_report.end(), report.begin() + i + 1,
                               report.end());

        if (is_safe(adjusted_report)) {
            return true;
        }
    }

    return false;
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    auto reports = parse_stdin();

    auto part1 = 0;
    for (auto &report : reports) {
        part1 += is_safe(report) ? 1 : 0;
    }

    auto part2 = 0;
    for (auto &report : reports) {
        part2 += (is_safe(report) || could_be_safe(report)) ? 1 : 0;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto dur =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::printf("part 1: %d\n", part1);
    std::printf("part 2: %d\n", part2);
    std::printf("dur:    %lldus\n", dur.count());

    return 0;
}
