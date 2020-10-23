#include <iostream>
#include <cmath>

#include "../include/hyperCube.h"

using namespace std;


/*
 use 2 unordered sets instead of map as they dont add time complexity for searching
 since 2 O(1) == O(1)
 while using less space since they only store the keys and not the values associated with them
*/

f::f()
{
// create a hash table here maybe from stl ?!
    cout << "i do nothing" << endl;
}


f::~f()
{

}


int f::calculate_f(std::string key)
{
    int num;

    if (this->setOfZeros.find(key) != this->setOfZeros.end())
        return 0;
    else if (this->setOfOnes.find(key) != this->setOfOnes.end())
        return 1;
    else {
        num = rand() % 2;
        if (num == 0) {
            this->setOfZeros.insert(key);
            return 0;
        }
        else {
            this->setOfOnes.insert(key);
            return 1;
        }
    }

    return -1;
}


// k == d' if i remember correctly
hyperCube::hyperCube(int R, int indexSize, Data &data, int k, int d, uint32_t w)
    : R(R), indexSize(indexSize), k(k), d(d), w(w), data(data)
{
    this->M = uint32_t(pow(2, 32 / this->k));

    this->ht = new hashTable(indexSize, k, d, w);
    
    // initialize array of f functions
    for (int i=0; i<k; i++) {
        f* f_instance = new f();
        this->fTable.push_back(f_instance); 
    }
}


hyperCube::~hyperCube()
{

}


int hyperCube::hyperCubeRun()
{
    // na pernaw stin hamming to ht kai to R kai na mou epistrefei apla mia lista me tous geitones
    hashData();
    string str = "001100";

    list<string> l = hammingDist(str);
    list<string>::iterator it;
    for (it=l.begin(); it!=l.end(); ++it)
        cout << *it << endl;


    f* function = new f();
    function->calculate_f(str);

    cout << "geia" << endl;
    return 0;
}


void hyperCube::hashData()
{

// 8a kanw calculate mia h tin opoia 8a petaw stin f kai 8a mou dinei 0 h 1
// kai istera oles autes tis times 8a tis enwsw se ena megalo string to 
// opoio 8a mpei sto ht-hc

    // s = s + std::to_string(1);

    for (int j = 0; j < this->data.n; j++)
    {

        // anti gia calculate h 8a balw mia rand pou dinei int 
        // prepei na baloume thn calculate h kai calculate a 
        // sto hash table wste na min epanalambanoume kwdika

        int h = rand() % 300;

        // cout << this->fTable[0]->calculate_f(std::to_string(h)) << endl;
        

        // calculate_f and glue the resaults together to big string
        // this->hyperCubeInsert
    }
}


void hyperCube::hyperCubeInsert(std::string s)
{
    cout << "String is : " << s << endl;
}


list<string> hyperCube::hammingDist(std::string s)
{
    // check here whether they exist in ht or in to calling function ?
    // take the string and make a list of all the edges in hamming distance from the given one
    list<string> l;

    cout << "initial hamming string : " << s << endl;

    for (int i=0; i < (int)s.size(); i++) {
        if (s[i] == '0')
            s[i] = '1';
        else 
            s[i] = '0';
        
        l.push_back(s);

        if (s[i] == '0')
            s[i] = '1';
        else 
            s[i] = '0';
    }

    return l;
}