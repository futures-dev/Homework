#include "SimilairProvider.h"

using namespace std;

void SimilairProvider::suggest_replacement(const string &a_word, const StringContainer &dict,
                                           set<string> &suggestions) const {
    string word(a_word);
    int len = word.length();
    char temp;
    for (int i = 0; i < len; i++) {
// replace i-th letter
        temp = word[i];
        for (char c = 'a'; c <= 'z'; c++) {
// replace by c char
            if (c == temp) {
// same word
                continue;
            }
            word[i] = c;
            if (dict.search(word)) {
                suggestions.insert(word);
            }
        }
        word[i] = temp;
    }
}