//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 21.05.2016 
//

#ifndef HOMEWORK_PREFIXTREE_H
#define HOMEWORK_PREFIXTREE_H

#include "StringContainer.h"


class PrefixTree : public StringContainer {
    static const int alphabet_length = 26;
    static const char offset = 'a';

    struct PrefixTreeNode {
        char letter;
        PrefixTreeNode *links[alphabet_length] = {nullptr};
        bool full;

        PrefixTreeNode(char letter, bool full) : letter(letter), full(full) { }
    };

    PrefixTreeNode *root;

    inline int charToIdx(char c);

public:
    PrefixTree();

    void insert(const std::string &s);

    bool search(const std::string &s);

    virtual ~PrefixTree() { }
};


#endif //HOMEWORK_PREFIXTREE_H
