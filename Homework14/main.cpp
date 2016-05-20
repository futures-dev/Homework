//
// Andrei Kolomiets 143-1
// CLion 2016.1.1 MinGW 3.2.1
// 21.05.2016
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "dictionary.h"

using namespace std;

void lower(string &s);

string stripPunct(const string &s);

void checkSpelling(ifstream &in, Dictionary &dict);

inline void eval_suggestion(Dictionary &dict, Dictionary &suggestions, const string &word);

inline void suggest_adjacent(Dictionary &dict, Dictionary &suggestions, string word);

inline void suggest_odd(Dictionary &dict, Dictionary &suggestions, string &word);

inline void suggest_replacement(Dictionary &dict, Dictionary &suggestions, string &word);

inline void suggest_insertion(Dictionary &dict, Dictionary &suggestions, string &word);

int main(int argc, char *argv[]) {

    // Output usage message if improper command line args were given.
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " wordlist_filename input_file\n";
        return EXIT_FAILURE;
    }

    ifstream inf(argv[2]);
    if (!inf) {
        cerr << "Could not open " << argv[2] << "\n";
        return EXIT_FAILURE;
    }

    // Read dictionary, but let user know what we are working on.
    cout << "Loading dictionary, this may take awhile...\n";

    Dictionary d(argv[1]);

    checkSpelling(inf, d);

    inf.close();

    return EXIT_SUCCESS;
}

void checkSpelling(ifstream &in, Dictionary &dict) {

    int line_number = 0;

    while (in) {
        line_number++;

        string line;
        getline(in, line);

        stringstream ss(stringstream::in | stringstream::out);
        ss << line;

        string word;

        while (ss >> word) {
            // preprocess
            // btw, lower and stripPunct have way different signatures..
            lower(word);
            word = stripPunct(word);

            auto found = dict.search(word);
            if (!found) {
                cout << "Line " << line_number << ": '" << word << "'" << endl;
                cout << "\tsuggestions:" << endl;

                // store suggestions not to repeat them
                Dictionary suggestions;

                // suggest different ways
                suggest_adjacent(dict, suggestions, word);
                suggest_odd(dict, suggestions, word);
                suggest_replacement(dict, suggestions, word);
                suggest_insertion(dict, suggestions, word);
            }

        }

    }

}

void suggest_insertion(Dictionary &dict, Dictionary &suggestions, string &word) {
    // to make sure `word` is not altered and make it `const string &word`
    // string editable_word(word);
    int len = word.length();
    for (int i = 0; i <= len; i++) {
        // insert before i-th letter
        word.insert(i, 1, 'a');
        while (word[i] <= 'z') {
            eval_suggestion(dict, suggestions, word);
            word[i]++;
        }
        word.erase(i, 1);
    }
}

void suggest_replacement(Dictionary &dict, Dictionary &suggestions, string &word) {
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
            eval_suggestion(dict, suggestions, word);
        }
        word[i] = temp;
    }
}

void suggest_odd(Dictionary &dict, Dictionary &suggestions, string &word) {
    int len = word.length();
    char temp;
    for (int i = 0; i < len; i++) {
        // erase i-th letter
        temp = word[i];
        word.erase(i, 1);
        eval_suggestion(dict, suggestions, word);
        // insert back
        word.insert(i, 1, temp);
    }
}

void suggest_adjacent(Dictionary &dict, Dictionary &suggestions, string word) {
    int len = word.length();
    char temp;
    for (int i = 1; i < len; i++) {
        // swap i-1 -th and i-th letters
        temp = word[i - 1];
        word[i - 1] = word[i];
        word[i] = temp;
        eval_suggestion(dict, suggestions, word);
        word[i] = word[i - 1];
        word[i - 1] = temp;
    }
}

void eval_suggestion(Dictionary &dict, Dictionary &suggestions, const string &word) {
    if (dict.search(word) && !suggestions.search(word)) {
        // correct and new suggestion
        cout << "\t\t" << word << endl;
        suggestions.insert(word);
    }
}

void lower(string &s) {
    // Ensures that a word is lowercase
    for (int i = 0; i < s.length(); i++) {
        s[i] = tolower(s[i]);
    }
}

string stripPunct(const string &s) {
    // Remove any single trailing
    // punctuation character from a word.
    if (ispunct(s[s.length() - 1])) {
        return s.substr(0, s.length() - 1);
    }
    else {
        return s;
    }
}

