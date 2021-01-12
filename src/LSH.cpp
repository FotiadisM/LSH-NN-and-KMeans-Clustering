#include <iostream>
#include <chrono>
#include <unordered_set>
#include <bits/stdc++.h> 

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

    cout << "Running with w: " << w << " m: " << this->m << " and M: " << this->M << endl;

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
    double tLSH = 0;
    double tTrue = 0;
    double tReduced = 0;
    clock_t start, end;

    double approximationFactorLSH = 0.0;
    double approximationFactorReduced = 0.0;

    for (int i = 0; i < int(queries.size()); i++)
    {
        start = clock();
        vector<pair<int, int>> lshResult = this->exec_query(queries[i], N);
        end = clock();

        tLSH = tLSH + double(end - start) / double(CLOCKS_PER_SEC);

        start = clock();
        vector<pair<int, int>> trueResult = this->data.BruteForceNeighbors(queries[i], N);
        end = clock();

        tTrue = tTrue + double(end - start) / double(CLOCKS_PER_SEC);

        start = clock();
        vector<pair<int, int>> reducedResult = this->data.BruteForceNeighborsNewSpace(data.newSpaceQueries[i], N);
        end = clock();

        tReduced = tReduced + double(end - start) / double(CLOCKS_PER_SEC);
        approximationFactorLSH = approximationFactorLSH + (double)lshResult[0].first / (double)trueResult[0].first;

        approximationFactorReduced = approximationFactorReduced + 
        (double)data.ManhattanDistance(this->data.data[reducedResult[0].second], this->data.data[trueResult[0].second]) / (double)trueResult[0].first;

        this->print(outputFile, i, lshResult, trueResult, this->data.RangeSearch(queries[i], R), reducedResult);
    }

    outputFile << "time Reduced " << tReduced << setprecision(10) << endl;
    outputFile << "time LSH " << tLSH << setprecision(10) << endl;
    outputFile << "time True " << tTrue << setprecision(10) << endl;

    outputFile << "approximation factor LSH : " << approximationFactorLSH / queries.size() << endl;
    outputFile << "approximation factor Reduced : " << approximationFactorReduced / queries.size() << endl;

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
                if (point.second.get() != query)
                    possible_neighbors.emplace_back(point.first, point.second);
            }
        }
    }

    return this->data.GetClosestNeighbors(query, possible_neighbors, N);
}


void LSH::print(ofstream &outputFile, const int &query, vector<pair<int, int>> lshResult, vector<std::pair<int, int>> trueResult, vector<std::pair<int, int>> rangeSearch, vector<std::pair<int, int>> reducedResult)
{
    outputFile << "Query: " << query << endl;

    for (int i = 0; i < int(lshResult.size()); i++)
    {
        outputFile << "nearest neighbor Reduced : " << reducedResult[i].second << endl;
        outputFile << "nearest neighbor LSH: " << lshResult[i].second << endl;
        outputFile << "nearest neighbor True: " << trueResult[i].second << endl;
        outputFile << "distanceReduced: " << data.ManhattanDistance(this->data.data[query], this->data.data[reducedResult[i].second]) << endl;
        outputFile << "distanceLSH: " << lshResult[i].first << endl;
        outputFile << "distanceTrue: " << trueResult[i].first << endl << endl;
    }
}