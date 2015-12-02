#include "block_searcher.h"

using namespace std;

//
// Коломиец Андрей БПИ143
// CLion 1.1.1 MinGW 3.21
//
std::vector<int> *block_substring_searcher::find_substrings(
        string &source, string &substring) {
    vector<int> *a = new vector<int>();
    int substringLength = substring.length();
    int sourceLength = source.length();
    if (substringLength > sourceLength)
        return a;
    string s = substring + "\1" + source;
    int sLength = substringLength + sourceLength;
    for (int blockStart = substringLength + 1; blockStart < sLength; blockStart++) {
        for (int prefixLength = 1; prefixLength < substringLength; prefixLength++) {
        }
    }
    return a;
    return nullptr;
}
