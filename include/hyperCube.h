#include <list>
#include <unordered_set>
#include <vector>

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

    void hashData();

public:
    hyperCube(int R, int indexSize, Data &data, int k, int d, uint32_t w = 52);
    ~hyperCube();
    int hyperCubeRun();
    void hyperCubeInsert(std::string s);
    std::list<std::string> hammingDist(std::string s);
};