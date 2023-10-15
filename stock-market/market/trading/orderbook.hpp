#pragma once

#include <cassert>
#include <vector>
#include <set>

#include <trading/order.hpp>
#include <trading/operation.hpp>

namespace trading {

namespace detail {

    struct BuyOrd {
        bool operator()(const Order& lhs, const Order& rhs) const {
            assert(lhs.timestep != rhs.timestep);
            if (lhs.cost > rhs.cost) {
                return true;
            } else if (lhs.cost < rhs.cost) {
                return false;
            }
            if (lhs.timestep < rhs.timestep) {
                return true;
            } 
            return false;
        }
    };

    struct SaleOrd {
        bool operator()(const Order& lhs, const Order& rhs) const {
            assert(lhs.timestep != rhs.timestep);
            if (lhs.cost < rhs.cost) {
                return true;
            } else if (lhs.cost > rhs.cost) {
                return false;
            }
            if (lhs.timestep < rhs.timestep) {
                return true;
            } 
            return false;
        }
    };

} // namespace detail

class OrderBook {
public:
    OrderBook() = default;

    std::vector<Operation> Execute(const Order& order, OrderType type) {
        switch (type) {
            case OrderType::Buy: {
                return ExecuteBuy(order);
            }
            case OrderType::Sale: {
                return ExecuteSale(order);
            }
            default: {
                assert(false);
            }
        }
    }

    auto BeginBuy() const noexcept {
        return buy_.cbegin();
    }

    auto EndBuy() const noexcept {
        return buy_.cend();
    }

    auto BeginSale()const noexcept {
        return sale_.cbegin();
    }

    auto EndSale() const noexcept {
        return sale_.cend();
    }

private:
    std::vector<Operation> ExecuteBuy(Order order) {
        std::vector<Operation> done_operations;
        std::vector<Order> my_sale_order;
        while (true) {
            if (sale_.empty() || order.volume == 0) {
                break;
            }
            auto del_order = *sale_.begin();
            auto iter_order = sale_.begin();
            if (del_order.cost <= order.cost) {
                sale_.erase(iter_order);
                if (del_order.from == order.from) {
                    my_sale_order.push_back(del_order);
                    continue;
                }
                auto vol_oper = std::min(del_order.volume, order.volume);
                done_operations.push_back({del_order.from, order.from, del_order.cost, vol_oper});
                order.volume -= vol_oper;
                if (vol_oper != del_order.volume) {
                    sale_.insert({del_order.timestep, del_order.from, del_order.cost, del_order.volume - vol_oper});
                }
            } else {
                break;
            }
        }
        sale_.insert(my_sale_order.begin(), my_sale_order.end());
        if (order.volume != 0) {
            buy_.insert(order);
        }
        return done_operations;
    }

    std::vector<Operation> ExecuteSale(Order order) {
        std::vector<Operation> done_operations;
        std::vector<Order> my_buy_order;
        while (true) {
            if (buy_.empty() || order.volume == 0) {
                break;
            }
            auto del_order = *buy_.begin();
            auto iter_order = buy_.begin();
            if (del_order.cost >= order.cost) {
                buy_.erase(iter_order);
                if (del_order.from == order.from) {
                    my_buy_order.push_back(del_order);
                    continue;
                }
                auto vol_oper = std::min(del_order.volume, order.volume);
                done_operations.push_back({order.from, del_order.from, del_order.cost, vol_oper});
                order.volume -= vol_oper;
                if (vol_oper != del_order.volume) {
                    buy_.insert({del_order.timestep, del_order.from, del_order.cost, del_order.volume - vol_oper});
                }
            } else {
                break;
            }
        }
        buy_.insert(my_buy_order.begin(), my_buy_order.end());
        if (order.volume != 0) {
            sale_.insert(order);
        }
        return done_operations;
    }

    std::set<Order, detail::BuyOrd> buy_;
    std::set<Order, detail::SaleOrd> sale_;
};

} // namespace trading