//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 22.05.2016 
//

#ifndef HOMEWORK_HASHTABLE_H
#define HOMEWORK_HASHTABLE_H

#include <unordered_set>
#include "StringContainer.h"


class HashTable : public StringContainer {
    class hash_function {
    public:
        hash_function() { }

        unsigned int operator()(const std::string &str) const {
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

        bool  operator()(const std::string &A, const std::string &B) const {
            return (A == B);
        }
    };

    std::unordered_set<std::string, hash_function, equality> words;
public:
    void insert(const std::string &word);

    bool search(const std::string &word);

    virtual ~HashTable() { }
};


#endif //HOMEWORK_HASHTABLE_H
