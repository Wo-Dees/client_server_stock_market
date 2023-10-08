#include <broker.hpp>

void Broker::Push(const Order& order) {
    quque_.push(order);
}

bool Broker::Pop(Order& order) {
    bool exe = quque_.pop(order);
    order.time_point = ++time_point_;
    return exe;
}