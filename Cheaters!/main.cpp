#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <functional>
#include <queue>
#include <algorithm>
#include "hashTable.h"
using namespace std;

//Function declarations
int getdir (string dir, vector<string> &files);
string removeChars(string word);
unsigned long hashString(const string& words);
void readFile(string dir, vector<string> &files, unsigned int pVal, HashTable &hashTable);
void collisionsCounter(HashTable &hashTable, vector<string> &files, int mVal);
bool comparePair(const pair<int,string> &a,const pair<int,string> &b);

int main(int argc, char *argv[]) {

    if (argc < 2) {
        cout << "ERROR: enter directory name as an argument" << endl;
        return (0);
    }
    string dir = argv[1];
    vector<string> files = vector<string>();
    string str;

    getdir(dir,files);


    unsigned int pVal = stoi(argv[2]);
    int mVal = stoi(argv[3]);

    HashTable hashTable(60013, files.size());   //Build hastable
    readFile(dir, files, pVal, hashTable);  //Readfile, preprocess, and hash p-word sequences

    //Create 2d matrix (vector of vectors) to store number of collisions between each file
    //hashTable.display();
    hashTable.collisions(files);    //Build 2d array with number of collisions

    collisionsCounter(hashTable, files, mVal);  //Count number of collisions between files and output results

    return 0;
}

int getdir (string dir, vector<string> &files) {
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == nullptr) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != nullptr) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}



void readFile(string dir, vector<string> &files, unsigned int pVal, HashTable &hashTable){
    ifstream inFile;
    queue<string> pWords;   //Stores p consecutive words
    //Iterate through files
    for (unsigned int fileIndex = 2; fileIndex < files.size(); fileIndex++) {
        // ignore . and ..
        string fileName = "./" + dir + '/' + files[fileIndex];  //Path to files
        inFile.open(fileName);  //Open file
        while(inFile) {
            while (pWords.size() < pVal && !inFile.eof()) {  //Get p words from file
                string word;
                inFile >> word; //Extract single word from file
                word = removeChars(word);   //Clear word of special characters except letters, numbers, and apostrophes. Make uppercase lowercase
                if(!word.empty()){  //Make sure word isn't null or empty
                    pWords.push(word);
                }
            }
            string words;   //Holds p-word string
            for(unsigned int i = 0; i < pWords.size(); i++){
                words += pWords.front();    //Concatenate p words together
                pWords.push(pWords.front());
                pWords.pop();
            }
            //Hash p-word string and pop 1 word
            if(!words.empty()){
                unsigned long hash = hashString(words);
                hashTable.insert(hash, fileIndex);
                pWords.pop();
            }
        }
        inFile.close(); //Close file
    }
}

string removeChars(string word){    //Clear word of special characters except letters, numbers, and apostrophes. Make uppercase lowercase
    for (unsigned int i = 0; i < word.size(); i++){  //Convert uppercase to lowercase
        if (word[i] >= 'A' && word[i] <= 'Z'){
            word[i] = tolower(word[i]);
        }
        //Remove special characters
        if (!((word[i] >= '0' && word[i] <= '9') || (word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= 'a' && word[i] <= 'z') || word[i] == '\'')){ //Remove special characters
            word.erase(i, 1);
            i--;
        }
    }
    return word;
}

unsigned long hashString(const string& words){  //Hash string using STL hash function. Returns unsigned long
    hash<string> hashFunc;
    auto hashNum = hashFunc(words); //Hash using STL hash. Returns unsigned long
    return hashNum;
}

void collisionsCounter(HashTable &hashTable, vector<string> &files, int mVal){  //Counts number of collisions and prints results
    vector<pair<int,string>> nameCollisions;    //Vector of pairs. Pairs contain number of collisions and filenames
    for(unsigned int i = 0; i < files.size(); i++){
        for(unsigned int j = i + 1; j < files.size(); j++){
            if(i != j){
                int coli = hashTable.getCollisionNum(i, j); //Retrieve number of collisions between two files
                if (coli >= mVal) {
                    string names = files[i] + ", " + files[j];
                    nameCollisions.emplace_back(coli, names);   //Push pair onto vector
                }
            }
        }
    }

    //Sort values by collisions
    sort(nameCollisions.begin(), nameCollisions.end(), comparePair);
    //Print collisions
    for(unsigned int i = 0; i < nameCollisions.size(); i++){
        cout << nameCollisions[i].first << ": " << nameCollisions[i].second << endl;
    }


}

bool comparePair(const pair<int,string> &a,const pair<int,string> &b){  //Helper for sort. Sorts in descending order
    return a.first > b.first;
}