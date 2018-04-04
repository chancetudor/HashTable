#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

#ifndef HASH_H
#define HASH_H

struct Item {
  string key;
  vector<int> lineVec;
  Item() {
    key = "\0";
  }
};

class HashTable {
  public:
    HashTable(int size);
    int getCollisions() { return collisions; }
    int getUniqueWords() { return uniqueWords; }
    unsigned long hashFunction(string k);
    unsigned long hashFunction2(string k, int a);
    void linearSearch(string k);
    void linearInsert(string k, int l);
    void quadraticSearch(string k);
    void quadraticInsert(string k, int l);
    void doubleHashSearch(string k, int a);
    void doubleHashInsert(string k, int l, int a);

  private:
    int tableSize = 0;
    int collisions = 0;
    int uniqueWords = 0;
    vector<Item> hashTable;
};

#endif // HASH_H
