/*Kolos Maria
BSE141-1
Project #13 - Hospital*/

#include "parts.h"
#include <iostream>

/*Add new part*/
void NameContainer::addPart(string const &part, int quantity, string const &subpart) {
	Part *current;
	Part *subp = new Part(subpart);

	//searching for a Part
	current = lookup(part);
	//and adding the subpart to it
	current->subparts.insert(std::pair<Part *, int>(subp, quantity));

	//adding the part to the nameMap
	nameMap.insert(std::pair<string, Part *>(subpart, subp));
}

//returns a Part from the nameMap by name
Part *NameContainer::lookup(string const &name) {
	//if there is no such part
	if (nameMap.find(name) == nameMap.end()) {
		//creating one
		Part *part = new Part(name);
		//and adding to nameMap
		nameMap.insert(std::pair<string, Part *>(name, part));
		return part;
	}
	else
		return nameMap.at(name);
}

//Part's subparts info
void Part::describe(void) {
	std::cout << "Part " << this->name << " subparts are:" << endl;
	if (this->subparts.size() == 0)
		std::cout << "\tIt has no subparts." << endl;
	else {
		for (auto it = this->subparts.begin(); it != this->subparts.end(); it++) {
			std::cout << "\t" << it->second << " " << it->first->name << endl;
		}
	}
}

//All Part's subparts info
void Part::describeAll(void) {
	std::cout << this->level << "Part " << this->name << " subparts are:" << endl;
	if (this->subparts.size() == 0)
		std::cout << this->level << "\tIt has no subparts." << endl;
	else {
		for (auto it = this->subparts.begin(); it != this->subparts.end(); it++) {
			std::cout << "  " << this->level << it->first->level << it->second << " " << it->first->name << endl;
			//changing the level accoring to the hierarchy
			it->first->level += "  " + this->level;
			//just adding some recursion to go deeper
			it->first->describeAll();

		}

	}
	this->level = "";//cleaning up the level for the next method calls
	
}

//Counts the number of instances of the part pointed to by p
int Part::countHowMany(Part const *p) {
	int res = this == p ? 1 : 0;//if this contains p the multiplier is 1

	//iterating all subparts
	for (auto it = this->subparts.begin(); it != this->subparts.end(); it++) {
		res += it->second * it->first->countHowMany(p);

	}
	return res;
	
	
}
