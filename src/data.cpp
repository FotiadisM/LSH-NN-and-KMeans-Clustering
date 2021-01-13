#include <iostream>
#include <queue>
#include <cmath>
#include <functional>

#include "../include/data.h"

using namespace std;

Data::Data()
{
    this->distanceFunction = &(this->ManhattanDistance);
    this->distanceFunctionNewSpace = &(this->ManhattanDistanceNewSpace);
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
    int x = __builtin_bswap32(a);

    inputFile.read((char *)(&a), sizeof(a));
    if (!inputFile)
    {
        cerr << "Input file io error" << endl;
        return -1;
    }
    int y = __builtin_bswap32(a);

    this->d = x * y;

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


int Data::InitMnistDataSetNewSpace(std::ifstream &inputFile)
{
    int32_t a = 0;
    uint16_t b = 0;

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
    int x = __builtin_bswap32(a);

    inputFile.read((char *)(&a), sizeof(a));
    if (!inputFile)
    {
        cerr << "Input file io error" << endl;
        return -1;
    }
    int y = __builtin_bswap32(a);

    this->newSpaced = x * y;

    for (int i = 0; i < this->n; i++)
    {
        vector<uint16_t> image;

        for (int j = 0; j < this->newSpaced; j++)
        {
            inputFile.read((char *)(&b), sizeof(b));
            if (!inputFile)
            {
                cerr << "read() from input file failed" << endl;
                return -1;
            }
            image.push_back(b);
        }
        this->newSpaceData.push_back(image);
    }

    // for (int i = 0; i < this->n; i++){

    // }

    return 0;
}


int Data::InitDataSetClassification(std::ifstream &inputFile)
{
    int32_t a = 0;
    int dimensions[10];

    for (int i=0; i<=9; i++) {
        inputFile.read((char *)(&a), sizeof(a));
        if (!inputFile)
        {
            cerr << "Input file io error" << endl;
            return -1;
        }
        dimensions[i] = a;
    }

    int toggle = 0;
    vector<vector<int>> temp(10);
    int j=0;

    for (int i=0; i<this->n; i++) {

        inputFile.read((char *)(&a), sizeof(a));
        if (!inputFile)
        {
            cerr << "Input file io error" << endl;
            return -1;
        }

        temp[toggle].push_back(a);
        j++;
        if ( j == dimensions[toggle] ) {
            toggle++;
            j=0;
        }

    }

    this->classificationClusters = temp;

    // for (int i=0; i<10; i++) {
    //     for (int j=0; j<this->classificationClusters[3].size(); j++) {
    //         printf("%d\n",this->classificationClusters[3][j]);
    //     }
    // }
    return 0;
}












int Data::ReadQueryFile(std::ifstream &queryFile)
{
    int count = 0;
    uint8_t b;
    vector<uint8_t> point(this->d);

    while (1)
    {
        queryFile.read((char *)(&b), sizeof(b));
        if (queryFile.eof())
        {
            if (count != 0)
            {
                cerr << "Corupter query file" << endl;
                return -1;
            }
            break;
        }

        point[count] = b;
        if (++count == this->d)
        {
            this->queries.push_back(point);
            count = 0;
        }
    }

    return 0;
}


int Data::ReadQueryFileNewSpace(std::ifstream &queryFile)
{
    int count = 0;
    uint16_t b;
    vector<uint16_t> point(this->newSpaced);

    while (1)
    {
        queryFile.read((char *)(&b), sizeof(b));
        if (queryFile.eof())
        {
            if (count != 0)
            {
                cerr << "Corupter query file" << endl;
                return -1;
            }
            break;
        }

        point[count] = b;
        if (++count == this->newSpaced)
        {
            this->newSpaceQueries.push_back(point);
            count = 0;
        }
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

    for (int i = 0; i < int(p1.size()); i++)
    {
        d += abs(p2[i] - p1[i]);
    }

    return d;
}

int Data::ManhattanDistanceNewSpace(const std::vector<uint16_t> &p1, const std::vector<uint16_t> &p2)
{
    int d = 0;

    for (int i = 0; i < int(p1.size()); i++)
    {
        d += abs(p2[i] - p1[i]);
    }

    return d;
}

vector<pair<int, int>> Data::RangeSearch(vector<uint8_t> query, float R)
{
    vector<pair<int, int>> result;

    for (int i = 0; i < this->n; i++)
    {
        int d = this->distanceFunction(this->data[i], query);
        if (d < R)
        {
            result.emplace_back(d, i);
        }
    }

    return result;
}

vector<pair<int, int>> Data::GetClosestNeighbors(const vector<uint8_t> &query, const vector<pair<int, vector<uint8_t>>> &data, const int &N)
{
    vector<pair<int, int>> result;

    auto cmp = [](pair<int, int> left, pair<int, int> right) {
        return left.first > right.first;
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);

    for (int i = 0; i < int(data.size()); i++)
    {
        if (this->data[i] != query)
            q.push(make_pair(this->distanceFunction(data[i].second, query), data[i].first));
    }

    int min = (N < int(q.size())) ? N : q.size();

    for (int i = 0; i < min; i++)
    {
        result.push_back(q.top());
        q.pop();
    }

    return result;
}

vector<pair<int, int>> Data::BruteForceNeighbors(const vector<uint8_t> &query, const int &N)
{
    vector<pair<int, int>> result;

    auto cmp = [](pair<int, int> left, pair<int, int> right) {
        return left.first > right.first;
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);

    for (int i = 0; i < int(this->data.size()); i++)
    {
        if (this->data[i] != query)
            q.push(make_pair(this->distanceFunction(this->data[i], query), i));
    }

    int min = (N < int(q.size())) ? N : q.size();

    for (int i = 0; i < min; i++)
    {
        result.push_back(q.top());
        q.pop();
    }

    return result;
}

vector<pair<int, int>> Data::BruteForceNeighborsNewSpace(const vector<uint16_t> &query, const int &N)
{
    vector<pair<int, int>> result;

    auto cmp = [](pair<int, int> left, pair<int, int> right) {
        return left.first > right.first;
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);

    for (int i = 0; i < int(this->newSpaceData.size()); i++)
    {
        if (this->newSpaceData[i] != query)
            q.push(make_pair(this->ManhattanDistanceNewSpace(this->newSpaceData[i], query), i));
    }

    int min = (N < int(q.size())) ? N : q.size();

    for (int i = 0; i < min; i++)
    {
        result.push_back(q.top());
        q.pop();
    }

    return result;
}
