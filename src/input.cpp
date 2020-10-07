#include <iostream>
#include <algorithm>

#include <stdio.h>

#include "../include/input.h"

using namespace std;

char *Input::getCmdOption(char **begin, char **end, const string &option)
{
    char **itr = find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }

    return NULL;
}

Input::Input()
    : k(4), L(5), N(1), R(1.0)
{
    inputFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    queryFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    outputFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
}

Input::~Input()
{
    if (inputFile.is_open())
    {
        inputFile.close();
    }

    if (queryFile.is_open())
    {
        queryFile.close();
    }

    if (outputFile.is_open())
    {
        outputFile.close();
    }
}

int Input::parseCmdOptions(int argc, char *argv[])
{
    char *val = NULL;

    if ((val = this->getCmdOption(argv, argv + argc, "-d")) != NULL)
    {
        try
        {
            this->inputFile.open(val, ifstream::in);
        }
        catch (const ifstream::failure &e)
        {
            perror("open()");
            cerr << "Failed to open " << val << endl;
            return -1;
        }
    }

    if ((val = this->getCmdOption(argv, argv + argc, "-q")) != NULL)
    {
        try
        {
            this->queryFile.open(val, ifstream::in);
        }
        catch (const ifstream::failure &e)
        {
            perror("open()");
            cerr << e.what() << endl;
            cerr << "Failed to open " << val << endl;
            return -1;
        }
    }

    if ((val = this->getCmdOption(argv, argv + argc, "-k")) != NULL)
    {
        sscanf(val, "%d", &(this->k));
        cout << this->k << endl;
    }

    if ((val = this->getCmdOption(argv, argv + argc, "-L")) != NULL)
    {
        sscanf(val, "%d", &(this->L));
        cout << this->L << endl;
    }

    if ((val = this->getCmdOption(argv, argv + argc, "-o")) != NULL)
    {
        try
        {
            this->outputFile.open(val, ofstream::out);
        }
        catch (const ofstream::failure &e)
        {
            perror("open()");
            cerr << e.what() << endl;
            cerr << "Failed to open " << val << endl;
            return -1;
        }
    }

    if ((val = this->getCmdOption(argv, argv + argc, "-N")) != NULL)
    {
        sscanf(val, "%d", &(this->N));
        cout << this->N << endl;
    }

    if ((val = this->getCmdOption(argv, argv + argc, "-R")) != NULL)
    {
        sscanf(val, "%f", &(this->R));
        cout << this->R << endl;
    }

    return 0;
}