#include <print>
#include <stdexcept>
#include <vector>

namespace aoc {

enum class opcode {
    add = 1,
    mult = 2,
    input = 3,
    output = 4,
    quit = 99,
};

enum mode { position = 0, immediate = 1 };

struct operation {
    opcode op;
    mode a, b, c;

    operation(int code) {
        op = opcode(code % 100);

        a = mode((code / 100) % 10);
        b = mode((code / 1000) % 10);
        c = mode((code / 1000) % 10);
    }
};

struct vm {
    std::vector<int> memory;
    int pc = 0;

    vm(const std::vector<int> mem) : memory(mem), pc(0) {}

    int &operator[](size_t loc) { return memory[loc]; }

    void simulate() {
        while (pc < memory.size()) {
            auto raw = memory[pc];

            auto op = operation(raw);

            if (op.op == opcode::quit) {
                break;
            }

            switch (op.op) {
            case opcode::add:
                add(op);
                break;
            case opcode::mult:
                mult(op);
                break;
            case opcode::input:
                break;
            case opcode::output:
                break;
            default:
                throw std::runtime_error("unimplemented");
            }
        }
    }

    void add(operation op) {
        auto a = memory[pc + 1];
        auto b = memory[pc + 2];
        auto c = memory[pc + 3];

        a = op.a ? a : memory[a];
        b = op.a ? b : memory[b];

        memory[c] = a + b;
        pc += 4;
    }

    void mult(operation op) {
        auto a = memory[pc + 1];
        auto b = memory[pc + 2];
        auto c = memory[pc + 3];

        a = op.a ? a : memory[a];
        b = op.a ? b : memory[b];

        memory[c] = a * b;
        pc += 4;
    }

    void input(operation op) {
        auto a = memory[pc + 1];

        memory[a] = 1;
        pc += 2;
    }

    void output(operation op) {
        auto a = memory[pc + 1];

        a = op.a ? a : memory[a];

        std::println("{}", a);

        pc += 2;
    }
};
} // namespace aoc
