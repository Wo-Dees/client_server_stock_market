#pragma once

#include <cstdint>

namespace trading {

struct Operation {
    constexpr Operation(std::size_t seller, std::size_t buyer, double cost, std::size_t volume) noexcept
            : seller(seller), buyer(buyer), cost(cost), volume(volume) {

    }
    std::size_t seller;
    std::size_t buyer;
    double cost;
    std::size_t volume;
};

} // namespace trading