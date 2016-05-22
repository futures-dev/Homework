#ifndef  _DICTIONARY_H_
#define  _DICTIONARY_H_

/*Kolos Maria
BSE 141-1
Project #14 SpellChecker*/

#include  <iostream>
#include  <fstream>
#include  <vector>
#include  <list>
#include  <algorithm>
#include  <string>

#include  "hashset.h"
#include  "hashset.cpp"


using namespace std;

class hash_function {
public:
	hash_function() { }

	/*Hash*/
	unsigned int operator()(const string &key) const {
		unsigned int hash = 0;
		int len = key.length();
		for (int i = 0; i < len; i++)
			hash = (hash * 1664525) + (unsigned char) (key[i]) + 1013904223;

		return hash;

	}

};

class equality {
public:
	equality() { }

	bool  operator()(const string &A, const string &B) const {
		return (A == B);
	}
};

class Dictionary : public HashSet<string, hash_function, equality> {

	// Complete definition
public:
	Dictionary(string filename);//constructor with a parameter

	void removeLetter(string &s);

	// Removal of each letter
	void transpose(string &s);

	// Transposing of adjacent letters. The main method
	void transposeBranch(string &s, int pos);

	// Transposing of adjacent letters. A recursive helper
	void replacement(string &s);

	// Replacement of each letter
	void inserting(string &s);// Inserting any letter at any position in a word

	list<string> suggestions;//list of suggestions 

};

#endif
