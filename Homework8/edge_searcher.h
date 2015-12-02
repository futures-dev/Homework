#ifndef STRINGS_PROJECT_EDGE_SUBSTRING_H
#define STRINGS_PROJECT_EDGE_SUBSTRING_H

#include "substring_searcher.h"

/**
 * Here you need to implement a class to implement the function of all
 * substring occurrences with edge algorithm (check course presentations).
 *
 * Create edge_searcher.cpp file for implementation.
 */
class edge_substring_searcher : public substring_searcher {
public:
    /**
     * Check the inherited method documentation.
     *
     * Here you need to implement substrings searching with edge algorithm.
     */
    vector<int> *find_substrings(string &source, string &substring);
};


#endif //STRINGS_PROJECT_EDGE_SUBSTRING_H
