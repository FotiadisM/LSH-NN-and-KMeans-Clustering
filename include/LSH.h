#pragma once

#include <cmath>
#include <vector>

#include "./data.h"
#include "./hashTable.h"

class LSH
{
private:
    int k, L;
    Data &data;
    uint32_t w, m, M;
    std::vector<uint32_t> md; // stores (m^i)modM from i=0 to i = d-1 so as to no recompute
    std::vector<hashTable *> tables;

    void hashData();
    void calculate_s(std::vector<std::vector<int>> &S);
    uint32_t calculate_g(const std::vector<uint8_t> &x, const std::vector<std::vector<int>> &S);
    uint32_t calculate_h(const std::vector<uint8_t> &x, const std::vector<int> &s);
    int calculate_a(const uint8_t &xi, const int &si);

public:
    LSH(int k, int L, Data &data, uint32_t w = 10, uint32_t m = uint32_t(pow(2, 30) - 5));
    ~LSH();

    int Run(const std::vector<uint8_t> &query, std::ofstream &outputFile, const int &N);

    std::vector<std::pair<int, int>>
    exec_query(const std::vector<uint8_t> &query, const int &N);
};
