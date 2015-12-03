#ifndef STRINGS_PROJECT_BLOCK_SUBSTRING_H
#define STRINGS_PROJECT_BLOCK_SUBSTRING_H

#include "substring_searcher.h"

/**
 * Here you need to implement a class to implement the function of all
 * substring occurrences with block algorithm (check course presentations).
 *
 * Create block_searcher.cpp file for implementation.
 */
class block_substring_searcher : public substring_searcher {
public:
    /**
     * Check the inherited method documentation.
     *
     * Here you need to implement substrings searching with block algorithm.
     */
    vector<int> *find_substrings(string &source, string &substring);
};


#endif //STRINGS_PROJECT_BLOCK_SUBSTRING_H
