//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 22.05.2016
//

#ifndef HOMEWORK_SPELLCHECKER_H
#define HOMEWORK_SPELLCHECKER_H

#include <string>
#include <vector>
#include <set>

using namespace std;

class SpellChecker {
    const char *wordRegex = "([a-zA-Z][a-zA-Z'\\-]*)";
    const char *POSSIBLE_ACTIONS_STRING = "Возможные действия - (R) заменить | (I) игнорировать | (X) завершить работу";
    const char *POSSIBLE_REPLACEMENTS_STRING = "Возможные действия - (N) сделать замену на слово под номером N, где N - число из списка | (I) игнорировать";
    const char *IGNORE_ALL_STRING = "Игнорировать все вхождения данного слова? Возможные действия - (A) игнорировать все | (S) не игнорировать все";
    const char *REPLACE_ALL_STRING = "Заменить все вхождения данного слова? Возможные действия - (A) заменить все | (S) не заменять все";
    const char *MAYBE_STRING = "Возможно, имелось в виду:";
    const char *WORD_FOUND_STRING = "Обнаружено слово ";
    const char *WORD_MISSING_STRING = " - оно отсутствует в словаре";

    unsigned char hash(const std::string &str) const;

    vector<string> *hashset;

    void print_sorted(const string &output) const;

    size_t _size;
public:
    SpellChecker() : hashset(new vector<string>[UINT8_MAX + 1]) { };

    bool d_search(const string &word) const;

    bool dwd_insert(const string &word);

    bool d_delete(const string &word);

    size_t d_count() const;

    void d_print(const string &output, bool sorted = false) const;

    void load_words(const string &input);

    void spell_check(const string &input, const string &output) const;

    void suggest_insertion(const string &a_word, set<string> &suggestions) const;

    void suggest_replacement(const string &a_word, set<string> &suggestions) const;

    void suggest_odd(const string &a_word, set<string> &suggestions) const;

    void suggest_adjacent(const string &a_word, set<string> &suggestions) const;
};


#endif //HOMEWORK_SPELLCHECKER_H
