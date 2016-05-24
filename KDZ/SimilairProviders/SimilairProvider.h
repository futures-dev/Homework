//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 22.05.2016
//

#ifndef HOMEWORK_SIMILAIRPROVIDER_H
#define HOMEWORK_SIMILAIRPROVIDER_H

#include "../StringContainers/StringContainer.h"
#include <set>
#include <string>

class SimilairProvider {
protected:
    void suggest_insertion(const std::string &a_word, const StringContainer &dict,
                           std::set<std::string> &suggestions) const;

    void suggest_replacement(const std::string &a_word, const StringContainer &dict,
                             std::set<std::string> &suggestions) const;

    void suggest_odd(const std::string &a_word, const StringContainer &dict, std::set<std::string> &suggestions) const;

    void suggest_adjacent(const std::string &a_word, const StringContainer &dict,
                          std::set<std::string> &suggestions) const;
public:
    virtual void insert(const std::string &word, const StringContainer &dict) = 0;

    virtual std::set<std::string> operator[](const std::string &word) const = 0;

    virtual void output(const std::string &output) const = 0;

    virtual ~SimilairProvider() { };
};


#endif //HOMEWORK_SIMILAIRPROVIDER_H
