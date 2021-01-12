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
    uint32_t calculate_g(const std::vector<uint8_t> &x, hashTable *ht);

    void print(
        std::ofstream &outputFile,
        const int &query,
        std::vector<std::pair<int, int>> lshResult,
        std::vector<std::pair<int, int>> trueResult,
        std::vector<std::pair<int, int>> rangeSearch,
        std::vector<std::pair<int, int>> reducedResult
        );

public:
    LSH(int k, int L, Data &data, uint32_t w = 10000, uint32_t m = pow(2, 30) - 5);
    ~LSH();

    int Run(const std::vector<std::vector<uint8_t>> &queries, std::ofstream &outputFile, const int &N, const int &R);

    std::vector<std::pair<int, int>>
    exec_query(const std::vector<uint8_t> &query, const int &N);
};
