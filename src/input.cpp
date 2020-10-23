#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>

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
        ifstream confFile;

        try
        {
            confFile.open(val, ifstream::in);
        }
        catch (const ifstream::failure &e)
        {
            perror("open()");
            cerr << e.what() << endl;
            cerr << "Failed to open " << val << endl;
            return -1;
        }

        for (string line; std::getline(confFile, line);)
        {
            istringstream ss(line);
            istream_iterator<string> begin(ss), end;

            vector<string> options(begin, end);

            this->L = 3;
            this->lsh_k = 4;
            this->M = 10;
            this->cube_k = 3;
            this->probes = 2;

            if (!options[0].compare("number_of_clusters:"))
            {
                this->clusters = stoi(options[1]);
            }
            else if (!options[0].compare("number_of_vector_hash_tables:"))
            {
                this->L = stoi(options[1]);
            }
            else if (!options[0].compare("number_of_vector_hash_functions:"))
            {
                this->lsh_k = stoi(options[1]);
            }
            else if (!options[0].compare("max_number_M_hypercube:"))
            {
                this->M = stoi(options[1]);
            }
            else if (!options[0].compare("number_of_hypercube_dimensions:"))
            {
                this->cube_k = stoi(options[1]);
            }
            else if (!options[0].compare("number_of_probes:"))
            {
                this->probes = stoi(options[1]);
            }
            else
            {
                cout << "unknown option in .conf file" << endl;
            }
        }

        confFile.close();
    }
    else
    {
        cerr << "Configuration file required" << endl;
        return -1;
    }

    if ((val = this->getCmdOption(argv, argv + argc, "-complete")) != nullptr)
    {
    }

    if ((val = this->getCmdOption(argv, argv + argc, "-m")) != nullptr)
    {
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