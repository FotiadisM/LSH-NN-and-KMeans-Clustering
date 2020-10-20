#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

#include "../include/input.h"
#include "../include/LSH.h"
#include "../include/hyperCube.h"

using namespace std;

int main(int argc, char *argv[])
{
    LSH *lsh;
    Data data;
    Input input;

    srand(time(NULL));

    if (input.parseCmdOptions(argc, argv) == -1)
    {
        cerr << "Failed to parse command line input" << endl;
        return -1;
    }

    if (data.InitMnistDataSet(input.inputFile) == -1)
    {
        cerr << "Data::InitMnistDataSet() failed" << endl;
        return -1;
    }

    // if (data.ReadQueryFile(input.queryFile) == -1)
    // {
    //     cerr << "Data::ReadQueryFile() failed" << endl;
    //     return -1;
    // }

    // lsh = new LSH(input.k, input.L, input.N, data);
    // if (lsh->Run(data.data[0], input.outputFile) == -1)
    // {
    //     cerr << "LSH::Run() failed" << endl;
    // }

    // delete lsh;

    int indexSize = 5;
    hyperCube* hc = new hyperCube(input.R, indexSize, data, input.k, data.d);
    if (hc->hyperCubeRun() == -1)
    {
        cerr << "hyperCubeRun() failed" << endl;
    }

    // delete hc;


    return 0;
}