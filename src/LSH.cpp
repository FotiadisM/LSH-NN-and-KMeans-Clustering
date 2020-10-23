#include <iostream>

#include "../include/LSH.h"
#include "../include/hashTable.h"

using namespace std;

LSH::LSH(int k, int L, int N, Data &data, uint32_t w, uint32_t m)
    : k(k), L(L), N(N), data(data), w(w), m(m)
{
    // this->M = uint32_t(pow(2, 32 / this->k));

    // this->md.resize(this->data.d, 0);
    // this->md[1] = this->m % this->M;

    this->tables.resize(this->L);
    for (int i = 0; i < L; i++)
    {
        this->tables[i] = new hashTable(this->data.n / 16, this->k, this->data.d, this->w);
    }

    cout << "m: " << this->m << " M: " << this->M << endl;
    // cout << this->md.size() << " " << this->md[1] << endl;
}

LSH::~LSH()
{
    for (int i = 0; i < L; i++)
    {
        delete this->tables[i];
    }
}

int LSH::Run(const vector<uint8_t> &query, ofstream &outputFile)
{
    hashData();

    if (exec_query(query, outputFile) == -1)
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
            uint32_t g = this->calculate_g(this->data.data[j], this->tables[i]->S);

            // store image in HashTables[i][g]
            this->tables[i]->insertItem(g, this->data.data[j]);
        }
    }
}

uint32_t LSH::calculate_g(const vector<uint8_t> &x, const vector<vector<int>> &S)
{
    uint32_t g = 0;

    for (int i = 0; i < this->k; i++)
    {
        g = g << 32 / this->k;
        g = g | this->tables[i]->calculate_h(x, S[i]);
    }

    return g;
}

int LSH::exec_query(const vector<uint8_t> &query, ofstream &outputFile)
{
    vector<vector<uint8_t>> possible_neighbors;
    vector<pair<int, vector<uint8_t>>> actual_neigbors;

    for (auto &table : this->tables)
    {
        uint32_t g = this->calculate_g(query, table->S);

        for (auto &image : table->getItems(g))
        {
            possible_neighbors.push_back(image);
        }
    }

    actual_neigbors = this->data.GetClosestNeighbors(query, possible_neighbors, 50);

    for (auto &neighbor : actual_neigbors)
    {
        outputFile << "Distance: " << neighbor.first << endl;
    }

    return 0;
}