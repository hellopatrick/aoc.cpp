#include "lib.h"
#include "scn/scan.h"

#include <algorithm>
#include <chrono>
#include <functional>
#include <numeric>
#include <print>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

struct Ruleset {
    std::unordered_map<int, std::unordered_set<int>> rules;

    bool operator()(int const &a, int const &b) const {
        if (rules.at(a).contains(b)) {
            return true;
        }

        if (rules.at(b).contains(a)) {
            return false;
        }

        return true;
    }
};

std::pair<Ruleset, std::vector<std::vector<int>>> parse_stdin() {
    auto lines = aoc::readlines();

    std::unordered_map<int, std::unordered_set<int>> rules;
    std::vector<std::vector<int>> updates;

    for (auto &line : lines) {
        auto result = scn::scan<int, int>(line, "{}|{}");
        if (result.has_value()) {
            auto [a, b] = result->values();
            rules[a].insert(b);
            continue;
        }

        if (line == "") {
            continue;
        }

        std::istringstream is(line);
        std::string token;
        std::vector<int> update;
        while (std::getline(is, token, ',')) {
            update.push_back(std::stoi(token));
        }

        updates.push_back(update);
    }

    return {Ruleset{rules}, updates};
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    auto [rs, updates] = parse_stdin();

    auto incorrect = std::partition(
        updates.begin(), updates.end(), [&rs](std::vector<int> i) {
            return std::is_sorted(i.begin(), i.end(), rs);
        });

    auto part1 = std::transform_reduce(
        updates.begin(), incorrect, 0, std::plus{},
        [](auto update) { return update[update.size() / 2]; });

    auto part2 = std::transform_reduce(
        incorrect, updates.end(), 0, std::plus{}, [&rs](auto update) {
            std::sort(update.begin(), update.end(), rs);
            return update[update.size() / 2];
        });
    ;

    auto end = std::chrono::high_resolution_clock::now();
    auto dur =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::print("part 1: {}\n", part1);
    std::print("part 2: {}\n", part2);
    std::print("dur:    {}us\n", dur.count());
}
