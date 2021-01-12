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


        // open input file old space
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

        // open input file new space
        while (!input.inputFileNewSpace.is_open())
        {
            cout << "Please provide a path to an new space input file" << endl;
            cin >> file;
            input.OpenInputFileNewSpace(file);
        }

        if (data.InitMnistDataSetNewSpace(input.inputFileNewSpace) == -1)
        {
            cerr << "Data::InitMnistDataSet() failed" << endl;
            return -1;
        }

        if (input.mode == _cluster)
        {
            while (!input.inputFileClassification.is_open())
            {
                cout << "Please provide a path to a classification data file" << endl;
                cin >> file;
                input.OpenInputFile(file);
            }
            data.InitDataSetClassification(input.inputFileClassification);
            
            kmeansplusplus *kmeans;
            if (!strcmp(input.method, "Classic"))
            {
                kmeans = new kmeansplusplus(input.nClusters, input.complete, data);
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

            // open query file old space
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

            // open query file new space
            while (!input.queryFileNewSpace.is_open())
            {
                cout << "Please provide a path to queryFileNewSpace" << endl;
                cin >> file;
                input.OpenQueryFileNewSpace(file);
            }

            if (data.ReadQueryFileNewSpace(input.queryFileNewSpace) == -1)
            {
                cerr << "Data::ReadQueryFileNewSpace() failed" << endl;
                return -1;
            }


            LSH *lsh = new LSH(input.lsh_k, input.L, data);

            if (lsh->Run(data.queries, input.outputFile, 1, input.R) == -1)
            {
                cerr << "LSH::Run() failed" << endl;
            }

            delete lsh;
            
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