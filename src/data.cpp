#include <iostream>
#include <queue>
#include <cmath>
#include <functional>

#include "../include/data.h"

using namespace std;

Data::Data()
{
    this->distanceFunction = &(this->ManhattanDistance);
}

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
    cout << "number of images: " << this->n << endl;

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

int Data::ReadQueryFile(std::ifstream &queryFile)
{
    uint8_t b;

    for (int i = 0; i < this->d; i++)
    {
        queryFile.read((char *)(&b), sizeof(b));
        if (!queryFile)
        {
            cerr << "read() from query file failed" << endl;
            return -1;
        }
        this->query.push_back(b);
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

vector<vector<uint8_t>> Data::RangeSearch(vector<uint8_t> query, float R)
{
    vector<vector<uint8_t>> result;

    for (auto &point : data)
    {
        if (this->distanceFunction(point, query) < R)
        {
            result.push_back(point);
        }
    }

    return result;
}

vector<pair<int, vector<uint8_t>>> Data::RangeSearch2(vector<uint8_t> query, float R)
{
    vector<pair<int, vector<uint8_t>>> result;
    int dist;

    for (auto &point : data)
    {
        if ((dist = this->distanceFunction(point, query)) < R)
        {
            result.emplace_back(dist, point);
        }
    }

    return result;
}


vector<pair<int, int>> Data::GetClosestNeighbors(const vector<uint8_t> &query, const vector<pair<int, vector<uint8_t>>> &data, const int &N)
{
    vector<pair<int, int>> result;
    vector<pair<int, int>> costs;

    for (const auto &point : data)
    {
        costs.emplace_back(this->distanceFunction(point.second, query), point.first);
    }

    auto cmp = [](pair<int, int> left, pair<int, int> right) {
        return left.first > right.first;
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);

    for (auto &element : costs)
    {
        q.push(element);
    }

    int min = (N < int(q.size())) ? N : q.size();

    for (int i = 0; i < min; i++)
    {
        result.push_back(q.top());
        q.pop();
    }

    return result;
}
