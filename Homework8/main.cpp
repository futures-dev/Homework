//
// Created by Computer on 01.12.2015.
//

#include "edge_searcher.h"
#include<string>

int main() {
    auto edge_searcher = new edge_substring_searcher();
    string sub = "ba";
    string s = "abbabaabbaababba";
    edge_searcher->find_substrings(s, sub);
    return 0;
}