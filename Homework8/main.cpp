//
// Created by Computer on 01.12.2015.
//

#include "edge_searcher.h"
#include "block_searcher.h"
#include <iostream>

using namespace std;
int main() {
    edge_substring_searcher *edge_searcher = new edge_substring_searcher();
    string sub = "ba";
    string s = "abbabaabbaababba";
    vector<int> a = *edge_searcher->find_substrings(s, sub);
    block_substring_searcher *block_searcher = new block_substring_searcher();
    vector<int> b = *block_searcher->find_substrings(s, sub);
    for (int i = 0; i < a.size(); i++)
        cout << a[i] << " ";
    for (int i = 0; i < b.size(); i++)
        cout << b[i] << " ";
    cin >> s;
    return 0;
}