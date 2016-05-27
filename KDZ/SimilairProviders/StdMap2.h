//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 25.05.2016 
//

#ifndef HOMEWORK_STDMAP2_H
#define HOMEWORK_STDMAP2_H

#include "SimilairProvider.h"
#include <map>

class StdMap2 : public SimilairProvider {
    std::map<int, std::map<std::string, std::set<std::string>>> words;

public:
    virtual void insert(const std::string &word, const StringContainer &dict);

    virtual std::set<std::string> operator[](const std::string &word) const;

    virtual void output(const std::string &output) const;

    virtual ~StdMap2() { };
};


#endif //HOMEWORK_STDMAP2_H
