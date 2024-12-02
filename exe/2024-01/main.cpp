#include "lib.h"

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <unordered_map>
#include <vector>

using namespace std;

pair<vector<int>, vector<int>> parse_stdin() {
    vector<int> lefts, rights;
    lefts.reserve(1000);
    rights.reserve(1000);

    int left, right;
    while (scanf("%d %d", &left, &right) != EOF) {
        lefts.push_back(left);
        rights.push_back(right);
    }

    sort(lefts.begin(), lefts.end());
    sort(rights.begin(), rights.end());

    return pair(lefts, rights);
}

int main() {
    auto start = chrono::high_resolution_clock::now();

    auto data = parse_stdin();

    auto [lefts, rights] = data;

    auto part1 = 0;
    for (auto i = 0; i < lefts.size(); i++) {
        part1 += abs(lefts[i] - rights[i]);
    }

    unordered_map<int, int> tally;
    for (auto &r : rights) {
        tally[r] += 1;
    }

    auto part2 = 0;
    for (auto &l : lefts) {
        part2 += (l * tally[l]);
    }

    auto end = chrono::high_resolution_clock::now();
    auto dur = chrono::duration_cast<chrono::microseconds>(end - start);

    std::print("part 1: {}\n", part1);
    std::print("part 2: {}\n", part2);
    std::print("dur:    {}us\n", dur.count());

    return 0;
}
