#include <iostream>
#include <cmath>

#include "../include/LSH.h"

using namespace std;

LSH::LSH(int k, int L, int N, Data &data, uint32_t w, uint32_t m)
    : k(k), L(L), N(N), data(data), w(w), m(m)
{
    this->M = uint32_t(pow(2, 32 / this->k));
}

LSH::~LSH()
{
}

int LSH::Run()
{
    // for every hash table
    for (int i = 0; i < this->L; i++)
    {
        // find g(x) after calculating k h(x)
        for (int j = 0; j < this->k; j++)
        {
            int h = 0;

            if ((h = this->calculate_h()) != -1)
            {
                H[j] = h;
            }
        }
    }

    return 0;
}

int LSH::calculate_h()
{
    for (int i = 0; i < data.d; i++)
    {
        int a = 0;

        a = this->calculate_a(i); // need to pass xi
    }
}

int LSH::calculate_a(int x)
{
}