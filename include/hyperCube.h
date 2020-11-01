#include <list>
#include <unordered_set>
#include <vector>
#include <string>
#include <chrono>
#include <random>

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
    int k, M, probes, R;
    Data &data;
    hashTable *ht;
    std::vector<f *> fTable;

    uint32_t calculate_h(const std::vector<uint8_t> &x, const std::vector<int> &s);
    int calculate_a(const uint8_t &xi, const int &si);
    std::string toBinary(int n, int size);
    int hamming(std::string str1, std::string str2);
    std::list<std::string> HammingDist(const std::string s, int probes);
    void print(
        std::ofstream &outputFile,
        const int &query,
        std::vector<std::pair<int, int>> cubeResult,
        std::vector<std::pair<int, int>> trueResult,
        const int64_t &tCube, const int64_t &tTrue,
        std::vector<std::pair<int, int>> rangeSearch);

    void hashData();
    void hyperCubeInsert(const std::string &s, int index, std::vector<uint8_t> &point);

public:
    HyperCube(int k, int M, int probes, Data &data, uint32_t w = 10, uint32_t m = pow(2, 30) - 5);
    ~HyperCube();

    int Run(const std::vector<std::vector<uint8_t>> &queries, std::ofstream &outputFileint, const int &N);
    std::vector<std::pair<int, int>> exec_query(const std::vector<uint8_t> &query, const int &N);
};