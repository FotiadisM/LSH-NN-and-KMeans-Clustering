#pragma once

#include <fstream>
#include <vector>

class Data
{
private:
public:
    int n;                                  // number of data
    int d;                                  // dimension
    std::vector<std::vector<uint8_t>> data; // n * d array

    int InitMnistDataSet(std::ifstream &inputFile);
};
