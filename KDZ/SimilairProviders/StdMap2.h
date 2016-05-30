//
// Andrei Kolomiets 143-1
// CLion 2016.1.2 MinGW 3.21 GCC 4.9.1
// 25.05.2016 
//

#ifndef HOMEWORK_STDMAP2_H
#define HOMEWORK_STDMAP2_H

#include "SimilairProvider.h"
#include <map>

class StdMap2 : public SimilairProvider {
    std::map<int, std::map<std::string, std::vector<std::string>>> words;

public:
    virtual void insert(const std::string &word, const StringContainer &dict);

    virtual std::vector<std::string> operator[](const std::string &word) const;

    virtual void output(const std::string &output) const;

    virtual ~StdMap2() { };
};


#endif //HOMEWORK_STDMAP2_H
