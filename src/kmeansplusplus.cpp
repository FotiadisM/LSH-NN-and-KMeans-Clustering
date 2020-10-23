#include <cstdlib>
#include <cmath>
#include <cstring>
#include <random>
#include <algorithm>

#include "../include/kmeansplusplus.h"

using namespace std;

kmeansplusplus::kmeansplusplus(const int &mClusters, char *m, Data &mData)
    : clusters(mClusters), data(mData)
{
    if (!strcmp(m, "Classic"))
        this->method = _Classic;
    else if (!strcmp(m, "LSH"))
        this->method = _LSH;
    else if (!strcmp(m, "Hypercube"))
        this->method = _Hypercube;
    else if (!strcmp(m, "Complete"))
        this->method = _Complete;
    else
    {
        cout << "Unknown option: " << m << endl;
    }
}

kmeansplusplus::~kmeansplusplus() {}

//lsh
int kmeansplusplus::Run(const int &lsh_k, const int &L)
{
    this->lsh_k = lsh_k;
    this->L = L;

    return 0;
}

//hypercube
int kmeansplusplus::Run(const int &cube_k, const int &M, const int &probes)
{
    this->cube_k = cube_k;
    this->M = M;
    this->probes = probes;

    return 0;
}

//complete
int kmeansplusplus::Run(const int &lsh_k, const int &L, const int &cube_k, const int &M, const int &probes)
{
    this->lsh_k = lsh_k;
    this->L = L;
    this->cube_k = cube_k;
    this->M = M;
    this->probes = probes;

    this->initCentroids();

    //do until change very small ? how to count change ? what small means
    // assign each point to closest centroid
    // for every centroid find mean distance and move it ? for every centroid return total distance moved

    return 0;
}

void kmeansplusplus::initCentroids()
{
    vector<int> centroidIndexes(this->clusters); // storing points that are picked to be ceontroids so as not to be reused

    // picking first centroid at random
    centroidIndexes.push_back(rand() % this->data.n);
    this->centroids.push_back(this->data.data[centroidIndexes[0]]);
    cout << centroidIndexes[0] << endl;

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
            double Di = double(this->minDistancefromCentroids(this->data.data[j]));

            P[j] = pow(Di / maxDi, 2) + P[j - 1]; // overflow!!, Di/maxDi??

            // cout << j << " " << Di << " " << P[j] << endl;
        }

        // double x = double(rand()) % P[this->data.n];

        uniform_real_distribution<double> unif(double(0), P[this->data.n]);
        default_random_engine re;
        double x = unif(re);

        cout << x << endl;

        centroidIndexes.push_back(this->findNextCentroid(P, x, centroidIndexes) - 1);
        this->centroids.push_back(this->data.data[centroidIndexes[i]]);
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

int kmeansplusplus::findNextCentroid(const vector<double> &P, const double x, const vector<int> centroidIndexes)
{
    for (int i = 1; i <= this->data.n; i++)
    {
        if (find(centroidIndexes.begin(), centroidIndexes.end(), i - 1) == centroidIndexes.end())
        {
            if (x <= P[i])
            {
                // cout << x << " " << P[i] << " " << i - 1 << endl;

                return i;
            }
        }
    }

    return -1;
}
