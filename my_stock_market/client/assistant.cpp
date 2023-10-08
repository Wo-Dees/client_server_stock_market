#include <assistant.hpp>
#include <utility>
#include <ostream>
#include <istream>

Assistant::Assistant(std::ostream& os, std::istream& is, std::pair<std::string, std::uint16_t> remote) : output_(os), input_(is), remote_(std::move(remote)) {
}

void Assistant::Greeting() {
    output_ << "Hi, I am Clippy, your personal assistant." << std::endl;
}

void Assistant::Authorization() {
    output_ << "Do you want to register or log in?" << std::endl;
    std::string name, password, request;
    while (true) {
        input_ >> request;
        if (request == "login") {
            input_ >> name >> password;
            // client_.Login(name, password);
            break;
        } else if (request == "register") {
            input_ >> name >> password;
            // client_.Registration(name, password);
            break;
        } else {
            output_ << "Don't correct query, try again." << std::endl;
        }
    }
}

int Assistant::RunContextMenu() {
    output_ << "What would you like to do?" << std::endl;
    std::string request;
    while (true) {
        if (request == "balance") {

        } else if (request == "active orders") {

        } else if (request == "completed transactions") {

        } else if (request == "quotes") {

        } else if (request == "add order") {

        } else if (request == "cancel order") {

        } else if (request == "logout") {
            break;
        } else {
            output_ << "Don't correct query, try again." << std::endl;
        }
    }
    return 0;
}

int Assistant::Run() {
    assert(remote_.has_value());
    Greeting();
    Authorization();
    return RunContextMenu();
}