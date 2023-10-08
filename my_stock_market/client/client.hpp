#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string>

class Client {
public:
    Client();

    void Connection(std::pair<std::string, std::uint16_t>);

    void Login(std::string name, std::string password);
    void Logout();

    bool Registration(std::string name, std::string password);

    void GetBalance();

    void GetActiveOrders();
    void GetCompletedTransactions();
    void GetQuotes();

    void AddOrder();
    void CancelOrder();
private:
    boost::asio::io_service io_service_;
    boost::asio::ip::tcp::socket connection_;
};