#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

#include "../include/input.h"
#include "../include/kmeansplusplus.h"

using namespace std;

int main(int argc, char *argv[])
{
    // LSH *lsh;
    kmeansplusplus *kmeans;
    Data data;
    Input input;

    srand(time(NULL));

    if (input.parseCmdClusterOptions(argc, argv) == -1)
    {
        cerr << "Failed to parse command line input" << endl;
        return -1;
    }

    // if (input.parseCmdLSHOptions(argc, argv) == -1)
    // {
    //     cerr << "Failed to parse command line input" << endl;
    //     return -1;
    // }

    if (data.InitMnistDataSet(input.inputFile) == -1)
    {
        cerr << "Data::InitMnistDataSet() failed" << endl;
        return -1;
    }

    char method[] = "Complete";
    kmeans = new kmeansplusplus(input.clusters, method, data);

    kmeans->Run(input.lsh_k, input.L, input.cube_k, input.M, input.probes);

    // if (data.ReadQueryFile(input.queryFile) == -1)
    // {
    //     cerr << "Data::ReadQueryFile() failed" << endl;
    //     return -1;
    // }

    // lsh = new LSH(input.lsh_k, input.L, input.N, data);
    // if (lsh->Run(data.data[0], input.outputFile) == -1)
    // {
    //     cerr << "LSH::Run() failed" << endl;
    // }

    // delete lsh;
    delete kmeans;

    return 0;
}