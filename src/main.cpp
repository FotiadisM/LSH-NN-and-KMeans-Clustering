#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

#include "../include/input.h"
#include "../include/kmeansplusplus.h"

using namespace std;

int main(int argc, char *argv[])
{
    Data data;
    Input input;

    srand(time(NULL));

    if (input.parseCmdOptions(argc, argv) == -1)
    {
        cerr << "input::ParseCmdOptions() failed" << endl;
    }

    if (data.InitMnistDataSet(input.inputFile) == -1)
    {
        cerr << "Data::InitMnistDataSet() failed" << endl;
        return -1;
    }

    if (input.mode == _cluster)
    {
        kmeansplusplus *kmeans = new kmeansplusplus(input.nClusters, data);

        kmeans->Run();

        delete kmeans;
    }
    else
    {

        // if (data.ReadQueryFile(input.queryFile) == -1)
        // {
        //     cerr << "Data::ReadQueryFile() failed" << endl;
        //     return -1;
        // }

        if (input.mode == _lsh)
        {
            LSH *lsh = new LSH(input.lsh_k, input.L, input.N, data);

            if (lsh->Run(data.data[0], input.outputFile) == -1)
            {
                cerr << "LSH::Run() failed" << endl;
            }

            delete lsh;
        }
        else
        {
            cout << "ola edw plhrwnontai" << endl;
        }
    }

    return 0;
}