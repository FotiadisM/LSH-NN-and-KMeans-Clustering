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
    bool complete = false;
    Mode mode;
    std::ifstream inputFile, queryFile;
    std::ifstream inputFileClassification;
    std::ifstream inputFileNewSpace, queryFileNewSpace;
    std::ofstream outputFile;

    Input();
    ~Input();

    int parseCmdOptions(const int &argc, char *argv[]);

    int OpenInputFile(const std::string &file);
    int OpenInputFileNewSpace(const std::string &file);
    int OpenQueryFile(const std::string &file);
    int OpenQueryFileNewSpace(const std::string &file);
    int OpenInputFileClassification(const std::string &file);
};
