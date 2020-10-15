#include <iostream>

#include "../include/LSH.h"
#include "../include/hashTable.h"

using namespace std;

LSH::LSH(int k, int L, int N, Data &data, uint32_t w, uint32_t m)
    : k(k), L(L), N(N), data(data), w(w), m(m)
{
    this->M = uint32_t(pow(2, 32 / this->k));

    this->md.resize(this->data.d, 0);
    this->md[1] = this->m % this->M;

    this->tables.resize(this->L, hashTable(this->data.n / 16, this->k, this->data.d, this->w));

    cout << "m: " << this->m << " M: " << this->M << endl;
    cout << this->md.size() << " " << this->md[1] << endl;
}

LSH::~LSH() {}

int LSH::Run(const vector<uint8_t> &query, ofstream &outputFile)
{
    hashData();

    if (exec_query(this->data.data[0], outputFile) == -1)
    {
        cerr << "Run::exec_query() failed" << endl;
        return 0;
    }

    return 0;
}

void LSH::hashData()
{
    for (int i = 0; i < this->L; i++)
    {
        for (int j = 0; j < this->data.n; j++)
        {
            uint32_t g = this->calculate_g(this->data.data[j], this->tables[i].S);

            // store image in HashTables[i][g]
        }
    }
}

uint32_t LSH::calculate_g(const vector<uint8_t> &x, const vector<vector<int>> &S)
{
    uint32_t g = 0;

    for (int i = 0; i < this->k; i++)
    {
        g = g << 32 / this->k;
        g = g | this->calculate_h(x, S[i]);
    }

    return g;
}

uint32_t LSH::calculate_h(const vector<uint8_t> &x, const vector<int> &s)
{
    uint32_t h = uint32_t(calculate_a(x[this->data.d - 1], s[this->data.d - 1])) % this->M;

    for (int i = this->data.d - 2; i >= 0; i--)
    {
        if (this->md[this->data.d - 1 - i] == 0)
        {
            this->md[this->data.d - 1 - i] = (this->md[this->data.d - 2 - i] * this->md[1]) % this->M;
        }

        int a = calculate_a(x[i], s[i]);
        if (a != 0) // saving some compute time
        {
            h += (((a % this->M) * this->md[this->data.d - 1 - i]) % this->M) % this->M;
        }
    }

    return h % this->M;
}

int LSH::calculate_a(const uint8_t &xi, const int &si)
{
    return floor(double((int(xi) - si)) / double(this->w));
}

int LSH::exec_query(const vector<uint8_t> &query, ofstream &outputFile)
{
    vector<vector<uint8_t>> possible_neighbors;
    vector<pair<int, vector<uint8_t>>> actual_neigbors;

    for (auto &table : this->tables)
    {
        uint32_t g = this->calculate_g(query, table.S);

        // possible_neighbors.push_back( fetch from hashtable )
    }

    actual_neigbors = this->data.GetClosestNeighbors(query, this->data.data, this->N);

    for (auto &neighbor : actual_neigbors)
    {
        outputFile << "Distance: " << neighbor.first << endl;
    }

    return 0;
}