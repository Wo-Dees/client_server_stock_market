#pragma once

#include <string>

namespace trading {

class Client {
private:
    std::size_t id_;
    std::string name_;
    double balance_;
public:
    Client() = default;

    explicit Client(std::size_t id, std::string name) noexcept : id_(id), name_(std::move(name)), balance_(0) {}

    double GetBalance() const noexcept {
        return balance_;
    }
    
    void ChangeBalance(double change) noexcept {
        balance_ += change;
    }
};

} // namespace trading