#pragma once

#include "order.hpp"
#include <broker.hpp>
#include <orderdatabase.hpp>
#include <orderbook.hpp>

class TradingMachine {
public:

    void Run() {
        while (true) {
            Order order;
            broker_.Pop(order);
            if (Order matched_order = pool_.Match(std::move(order))) {
                matched_.Push(std::move(matched_order));
            }
        }
    }
    
private:
    Broker broker_;
    OrderBook pool_;
    DataBase matched_;
};