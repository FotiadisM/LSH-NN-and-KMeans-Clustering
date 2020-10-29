#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

#include "../include/hyperCube.h"

using namespace std;

/*
 use 2 unordered sets instead of map as they dont add time complexity for searching
 since 2 O(1) == O(1)
 while using less space since they only store the keys and not the values associated with them
*/

f::f()
{
    // cout << "i do nothing" << endl;
}

f::~f()
{
}

int f::calculate_f(std::string key)
{
    // leave to see if h produces random numbers
    cout << " string " << key << endl;
    int num;

    if (this->setOfZeros.find(key) != this->setOfZeros.end())
        return 0;
    else if (this->setOfOnes.find(key) != this->setOfOnes.end())
        return 1;
    else
    {
        num = rand() % 2;
        if (num == 0)
        {
            this->setOfZeros.insert(key);
            return 0;
        }
        else
        {
            this->setOfOnes.insert(key);
            return 1;
        }
    }

    return -1;
}

// k == d' if i remember correctly
HyperCube::HyperCube(int R, int indexSize, Data &data, int k, int d, uint32_t w, uint32_t m)
    : R(R), indexSize(indexSize), k(k), d(d), w(w), data(data)
{
    this->M = uint32_t(pow(2, 32 / this->k));

    this->ht = new hashTable(pow(2, k), k, d, w, m, m / k);

    // initialize array of f functions
    for (int i = 0; i < k; i++)
    {
        f *f_instance = new f();
        this->fTable.push_back(f_instance);
    }
}

HyperCube::~HyperCube()
{
}

int HyperCube::hyperCubeRun(const vector<uint8_t> &query, ofstream &outputFile)
{
    hashData();

    if (exec_query(query, outputFile) == -1)
    {
        cerr << "Run::exec_query() failed" << endl;
        return 0;
    }

    return 0;
}

void HyperCube::hashData()
{
    // s = s + std::to_string(1);
    std::string s;
    for (int j = 0; j < this->data.n; j++)
    {
        s = "";
        for (int i = 0; i < this->k; i++)
            s = s + std::to_string(this->fTable[i]->calculate_f(std::to_string(this->ht->calculate_h(this->data.data[j], this->ht->S[i]))));

        cout << "------------------------------" << endl;

        this->hyperCubeInsert(s, this->data.data[j]);
    }
}

void HyperCube::hyperCubeInsert(const std::string &s, std::vector<uint8_t> &point)
{
    cout << "String is : " << s << endl;

    // uint32_t m =static_cast<uint32_t>(std::stoul(s));
    // cout << m << endl;

    // nopt 8 is bad need to pput something else in therre fuck
    // need to make a function for that because cannot leave it hard coded
    std::bitset<8> bits(s);
    uint32_t m = bits.to_ulong();
    std::cout << m << std::endl;
    this->ht->insertItem(m, 0, point);
}

int HyperCube::exec_query(const std::vector<uint8_t> &query, std::ofstream &outputFile, int M, int probes)
{

    int counter = 0;

    std::string s = "";

    for (int i = 0; i < this->k; i++)
        s = s + std::to_string(this->fTable[i]->calculate_f(std::to_string(this->ht->calculate_h(query, this->ht->S[i]))));

    // use the new function here as well i suppose
    std::bitset<8> bits(s);
    uint32_t m = bits.to_ulong();

    // this gives me the list of items in the bucket of the query
    vector<vector<uint8_t>> possible_neighbors;
    vector<pair<int, vector<uint8_t>>> actual_neigbors;

    list<string> bucketList = HammingDist(s, probes);
    bucketList.push_front(s);
    // list<string>::iterator it;
    // for (it=bucketList.begin(); it!=bucketList.end(); ++it) {
    //     cout << *it << endl;
    // }

    list<string>::iterator it = bucketList.begin();
    while (counter < M && it != bucketList.end())
    {
        std::bitset<8> bits(*it);
        uint32_t m = bits.to_ulong();
        for (auto &image : this->ht->getItems(m))
        {
            possible_neighbors.push_back(image.second);
            counter++;
            if (counter >= M)
                break;
        }
        ++it;
    }

    actual_neigbors = this->data.GetClosestNeighbors(query, possible_neighbors, 50);

    for (auto &neighbor : actual_neigbors)
    {
        outputFile << "Distance: " << neighbor.first << endl;
    }
    return 1;
}

std::string HyperCube::toBinary(int n, int size)
{
    std::string r;
    while (n != 0)
    {
        r = (n % 2 == 0 ? "0" : "1") + r;
        n /= 2;
    }

    while (int(r.size()) < size)
        r = "0" + r;
    return r;
}

int HyperCube::hamming(std::string str1, std::string str2)
{
    int i = 0, count = 0;

    while (str1[i] != '\0')
    {
        if (str1[i] != str2[i])
            count++;
        i++;
    }

    return count;
}

list<string> HyperCube::HammingDist(const std::string s, int probes)
{
    list<string> l;
    std::string curr;
    int level = 1;
    int counter = 0;
    int dist;

    while (1)
    {
        for (int i = 0; i < pow(2, s.size()); i++)
        {
            // cout << toBinary(i, s.size()) << endl;
            curr = toBinary(i, s.size());
            dist = hamming(s, curr);
            if (dist == level)
            {
                l.push_back(curr);
                counter++;
            }

            if (counter >= probes)
                return l;
        }
        level++;
    }
    return l;
}