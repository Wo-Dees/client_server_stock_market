#pragma once

#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <optional>
#include <unordered_set>

class Server {
public:
    Server(boost::asio::io_context& io_context, std::uint16_t port);

    void Acync_accept();

private:
    std::optional<boost::asio::ip::tcp::socket> socket_;
    boost::asio::io_context& io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    // std::unordered_set<std::shared_ptr<session>> clients_;
};