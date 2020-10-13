#pragma once

#include <list>
#include <vector>
#include <cmath>

#include "./data.h"

class hashTable
{
private:
    int bucketNum;
    std::list<int> * table;
    std::vector<uint32_t> md;
    int k, L, N;
    Data &data;
    uint32_t w, m, M;

public:

    hashTable(int k, Data &data, uint32_t w = 52, uint32_t m = uint32_t(pow(2, 30) - 5));
    ~hashTable();
    void insertItem();
    void printHashTable();

    void calculate_s(std::vector<std::vector<int>> &S);
    uint32_t calculate_h(const std::vector<uint8_t> &x, const std::vector<int> &s);
    int calculate_a(const uint8_t &xi, const int &si);
    void hashData();
};