// This is a program to implement hashing via linear, quadratic, and
// double hash probing. Program written by Chance Tudor, CS major at
// the University of Alabama. CS 101, Spring 2018
#include <cstdlib>
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>

#include "hash.cpp"

using namespace std;

int main(int argc, char const *argv[]) {
  ifstream inFile; // input file
  string line; // string to hold entire line
  string word; // string to hold individual word
  int lineNum = 1; // line # tracker -- lines always start @ 1
  int totalWords = 0; // total words tracker
  int mySize = atoi(argv[3]); // takes command line size arg, converts to int
  HashTable theTable(mySize); // creates object theTable with size

  inFile.open(argv[1]); // opens input file
  if (!inFile.is_open()) { // checks if error when opening
    cout << "Could not open file " << argv[1] << endl;
    return 1; // 1 indicates error
  }

  else { // opens file
    while (getline(inFile, line)) { // gets entire line of text
      istringstream iss(line); // takes line and puts it into a stringstream

      while (iss >> word) { // parses line into individual words
        totalWords++; // counts total number of words
        if (strcmp(argv[4], "lp") == 0) { // calls for linear probing
          theTable.linearInsert(word, lineNum); // calls linear insert, passing the word and line number
        }
        else if (strcmp(argv[4], "qp") == 0) { // calls for quadratic probing
          theTable.quadraticInsert(word, lineNum); // calls quadratic insert, passing the word and line number
        }
        else if (strcmp(argv[4], "dh") == 0) { // calls for double hashing
          int arg = atoi(argv[5]); // sets the fifth command line argument as an integer
          theTable.doubleHashInsert(word, lineNum, arg); // calls double hash insert, passing word, line number, and argument
        }
      }

      lineNum++; // tracks line number
      iss.clear(); // clears iss var to hold a different word
    }
  }
  inFile.close(); // closes input file

  if (strcmp(argv[4], "lp") != 0) { cout << "\n"; } // for lame formatting purposes
  cout << "The number of words found in the file was " << totalWords << endl; // outputs total number of words found in file
  cout << "The number of unique words found in the file was " << theTable.getUniqueWords() << endl; // outputs total number of unique words found in file
  cout << "The number of collisions was " << theTable.getCollisions() << endl << endl; // outputs total number of collisions when inserting

  line.clear(); // clears string to hold entire line for reuse

  ifstream qFile; // query file
  qFile.open(argv[2]); // opens query file
  if (!qFile.is_open()) { // checks if error when opening
    cout << "Could not open file " << argv[2] << endl;
    return 1; // 1 indicates error
  }

  else { // opens file
    while (getline(qFile, line)) { // gets entire line of text
      istringstream iss(line); // takes line and puts it into a stringstream

      while (iss >> word) { // parses line into individual words
        if (strcmp(argv[4], "lp") == 0) { // calls for linear probing
          theTable.linearSearch(word); // calls linear insert, passing the word and line number
        }
        else if (strcmp(argv[4], "qp") == 0) { // calls for quadratic probing
          theTable.quadraticSearch(word); // calls quadratic insert, passing the word and line number
        }
        else if (strcmp(argv[4], "dh") == 0) { // calls for double hashing
          int arg = atoi(argv[5]); // sets the fifth command line argument as an integer
          theTable.doubleHashSearch(word, arg); // calls double hash insert, passing word, line number, and argument
        }
      }
      iss.clear(); // clears iss var to hold a different word
    }
  }
  qFile.close(); // closes query file

  return 0;
}
