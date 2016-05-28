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

class StdMap : public SimilairProvider {
    std::map<std::string, std::vector<std::string>> words;

public:
    virtual void insert(const std::string &word, const StringContainer &dict);

    virtual std::vector<std::string> operator[](const std::string &word) const;

    virtual void output(const std::string &output) const;

    virtual ~StdMap() { };
};


#endif //HOMEWORK_STDMAPSIMILAIRPROVIDER_H
