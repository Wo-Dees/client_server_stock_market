#include <boost/asio/io_context.hpp>
#include <server.hpp>
#include <system_error>
#include <session.hpp>

Server::Server(boost::asio::io_context& io_context, std::uint16_t port) : io_context_(io_context),
    acceptor_(io_context_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {
}

void Server::Acync_accept() {
    socket_.emplace(io_context_);

    acceptor_.async_accept(*socket_, [&](std::error_code error){
        auto client = std::make_shared<Session>(std::move(*socket));
        
        Acync_accept();
    });
}