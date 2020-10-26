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

class hyperCube
{
private:
    int R, indexSize, k, d, w;
    Data &data;
    hashTable* ht;
    std::vector<f*> fTable;
    uint32_t M;

    uint32_t calculate_h(const std::vector<uint8_t> &x, const std::vector<int> &s);
    int calculate_a(const uint8_t &xi, const int &si);
    void hashData();

public:
    hyperCube(int R, int indexSize, Data &data, int k, int d, uint32_t w = 52);
    ~hyperCube();
    int hyperCubeRun();
    void hyperCubeInsert(const std::string &s, std::vector<uint8_t> &point);
    std::list<std::string> hammingDist(std::string s);
};