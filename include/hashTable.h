#include <list>

class hashTable
{
private:
    int bucketNum;
    std::list<int> * table;

public:
    hashTable();
    ~hashTable();
    void insertItem();
    void deleteItem(); // prob not needed
    int hashFunction();
    void printHashTable();
};