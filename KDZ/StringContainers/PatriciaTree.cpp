//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 21.05.2016 
//

#include "PatriciaTree.h"

int PatriciaTree::check(const std::string &word1, int start1, const std::string &word2, int start2, int len) const {
    if (start1 + len > word1.length() || start2 + len > word2.length()) {
        return 0;
    }
    int i = 0;
    for (; i < len; i++) {
        if (word1[i + start1] != word2[i + start2]) {
            return 0;
        }
    }
    return i;
}

void PatriciaTree::insert(const std::string &word) {
    auto current = root;
    int idx = 0;
    int len = word.length();
    while (idx < len) {
        int linkN = current->links.size();
        int i = 0;
        for (; i < linkN; i++) {
            int linkLen = current->links[i]->value.length();
            int prefixLen = check(word, idx, current->links[i]->value, 0, linkLen);
            if (prefixLen == idx + len) {
                // word already inserted
                return;
            }
            if (prefixLen == linkLen) {
                // node is prefix of word
                // make it current
                // continue while
                current = current->links[i];
                idx += linkLen;
                break;
            }
            if (prefixLen > 0) {
                // node has common prefix with word
                // make node prefix
                PatriciaTreeNode *prefixNode = new PatriciaTreeNode(word.substr(idx, prefixLen));
                current->links[i]->value = current->links[i]->value.substr(prefixLen);
                prefixNode->links.push_back(current->links[i]);
                current->links[i] = prefixNode;
                prefixNode->links.push_back(new PatriciaTreeNode(word.substr(idx + prefixLen)));
                return;
            }
        }
        if (i == linkN) {
            current->links.push_back(new PatriciaTreeNode(word.substr(idx)));
            return;
        }
    }
}

bool PatriciaTree::search(const std::string &word) const {
    auto current = root;
    int idx = 0;
    int len = word.length();
    while (current && idx < len) {
        int linkN = current->links.size();
        int i = 0;
        for (; i < linkN; i++) {
            int linkLen = current->links[i]->value.length();
            if (check(word, idx, current->links[i]->value, 0, linkLen)) {
                current = current->links[i];
                idx += linkLen;
                break;
            }
        }
        if (i == linkN) {
            return false;
        }
    }
    return idx == len;
}
