#ifndef STRINGS_PROJECT_SUBSTRING_SEARCHER_H
#define STRINGS_PROJECT_SUBSTRING_SEARCHER_H

#include <string>
#include <vector>

using namespace std;

/**
 * A class to be extended with your implementation in order to implement two types of the algorithm
 * that corresponds to your assignment task of searching all of the substrings positions.
 *
 * You don't need to implement substring_searcher class itself, but it's heirs.
 */
class substring_searcher {
public:
    /**
     * Method to find all occurrences of a substring in source string.
     *
     * Parameters:
     *  string& source    - a reference to a string, where positions of substrings are searched.
     *  string& substring - a reference to a string, occurrences of which are searched in the source string.
     *
     * Returns:
     *  a pointer to integer values vector which should contain all values of indices of starts of passed substring
     *  in the source string. In case of zero such substrings an empty vector should be returned (not a nullptr).
     */
    virtual vector<int> *find_substrings(string &source, string &substring) = 0;
};

#endif //STRINGS_PROJECT_SUBSTRING_SEARCHER_H
