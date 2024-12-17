#include <chrono>
#include <cstdint>
#include <numeric>
#include <print>
#include <scn/scan.h>
#include <stdexcept>
#include <utility>
#include <vector>

struct Machine {
    int64_t a, b, c;

    std::vector<int> tape;

    std::string result() {
        return std::accumulate(tape.begin(), tape.end(), std::string(""),
                               [](const std::string &a, const int &b) {
                                   return a + (a.empty() ? "" : ",") +
                                          std::to_string(b);
                               });
    }
};

using Program = std::vector<int64_t>;
using Puzzle = std::pair<Machine, Program>;

Puzzle parse_stdin() {
    Machine p{0, 0, 0};

    p.a = scn::scan<int64_t>(stdin, "Register A: {}\n")->value();
    p.b = scn::scan<int64_t>(stdin, "Register B: {}\n")->value();
    p.c = scn::scan<int64_t>(stdin, "Register C: {}\n")->value();

    auto _ = scn::scan(stdin, "Program: ");

    auto ops = Program();

    while (true) {
        if (auto o = scn::scan<int64_t>(stdin, "{}")) {
            ops.push_back(o->value());
        } else {
            break;
        }

        auto o = scn::scan(stdin, ",");
    }

    return {p, ops};
}

int64_t combo(Machine &m, int op) {
    if (op <= 3) {
        return op;
    } else if (op == 4) {
        return m.a;
    } else if (op == 5) {
        return m.b;
    } else if (op == 6) {
        return m.c;
    } else {
        throw std::runtime_error("invalid op");
    }
}

Machine execute(Machine m, const Program &p) {
    int pc = 0;
    while (pc + 1 < p.size()) {
        int op = p[pc];
        int co = p[pc + 1];

        if (op == 0) {
            m.a = m.a >> combo(m, co); // dividing by power of 2.
        } else if (op == 1) {
            m.b = m.b ^ co;
        } else if (op == 2) {
            m.b = combo(m, co) % 8;
        } else if (op == 3 && m.a != 0) {
            pc = co;
            continue;
        } else if (op == 4) {
            m.b = m.b ^ m.c;
        } else if (op == 5) {
            m.tape.push_back(combo(m, co) % 8);
        } else if (op == 6) {
            m.b = m.a >> combo(m, co);
        } else if (op == 7) {
            m.c = m.a >> combo(m, co);
        }

        pc += 2;
    }

    return m;
}

// "decompiled" puzzle input.
int64_t compute(int64_t a) {
    auto b = (a % 8) ^ 1;
    auto c = a >> b;

    b = b ^ 4;
    b = b ^ c;

    return b % 8;
}

int64_t solve(const Program &p, int64_t res, int64_t i) {
    if (i < 0) {
        return res;
    } else if (i >= p.size()) {
        return -1;
    }

    int64_t target = p[i];

    for (int a = 0; a < 8; a++) {
        auto attempt = (res << 3) + a;
        if (compute(attempt) == target) {
            auto v = solve(p, attempt, i - 1);

            if (v != -1) {
                return v;
            }
        }
    }

    return -1;
}

int main() {
    auto [machine, ops] = parse_stdin();

    auto start = std::chrono::high_resolution_clock::now();

    auto p1 = execute(machine, ops);

    auto part1 = p1.result();
    auto part2 = solve(ops, 0, ops.size() - 1);

    auto end = std::chrono::high_resolution_clock::now();
    auto dur =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::print("part 1: {}\n", part1);
    std::print("part 2: {}\n", part2);
    std::print("dur:    {}us\n", dur.count());
}
