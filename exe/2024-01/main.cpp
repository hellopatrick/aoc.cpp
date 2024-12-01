#include "lib.h"

#include <algorithm>
#include <iostream>
#include <unordered_map>

using namespace std;

pair<vector<int>, vector<int>> parse(istream &in) {
    vector<int> lefts;
    vector<int> rights;

    int left, right;
    while (!in.eof()) {
        in >> left >> right;
        lefts.push_back(left);
        rights.push_back(right);
    }

    sort(lefts.begin(), lefts.end());
    sort(rights.begin(), rights.end());

    return pair(lefts, rights);
}

int main() {
    auto data = parse(std::cin);

    auto [lefts, rights] = data;

    auto diff = 0;
    for (auto i = 0; i < lefts.size(); i++) {
        diff += abs(lefts[i] - rights[i]);
    }

    printf("part 1: %d\n", diff);

    unordered_map<int, int> tally;
    for (auto &r : rights) {
        tally[r] += 1;
    }

    auto sim = 0;
    for (auto &l : lefts) {
        sim += (l * tally[l]);
    }

    printf("part 2: %d\n", sim);

    return 0;
}
