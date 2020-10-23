#pragma once

#include <iostream>
#include <vector>

#include "./data.h"
#include "./LSH.h"

enum Method
{
    _Classic,
    _LSH,
    _Hypercube,
    _Complete
};

class kmeansplusplus
{
private:
    int clusters;
    int lsh_k, L;          // for lsh
    int cube_k, M, probes; // for hypercube
    Method method;
    std::vector<std::vector<uint8_t>> centroids;
    Data &data;
    LSH *lsh;

    void initCentroids();
    uint32_t minDistancefromCentroids(const std::vector<uint8_t> &point);
    int findNextCentroid(const std::vector<double> &P, const double x); // used only for initalization
    int minCentroid(const std::vector<uint8_t> &point);

public:
    kmeansplusplus(const int &clusters, Data &data);
    kmeansplusplus(const int &clusters, const int &lsh_k, const int &L, Data &data);
    kmeansplusplus(const int &clusters, const int &cube_k, const int &M, const int &probes, Data &data);
    kmeansplusplus(const int &clusters, const int &lsh_k, const int &L, const int &cube_k, const int &M, const int &probes, Data &data);
    ~kmeansplusplus();

    int Run();
};