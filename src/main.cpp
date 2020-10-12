#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

#include "../include/input.h"
#include "../include/LSH.h"

using namespace std;

int main(int argc, char *argv[])
{
    Data data;
    LSH *lsh;
    Input *input;

    srand(time(NULL));

    if ((input = new Input()) == nullptr)
    {
        perror("new");
        return -1;
    }

    if (input->parseCmdOptions(argc, argv) == -1)
    {
        cerr << "Failed to parse command line input" << endl;
        return -1;
    }

    data.InitMnistDataSet(input->inputFile);

    lsh = new LSH(input->k, input->L, input->N, data);
    if (lsh->Run() == -1)
    {
        cerr << "LSH::Run() failed" << endl;
    }

    delete input;
    delete lsh;

    return 0;
}