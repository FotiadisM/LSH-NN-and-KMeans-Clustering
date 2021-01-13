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
    std::vector<std::vector<uint16_t>> centroidsNewSpace;

    void initCentroids();
    void initCentroidsNewSpace();
    uint32_t minDistancefromCentroids(const std::vector<uint8_t> &point);
    uint32_t minDistancefromCentroidsNewSpace(const std::vector<uint16_t> &point);

    int findNextCentroid(const std::vector<double> &P, const double x); // used only for initalization

    int median(std::vector<uint8_t> &v);
    int medianNewSpace(std::vector<uint16_t> &v);

    int minCentroid(const std::vector<uint8_t> &point);
    int minCentroidNewSpace(const std::vector<uint16_t> &point);

    int nextCentroid(const std::vector<uint8_t> &point);
    int nextCentroidNewSpace(const std::vector<uint16_t> &point);

    void print(const std::vector<std::vector<int>> &clusters, std::ofstream &outputFile, int64_t time, std::vector<double> silouette, std::vector<double> silouetteClassification, std::vector<double> silouetteNewSpace, int64_t newSpaceTime, int obj1, int obj2);

    std::vector<std::vector<int>> LloydsClustering();
    std::vector<std::vector<int>> LloydsClusteringNewSpace();

    std::vector<double> Silouette(std::vector<std::vector<int>> clusters);
    std::vector<double> SilouetteNewSpace(std::vector<std::vector<int>> clusters);

    int objectiveFuntion(std::vector<std::vector<int>> clusters);

    int returnMedian(std::vector<int> clusterIntRepresented);

public:
    kmeansplusplus(const int &clusters, const bool &complete, Data &data);
    ~kmeansplusplus();

    int Run(std::ofstream &outputFile);
};