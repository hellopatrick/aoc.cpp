#!/bin/bash

day=$1
year=$(date +"%Y")
name="${year}-${day}"
exe="exe/${name}"

echo "generate files: ${exe}"

mkdir -p $exe

cat <<EOF > "${exe}/CMakeLists.txt"
include(../day.cmake)
EOF

cat <<EOF > "${exe}/main.cpp"
#include "lib.h"

#include <chrono>
#include <print>
#include <vector>

using Puzzle = std::vector<int>;

Puzzle parse_stdin() {
    Puzzle p;

    return p;
}

int main() {
    auto data = parse_stdin();

    auto start = std::chrono::high_resolution_clock::now();

    auto part1 = 0;
    auto part2 = 0;

    auto end = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::print("part 1: {}\n", part1);
    std::print("part 2: {}\n", part2);
    std::print("dur:    {}us\n", dur.count());
}
EOF

touch "testdata/${name}.txt"
