//
// Andrei Kolomiets 143-1
// CLion 2016.1.1 MinGW 3.2.1
// 21.05.2016
//

#ifndef  _DICTIONARY_H_
#define  _DICTIONARY_H_

#include  <iostream>
#include  <vector>
#include  <list>
#include  <algorithm>
#include  <string>

#include  "hashset.h"
#include  "hashset.cpp"

using namespace std;

class hash_function {
public:
    hash_function() { }

    unsigned int operator()(const string &str) const {
        // Rot13
        unsigned int hash = 0;
        int len = str.length();
        for (int i = 0; i < len; i++) {
            hash += (unsigned char) (str[i]);
            hash -= (hash << 13) | (hash >> 19);
        }
        return hash;
    }
};

class equality {
public:
    equality() { }

    bool  operator()(const string &A, const string &B) const {
        return (A == B);
    }
};

class Dictionary : public HashSet<string, hash_function, equality> {

public:
    Dictionary(const string &s) {
        ifstream fin(s);
        string buf;
        if (!fin.is_open()) {
            throw invalid_argument("File " + s + " Not Found");
        }
        while (getline(fin, buf)) {
            // each line contains one word
            insert(buf);
        }
    }

    Dictionary() {
        // Why not?
    }
};

#endif
