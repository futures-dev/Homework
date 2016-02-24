//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 24.02.2016
//

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <stdlib.h>
#include "DNARepairer.h"

// typedef DNA is awful as every name here contains DNA

void DNARepairer::readFile(string filename) {
    {
        // open file stream
        ifstream file(filename, ios_base::in);

        if (!file) {
            throw std::invalid_argument("File could not be opened");
        }

        string line; // input buffer
        getline(file, line); // line contains the number of lines
        int linesNumber = atoi(line.c_str());
        int i = 0;
        Node<LinkedList<DNAElement>> *current = DNAStorage.getPreHead();
        while (getline(file, line)) {
            if (++i > linesNumber) {
                break; // read enough
            }
            Node<LinkedList<DNAElement>> *node = new Node<LinkedList<DNAElement>>; // new DNA chain
            istringstream words(line); // token stream
            string word; // word buffer

            // input
            while (words >> word) {
                DNAElement element;
                element.readString(word);
                node->value.addElementToEnd(element);
            }

            current->next = node; // add new node to the list
            current = current->next;
        }
        if (i < linesNumber) {
            throw invalid_argument("Not enough strings in input");
        }
    }
}

LinkedList<LinkedList<DNAElement>> &DNARepairer::getDNAStorage(void) {
    return DNAStorage;
}

void DNARepairer::repairDNA(void) {
    int idNumber = 0; // how many IDs found while repairing
    LinkedList<LinkedList<DNAElement>> DNAStorageNew; // repaired DNAStorage
    char ids['z' - 'a' + 1]; // indices of IDs chains in DNAStorageNew
    for (int i = 0; i <= 'z' - 'a'; i++) {
        ids[i] = -1; // not found
    }

    // In each chain,
    // one-by-one process elements.
    // If next element is from same base and number is consequent,
    // move them together.
    Node<LinkedList<DNAElement>> *dnaNode = DNAStorage.getPreHead();
    while (dnaNode->next) {
        dnaNode = dnaNode->next;
        Node<DNAElement> *before = dnaNode->value.getPreHead();
        Node<DNAElement> *last = before;
        char currentId; // current sequence Id
        int currentNumber; // current sequence last number
        while (last->next) {
            before = last;
            last = before->next;
            currentId = last->value.id[0];
            currentNumber = last->value.number;
            while (last->next && last->next->value.id[0] == currentId &&
                   last->next->value.number == (++currentNumber)) {
                // when everything but the number matches, we actually increment currentNumber extra time
                // but that's ok because the loop will certainly break and there are no recurring numbers in base
                last = last->next;
            }
            currentId -= 'a'; // shift to array indexing
            int index = ids[currentId]; // get base-corresponding list index
            if (index < 0) {
                // create new list for base
                ids[currentId] = index = idNumber;
                idNumber++;
                // why not use pointers?
                DNAStorageNew.addElementToEnd(*new LinkedList<DNAElement>());
            }
            // find place where to put new elements
            Node<DNAElement> *current = DNAStorageNew[index].getPreHead();
            // last number less than current (no recurring numbers)
            while (current->next && (current->next->value.number < currentNumber)) {
                current = current->next;
            }
            // insertion
            DNAStorageNew[index].moveNodesAfter(current, before, last);
            last = before; // assert(last.value is nullptr, last is prehead)
        }
    }

    // DNAStorage <- DNAStorageNew
    Node<LinkedList<DNAElement>> *prev = DNAStorage.getPreHead();
    Node<LinkedList<DNAElement>> *last = DNAStorage.getPreHead();
    while (last->next) {
        prev = last;
        last = last->next;
    }
    Node<LinkedList<DNAElement>> *lastNew = DNAStorageNew.getPreHead();
    while (lastNew->next) {
        lastNew = lastNew->next;
    }
    DNAStorage.moveNodesAfter(DNAStorage.getPreHead(), DNAStorageNew.getPreHead(), lastNew);
    DNAStorageNew.moveNodesAfter(DNAStorageNew.getPreHead(), prev, last);
}

void DNARepairer::printDNAStorage(void) {
    // foreach DNA chain
    Node<LinkedList<DNAElement>> *dnaNode = DNAStorage.getPreHead();
    while (dnaNode->next) {
        dnaNode = dnaNode->next;
        // foreach DNA element
        Node<DNAElement> *elementNode = dnaNode->value.getPreHead();
        while (elementNode->next) {
            elementNode = elementNode->next;
            cout << elementNode->value.id << elementNode->value.number << ":" << elementNode->value.base << " ";
        }
        cout << endl;
    }
    cout << endl;
}
