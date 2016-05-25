//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 22.05.2016
//

#include "StringContainers/HashTable.h"
#include "Dictionary.hpp"
#include "StringContainers/PatriciaTree.h"
#include "StringContainers/PrefixTree.h"
#include "StringContainers/StdSet.h"

#ifdef _MSC_VER
#include <direct.h>
#else

#include <unistd.h>

#endif
int main() {
    using namespace std;
    chdir("C:\\Users\\Computer\\ClionProjects\\Homework\\KDZ");
    const string dictPath[4]{"dictionary.txt", "dictionary1.txt", "dictionary2.txt", "dictionary3.txt"};
    const string textPath = "1984.txt";
    const string outPath = "output.txt";
    const string simPath = "simOutput.txt";

    for (int i = 0; i < 4; i++) {
        cout << dictPath[i] << endl;
        Dictionary<HashTable> dictionaryHashTable(dictPath[i]);
        cout << "HashTable. Comparison took: " << dictionaryHashTable.compareText(textPath, outPath) << endl;
        Dictionary<PatriciaTree> dictionaryPatriciaTree(dictPath[i]);
        cout << "PatriciaTree. Comparison took: " << dictionaryPatriciaTree.compareText(textPath, outPath) << endl;
        Dictionary<PrefixTree> dictionaryPrefixTree(dictPath[i]);
        cout << "PrefixTree. Comparison took: " << dictionaryPrefixTree.compareText(textPath, outPath) << endl;
        Dictionary<StdSet> dictionaryStdSet(dictPath[i]);
        cout << "StdSet. Comparison took: " << dictionaryStdSet.compareText(textPath, outPath) << endl;
        //dictionary.compareDict(outPath, "secondOutput.txt");

        //cout << "1. similair search took: " << dictionary.findSimilair<StdMap>(dictPath, simPath) << endl;
        //cout << "2. similair search took: " << dictionary.findSimilair<StdMap2>(dictPath, simPath) << endl;

        //SpellChecker spellChecker;
        //spellChecker.load_words(dictPath);
        //spellChecker.spell_check(textPath, "thirdOutput.txt");
    }
}

int make_dict() {

    if (true) {
        ifstream fin("dictionary.txt");
        string buf;
        ofstream *fout[3];
        string numbers[3]{"1", "2", "3"};
        for (int j = 0; j < 3; j++) {
            fout[j] = new ofstream("dictionary" + numbers[j] + ".txt");
        }
        int i = 0;
        while (getline(fin, buf)) {
            if (i % 2 == 0) {
                *fout[0] << buf << endl;
            }
            if (i % 3 == 0) {
                *fout[1] << buf << endl;
            }
            if (i % 5 == 0) {
                *fout[2] << buf << endl;
            }
            i++;
        }
        for (int j = 0; j < 3; j++) {
            delete fout[j];
        }
        return 0;
    }

}