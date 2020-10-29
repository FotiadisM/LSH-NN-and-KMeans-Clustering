#pragma once

#include <vector>
#include <cmath>
#include <functional>
#include <tuple>

class hashTable
{
private:
    int d;
    uint32_t w, m, M;
    std::vector<uint32_t> md;

    int calculate_a(const uint8_t &xi, const int &si);

public:
    std::vector<std::vector<int>> S;
    std::vector<std::vector<std::tuple<uint32_t, int, std::reference_wrapper<std::vector<uint8_t>>>>> table;

    hashTable(int indexSize, int k, int d, uint32_t w, uint32_t m, uint32_t M);
    ~hashTable();

    void calculate_s(std::vector<std::vector<int>> &S, int k, int d, int w);
    uint32_t calculate_h(const std::vector<uint8_t> &x, const std::vector<int> &s);

    void insertItem(uint32_t g, int index, std::vector<uint8_t> &point);
    std::vector<std::pair<int, std::reference_wrapper<std::vector<uint8_t>>>>
    getItems(const uint32_t &g);
};