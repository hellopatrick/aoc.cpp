#include "lib.h"
#include "scn/scan.h"

#include <chrono>
#include <iostream>
#include <print>
#include <vector>

using Tape = std::vector<int>;

Tape parse_stdin() {
    Tape p;

    while (auto i = scn::scan<int>(stdin, "{}")) {
        auto j = i->value();

        p.push_back(i->value());

        auto _ = scn::scan(stdin, ",");
    }

    return p;
}

void simulate(Tape &t) {
    int pc = 0;

    while (pc < t.size()) {
        auto op = t[pc];

        auto a = t[pc + 1];
        auto b = t[pc + 2];
        auto c = t[pc + 3];

        if (op == 1) {
            t[c] = t[a] + t[b];
        } else if (op == 2) {
            t[c] = t[a] * t[b];
        } else if (op == 99) {
            break;
        }

        pc += 4;
    }
}

int main() {
    auto data = parse_stdin();

    auto start = std::chrono::high_resolution_clock::now();

    data[1] = 12;
    data[2] = 2;

    std::vector<int> part1;
    part1.append_range(data);

    simulate(part1);

    auto part2 = 0;
    auto target = 19690720;

    int n = 0;
    int v = 0;
    for (n = 0; n < data.size(); n++) {
        for (v = 0; v < data.size(); v++) {
            std::vector<int> attempt;
            attempt.append_range(data);

            attempt[1] = n;
            attempt[2] = v;

            simulate(attempt);

            if (attempt[0] == target) {
                goto found;
            }
        }
    }
found:

    auto end = std::chrono::high_resolution_clock::now();
    auto dur =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::print("part 1: {}\n", part1[0]);
    std::print("part 2: {}\n", 100 * n + v);
    std::print("dur:    {}us\n", dur.count());
}
