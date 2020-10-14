#pragma once

#include <fstream>
#include <vector>

class Data
{
private:
public:
    int n; // number of data
    int d; // dimension
    std::vector<std::vector<uint8_t>> data;

    int InitMnistDataSet(std::ifstream &inputFile);

    int EuclideanDistance(std::vector<uint8_t> &p1, std::vector<uint8_t> &p2);
    int ManhattanDistance(const std::vector<uint8_t> &p1, const std::vector<uint8_t> &p2);
    std::vector<uint8_t> GetClosestNeighbors(const std::vector<uint8_t> &point, const std::vector<std::vector<uint8_t>> &data, const int &N);
};
