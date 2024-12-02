#include "lib.h"

#include <algorithm>
#include <cstdio>
#include <unordered_map>
#include <vector>

using namespace std;

pair<vector<int>, vector<int>> parse_input() {
    vector<int> lefts;
    vector<int> rights;

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
    auto data = parse_input();

    auto [lefts, rights] = data;

    auto diff = 0;
    for (auto i = 0; i < lefts.size(); i++) {
        diff += abs(lefts[i] - rights[i]);
    }

    unordered_map<int, int> tally;
    for (auto &r : rights) {
        tally[r] += 1;
    }

    auto sim = 0;
    for (auto &l : lefts) {
        sim += (l * tally[l]);
    }

    printf("part 1: %d\n", diff);
    printf("part 2: %d\n", sim);

    return 0;
}
