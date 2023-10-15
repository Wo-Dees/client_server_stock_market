#pragma once

#include <cassert>
#include <cstdint>
#include <functional>

enum class TypeOrder {
    Buy = 0,
    Sale = 1
};

struct Order {
    double cost;
    std::size_t id;
    std::size_t volume;
    std::size_t time_point;
};

