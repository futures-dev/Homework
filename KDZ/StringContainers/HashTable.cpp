//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 22.05.2016 
//

#include "HashTable.h"

void HashTable::insert(const std::string &word) {
    words.insert(word);
}

bool HashTable::search(const std::string &word) {
    return words.find(word) != words.end();
}
