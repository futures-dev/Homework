//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 22.05.2016
//

#ifndef HOMEWORK_TREE_H
#define HOMEWORK_TREE_H

#include <string>

class StringContainer {
public:
    virtual void insert(const std::string &s) = 0;

    virtual bool search(const std::string &s) const = 0;

    virtual ~StringContainer() { };
};


#endif //HOMEWORK_TREE_H
