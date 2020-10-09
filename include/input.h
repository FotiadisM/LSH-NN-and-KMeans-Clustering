#pragma once

#include <iostream>
#include <fstream>

class Input
{
private:
    char *getCmdOption(char **begin, char **end, const std::string &option);

public:
    int k, L, N;
    float R;
    std::ifstream inputFile, queryFile;
    std::ofstream outputFile;

    Input();
    ~Input();
    int parseCmdOptions(int argc, char *argv[]);
};
