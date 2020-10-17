#pragma once

#include <vector>
#include <functional>

class hashTable
{
public:
    int indexSize;
    std::vector<std::vector<int>> S;
    std::vector<std::vector<std::pair<uint32_t, std::reference_wrapper<std::vector<uint8_t>>>>> table;

    hashTable(int indexSize, int k, int d, int w);
    ~hashTable();

    void calculate_s(std::vector<std::vector<int>> &S, int k, int d, int w);
    void insertItem(uint32_t &g, std::vector<uint8_t> &point);
    std::vector<std::reference_wrapper<std::vector<uint8_t>>> getItems(const uint32_t &g);
};