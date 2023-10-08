#pragma once

#include <order.hpp>

#include <set>

class OrderBook {
public:
    Order Match(Order order);
private:
    std::set<Order> buy_;
    std::set<Order> sale_;
};
