//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 21.05.2016 
//

#include "PrefixTree.h"

bool PrefixTree::search(const std::string &s) {
    int len = s.length();
    PrefixTreeNode *current = root;
    for (int i = 0; i < len; i++) {
        PrefixTreeNode *&nextNode = current->links[charToIdx(s[i])];
        if (nextNode == nullptr) {
            return false;
        }
        current = nextNode;
    }
    return true;
}

void PrefixTree::insert(const std::string &s) {
    int len = s.length();
    PrefixTreeNode *current = root;
    for (int i = 0; i < len; i++) {
        PrefixTreeNode *&nextNode = current->links[charToIdx(s[i])];
        if (nextNode == nullptr) {
            nextNode = new PrefixTreeNode(s[i], i + 1 == len);
        }
        current = nextNode;
    }
}

int inline PrefixTree::charToIdx(char c) {
    return c - offset;
}

PrefixTree::PrefixTree() {
    root = new PrefixTreeNode('\0', false);
}