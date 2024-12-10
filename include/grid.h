#pragma once

#include "coord.h"

#include <__ios/fpos.h>
#include <cstddef>
#include <optional>
#include <vector>

namespace aoc {
template <typename T> struct grid {
    std::vector<std::vector<T>> g;
    size_t h, w;

    grid(const std::vector<std::vector<T>> v) {
        g = std::move(v);

        h = g.size();
        w = h > 0 ? g[0].size() : 0;
    };

    std::optional<T> operator[](Coord const &c) const {
        if (c.x < 0 || c.x >= w) {
            return std::nullopt;
        } else if (c.y < 0 || c.y >= h) {
            return std::nullopt;
        }

        return g[c.y][c.x];
    };
};
} // namespace aoc
