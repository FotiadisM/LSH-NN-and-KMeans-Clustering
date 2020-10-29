#include <iostream>
#include <unordered_set>

#include "../include/LSH.h"
#include "../include/hashTable.h"

using namespace std;

LSH::LSH(int k, int L, Data &data, uint32_t w, uint32_t m)
    : k(k), L(L), data(data), w(w), m(m)
{
    this->M = uint32_t(pow(2, 32 / this->k));

    this->md.resize(this->data.d, 0);
    this->md[1] = this->m % this->M;

    this->tables.resize(this->L);
    for (int i = 0; i < L; i++)
    {
        this->tables[i] = new hashTable(this->data.n / 16, this->k, this->data.d, this->w);
    }

    cout << "Running with w: " << w << "m : " << this->m << " and M : " << this->M << endl;

    hashData();
}

LSH::~LSH()
{
    for (int i = 0; i < L; i++)
    {
        delete this->tables[i];
    }
}

int LSH::Run(const vector<uint8_t> &query, ofstream &outputFile, const int &N)
{
    vector<pair<int, int>> result = this->exec_query(query, N);

    for (auto &point : result)
    {
        outputFile << point.first << " " << point.second << endl;
    }
    outputFile << endl;

    return 0;
}

void LSH::hashData()
{
    for (int i = 0; i < this->L; i++)
    {
        for (int j = 0; j < this->data.n; j++)
        {
            uint32_t g = this->calculate_g(this->data.data[j], this->tables[i]->S);

            // store image in HashTables[i][g]
            this->tables[i]->insertItem(g, j, this->data.data[j]);
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

vector<pair<int, int>> LSH::exec_query(const vector<uint8_t> &query, const int &N)
{
    unordered_set<int> pickedPoints;
    vector<vector<uint8_t>> possible_neighbors;

    for (auto &table : this->tables)
    {
        uint32_t g = this->calculate_g(query, table->S);

        for (auto &point : table->getItems(g))
        {
            if (pickedPoints.find(point.first) == pickedPoints.end()) // exclude duplicate points
            {
                pickedPoints.insert(point.first);
                possible_neighbors.push_back(point.second);
            }
        }
    }

    return this->data.GetClosestNeighbors2(query, possible_neighbors, N);
}