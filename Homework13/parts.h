/*Kolos Maria
BSE141-1
Project #13 - Hospital*/

// parts.h

#ifndef _PARTS_H_
#define _PARTS_H_

#include <vector>
#include <map>
#include <string>

using namespace std;

//**************** Part ****************
class Part {
public:
	string name;
	map<Part *, int> subparts;//map of subparts

	Part(string const &n) : name(n) { };

	void describe(void);

	void describeAll(void);

	//method that displays all subparts of a Part
	int countHowMany(Part const *p);

private:
	string level = "";//the level in hierarchy in the output
};


//**************** NameContainer ****************
class NameContainer {

private:
	map<string, Part *> nameMap;

public:

	NameContainer(void) { };

	void addPart(string const &part, int quantity, string const &subpart);

	Part *lookup(string const &name);
	// You can add some methods here 
};

#endif