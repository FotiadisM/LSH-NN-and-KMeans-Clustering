#pragma once

#include <climits>
#include <vector>
#include "./data.h"

class LSH
{
private:
    void calculate_s(std::vector<std::vector<int>> &S);
    int calculate_h(const std::vector<uint8_t> &x, const std::vector<int> &s);
    int calculate_a(const uint8_t &xi, const int &si);

public:
    int k, L, N;
    Data &data;
    uint32_t w, m, M;

    LSH(int k, int L, int N, Data &data, uint32_t w = 52, uint32_t m = UINT32_MAX - 4);
    ~LSH();

    int Run();
};
