#pragma once

#include <fstream>

enum Mode
{
    _lsh,
    _cube,
    _cluster
};

class Input
{
private:
    char *getCmdOption(char **begin, char **end, const std::string &option);

public:
    int nClusters;         // for cluster
    int lsh_k, L;          // for lsh
    int cube_k, M, probes; // for hypercube
    int N, R;              // for lsh and hypercube
    char *method = nullptr;
    Mode mode;
    std::ifstream inputFile, queryFile;
    std::ofstream outputFile;

    Input();
    ~Input();

    int parseCmdOptions(const int &argc, char *argv[]);
};
