#include <iostream>
#include "../include/hashTable.h"

using namespace std;

hashTable::hashTable(int indexSize, int k, int d, int w)
    : indexSize(indexSize)
{
    this->table.resize(indexSize, vector<int>());
    this->calculate_s(this->S, k, d, w);
}

hashTable::~hashTable()
{
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

void hashTable::insertItem(int index, int item)
{
    this->table[index].push_back(item);
}