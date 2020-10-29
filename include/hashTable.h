#pragma once

#include <vector>
#include <functional>
#include <tuple>

class hashTable
{
public:
    int indexSize;
    std::vector<std::vector<int>> S;
    std::vector<std::vector<std::tuple<uint32_t, int, std::reference_wrapper<std::vector<uint8_t>>>>> table;

    hashTable(int indexSize, int k, int d, int w);
    ~hashTable();

    void calculate_s(std::vector<std::vector<int>> &S, int k, int d, int w);
    void insertItem(uint32_t g, int index, std::vector<uint8_t> &point);

    std::vector<std::pair<int, std::reference_wrapper<std::vector<uint8_t>>>>
    getItems(const uint32_t &g);
};