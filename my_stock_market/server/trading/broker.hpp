#pragma once

#include <boost/lockfree/queue.hpp>

#include <order.hpp>

class Broker {
public:
    Broker() = default;

    void Push(const Order& order) {
        quque_.push(order);
    }

    bool Pop(Order& order) {
        bool exe = quque_.pop(order);
        order.time_point = ++time_point_;
        return exe;
    }

private:
    std::size_t time_point_{0};
    boost::lockfree::queue<Order> quque_;
};
