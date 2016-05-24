//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 22.05.2016 
//

#ifndef HOMEWORK_STDSET_H
#define HOMEWORK_STDSET_H

#include <set>
#include "StringContainer.h"

class StdSet : public StringContainer {
    std::set<std::string> words;
public:
    void insert(const std::string &word);

    bool search(const std::string &word) const;

    virtual ~StdSet() { }
};


#endif //HOMEWORK_STDSET_H