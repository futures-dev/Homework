#include "SimilairProvider.h"

using namespace std;

void SimilairProvider::suggest_insertion(const string &a_word, const StringContainer &dict,
                                         set<string> &suggestions) const {
    string word(a_word);
    int len = word.length();
    for (int i = 0; i <= len; i++) {
        // insert before i-th letter
        word.insert(i, 1, 'a');
        while (word[i] <= 'z') {
            if (dict.search(word)) {
                suggestions.insert(word);
            }
            word[i]++;
        }
        word.erase(i, 1);
    }
}

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

void SimilairProvider::suggest_odd(const string &a_word, const StringContainer &dict, set<string> &suggestions) const {
    string word(a_word);
    int len = word.length();
    char temp;
    for (int i = 0; i < len; i++) {
        // erase i-th letter
        temp = word[i];
        word.erase(i, 1);
        if (dict.search(word)) {
            suggestions.insert(word);
        }
        // insert back
        word.insert(i, 1, temp);
    }
}

void SimilairProvider::suggest_adjacent(const string &a_word, const StringContainer &dict,
                                        set<string> &suggestions) const {
    string word(a_word);
    int len = word.length();
    char temp;
    for (int i = 1; i < len; i++) {
        // swap i-1 -th and i-th letters
        temp = word[i - 1];
        word[i - 1] = word[i];
        word[i] = temp;
        if (dict.search(word)) {
            suggestions.insert(word);
        }
        word[i] = word[i - 1];
        word[i - 1] = temp;
    }
}