#include "trading/order.hpp"
#include <catch2/catch_test_macros.hpp>

#include <trading/trading_pool.hpp>

#include <iostream>

void PrintReportPool(std::string name, trading::TradingPool::OrderPack pack) {
    std::cerr << std::endl << std::endl;
    std::cerr << name << std::endl;
    std::cerr << "From buy" << std::endl;
    std::cerr << "from cost timestep volume" << std::endl;
    for (auto el : pack.from_buy) {
        std::cerr << el.from << "  " << el.cost << "  " << el.timestep << "  " << el.volume << std::endl;
    }
    std::cerr << "From sale" << std::endl;
    std::cerr << "from cost timestep volume" << std::endl;
    for (auto el : pack.from_sale) {
        std::cerr << el.from << "  " << el.cost << "  " << el.timestep << "  " << el.volume << std::endl;
    }
    std::cerr << std::endl << std::endl;
}

TEST_CASE("Empty") {
    trading::TradingPool pool;

    auto vasya_id = pool.AddClient("vasia");
    auto petya_ip = pool.AddClient("petya");

    REQUIRE(pool.GetBalance(vasya_id) == 0);

    REQUIRE(pool.GetActiveOrders(vasya_id).from_buy.empty());
    REQUIRE(pool.GetActiveOrders(vasya_id).from_sale.empty());

    REQUIRE(pool.GetCompleteOrders(petya_ip).empty());
}

TEST_CASE("SimpleMatch") {
    trading::TradingPool pool;

    auto vasya_id = pool.AddClient("vasia");
    auto petya_ip = pool.AddClient("petya");

    pool.Submit({0, vasya_id, 100, 2}, trading::OrderType::Buy);
    pool.Submit({0, petya_ip, 100, 2}, trading::OrderType::Sale);

    REQUIRE(pool.GetBalance(vasya_id) == -200.0);
    REQUIRE(pool.GetBalance(petya_ip) == +200.0);
}

TEST_CASE("Matching Sale") {
    trading::TradingPool pool;

    auto vasya_id = pool.AddClient("vasia");
    auto petya_ip = pool.AddClient("petya");
    auto arman_ip = pool.AddClient("arman");

    pool.Submit({0, vasya_id, 100, 2}, trading::OrderType::Buy);
    pool.Submit({0, petya_ip, 102, 4}, trading::OrderType::Buy);
    pool.Submit({0, arman_ip, 99, 3}, trading::OrderType::Buy);
    pool.Submit({0, petya_ip, 98, 10}, trading::OrderType::Sale);

    REQUIRE(pool.GetBalance(vasya_id) == - 100 * 2);
    REQUIRE(pool.GetBalance(petya_ip) == + 99 * 3 + 100 * 2);
    REQUIRE(pool.GetBalance(arman_ip) == - 99 * 3);
}

TEST_CASE("Matching Buy") {
    trading::TradingPool pool;

    auto vasya_id = pool.AddClient("vasia");
    auto petya_ip = pool.AddClient("petya");
    auto arman_ip = pool.AddClient("arman");

    pool.Submit({0, vasya_id, 100, 2}, trading::OrderType::Sale);
    pool.Submit({0, petya_ip, 102, 4}, trading::OrderType::Sale);
    pool.Submit({0, arman_ip, 99, 3}, trading::OrderType::Sale);
    pool.Submit({0, petya_ip, 103, 10}, trading::OrderType::Buy);

    REQUIRE(pool.GetBalance(vasya_id) == + 100 * 2);
    REQUIRE(pool.GetBalance(petya_ip) == - 99 * 3 - 100 * 2);
    REQUIRE(pool.GetBalance(arman_ip) == + 99 * 3);
}

TEST_CASE("More matching") {
    trading::TradingPool pool;

    auto vasya_id = pool.AddClient("vasia");
    auto petya_ip = pool.AddClient("petya");
    auto arman_ip = pool.AddClient("arman");
    auto danil_ip = pool.AddClient("danil");

    pool.Submit({0, vasya_id, 100, 2}, trading::OrderType::Buy);
    pool.Submit({0, vasya_id, 101, 1}, trading::OrderType::Buy);
    pool.Submit({0, petya_ip, 102, 4}, trading::OrderType::Buy);
    pool.Submit({0, petya_ip, 103, 2}, trading::OrderType::Buy);
    pool.Submit({0, arman_ip, 99, 3}, trading::OrderType::Buy);
    pool.Submit({0, arman_ip, 97, 10}, trading::OrderType::Buy);

    auto leonid_id = pool.AddClient("leonid");
    auto sasha_id = pool.AddClient("sasha");

    pool.Submit({0, leonid_id, 99, 3}, trading::OrderType::Sale);
    pool.Submit({0, sasha_id, 100, 2}, trading::OrderType::Sale);
    pool.Submit({0, sasha_id, 98, 1}, trading::OrderType::Sale);
    pool.Submit({0, leonid_id, 97, 2}, trading::OrderType::Sale);

    REQUIRE(pool.GetBalance(leonid_id) == 2 * 103 + 102 * 1 + 101 * 1 + 100 * 1);
    REQUIRE(pool.GetBalance(sasha_id) == 2 * 102 + 102 * 1);
} 