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
    int flag = true;
    Input input;

    srand(time(NULL));

    if (input.parseCmdOptions(argc, argv) == -1)
    {
        cerr << "input::ParseCmdOptions() failed" << endl;
    }

    while (flag)
    {
        string file;
        Data data;

        while (!input.inputFile.is_open())
        {
            cout << "Please provide a path to an input file" << endl;
            cin >> file;
            input.OpenInputFile(file);
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
                kmeans = new kmeansplusplus(input.nClusters, input.complete, data);
            }
            else if (!strcmp(input.method, "LSH"))
            {
                kmeans = new kmeansplusplus(input.nClusters, input.complete, input.lsh_k, input.L, data);
            }
            else if (!strcmp(input.method, "Hypercube"))
            {
                kmeans = new kmeansplusplus(input.nClusters, input.complete, input.cube_k, input.M, input.probes, data);
            }
            else
            {
                cout << "Method: " << input.method << "not recognized" << endl;

                return -1;
            }

            kmeans->Run(input.outputFile);

            delete kmeans;
        }
        else
        {
            while (!input.queryFile.is_open())
            {
                cout << "Please provide a path to an query file" << endl;
                cin >> file;
                input.OpenQueryFile(file);
            }

            if (data.ReadQueryFile(input.queryFile) == -1)
            {
                cerr << "Data::ReadQueryFile() failed" << endl;
                return -1;
            }

            if (input.mode == _lsh)
            {
                LSH *lsh = new LSH(input.lsh_k, input.L, data, 10000, 200);

                if (lsh->Run(data.queries, input.outputFile, input.N, input.R) == -1)
                {
                    cerr << "LSH::Run() failed" << endl;
                }

                delete lsh;
            }
            else
            {
                HyperCube *hc = new HyperCube(floor(log2(data.n)), input.M, input.probes, data);

                if (hc->Run(data.queries, input.outputFile, input.N, input.R) == -1)
                {
                    cerr << "HyperCube::hyperCubeRun() failed!" << endl;
                }

                delete hc;
            }
        }

        string str;
        while (1)
        {
            cout << "Would like to run again with different input? [Y, N]" << endl;
            cin >> str;
            if (!str.compare("Y") || !str.compare("y"))
            {
                input.inputFile.close();
                input.queryFile.close();
                break;
            }
            else if (!str.compare("N") || !str.compare("n"))
            {
                flag = false;
                break;
            }
        }
    }

    return 0;
}