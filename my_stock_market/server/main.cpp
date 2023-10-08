#include <boost/asio.hpp>
#include <boost/asio/thread_pool.hpp>
#include <server.hpp>
#include <string>

int RunStockMarket(std::uint16_t port) {
    boost::asio::io_context io_context;
    Server srv(io_context, port);
    srv.Acync_accept();
    io_context.run();
    return 0;
}

int main() {
    return RunStockMarket(5555);
}