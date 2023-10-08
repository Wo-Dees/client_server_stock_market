#include <client.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <utility>

Client::Client() : connection_(io_service_) {}

void Client::Connection(std::pair<std::string, std::uint16_t> remote) {
    boost::asio::ip::tcp::resolver resolver(io_service_);
    boost::asio::ip::tcp::resolver::query dns_query(boost::asio::ip::tcp::v4(), remote.first, std::to_string(remote.second));
    boost::asio::ip::tcp::resolver::iterator addresses = resolver.resolve(dns_query);

    connection_.connect(*addresses);
}