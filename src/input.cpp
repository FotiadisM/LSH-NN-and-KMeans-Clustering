#include <iostream>
#include <algorithm>
#include <cstring>

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

    return nullptr;
}

Input::Input()
    : lsh_k(4), L(5), N(1), R(1.0)
{
    inputFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    queryFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    outputFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    confFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
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

int Input::parseCmdLSHOptions(int argc, char *argv[])
{
    char *val = nullptr;

    if ((val = this->getCmdOption(argv, argv + argc, "-d")) != nullptr)
    {
        try
        {
            this->inputFile.open(val, ifstream::in | ifstream::binary);
        }
        catch (const ifstream::failure &e)
        {
            perror("open()");
            cerr << "Failed to open " << val << endl;
            return -1;
        }
    }
    else
    {
        cerr << "Input file required" << endl;
        return -1;
    }

    if ((val = this->getCmdOption(argv, argv + argc, "-q")) != nullptr)
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
    else
    {
        cerr << "Query file required" << endl;
        // return -1;
    }

    if ((val = this->getCmdOption(argv, argv + argc, "-k")) != nullptr)
    {
        sscanf(val, "%d", &(this->lsh_k));
    }

    if ((val = this->getCmdOption(argv, argv + argc, "-L")) != nullptr)
    {
        sscanf(val, "%d", &(this->L));
    }

    if ((val = this->getCmdOption(argv, argv + argc, "-o")) != nullptr)
    {
        try
        {
            this->outputFile.open(val, ofstream::out | ofstream::trunc);
        }
        catch (const ofstream::failure &e)
        {
            perror("open()");
            cerr << e.what() << endl;
            cerr << "Failed to open " << val << endl;
            return -1;
        }
    }

    if ((val = this->getCmdOption(argv, argv + argc, "-N")) != nullptr)
    {
        sscanf(val, "%d", &(this->N));
    }

    if ((val = this->getCmdOption(argv, argv + argc, "-R")) != nullptr)
    {
        sscanf(val, "%f", &(this->R));
    }

    return 0;
}

int Input::parseCmdClusterOptions(const int &argc, char *argv[])
{
    char *val = nullptr;

    if ((val = this->getCmdOption(argv, argv + argc, "-i")) != nullptr)
    {
        try
        {
            this->inputFile.open(val, ifstream::in | ifstream::binary);
        }
        catch (const ifstream::failure &e)
        {
            perror("open()");
            cerr << "Failed to open " << val << endl;
            return -1;
        }
    }
    else
    {
        cerr << "Input file required" << endl;
        return -1;
    }

    if ((val = this->getCmdOption(argv, argv + argc, "-c")) != nullptr)
    {
        try
        {
            this->confFile.open(val, ifstream::in);
        }
        catch (const ifstream::failure &e)
        {
            perror("open()");
            cerr << e.what() << endl;
            cerr << "Failed to open " << val << endl;
            return -1;
        }
    }
    else
    {
        cerr << "Configuration file required" << endl;
        return -1;
    }

    if ((val = this->getCmdOption(argv, argv + argc, "-complete")) != nullptr)
    {
        this->complete = true;
    }
    else
    {
        this->complete = false;
    }

    if ((val = this->getCmdOption(argv, argv + argc, "-m")) != nullptr)
    {
        if (!strcmp(val, "Callic"))
            this->m = _Classic;
        else if (!strcmp(val, "LSH"))
            this->m = _LSH;
        else if (!strcmp(val, "Hypercube"))
            this->m = _Hypercube;
        else
        {
            cout << "unknown method: " << val << endl;
            return -1;
        }
    }

    if ((val = this->getCmdOption(argv, argv + argc, "-o")) != nullptr)
    {
        try
        {
            this->outputFile.open(val, ofstream::out | ofstream::trunc);
        }
        catch (const ofstream::failure &e)
        {
            perror("open()");
            cerr << e.what() << endl;
            cerr << "Failed to open " << val << endl;
            return -1;
        }
    }

    return 0;
}