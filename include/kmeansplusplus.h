#pragma once

#include <iostream>
#include <vector>

#include "./data.h"

class kmeansplusplus
{
private:
    int clusters;
    std::vector<std::vector<uint8_t>> centroids;
    Data &data;

    void initCentroids();
    uint32_t minDfromInitialCentroids(const std::vector<uint8_t> &point, const int &index);
    int findNextCentroid(std::vector<uint32_t> &P, const uint32_t x);

public:
    kmeansplusplus(const int &clusters, Data &data);
    ~kmeansplusplus();
};