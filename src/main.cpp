#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

#include "../include/input.h"
#include "../include/LSH.h"

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

    lsh = new LSH(input.k, input.L, input.N, data);
    if (lsh->Run(data.query, input.outputFile) == -1)
    {
        cerr << "LSH::Run() failed" << endl;
    }

    delete lsh;

    return 0;
}