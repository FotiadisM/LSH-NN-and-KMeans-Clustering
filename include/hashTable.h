#pragma once

#include <vector>
#include <functional>

#include "./data.h"

class hashTable
{
private:
    int indexSize;
    std::vector<std::vector<int>> table;

public:
    std::vector<std::vector<int>> S;

    hashTable(int indexSize, int k, int d, int w);
    ~hashTable();

    void calculate_s(std::vector<std::vector<int>> &S, int k, int d, int w);
    void insertItem(int index, int item);
};