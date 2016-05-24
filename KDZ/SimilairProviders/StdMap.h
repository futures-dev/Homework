//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 22.05.2016
//

#ifndef HOMEWORK_STDMAPSIMILAIRPROVIDER_H
#define HOMEWORK_STDMAPSIMILAIRPROVIDER_H

#include "SimilairProvider.h"
#include <string>
#include <map>
#include <set>

class StdMap : public SimilairProvider {
    std::map<std::string, std::set<std::string>> words;

public:
    virtual void insert(const std::string &word, const StringContainer &dict);

    virtual std::set<std::string> operator[](const std::string &word) const;

    virtual void output(const std::string &output) const;

    virtual ~StdMap() { };
};


#endif //HOMEWORK_STDMAPSIMILAIRPROVIDER_H
