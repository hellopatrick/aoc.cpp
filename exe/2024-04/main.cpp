#include "lib.h"

#include <chrono>
#include <print>

std::vector<std::vector<char>> parse_stdin() {
    std::vector<std::vector<char>> puzzle;

    auto lines = aoc::readlines();

    for (auto &line : lines) {
        puzzle.emplace_back(line.begin(), line.end());
    }

    return puzzle;
}

const std::string XMAS = "XMAS";

bool xmas(std::vector<std::vector<char>> puzzle, int x, int y, int dx, int dy) {
    int px = x;
    int py = y;

    int height = puzzle.size();
    int width = puzzle[0].size();

    for (auto c : XMAS) {
        if (x < 0 || y < 0 || x >= width || y >= height) {
            return false;
        }

        if (puzzle[y][x] != c) {
            return false;
        }

        x += dx;
        y += dy;
    }

    return true;
}

bool x_mas(std::vector<std::vector<char>> puzzle, int x, int y) {
    int height = puzzle.size();
    int width = puzzle[0].size();

    if (x - 1 < 0 || y - 1 < 0 || x + 1 >= width || y + 1 >= height) {
        return false;
    }

    if (puzzle[y][x] != 'A') {
        return false;
    }

    std::string left = {puzzle[y - 1][x - 1], puzzle[y][x],
                        puzzle[y + 1][x + 1]};

    std::string right = {puzzle[y + 1][x - 1], puzzle[y][x],
                         puzzle[y - 1][x + 1]};

    return (left == "SAM" || left == "MAS") &&
           (right == "SAM" || right == "MAS");
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    auto data = parse_stdin();

    auto part1 = 0;
    auto part2 = 0;

    std::vector<std::pair<int, int>> dirs = {
        {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

    for (int y = 0; y < data.size(); y++) {
        auto row = data[y];
        for (int x = 0; x < row.size(); x++) {
            for (auto [dx, dy] : dirs) {
                part1 += xmas(data, x, y, dx, dy);
            }

            part2 += x_mas(data, x, y);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto dur =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::print("part 1: {}\n", part1);
    std::print("part 2: {}\n", part2);
    std::print("dur:    {}us\n", dur.count());
}
