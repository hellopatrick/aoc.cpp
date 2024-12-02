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

    auto end = chrono::high_resolution_clock::now();
    auto dur = chrono::duration_cast<chrono::microseconds>(end - start);

    printf("part 1: %d\n", diff);
    printf("part 2: %d\n", sim);
    printf("dur:    %lldus\n", dur.count());

    return 0;
}
