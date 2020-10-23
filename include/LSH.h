#pragma once

#include <cmath>
#include <vector>

#include "./data.h"
#include "./hashTable.h"

class LSH
{
private:
    int k, L, N;
    Data &data;
    uint32_t w, m, M;
    // stores (m^i)modM from i=0 to i = d-1 so as to no recompute
    // std::vector<uint32_t> md;
    std::vector<hashTable *> tables;

    void hashData();
    uint32_t calculate_g(const std::vector<uint8_t> &x, const std::vector<std::vector<int>> &S);

    int exec_query(const std::vector<uint8_t> &query, std::ofstream &outputFile);

public:
    LSH(int k, int L, int N, Data &data, uint32_t w = 52, uint32_t m = uint32_t(pow(2, 30) - 5));
    ~LSH();

    int Run(const std::vector<uint8_t> &query, std::ofstream &outputFile);
};
