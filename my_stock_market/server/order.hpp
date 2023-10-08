#pragma once

#include <cassert>
#include <cstdint>
#include <functional>

enum class TypeOrder {
    Buy = 0,
    Sale = 0
};

struct Order {
    std::size_t id;
    TypeOrder type;
    std::size_t volume;
    double cost;
    std::size_t time_point;
};

template <>
struct std::less<Order> {
    bool operator()(const Order& lhs, const Order& rhs) const {
        assert(lhs.time_point == rhs.time_point);
        assert(lhs.type == rhs.type);
        if (lhs.type == TypeOrder::Buy) {
            if (lhs.cost < rhs.cost) {
                return true;
            } else if (lhs.cost > rhs.cost) {
                return false;
            }
        } else {
            if (lhs.cost > rhs.cost) {
                return true;
            } else if (lhs.cost < rhs.cost) {
                return false;
            }
        }
        if (lhs.time_point > rhs.time_point) {
            return true;
        } else {
            return false;
        }
    }
};