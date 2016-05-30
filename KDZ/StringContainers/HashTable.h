//
// Andrei Kolomiets 143-1
// CLion 2016.1.2 MinGW 3.21 GCC 4.9.1
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

        unsigned int operator()(const std::string &str) const;
    };

    class equality {
    public:
        equality() { }

        bool operator()(const std::string &A, const std::string &B) const;
    };

    std::unordered_set<std::string, hash_function, equality> words;
public:
    void insert(const std::string &word);

    bool search(const std::string &word) const;

    virtual ~HashTable() { }
};


#endif //HOMEWORK_HASHTABLE_H
