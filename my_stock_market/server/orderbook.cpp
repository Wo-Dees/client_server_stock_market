#include <orderbook.hpp>

std::vector<Order> OrderBook::Match(Order& order) {
    if (order.type == TypeOrder::Buy) {
        while (!sale_.empty()) {
            auto neworder = sale_.top();
            if (neworder.cost > order.cost) {
                sale_.push(neworder);
                break;
            }
            sale_.pop();
            std::size_t buy = std::min(order.volume, neworder.volume);
            order.volume -= buy;
            neworder.volume -= buy;
            // перераспредеение баланса
            if (neworder.volume != 0) {
                sale_.push(neworder);
            }
            if (order.volume == 0) {
                break;
            }
        }
    } else {
        while (!buy_.empty()) {
            auto neworder = sale_.top();
            if (neworder.cost < order.cost) {
                sale_.push(neworder);
                break;
            }
            sale_.pop();
            std::size_t buy = std::min(order.volume, neworder.volume);
            order.volume -= buy;
            neworder.volume -= buy;
            // перераспредеение баланса
            if (neworder.volume != 0) {
                sale_.push(neworder);
            }
            if (order.volume == 0) {
                break;
            }
        }
    }
}