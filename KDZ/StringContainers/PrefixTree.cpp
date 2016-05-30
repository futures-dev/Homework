//
// Andrei Kolomiets 143-1
// CLion 2016.1.2 MinGW 3.21 GCC 4.9.1
// 21.05.2016 
//

#include "PrefixTree.h"

bool PrefixTree::search(const std::string &s) const {
    int len = s.length();
    PrefixTreeNode *current = root;
    for (int i = 0; i < len; i++) {
        PrefixTreeNode *&nextNode = current->links[charToIdx(s[i])];
        if (nextNode == nullptr) {
            return false;
        }
        current = nextNode;
    }
    return current->full;
}

void PrefixTree::insert(const std::string &s) {
    if (s.empty()) {
        // s equals root
        return;
    }
    int len = s.length();
    PrefixTreeNode *current = root;
    for (int i = 0; i < len; i++) {
        int idx = charToIdx(s[i]);

        if (current->links[idx] == nullptr) {
            current->links[idx] = new PrefixTreeNode(s[i], false);
        }
        current = current->links[idx];
    }
    current->full = true;
}

int inline PrefixTree::charToIdx(char c) const {
    return c - offset;
}

PrefixTree::PrefixTree() {
    root = new PrefixTreeNode('\0', false);
}

PrefixTree::~PrefixTree() {
    delete root;
}

PrefixTree::PrefixTreeNode::~PrefixTreeNode() {
    for (int i = 0; i < alphabet_length; i++) {
        delete links[i];
    }
}