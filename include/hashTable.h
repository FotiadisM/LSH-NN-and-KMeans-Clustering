#pragma once

#include <vector>
#include <cmath>
#include <functional>

class hashTable
{
public:
    int indexSize;
    std::vector<std::vector<int>> S;
    std::vector<std::vector<std::pair<uint32_t, std::reference_wrapper<std::vector<uint8_t>>>>> table;

    std::vector<uint32_t> md;
    uint32_t w, m, M;
    int k, d;

    hashTable(int indexSize, int k, int d, uint32_t w = 52, uint32_t m = uint32_t(pow(2, 30) - 5));
    ~hashTable();


    void calculate_s(std::vector<std::vector<int>> &S, int k, int d, int w);
    uint32_t calculate_h(const std::vector<uint8_t> &x, const std::vector<int> &s);
    int calculate_a(const uint8_t &xi, const int &si);
    void insertItem(uint32_t &g, std::vector<uint8_t> &point);
    std::vector<std::reference_wrapper<std::vector<uint8_t>>> getItems(const uint32_t &g);
};