#pragma once

#include <cstdint>

namespace trading {

enum class OrderType {
    Buy = 0,
    Sale = 1
};

struct Order {
    std::size_t timestep;
    std::size_t from;
    double cost;
    std::size_t volume;
};

} // namespace trading