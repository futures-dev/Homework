//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 22.05.2016
//

#ifndef HOMEWORK_SIMILAIRPROVIDER_H
#define HOMEWORK_SIMILAIRPROVIDER_H

#include <string>

template<class Container, class Iterator>
class SimilairProvider {
public:
    virtual void insert(const std::string &word) = 0;

    virtual Iterator operator[](const std::string &word) const = 0;
};


#endif //HOMEWORK_SIMILAIRPROVIDER_H
