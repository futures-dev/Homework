//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 22.05.2016
//

#ifndef HOMEWORK_STDMAPSIMILAIRPROVIDER_H
#define HOMEWORK_STDMAPSIMILAIRPROVIDER_H

#include "SimilairProvider.h"
#include <map>

class StdMap : public SimilairProvider<std::map<std::string, std::vector<string>>, std::vector<string>::iterator> {
    std::map<std::string, std::vector<string>> words;
    StringContainer &dict;
public:
    StdMap(const StringContainr &dict) : dict(dict) { };

    virtual void insert(const std::string &word, const std::string &similair) {
        words.
    }

};


#endif //HOMEWORK_STDMAPSIMILAIRPROVIDER_H
