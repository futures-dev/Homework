//
// Created by Computer on 27.05.2016.
//

#ifndef HOMEWORK_STDMAP3_H
#define HOMEWORK_STDMAP3_H

#include "SimilairProvider.h"
#include <map>

class StdMap3 : public SimilairProvider {
    std::map<char, std::map<int, std::map<std::string, std::vector<std::string>>>> words;

public:
    virtual void insert(const std::string &word, const StringContainer &dict);

    virtual std::vector<std::string> operator[](const std::string &word) const;

    virtual void output(const std::string &output) const;

    virtual ~StdMap3() { };
};


#endif //HOMEWORK_STDMAP3_H
