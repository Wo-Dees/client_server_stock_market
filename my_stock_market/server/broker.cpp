#include <broker.hpp>

void Broker::Push(const Order& order) {
    quque_.push(order);
}

bool Broker::Pop(Order& order) {
    return quque_.pop(order);
}