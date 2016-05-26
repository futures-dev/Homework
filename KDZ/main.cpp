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

const int dictN = 6;

int make_dict() {
    ifstream fin("dictionary.txt");
    string buf;
    ofstream *fout[dictN - 1];
    for (int j = 1; j < dictN; j++) {
        fout[j - 1] = new ofstream("dictionary" + to_string(j) + ".txt");
    }
    int i = 0;
    while (getline(fin, buf)) {
        for (int j = 0; j < dictN - 1; j++) {
            if (i % (2 << j) == 0) {
                *fout[j] << buf << endl;
            }
        }
        i++;
    }
    for (int j = 0; j < dictN - 1; j++) {
        delete fout[j];
    }
    return 0;
}

void task1() {
    make_dict();
    string dictPath[dictN];
    dictPath[0] = "dictionary.txt";
    for (int i = 1; i < dictN; i++) {
        dictPath[i] = "dictionary" + to_string(i) + ".txt";
    }
    const string textPath = "1984.txt";
    const string outPath = "output.txt";
    const string simPath = "simOutput.txt";
    const string numberPath = "numberOutput.txt";
    ofstream fout(numberPath);
    for (int i = 0; i < dictN; i++) {
        int64_t a = 0, b = 0, c = 0, d = 0;
        int n_attempts = 1;
        for (int j = 0; j < n_attempts; j++) {
            cout << dictPath[i] << endl;
            {
                Dictionary<HashTable> dictionaryHashTable(dictPath[i]);
                a += dictionaryHashTable.compareText(textPath, outPath + "hash.txt");
                a += 1;
                //cout << "HashTable. Comparison took: " << dictionaryHashTable.compareText(textPath, outPath) << endl;
            }
            {
                Dictionary<PatriciaTree> dictionaryPatriciaTree(dictPath[i]);
                b += dictionaryPatriciaTree.compareText(textPath, outPath + "patricia.txt");
                //cout << "PatriciaTree. Comparison took: " << dictionaryPatriciaTree.compareText(textPath, outPath) << endl;
                b += 1;
            }
            Dictionary<PrefixTree> dictionaryPrefixTree(dictPath[i]);
            c += dictionaryPrefixTree.compareText(textPath, outPath + "prefix.txt");
            //cout << "PrefixTree. Comparison took: " << dictionaryPrefixTree.compareText(textPath, outPath) << endl;
            c += 1;


            Dictionary<StdSet> dictionaryStdSet(dictPath[i]);
            d += dictionaryStdSet.compareText(textPath, outPath + "stdset.txt");
            //cout << "StdSet. Comparison took: " << dictionaryStdSet.compareText(textPath, outPath) << endl;
            d += 1;

        }
        fout << a / n_attempts << endl << b / n_attempts << endl << c / n_attempts << endl << d / n_attempts << endl;
        //dictionary.compareDict(outPath, "secondOutput.txt");

        //cout << "1. similair search took: " << dictionary.findSimilair<StdMap>(dictPath, simPath) << endl;
        //cout << "2. similair search took: " << dictionary.findSimilair<StdMap2>(dictPath, simPath) << endl;

        //SpellChecker spellChecker;
        //spellChecker.load_words(dictPath);
        //spellChecker.spell_check(textPath, "thirdOutput.txt");
    }
}

int main() {
    // make_dict();
    using namespace std;
    chdir("C:\\Users\\Computer\\ClionProjects\\Homework\\KDZ");
    task1();
}
