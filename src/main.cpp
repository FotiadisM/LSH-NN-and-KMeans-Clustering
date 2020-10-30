#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <math.h>

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
        kmeansplusplus *kmeans;

        if (!strcmp(input.method, "Classic"))
        {
            kmeans = new kmeansplusplus(input.nClusters, data);
        }
        else if (!strcmp(input.method, "LSH"))
        {
            kmeans = new kmeansplusplus(input.nClusters, input.lsh_k, input.L, data);
        }
        else if (!strcmp(input.method, "Hypercube"))
        {
            kmeans = new kmeansplusplus(input.nClusters, input.cube_k, input.M, input.probes, data);
        }
        else if (!strcmp(input.method, "Complete"))
        {
            kmeans = new kmeansplusplus(input.nClusters, input.lsh_k, input.L, input.cube_k, input.M, input.probes, data);
        }
        else
        {
            cout << "Method: " << input.method << "not recognized" << endl;

            return -1;
        }

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
            LSH *lsh = new LSH(input.lsh_k, input.L, data);

            if (lsh->Run(data.data[2000], input.outputFile, 50) == -1)
            {
                cerr << "LSH::Run() failed" << endl;
            }

            delete lsh;
        }
        else
        {
            HyperCube *hc = new HyperCube(input.cube_k, data, floor(log(data.n)), data.d);

            if (hc->hyperCubeRun(data.data[0], input.outputFile, 50) == -1)
            {
                cerr << "HyperCube::hyperCubeRun() failed!" << endl;
            }
        }
    }

    return 0;
}