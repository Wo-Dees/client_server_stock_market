#pragma once

#include <boost/lockfree/queue.hpp>

#include <order.hpp>

class Broker {
public:
    Broker() = default;

    void Push(const Order&);

    bool Pop(Order& order);

private:
    std::size_t time_point_{0};
    boost::lockfree::queue<Order> quque_;
};