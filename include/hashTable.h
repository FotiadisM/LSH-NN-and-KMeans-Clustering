#pragma once

#include <vector>
#include <functional>

class BucketNode
{
public:
    uint32_t g;
    std::vector<uint8_t> &point;

    BucketNode(uint32_t &mg, std::vector<uint8_t> &mpoint);
    ~BucketNode();
};

class hashTable
{
private:
    int indexSize;
    std::vector<std::vector<BucketNode *>> table;

public:
    std::vector<std::vector<int>> S;

    hashTable(int indexSize, int k, int d, int w);
    ~hashTable();

    void calculate_s(std::vector<std::vector<int>> &S, int k, int d, int w);
    void insertItem(uint32_t &g, std::vector<uint8_t> &point);
    std::vector<std::vector<uint8_t>> getItems(uint32_t &g);
};