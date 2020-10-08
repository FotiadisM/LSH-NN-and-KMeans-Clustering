#include <iostream>

#include "../include/input.h"
#include "../include/data.h"

using namespace std;

int main(int argc, char *argv[])
{
    Data data;
    Input *input;

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
    cout << "done" << endl;

    delete input;

    return 0;
}