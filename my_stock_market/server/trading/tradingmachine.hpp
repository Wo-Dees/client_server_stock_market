#pragma once

#include "order.hpp"
#include <broker.hpp>
#include <client.hpp>
#include <map>
#include <orderbook.hpp>
#include <orderdatabase.hpp>

class TradingMachine {
public:
    TradingMachine() = default;

    void AddOrder(const Order& order) {
        broker_.Push(order);
    }
    
private:
    Broker broker_;
    OrderBook pool_;
    DataBase matched_;
    std::map<std::size_t, Client> clients_;
};