#pragma once

#include <fstream>
#include <vector>

class Data
{
public:
    int n; // number of data
    int d; // dimension
    std::vector<std::vector<uint8_t>> data;
    std::vector<uint8_t> query;

    int InitMnistDataSet(std::ifstream &inputFile);
    int ReadQueryFile(std::ifstream &queryFile);

    int EuclideanDistance(std::vector<uint8_t> &p1, std::vector<uint8_t> &p2);
    int ManhattanDistance(const std::vector<uint8_t> &p1, const std::vector<uint8_t> &p2);
    std::vector<std::vector<uint8_t>> RangeSearch(std::vector<uint8_t> query, float R);

    std::vector<std::pair<int, std::vector<uint8_t>>>
    GetClosestNeighbors(const std::vector<uint8_t> &point, const std::vector<std::vector<uint8_t>> &data, const int &N);

    std::vector<std::pair<int, int>>
    GetClosestNeighbors2(const std::vector<uint8_t> &query, const std::vector<std::vector<uint8_t>> &data, const int &N);
};
