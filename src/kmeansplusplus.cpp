#include <cstdlib>
#include <cmath>
#include <algorithm>

#include "../include/kmeansplusplus.h"

using namespace std;

kmeansplusplus::kmeansplusplus(const int &clusters, Data &data)
    : clusters(clusters), data(data)
{
}

kmeansplusplus::~kmeansplusplus() {}

void kmeansplusplus::initCentroids()
{
    int randomIndex = rand() % this->data.d;

    // picking first centroid at random
    this->centroids.push_back(this->data.data[randomIndex]);

    for (int i = 0; i < this->clusters - 1; i++)
    {
        vector<uint32_t> P(this->data.n + 1); // plus one for P[0] = 0

        P[0] = 0;
        for (int i = 0; i < this->data.n; i++)
        {
            int d = this->minDfromInitialCentroids(this->data.data[i], i);

            (d == 0) ? P[i + 1] = P[i] : P[i + 1] = pow(d, 2) + P[i];
        }

        uint32_t x = uint32_t(rand()) % P[this->data.n];
        this->centroids.push_back(this->data.data[this->findNextCentroid(P, x) - 1]);
    }
}

uint32_t kmeansplusplus::minDfromInitialCentroids(const vector<uint8_t> &point, const int &index)
{
    vector<int> D;

    for (auto &centroid : this->centroids)
    {
        int d = this->data.ManhattanDistance(point, centroid);
        if (d != 0) //if the point is not a centroid, used Only when initializing when centroids are actual data points
        {
            D.push_back(this->data.ManhattanDistance(point, centroid));
        }
    }

    return (D.size() == 0) ? 0 : *min_element(begin(D), end(D));
}

int kmeansplusplus::findNextCentroid(vector<uint32_t> &P, const uint32_t x)
{
    for (int i = 1; i < this->data.n; i++)
    {
        if (P[i] != P[i - 1]) // exlude already picked centroids
        {
            if (x <= P[i])
            {
                return i;
            }
        }
    }
}
