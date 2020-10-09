#pragma once

#include <climits>
#include <vector>
#include "./data.h"

class LSH
{
private:
    int calculate_a(int x);
    int calculate_h();

public:
    int k, L, N;
    Data &data;
    uint32_t w, m, M;
    std::vector<int> a, H, g;

    LSH(int k, int L, int N, Data &data, uint32_t w = 100, uint32_t m = UINT32_MAX - 4);
    ~LSH();

    int Run();
};
