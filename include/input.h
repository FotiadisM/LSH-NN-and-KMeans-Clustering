#pragma once

#include <iostream>
#include <fstream>

class Input
{
private:
    char *getCmdOption(char **begin, char **end, const std::string &option);

public:
    int lsh_k, cube_k, L, N, M, probes, clusters;
    float R;
    char *method;
    std::ifstream inputFile, queryFile;
    std::ofstream outputFile;

    Input();
    ~Input();
    int parseCmdLSHOptions(int argc, char *argv[]);
    int parseCmdClusterOptions(const int &argc, char *argv[]);
};
