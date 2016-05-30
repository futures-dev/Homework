//
// Andrei Kolomiets 143-1
// CLion 2016.1.2 MinGW 3.21 GCC 4.9.1
// 21.05.2016 
//

#ifndef HOMEWORK_PREFIXTREE_H
#define HOMEWORK_PREFIXTREE_H

#include "StringContainer.h"


class PrefixTree : public StringContainer {
    static const char offset = 0x27; //'
    static const int alphabet_length = 'z' - offset + 1;

    struct PrefixTreeNode {
        char letter;
        PrefixTreeNode *links[alphabet_length] = {nullptr};
        bool full;

        PrefixTreeNode(char letter, bool full) : letter(letter), full(full) { }

        ~PrefixTreeNode();
    };

    PrefixTreeNode *root;

    inline int charToIdx(char c) const;


public:
    PrefixTree();

    void insert(const std::string &s);

    bool search(const std::string &s) const;

    virtual ~PrefixTree();
};


#endif //HOMEWORK_PREFIXTREE_H
