#include "hashTable.h"

//Constructor
//Initializes number of buckets needed for hashtable and 2d array for collisions
HashTable::HashTable(int buckets, int fileSize){
    this->BucketCount = buckets;
    table = new list<int>[BucketCount];
    this->FilesSize = fileSize;
    collisionCount.resize(FilesSize, vector<int>(FilesSize));
}

//Inserts key into hashtable
//hash is hashed string value
//key is file index
void HashTable::insert(unsigned long hash, unsigned int key){
    int bucketIndex = int (hash % BucketCount); //Get hash index
    if (bucketIndex < 0){   //Make sure index is not negative
        bucketIndex = bucketIndex * -1;
    }
    table[bucketIndex].push_back(key);
}

//Count number of collisions in hashtable
//Inserts them into 2D array, where i and j of 2d array are index of file1 and file2
void HashTable::collisions(vector<string> &files){
    for (int bucketIndex = 0; bucketIndex < BucketCount; bucketIndex++) {
        if (!table[bucketIndex].empty()) {  //If there are collisions
            for (auto i : table[bucketIndex]){
                for (auto j : table[bucketIndex]){
                    if(i != j){ //Make sure they're not collisions within the same file
                        collisionCount[i][j] += 1;
                    }
                }
            }
        }
    }
}