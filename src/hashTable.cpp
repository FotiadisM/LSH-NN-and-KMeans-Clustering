#include <iostream>

#include "../include/hashTable.h"

using namespace std;

hashTable::hashTable(int indexSize, int k, int d, int w)
    : indexSize(indexSize)
{
    this->table.resize(indexSize);
    this->calculate_s(this->S, k, d, w);
}

hashTable::~hashTable()
{
    for (auto &bucket : this->table)
    {
        for (auto &node : bucket)
        {
            delete node;
        }
    }
}

void hashTable::calculate_s(vector<vector<int>> &S, int k, int d, int w)
{
    S.resize(k, vector<int>(d));

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < d; j++)
        {
            S[i][j] = (rand() % w);
        }
    }
}

BucketNode::BucketNode(uint32_t &mg, vector<uint8_t> &mpoint)
    : g(mg), point(mpoint) {}

BucketNode::~BucketNode() {}

void hashTable::insertItem(uint32_t &g, vector<uint8_t> &point)
{
    // this->table[index].push_back(item);
    BucketNode *node = new BucketNode(g, point);

    this->table[g % this->indexSize].push_back(node);

    // this->table[g % this->indexSize].push_back(make_pair(g, point));
}
vector<vector<uint8_t>> hashTable::getItems(uint32_t &g)
{
    vector<vector<uint8_t>> result;

    for (auto &bucket : this->table[g % this->indexSize])
    {
        result.push_back(bucket->point);
    }

    return result;
}