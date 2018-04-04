#include <cstdlib>
#include <iostream>
#include <string>
#include <list>

#include "hash.h"

using namespace std;

HashTable::HashTable(int size) { // default constructor
  tableSize = size; // sets table size
  int i = 0;
  while (i < size) {
    hashTable.push_back(Item()); // creates hashTable of size tableSize
    i++;
  }
}

unsigned long HashTable::hashFunction(string key) { // djb2 hash function
  unsigned long len = key.length();
	unsigned long hash = 5381;
	unsigned int i = 0;

	for (i = 0; i < len; i++) { hash = ((hash << 5) + hash) + (key[i]); }

	return hash;
}

unsigned long HashTable::hashFunction2(string k, int a) { // double hash function
  unsigned long hash = 0;
  hash = (a - ((hashFunction(k) % tableSize) % a));
  return hash;
}

void HashTable::linearInsert(string k, int l) {
  unsigned long index = (hashFunction(k) % tableSize); // gets index from djb2 hash function
  while (hashTable.at(index).key != "\0") { // while bucket is not empty
    if (hashTable.at(index).key == k) { // if key at index matches search word
      hashTable.at(index).lineVec.push_back(l); // add line number to lineVec
      break; // break from while loop, because we don't need to continue iterating
    }
    else { // bucket contains word other than search word
      collisions++; // up collisions
      index = (index + 1) % tableSize; // index is increased linearly
    }
  }

  if (hashTable.at(index).key == "\0") { // bucket is empty
    hashTable.at(index).key = k; // update key at index to be search word
    hashTable.at(index).lineVec.push_back(l); // add line number to lineVec
    uniqueWords++; // unique word count increased by one
  }
}

void HashTable::linearSearch(string k) {
  unsigned long index = (hashFunction(k) % tableSize);
  collisions = 0;

  while (hashTable.at(index).key != k && hashTable.at(index).key != "\0") { // bucket doesn't match search term and is not empty
    collisions++; // collision count increased by one
    index = (index + 1) % tableSize; // index is increased linearly
  }

  if (hashTable.at(index).key == k) { // if key at index matches search word
    cout << k << " appears on lines [";
    for (auto itr = hashTable.at(index).lineVec.cbegin(); itr != hashTable.at(index).lineVec.cend(); itr++) { // iterates through line num vector
      if (itr != hashTable.at(index).lineVec.cbegin()) { cout << ","; }
      cout << *itr;
    }
    cout << "]" << endl;
    cout << "The search had " << collisions << " collisions" << endl << endl;
    return;
  }

  else {
    cout << k << " appears on lines []" << endl;
    cout << "The search had " << collisions << " collisions" << endl << endl;
    return;
  }
}

void HashTable::quadraticInsert(string k, int l) {
  unsigned long index = (hashFunction(k) % tableSize);
  int i = 1;

  while (hashTable.at(index).key != "\0") {
    if (hashTable.at(index).key == k) { // if key at index matches search word
      hashTable.at(index).lineVec.push_back(l); // add line number to lineVec
      break;
    }
    else {
      collisions++; // up collision count
      index = ((hashFunction(k) % tableSize) + (i * i)) % tableSize; // increase index quadratically
      i++;
    }
  }

  if (hashTable.at(index).key == "\0") {
    hashTable.at(index).key = k; // update key at index to be search word
    hashTable.at(index).lineVec.push_back(l); // add line number to lineVec
    uniqueWords++; // unique word count increased by one
  }
}

void HashTable::quadraticSearch(string k) {
  unsigned long index = (hashFunction(k) % tableSize);
  collisions = 0;
  int i = 1;

  while (hashTable.at(index).key != k && hashTable.at(index).key != "\0") {
    collisions++;
    index = ((hashFunction(k) % tableSize) + (i * i)) % tableSize;
    i++;
  }

  if (hashTable.at(index).key == k) { // if key at index matches search word
    cout << k << " appears on lines [";
    for (auto itr = hashTable.at(index).lineVec.cbegin(); itr != hashTable.at(index).lineVec.cend(); itr++) {
      if (itr != hashTable.at(index).lineVec.cbegin()) { cout << ","; }
      cout << *itr;
    }
    cout << "]" << endl;
    cout << "The search had " << collisions << " collisions" << endl << endl;
    return;
  }

  else {
    cout << k << " appears on lines []" << endl;
    cout << "The search had " << collisions << " collisions" << endl << endl;
    return;
  }
}

void HashTable::doubleHashInsert(string k, int l, int a) {
  unsigned long index = (hashFunction(k) % tableSize);
  int i = 1;

  while (hashTable.at(index).key != "\0") { // while bucket is not empty
    if (hashTable.at(index).key == k) { // if key at index matches search word
      hashTable.at(index).lineVec.push_back(l); // add line number to lineVec
      break;
    }
    else {
      collisions++; // up collision count
      index = ((hashFunction(k) % tableSize) + (i * hashFunction2(k, a))) % tableSize; // increase index via double hashing
      i++;
    }
  }

  if (hashTable.at(index).key == "\0") { // empty bucket
    hashTable.at(index).key = k; // update key at index to be search word
    hashTable.at(index).lineVec.push_back(l); // add line number to lineVec
    uniqueWords++; // unique word count increased by one
  }
}

void HashTable::doubleHashSearch(string k, int a) {
  unsigned long index = (hashFunction(k) % tableSize);
  collisions = 0;
  int i = 1;

  while (hashTable.at(index).key != k && hashTable.at(index).key != "\0") { // while bucket doesn't match key and bucket is not empty
    collisions++; // up collisions
    index = ((hashFunction(k) % tableSize) + (i * hashFunction2(k, a))) % tableSize; // move index via double hashing
    i++;
  }

  if (hashTable.at(index).key == k) { // if key at index matches search word
    cout << k << " appears on lines [";
    for (auto itr = hashTable.at(index).lineVec.cbegin(); itr != hashTable.at(index).lineVec.cend(); itr++) { // iterate thru line nums vector
      if (itr != hashTable.at(index).lineVec.cbegin()) { cout << ","; }
      cout << *itr;
    }
    cout << "]" << endl;
    cout << "The search had " << collisions << " collisions" << endl << endl;
    return;
  }

  else { // word was not found
    cout << k << " appears on lines []" << endl;
    cout << "The search had " << collisions << " collisions" << endl << endl;
    return;
  }
}
