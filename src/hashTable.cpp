#include <iostream>

#include "../include/hashTable.h"

using namespace std;

hashTable::hashTable(int indexSize, int k, int d, uint32_t w, uint32_t m)
    : indexSize(indexSize), k(k), d(d)
{
    this->M = uint32_t(pow(2, 32 / this->k));

    this->md.resize(this->d, 0);
    this->md[1] = this->m % this->M;

    this->table.resize(indexSize);
    this->calculate_s(this->S, k, d, w);
}

hashTable::~hashTable() {}

uint32_t hashTable::calculate_h(const vector<uint8_t> &x, const vector<int> &s)
{
    uint32_t h = uint32_t(calculate_a(x[this->d - 1], s[this->d - 1])) % this->M;

    for (int i = this->d - 2; i >= 0; i--)
    {
        if (this->md[this->d - 1 - i] == 0)
        {
            this->md[this->d - 1 - i] = (this->md[this->d - 2 - i] * this->md[1]) % this->M;
        }

        int a = calculate_a(x[i], s[i]);
        if (a != 0) // saving some compute time
        {
            h += (((a % this->M) * this->md[this->d - 1 - i]) % this->M) % this->M;
        }
    }

    return h % this->M;
}

int hashTable::calculate_a(const uint8_t &xi, const int &si)
{
    return floor(double((int(xi) - si)) / double(this->w));
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