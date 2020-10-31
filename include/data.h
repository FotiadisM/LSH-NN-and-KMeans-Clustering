#pragma once

#include <fstream>
#include <vector>

class Data
{
private:
    int EuclideanDistance(std::vector<uint8_t> &p1, std::vector<uint8_t> &p2);
    static int ManhattanDistance(const std::vector<uint8_t> &p1, const std::vector<uint8_t> &p2);
public:
    int n; // number of data
    int d; // dimension
    std::vector<std::vector<uint8_t>> data;
    std::vector<std::vector<uint8_t>> queries;

    Data();

    int InitMnistDataSet(std::ifstream &inputFile);
    int ReadQueryFile(std::ifstream &queryFile);

    int (*distanceFunction)(const std::vector<uint8_t> &p1, const std::vector<uint8_t> &p2);

    // std::vector<std::pair<int, std::vector<uint8_t>>> 
    // RangeSearch2(std::vector<uint8_t> query, float R);

    std::vector<std::vector<uint8_t>>
    RangeSearch(std::vector<uint8_t> query, float R);

    std::vector<std::pair<int, int>>
    RangeSearch2(std::vector<uint8_t> query, float R);

    std::vector<std::pair<int, int>> GetClosestNeighbors(const std::vector<uint8_t> &query, const std::vector<std::pair<int, std::vector<uint8_t>>> &data, const int &N);
    std::vector<std::pair<int, int>> BruteFroceNeighbors(const std::vector<uint8_t> &query, const int &N);
};
