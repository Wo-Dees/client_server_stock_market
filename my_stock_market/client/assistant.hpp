#pragma once

#include <client.hpp>
#include <cstdint>
#include <ostream>
#include <istream>
#include <optional>
#include <ostream>
#include <string>

class Assistant {
public:
    Assistant(std::ostream& os, std::istream& is, std::pair<std::string, std::uint16_t> remote);

    int Run();
    
private:
    void Greeting();
    void Authorization();
    int RunContextMenu();

    Client client_;
    std::ostream& output_;
    std::istream& input_;
    std::optional<std::pair<std::string, std::uint16_t>> remote_;
};