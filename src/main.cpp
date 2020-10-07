#include <iostream>
#include "../include/input.h"

using namespace std;

int main(int argc, char *argv[])
{
    Input *input = NULL;

    input = new Input();

    if (input->parseCmdOptions(argc, argv) == -1)
    {
        cerr << "Failed to parse command line input" << endl;
    }

    delete input;

    return 0;
}