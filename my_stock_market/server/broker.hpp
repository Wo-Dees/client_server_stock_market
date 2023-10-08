#pragma once

#include <boost/lockfree/queue.hpp>

#include <order.hpp>

class Broker {
public:
    Broker() = default;

    void Push(const Order&);

    bool Pop(Order& order);

private:
    boost::lockfree::queue<Order> quque_;
};