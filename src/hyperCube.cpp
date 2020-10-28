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
    cout << "i do nothing" << endl;
}


f::~f()
{

}


int f::calculate_f(std::string key)
{
    // leave to see if h produces random numbers
    cout << " string " << key  << endl;
    int num;

    if (this->setOfZeros.find(key) != this->setOfZeros.end())
        return 0;
    else if (this->setOfOnes.find(key) != this->setOfOnes.end())
        return 1;
    else {
        num = rand() % 2;
        if (num == 0) {
            this->setOfZeros.insert(key);
            return 0;
        }
        else {
            this->setOfOnes.insert(key);
            return 1;
        }
    }

    return -1;
}


// k == d' if i remember correctly
hyperCube::hyperCube(int R, int indexSize, Data &data, int k, int d, uint32_t w)
    : R(R), indexSize(indexSize), k(k), d(d), w(w), data(data)
{
    this->M = uint32_t(pow(2, 32 / this->k));

    this->ht = new hashTable(pow(2, k), k, d, w);
    
    // initialize array of f functions
    for (int i=0; i<k; i++) {
        f* f_instance = new f();
        this->fTable.push_back(f_instance); 
    }
}


hyperCube::~hyperCube()
{

}


int hyperCube::hyperCubeRun(const vector<uint8_t> &query, ofstream &outputFile)
{
    hashData();

    if (exec_query(query, outputFile) == -1)
    {
        cerr << "Run::exec_query() failed" << endl;
        return 0;
    }

    return 0;

    // string str = "001100";
    // list<string> l = hammingDist(str);
    // list<string>::iterator it;
    // for (it=l.begin(); it!=l.end(); ++it)
    //     cout << *it << endl;
    // f* function = new f();
    // function->calculate_f(str);
}


void hyperCube::hashData()
{
    // s = s + std::to_string(1);
    std::string s;
    for (int j = 0; j < this->data.n; j++) {
        s="";
        for (int i = 0; i < this->k; i++)
            s = s + std::to_string(this->fTable[i]->calculate_f(std::to_string(this->ht->calculate_h(this->data.data[j], this->ht->S[i]))));

        cout << "------------------------------" << endl;

        this->hyperCubeInsert(s, this->data.data[j]);
    }
}


void hyperCube::hyperCubeInsert(const std::string &s, std::vector<uint8_t> &point)
{
    cout << "String is : " << s << endl;

    // uint32_t m =static_cast<uint32_t>(std::stoul(s));
    // cout << m << endl;
    std::bitset<8> bits(s);
    uint32_t m = bits.to_ulong();
    std::cout << m << std::endl;
    this->ht->insertItem(m, point);
}


int hyperCube::exec_query(const std::vector<uint8_t> &query, std::ofstream &outputFile)
{

    int M = 100; // the limit of the search
    int counter = 0;

    std::string s = "";

    for (int i = 0; i < this->k; i++)
        s = s + std::to_string(this->fTable[i]->calculate_f(std::to_string(this->ht->calculate_h(query, this->ht->S[i]))));

    std::bitset<8> bits(s);
    uint32_t m = bits.to_ulong();
    std::cout << "lol n LOLOLOLLOLOLO " << m << std::endl;

    // this gives me the list of items in the bucket of the query
    vector<vector<uint8_t>> possible_neighbors;
    vector<pair<int, vector<uint8_t>>> actual_neigbors;

    for (auto &image : this->ht->getItems(m))
    {
        possible_neighbors.push_back(image);
    }

    actual_neigbors = this->data.GetClosestNeighbors(query, possible_neighbors, 50);

    for (auto &neighbor : actual_neigbors)
    {
        outputFile << "Distance: " << neighbor.first << endl;
    }


    // search the list of buckets and the list of the other buckets etc

    // for (int i=0; i<M; i++) {
        
    // }
    return 1;
}


list<string> hyperCube::hammingDist(std::string s)
{
    list<string> l;

    cout << "initial hamming string : " << s << endl;

    for (int i=0; i < (int)s.size(); i++) {
        if (s[i] == '0')
            s[i] = '1';
        else 
            s[i] = '0';
        
        l.push_back(s);

        if (s[i] == '0')
            s[i] = '1';
        else 
            s[i] = '0';
    }

    return l;
}