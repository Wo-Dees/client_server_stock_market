#pragma once

#include <order.hpp>

#include <vector>
#include <queue>

class OrderBook {
public:
    OrderBook() = default;
    std::vector<Order> Match(Order& order);
private:
    std::priority_queue<Order> buy_;
    std::priority_queue<Order> sale_;
};
