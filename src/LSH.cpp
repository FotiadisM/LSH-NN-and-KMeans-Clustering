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
        // L hashtables συνολο
        // 1 hastable == 1 g(x)
        // 1 g(x) θελει k h(x)
        // 1 h(x) θελει d s

        // stores all the (s0, s1, ..., sd-1) * k times
        // Θα πρεπει να αποθηκευουμε ολα τα s για να τα χρησιμοποιουμε στα query
        // αρα θα πρεπει να βαλουμε αυτο το vector σαν μεταβλητη της LSH
        // θα το αλλαξω αργοτερα
        vector<vector<int>> S(this->k, vector<int>(this->data.d)); // k * d array

        // calculate all the s and store them (meaning find all the h(x) that will be used
        // in this Li hashtable)
        this->calculate_s(S);

        // iterate the data, for each image, hash it and store in the hash table
        for (int j = 0; j < this->data.n; j++)
        {
            // stores all the h0, h1, ..., hk-1
            vector<int> H(this->k);

            // find g(x) after calculating k h(x)
            for (int l = 0; l < this->k; l++)
            {
                H[l] = this->calculate_h(this->data.data[j], S[l]);
            }

            // g(j) = [h0(j) | h1(j) | ... | hk-1(j)] = 0 - 2^32
            // ισως κανουμε g(j) = g(j) mod 8 ή 16 για να μειωσουμε τον χωρο
            // και να αποθηκευουμε καθε εικονα σε πιο μπακετ μπηκε με ακριβεια, δηλαδη το αρχικο g(j)
            //HashTable[g(j)] = image
        }
    }

    // g(query)
    // for i=0 : i < this->L) {
    //}
    // for all hashTabless
    //    get all images in hashTabless[i][g(query)]

    //filter images to find the N closest to the query

    return 0;
}

void LSH::calculate_s(vector<vector<int>> &S)
{
    for (int i = 0; i < this->k; i++)
    {
        for (int j = 0; j < this->data.d; j++)
        {
            S[i][j] = (rand() % this->w);
        }
    }
}

int LSH::calculate_h(const vector<uint8_t> &x, const vector<int> &s)
{
    // stores all the a0, a1, ..., ad-1
    vector<int> a(this->data.d);

    for (int i = 0; i < this->data.d; i++)
    {
        a[i] = this->calculate_a(x[i], s[i]);
    }

    // h(x) = (ad−1 + m*ad−2 + ... + md−1*a0) mod M

    return 0;
}

int LSH::calculate_a(const uint8_t &xi, const int &si)
{
    return (int(xi) - si) / int(this->w);
}