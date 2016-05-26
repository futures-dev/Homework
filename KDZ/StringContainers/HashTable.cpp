//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 22.05.2016 
//

#include "HashTable.h"

void HashTable::insert(const std::string &word) {
    words.insert(word);
}

bool HashTable::search(const std::string &word) const {
    return words.find(word) != words.end();
}

unsigned int HashTable::hash_function::operator()(const std::string &str) const {
    // Rot13
    unsigned int hash = 0;
    int len = str.length();
    for (int i = 0; i < len; i++) {
        hash += (unsigned char) (str[i]);
        hash -= (hash << 13) | (hash >> 19);
    }
    return hash;
}

bool HashTable::equality::operator()(const std::string &A, const std::string &B) const {
    return (A == B);
}