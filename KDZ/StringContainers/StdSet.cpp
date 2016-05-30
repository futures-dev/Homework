//
// Andrei Kolomiets 143-1
// CLion 2016.1.2 MinGW 3.21 GCC 4.9.1
// 22.05.2016 
//

#include "StdSet.h"

void StdSet::insert(const std::string &word) {
    words.insert(std::string(word));
}

bool StdSet::search(const std::string &word) const {
    return !(words.find(word) == words.end());
}