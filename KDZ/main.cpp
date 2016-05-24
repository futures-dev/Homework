//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 22.05.2016
//

#include "StringContainers/HashTable.h"
#include "Dictionary.hpp"
#include "SimilairProviders/StdMap.h"

int main() {
    system("chcp 1251");
    using namespace std;
    const string dictPath = "dictionary.txt";
    const string textPath = "1984.txt";
    const string outPath = "output.txt";
    const string simPath = "simOutput.txt";

    Dictionary<HashTable> dictionary(dictPath);
    cout << "comparison took: " << dictionary.compareText(textPath, outPath) << endl;
    dictionary.compareDict(outPath, "secondOutput.txt");

    //dictionary.findSimilair<StdMap>(dictPath,simPath);
    auto t = dictionary.findSimilair<StdMap>(dictPath, simPath);

    //SpellChecker spellChecker;
    //spellChecker.load_words(dictPath);
    //spellChecker.spell_check(textPath, "thirdOutput.txt");
}
