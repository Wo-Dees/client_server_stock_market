#pragma once

#include <trading/orderbook.hpp>
#include <trading/client.hpp>
#include <trading/operation.hpp>
#include <trading/order.hpp>
#include <trading/trading_pool.hpp>

#include <vector>
#include <map>

namespace trading {

class TradingPool {
public:
    TradingPool() = default;

    void Start() {}

    void Stop() {}

    std::size_t AddClient(std::string name) {
        std::size_t id = clients_.size();
        clients_[id] = Client(id, std::move(name));
        return id;
    }

    std::vector<Operation> Submit(Order order, OrderType type) {
        order.timestep = ++time_stamp_;
        assert(order.volume != 0);
        auto match_result = orderbook_.Execute(order, type);
        for (auto& op : match_result) {
            auto op_sum = op.volume * op.cost;
            clients_[op.seller].ChangeBalance(+ op_sum);
            clients_[op.buyer].ChangeBalance(- op_sum);
            history_.push_back(op);
        }
        return match_result;
    }

    double GetBalance(std::size_t id) {
        return clients_[id].GetBalance();
    }

    struct OrderPack {
        std::vector<Order> from_buy;
        std::vector<Order> from_sale;
    };

    OrderPack GetActiveOrders(std::size_t id) {
        OrderPack pack;
        for (auto iop = orderbook_.BeginBuy(); iop != orderbook_.EndBuy(); ++iop) {
            if (iop->from == id) {
                pack.from_buy.push_back(*iop);
            }
        }
        for (auto iop = orderbook_.BeginSale(); iop != orderbook_.EndSale(); ++iop) {
            if (iop->from == id) {
                pack.from_sale.push_back(*iop);
            }
        }
        return pack;
    }
    
    [[nodiscard]] std::vector<Operation> GetCompleteOrders(std::size_t id) {
        std::vector<Operation> user_history;
        for (auto& op : history_) {
            if (op.seller == id || op.buyer == id) {
                user_history.push_back(op);
            }
        }
        return user_history;
    }
    
private:
    std::map<std::size_t, Client> clients_;
    std::vector<Operation> history_;
    OrderBook orderbook_;
    std::size_t time_stamp_ = 0;
};

} // namespace trading