#include <iostream>

#include "../include/hashTable.h"

using namespace std;

hashTable::hashTable(int indexSize, int k, int d, int w)
    : indexSize(indexSize)
{
    this->table.resize(indexSize);
    this->calculate_s(this->S, k, d, w);
}

hashTable::~hashTable() {}

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

void hashTable::insertItem(uint32_t &g, vector<uint8_t> &point)
{
    this->table[g % this->indexSize].push_back(make_pair(g, ref(point)));
}

vector<reference_wrapper<vector<uint8_t>>> hashTable::getItems(const uint32_t &g)
{
    vector<reference_wrapper<vector<uint8_t>>> result;

    for (auto &bucket : this->table[g % this->indexSize])
    {
        result.push_back(bucket.second);
    }

    return result;
}