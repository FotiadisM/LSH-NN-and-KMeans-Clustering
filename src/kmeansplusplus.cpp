#include <cstdlib>
#include <cmath>
#include <cstring>
#include <random>
#include <chrono>
#include <algorithm>

#include "../include/kmeansplusplus.h"

using namespace std;

kmeansplusplus::kmeansplusplus(const int &mClusters, Data &mData)
    : clusters(mClusters), data(mData)
{
    this->method = _Classic;
}

kmeansplusplus::kmeansplusplus(const int &clusters, const int &lsh_k, const int &L, Data &data)
    : clusters(clusters), data(data), lsh_k(lsh_k), L(L)
{
    this->method = _LSH;
}

kmeansplusplus::kmeansplusplus(const int &clusters, const int &cube_k, const int &M, const int &probes, Data &data)
    : clusters(clusters), data(data), cube_k(cube_k), M(M), probes(probes)
{
    this->method = _Hypercube;
}

kmeansplusplus::kmeansplusplus(const int &clusters, const int &lsh_k, const int &L, const int &cube_k, const int &M, const int &probes, Data &data)
    : clusters(clusters), data(data), lsh_k(lsh_k), L(L), cube_k(cube_k), M(M), probes(probes)
{
    this->method = _Complete;
}

kmeansplusplus::~kmeansplusplus() {}

int kmeansplusplus::Run()
{
    this->initCentroids();

    for (int j = 0; j < 10; j++) // while change != minimum or 0, change it later
    {
        vector<vector<int>> clustering(this->clusters); // holds all data points for every centroid

        for (int j = 0; j < this->data.n; j++)
        {
            clustering[this->minCentroid(this->data.data[j])].push_back(j);
        }
    }

    return 0;
}

void kmeansplusplus::initCentroids()
{
    default_random_engine re(chrono::system_clock::now().time_since_epoch().count());

    // picking first centroid at random
    this->centroids.push_back(this->data.data[rand() % this->data.n]);

    for (int i = 1; i < this->clusters; i++)
    {
        double maxDi = 0;
        vector<double> P(this->data.n + 1); // plus one for P[0] = 0

        for (auto &point : this->data.data)
        {
            double Di = double(this->minDistancefromCentroids(point));

            if (Di > maxDi)
                maxDi = Di;
        }

        P[0] = 0;
        for (int j = 1; j <= this->data.n; j++)
        {
            double Di = this->minDistancefromCentroids(this->data.data[j]);

            P[j] = pow(Di / maxDi, 2) + P[j - 1];
        }

        uniform_real_distribution<double> unif(0.0, P[this->data.n]);
        double x = unif(re);

        this->centroids.push_back(this->data.data[this->findNextCentroid(P, x) - 1]);
    }
}

uint32_t kmeansplusplus::minDistancefromCentroids(const vector<uint8_t> &point)
{
    vector<int> D;

    for (auto &centroid : this->centroids)
    {
        D.push_back(this->data.ManhattanDistance(point, centroid));
    }

    return (D.size() == 0) ? 0 : *min_element(begin(D), end(D));
}

int kmeansplusplus::findNextCentroid(const vector<double> &P, const double x)
{
    for (int i = 1; i <= this->data.n; i++)
    {
        if (x <= P[i])
        {
            cout << i - 1 << endl;
            return i;
        }
    }

    return -1;
}

int kmeansplusplus::minCentroid(const vector<uint8_t> &point)
{
    int index, minDistance = INT32_MAX;

    for (int i = 0; i < this->clusters; i++)
    {
        int d = this->data.ManhattanDistance(this->centroids[i], point);
        if (d < minDistance)
        {
            minDistance = d;
            index = i;
        }
    }

    return index;
}