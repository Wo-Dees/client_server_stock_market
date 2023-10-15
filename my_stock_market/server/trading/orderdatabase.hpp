#pragma once 

#include <operation.hpp>

#include <vector>

class DataBase {
public:
    DataBase() = default;

    void Push(const Operation& operation) {
        database_.push_back(operation);
    }
    
private:
    std::vector<Operation> database_;
};