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

    std::vector<hashTable *> tables;

    void hashData();
    uint32_t calculate_g(const std::vector<uint8_t> &x, const std::vector<std::vector<int>> &S);

public:
    LSH(int k, int L, Data &data, uint32_t w = 10, uint32_t m = uint32_t(pow(2, 30) - 5));
    ~LSH();

    int Run(const std::vector<uint8_t> &query, std::ofstream &outputFile, const int &N);

    std::vector<std::pair<int, int>>
    exec_query(const std::vector<uint8_t> &query, const int &N);
};
