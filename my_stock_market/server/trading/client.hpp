#pragma once

#include <cstdint>
#include <string>

class Client {
public:
    Client(std::string name, std::size_t id) : name_(std::move(name)), id_(id), balance_(0) {}

    double GetBalance() const {
        return balance_;
    }

    double GetId() const {
        return id_;
    }

private:
    std::string name_;
    std::size_t id_;
    double balance_;
};