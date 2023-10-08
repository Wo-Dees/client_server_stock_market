#pragma once

#include <boost/asio.hpp>

class Session {
public:
    Session(boost::asio::ip::tcp::socket socket);

    void Start();

private:
    boost::asio::ip::tcp::socket socket_;
};