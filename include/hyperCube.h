#include <list>
#include <unordered_set>
#include <vector>
#include <string>

#include "hashTable.h"
#include "data.h"

class f
{
private:
    std::unordered_set<std::string> setOfZeros;
    std::unordered_set<std::string> setOfOnes;

public:
    f();
    ~f();
    int calculate_f(std::string key);
};

class HyperCube
{
private:
    int R, k, d, w;
    Data &data;
    hashTable *ht;
    std::vector<f *> fTable;
    uint32_t M;

    uint32_t calculate_h(const std::vector<uint8_t> &x, const std::vector<int> &s);
    int calculate_a(const uint8_t &xi, const int &si);
    std::string toBinary(int n, int size);
    int hamming(std::string str1, std::string str2);
    std::list<std::string> HammingDist(const std::string s, int probes);

    void hashData();
    std::vector<std::pair<int, int>> exec_query(const std::vector<uint8_t> &query,const int &N, int M = 10, int probes = 2);
    void hyperCubeInsert(const std::string &s, int index, std::vector<uint8_t> &point);

public:
    HyperCube(int R, Data &data, int k, int d, uint32_t w = 10, uint32_t m = pow(2, 30) - 5);
    ~HyperCube();

    int hyperCubeRun(const std::vector<uint8_t> &query, std::ofstream &outputFileint, const int &N);
};