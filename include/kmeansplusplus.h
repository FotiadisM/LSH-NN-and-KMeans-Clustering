#pragma once

#include <iostream>
#include <vector>

#include "./LSH.h"
#include "./hyperCube.h"

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
    int nClusters;
    int lsh_k, L;          // for lsh
    int cube_k, M, probes; // for hypercube
    int minChange = 0;
    Method method;
    std::vector<std::vector<uint8_t>> centroids;
    Data &data;
    LSH *lsh;
    HyperCube *cube;

    void initCentroids();
    uint32_t minDistancefromCentroids(const std::vector<uint8_t> &point);
    int findNextCentroid(const std::vector<double> &P, const double x); // used only for initalization
    int minCentroid(const std::vector<uint8_t> &point);

    std::vector<std::vector<int>> LloydsClustering();
    std::vector<std::vector<int>> LSHClustering();
    std::vector<std::vector<int>> HyperCubeClustering();

public:
    kmeansplusplus(const int &clusters, Data &data);
    kmeansplusplus(const int &clusters, const int &lsh_k, const int &L, Data &data);
    kmeansplusplus(const int &clusters, const int &cube_k, const int &M, const int &probes, Data &data);
    kmeansplusplus(const int &clusters, const int &lsh_k, const int &L, const int &cube_k, const int &M, const int &probes, Data &data);
    ~kmeansplusplus();

    int Run();
};