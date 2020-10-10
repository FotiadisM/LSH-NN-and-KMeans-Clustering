#include <iostream>
#include <cstdlib>
#include <cmath>

#include "../include/LSH.h"

using namespace std;

LSH::LSH(int k, int L, int N, Data &data, uint32_t w, uint32_t m)
    : k(k), L(L), N(N), data(data), w(w), m(m)
{
    this->M = uint32_t(pow(2, 32 / this->k));
}

LSH::~LSH() {}

int LSH::Run()
{
    // for every hash table
    for (int i = 0; i < this->L; i++)
    {
        // find g(x) after calculating k h(x)
        for (int j = 0; j < this->k; j++)
        {
            int h = 0;

            if ((h = this->calculate_h(j)) != -1)
            {
                // H[j] = h;
            }
        }
    }

    return 0;
}

int LSH::calculate_h(int j)
{
    for (int i = 0; i < data.d; i++)
    {
        int a = 0;
        cout << int(this->data.data[j][i]);
        a = this->calculate_a(this->data.data[j][i]); // need to pass xi

        cout << " a: " << a << endl;
    }

    return 0;
}

int LSH::calculate_a(uint8_t x)
{
    int s = (rand() % this->w);

    cout << " - " << (int(x) - s) << " w " << int(this->w);

    return (int(x) - s) / int(this->w);
}