#pragma once

#include <iostream>
#include <fstream>

enum Method
{
    _Classic,
    _LSH,
    _Hypercube
};

class Input
{
private:
    char *getCmdOption(char **begin, char **end, const std::string &option);

public:
    int lsh_k, cube_k, L, N, M, probes;
    float R;
    bool complete;
    Method m;
    std::ifstream inputFile, queryFile, confFile;
    std::ofstream outputFile;

    Input();
    ~Input();
    int parseCmdLSHOptions(int argc, char *argv[]);
    int parseCmdClusterOptions(const int &argc, char *argv[]);
};
