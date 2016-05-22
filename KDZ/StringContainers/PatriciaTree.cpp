//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 21.05.2016 
//

#include "PatriciaTree.h"

bool PatriciaTree::check(const std::string &word1, int start1, const std::string &word2, int start2, int len) {
    if (start1 + len > word1.length() || start2 + len > word2.length()) {
        return false;
    }
    for (int i = 0; i < len; i++) {
        if (word1[i + start1] != word2[i + start2]) {
            return false;
        }
    }
    return true;
}

void PatriciaTree::insert(const std::string &word) {
    auto current = root;
    int idx = 0;
    while (idx < word.length()) {
        int linkN = current->links.size();
        for (int i = 0; i < linkN; i++) {
            int linkLen = current->links[i]->value.length();
            if (check(word, idx, current->links[i]->value, 0, linkLen)) {
                current = current->links[i];
                idx += linkLen;
                continue;
            }
        }
        current->links.push_back(new PatriciaTreeNode(word.substr(idx)));
        break;
    }
}

bool PatriciaTree::search(const std::string &word) {
    auto current = root;
    int idx = 0;
    while (idx < word.length()) {
        int linkN = current->links.size();
        for (int i = 0; i < linkN; i++) {
            int linkLen = current->links[i]->value.length();
            if (check(word, idx, current->links[i]->value, 0, linkLen)) {
                current = current->links[i];
                idx += linkLen;
                continue;
            }
        }
        return false;
    }
    return true;
}
