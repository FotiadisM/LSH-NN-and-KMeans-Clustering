#pragma once

#include <fstream>
#include <vector>

class Data
{
private:
    int EuclideanDistance(std::vector<uint8_t> &p1, std::vector<uint8_t> &p2);
    static int ManhattanDistanceNewSpace(const std::vector<uint16_t> &p1, const std::vector<uint16_t> &p2);

public:
    int n; // number of data
    int d; // dimension
    int newSpaced;
    std::vector<std::vector<uint8_t>> data;
    std::vector<std::vector<uint8_t>> queries;

    std::vector<std::vector<uint16_t>> newSpaceData;
    std::vector<std::vector<uint16_t>> newSpaceQueries;

    std::vector<std::vector<int>> classificationClusters;

    Data();
    
    static int ManhattanDistance(const std::vector<uint8_t> &p1, const std::vector<uint8_t> &p2);

    int InitMnistDataSet(std::ifstream &inputFile);
    int InitMnistDataSetNewSpace(std::ifstream &inputFile);
    int InitDataSetClassification(std::ifstream &inputFile);

    int ReadQueryFile(std::ifstream &queryFile);
    int ReadQueryFileNewSpace(std::ifstream &queryFile);

    int (*distanceFunction)(const std::vector<uint8_t> &p1, const std::vector<uint8_t> &p2);
    int (*distanceFunctionNewSpace)(const std::vector<uint16_t> &p1, const std::vector<uint16_t> &p2);

    std::vector<std::pair<int, int>>
    RangeSearch(std::vector<uint8_t> query, float R);

    std::vector<std::pair<int, int>> GetClosestNeighbors(const std::vector<uint8_t> &query, const std::vector<std::pair<int, std::vector<uint8_t>>> &data, const int &N);
    std::vector<std::pair<int, int>> BruteForceNeighbors(const std::vector<uint8_t> &query, const int &N);
    std::vector<std::pair<int, int>> BruteForceNeighborsNewSpace(const std::vector<uint16_t> &query, const int &N);
};
