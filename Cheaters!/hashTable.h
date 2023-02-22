#ifndef PLAGIARISMCATCHER_HASHTABLE_H
#define PLAGIARISMCATCHER_HASHTABLE_H
#include <vector>
#include <list>
#include <string>
#include <iostream>
using namespace std;

class HashTable {

public:
    //Constructor
    //Initializes number of buckets needed for hashtable and 2d array for collisions
    HashTable(int buckets, int fileSize);

    //Inserts key into hashtable
    //hash is hashed string value
    //key is file index
    void insert(unsigned long hash, unsigned int key);

    //Count number of collisions in hashtable
    //Inserts them into 2D array, where i and j of 2d array are index of file1 and file2
    void collisions(vector<string> &files);

    //Returns number of collisions between files i, j
    int getCollisionNum(unsigned int i, unsigned int j){
        return collisionCount[i][j];
    }

    ~HashTable(){}

private:
    //Table holds hashtable
    list<int> *table;
    //Holds Number of Files
    int FilesSize;
    //Holds number of buckets
    int BucketCount;
    //2d array (vector of vectors)
    vector< vector<int> > collisionCount;
};


#endif //PLAGIARISMCATCHER_HASHTABLE_H
