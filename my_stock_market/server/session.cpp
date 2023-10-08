#include <session.hpp>

Session::Session(boost::asio::ip::tcp::socket socket) : socket_(std::move(socket)) {}

