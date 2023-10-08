#pragma once

#include "order.hpp"

#include <set>

class Answer {
public:

private:

};

class OrderPool {
public:
    Answer ProcessOrder(Order order);
private:
    std::set<Order> buy_;
    std::set<Order> sale_;
};
