#include <iostream>
#include <queue>
#include <cmath>

#include "../include/data.h"

using namespace std;

int Data::InitMnistDataSet(std::ifstream &inputFile)
{
    int32_t a = 0;
    uint8_t b = 0;

    //  magic number
    inputFile.read((char *)(&a), sizeof(a));
    if (!inputFile)
    {
        cerr << "Input file io error" << endl;
        return -1;
    }

    // number of images
    inputFile.read((char *)(&a), sizeof(a));
    if (!inputFile)
    {
        cerr << "Input file io error" << endl;
        return -1;
    }
    // from big endian to low endian
    this->n = __builtin_bswap32(a);

    inputFile.read((char *)(&a), sizeof(a));
    if (!inputFile)
    {
        cerr << "Input file io error" << endl;
        return -1;
    }

    inputFile.read((char *)(&a), sizeof(a));
    if (!inputFile)
    {
        cerr << "Input file io error" << endl;
        return -1;
    }

    this->d = 28 * 28;

    for (int i = 0; i < this->n; i++)
    {
        vector<uint8_t> image;

        for (int j = 0; j < this->d; j++)
        {
            inputFile.read((char *)(&b), sizeof(b));
            if (!inputFile)
            {
                cerr << "read() from input file failed" << endl;
                return -1;
            }
            image.push_back(b);
        }
        this->data.push_back(image);
    }

    return 0;
}

int Data::EuclideanDistance(std::vector<uint8_t> &p1, std::vector<uint8_t> &p2)
{
    int d = 0;

    for (size_t i = 0; i < p1.size(); i++)
    {
        d += pow(p2[i] - p1[i], 2);
    }

    return sqrt(d);
}

int Data::ManhattanDistance(const std::vector<uint8_t> &p1, const std::vector<uint8_t> &p2)
{
    int d = 0;

    for (size_t i = 0; i < p1.size(); i++)
    {
        d += abs(p2[i] - p1[i]);
    }

    return d;
}

vector<uint8_t> Data::GetClosestNeighbors(const vector<uint8_t> &point, const vector<vector<uint8_t>> &data, const int &N)
{
    vector<uint8_t> result;
    vector<pair<int, vector<uint8_t>>> costs;

    for (auto &element : data)
    {
        costs.emplace_back(this->ManhattanDistance(point, element), element);
    }

    auto cmp = [](pair<int, vector<uint8_t>> left, pair<int, vector<uint8_t>> right) {
        return left.first < right.first;
    };
    priority_queue<pair<int, vector<uint8_t>>, vector<pair<int, vector<uint8_t>>>, decltype(cmp)> q(cmp);

    for (auto &element : costs)
    {
        q.push(element);
    }

    // pop from queue and return

    // for (int i = 0; i < N; i++)
    // {
    //     result.push_back((vector<uint8_t>)q.pop().second);
    // }

    return result;
}