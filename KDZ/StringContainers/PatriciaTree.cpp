//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 21.05.2016 
//

#include "PatriciaTree.h"

int PatriciaTree::check(const std::string &word1, int start1, const std::string &word2, int start2) const {
    int len1 = word1.length();
    int len2 = word2.length();
    int i = start1;
    while (start1 < len1 && start2 < len2) {
        if (word1[start1++] != word2[start2++]) {
            return start1 - i;
        }
    }
    return start1 - i;
}

void PatriciaTree::insert(const std::string &word) {
    auto current = root;
    int idx = 0;
    int len = word.length();
    while (idx < len) {
        int linkN = current->links.size();
        int i = 0;
        for (; i < linkN; i++) {
            int prefixLen = check(word, idx, current->links[i]->value, 0);
            if (prefixLen == idx + len) {
                // word already inserted
                return;
            }
            int linkLen = current->links[i]->value.length();
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
            if (check(word, idx, current->links[i]->value, 0)) {
                current = current->links[i];
                idx += current->value.length();
                break;
            }
        }
        if (i == linkN) {
            return false;
        }
    }
    return idx == len;
}
