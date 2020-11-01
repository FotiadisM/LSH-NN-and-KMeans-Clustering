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
};

class kmeansplusplus
{
private:
    int nClusters;
    bool complete;
    int lsh_k, L;          // for lsh
    int cube_k, M, probes; // for hypercube
    int minChange = 0;
    int maxIterations = 90;
    Method method;
    Data &data;
    LSH *lsh = nullptr;
    HyperCube *cube = nullptr;
    std::vector<std::vector<uint8_t>> centroids;

    void initCentroids();
    uint32_t minDistancefromCentroids(const std::vector<uint8_t> &point);
    int findNextCentroid(const std::vector<double> &P, const double x); // used only for initalization
    int median(std::vector<uint8_t> &v);
    int minCentroid(const std::vector<uint8_t> &point);
    int nextCentroid(const std::vector<uint8_t> &point);
    void print(const std::vector<std::vector<int>> &clusters, std::ofstream &outputFile, int64_t time, std::vector<double> silouette);

    std::vector<std::vector<int>> LloydsClustering();
    std::vector<std::vector<int>> LSHClustering();
    std::vector<std::vector<int>> HyperCubeClustering();

    std::vector<double> Silouette(std::vector<std::vector<int>> clusters);

public:
    kmeansplusplus(const int &clusters, const bool &complete, Data &data);
    kmeansplusplus(const int &clusters, const bool &complete, const int &lsh_k, const int &L, Data &data);
    kmeansplusplus(const int &clusters, const bool &complete, const int &cube_k, const int &M, const int &probes, Data &data);
    ~kmeansplusplus();

    int Run(std::ofstream &outputFile);
};