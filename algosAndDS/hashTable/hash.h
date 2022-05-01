#ifndef HASH_H
#define HASH_H

#include<cstdlib>
#include<iostream>
#include<string>
using namespace std;


class hashTable{
private:
    static const int tableSize = 40;

    struct item{
        string name;
        string drink;
        item* next;
    };

    item* Buckets[tableSize];

public:
    hashTable();
    ~hashTable();
    int hashFunc(string key);
    void addItem(string name, string drink);
    int numberOfItemsInIndex(int index);
    void printTable();
    void printItemsInIndex(int index);
};


#endif 