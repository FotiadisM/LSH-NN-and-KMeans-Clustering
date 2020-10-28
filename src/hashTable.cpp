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

void hashTable::insertItem(uint32_t g, int index, vector<uint8_t> &point)
{
    this->table[g % this->indexSize].emplace_back(g, index, ref(point));
}

vector<pair<int, reference_wrapper<vector<uint8_t>>>> hashTable::getItems(const uint32_t &g)
{
    vector<pair<int, reference_wrapper<vector<uint8_t>>>> result;

    for (auto &bucket : this->table[g % this->indexSize])
    {
        result.emplace_back(get<1>(bucket), get<2>(bucket));
    }

    return result;
}