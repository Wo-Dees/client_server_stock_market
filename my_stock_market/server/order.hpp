#pragma once

#include <cstdint>

enum class TypeOrder {
    Buy = 0,
    Sale = 0
};

class Order {
public:
    Order() = default;


private:
    std::size_t id_;
    std::size_t number_;
    std::size_t volume_;
};