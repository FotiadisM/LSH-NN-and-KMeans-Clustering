#include <iostream>
#include <chrono>
#include <unordered_set>

#include "../include/LSH.h"
#include "../include/hashTable.h"

using namespace std;

LSH::LSH(int k, int L, Data &data, uint32_t w, uint32_t m)
    : k(k), L(L), data(data), w(w), m(m)
{
    this->M = pow(2, 32 / k);

    this->tables.resize(this->L);
    for (int i = 0; i < L; i++)
    {
        this->tables[i] = new hashTable(this->data.n / 32, this->k, this->data.d, this->w, this->m, this->M);
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

int LSH::Run(const vector<vector<uint8_t>> &queries, ofstream &outputFile, const int &N, const int &R)
{
    for (const auto &query : queries)
    {
        auto start = chrono::high_resolution_clock::now();
        vector<pair<int, int>> lshResult = this->exec_query(query, N);
        auto stop = chrono::high_resolution_clock::now();

        auto tLSH = chrono::duration_cast<chrono::seconds>(stop - start);

        // auto start = chrono::high_resolution_clock::now();
        // vector<pair<int, int>> trueResult = this->data.RangeSearch(query, this->data.data, 1000);
        // auto stop = chrono::high_resolution_clock::now();

        // h RangeSearch prepei na gurnaei vector<pair<int, int>> me to distance, index
        // an mporeis allakse to arxige

        auto tTrue = chrono::duration_cast<chrono::seconds>(stop - start);

        // this->print(lshResult, trueResult, tLSH.count(), tTrue.count)

        // for (auto &point : result)
        // {
        //     outputFile << point.first << " " << point.second << endl;
        // }
        // outputFile << endl;
    }

    return 0;
}

void LSH::hashData()
{
    for (int i = 0; i < this->L; i++)
    {
        for (int j = 0; j < this->data.n; j++)
        {
            uint32_t g = this->calculate_g(this->data.data[j], this->tables[i]);

            this->tables[i]->insertItem(g, j, this->data.data[j]);
        }
    }
}

uint32_t LSH::calculate_g(const vector<uint8_t> &x, hashTable *ht)
{
    uint32_t g = 0;

    for (int i = 0; i < this->k; i++)
    {
        g = g << 32 / this->k;
        g = g | ht->calculate_h(x, ht->S[i]);
    }

    return g;
}

vector<pair<int, int>> LSH::exec_query(const vector<uint8_t> &query, const int &N)
{
    unordered_set<int> pickedPoints;
    vector<pair<int, vector<uint8_t>>> possible_neighbors;

    for (auto &table : this->tables)
    {
        uint32_t g = this->calculate_g(query, table);

        for (auto &point : table->getItems(g))
        {
            if (pickedPoints.find(point.first) == pickedPoints.end()) // exclude duplicate points
            {
                pickedPoints.insert(point.first);
                possible_neighbors.emplace_back(point.first, point.second);
            }
        }
    }

    return this->data.GetClosestNeighbors(query, possible_neighbors, N);
}