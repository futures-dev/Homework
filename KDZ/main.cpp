//
// Created by Computer on 26.04.2016.
//

#include "StringContainers/HashTable.h"
#include "Dictionary.h"
#include <iostream>

int main() {
    using namespace std;
    const string dictPath = "dictionary.txt";
    const string textPath = "1984.txt";
    const string outPath = "output.txt";
    Dictionary<HashTable> dictionary(dictPath);
    cout << "comparison took: " << dictionary.compareText(textPath, outPath) << endl;
}
