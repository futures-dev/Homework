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
#include "SimilairProviders/StdMap.h"
#include "SimilairProviders/StdMap2.h"
#include "SimilairProviders/StdMap3.h"
#include "SpellChecker.h"
#include <complex>

#ifdef _MSC_VER
#include <direct.h>
#else
#include <unistd.h>
#endif

const int dictN = 6;

int make_dict(const string &path) {
	ifstream fin(path + ".txt");
	string buf;
	ofstream *fout[dictN - 1];
	for (int j = 1; j < dictN; j++) {
		fout[j - 1] = new ofstream(path + to_string(j) + ".txt");
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
	make_dict("dictSjsu/dictionary");
	string dictPath[dictN];
	dictPath[0] = "dictSjsu/dictionary.txt";
	for (int i = 1; i < dictN; i++) {
		dictPath[i] = "dictSjsu/dictionary" + to_string(i) + ".txt";
	}
	const string textPath = "1984.txt";
	const string outPath = "output/task1/output";
	ofstream fout(outPath + ".txt");

	for (int i = 0; i < dictN; i++) {
		int64_t hashTableInsert = 0, hashTableSearch = 0, patriciaTreeInsert = 0, patriciaTreeSearch = 0, prefixTreeInsert = 0, prefixTreeSearch = 0, stdSetInsert = 0, stdSetSearch = 0;
		int n_attempts = 3;
		for (int j = 0; j < n_attempts; j++) {
			{
				int64_t insert_time = 0;
				Dictionary<HashTable> dictionaryHashTable(dictPath[i], insert_time);
				hashTableInsert += insert_time;
				hashTableSearch += dictionaryHashTable.compareText(textPath,
																   outPath + "_hashTable_" + to_string(i) + ".txt");
			}
			{
				int64_t insert_time = 0;
				Dictionary<PatriciaTree> dictionaryPatriciaTree(dictPath[i], insert_time);
				patriciaTreeInsert += insert_time;
				patriciaTreeSearch += dictionaryPatriciaTree.compareText(textPath,
																		 outPath + "_patriciaTree_" + to_string(i) +
																		 ".txt");
			}
			{
				int64_t insert_time = 0;
				Dictionary<PrefixTree> dictionaryPrefixTree(dictPath[i], insert_time);
				prefixTreeInsert += insert_time;
				prefixTreeSearch += dictionaryPrefixTree.compareText(textPath,
																	 outPath + "_prefixTree_" + to_string(i) + ".txt");
			}
			{
				int64_t insert_time = 0;
				Dictionary<StdSet> dictionaryStdSet(dictPath[i], insert_time);
				stdSetInsert += insert_time;
				stdSetSearch += dictionaryStdSet.compareText(textPath, outPath + "_stdSet_" + to_string(i) + ".txt");
			}

		}
		hashTableInsert /= n_attempts, hashTableSearch /= n_attempts, patriciaTreeInsert /= n_attempts, patriciaTreeSearch /= n_attempts, prefixTreeInsert /= n_attempts, prefixTreeSearch /= n_attempts, stdSetInsert /= n_attempts, stdSetSearch /= n_attempts;
		cout << i << endl;
		cout << "HashTable Insert: " << hashTableInsert << endl;
		cout << "HashTable Search: " << hashTableSearch << endl;
		cout << "Patricia Insert: " << patriciaTreeInsert << endl;
		cout << "Patricia Search: " << patriciaTreeSearch << endl;
		cout << "Prefix Insert: " << prefixTreeInsert << endl;
		cout << "Prefix Search: " << prefixTreeSearch << endl;
		cout << "StdSet Insert: " << stdSetInsert << endl;
		cout << "StdSet Search: " << stdSetSearch << endl;
		fout << "HashTable Insert: " << hashTableInsert << endl;
		fout << "HashTable Search: " << hashTableSearch << endl;
		fout << "Patricia Insert: " << patriciaTreeInsert << endl;
		fout << "Patricia Search: " << patriciaTreeSearch << endl;
		fout << "Prefix Insert: " << prefixTreeInsert << endl;
		fout << "Prefix Search: " << prefixTreeSearch << endl;
		fout << "StdSet Insert: " << stdSetInsert << endl;
		fout << "StdSet Search: " << stdSetSearch << endl;
	}
}

void task2() {
	make_dict("dictSil/dictionary");
	string dictPath[dictN];
	dictPath[0] = "dictSil/dictionary.txt";
	for (int i = 1; i < dictN; i++) {
		dictPath[i] = "dictSil/dictionary" + to_string(i) + ".txt";
	}
	const string outPath = "output/task2/output";
	ofstream fout(outPath + ".txt");

	for (int i = 0; i < dictN; i++) {
		int64_t map1Similair = 0, map2Similair = 0, map3Similair = 0;
		int n_attempts = 4;
		// using HashTable
		{
			Dictionary<HashTable> dictionary(dictPath[i]);
			{
				map1Similair += dictionary.findSimilair<StdMap>(dictPath[i], outPath + "_map_" + to_string(i) + ".txt");
				cout << endl;
			}
			{
				map2Similair += dictionary.findSimilair<StdMap2>(dictPath[i],
																 outPath + "_map2_" + to_string(i) + ".txt");
				cout << endl;
			}
			{
				map3Similair += dictionary.findSimilair<StdMap3>(dictPath[i],
																 outPath + "_map3_" + to_string(i) + ".txt");
				cout << endl;
			}
		}

		// using PatriciaTree
		{
			Dictionary<PatriciaTree> dictionary(dictPath[i]);
			{
				map1Similair += dictionary.findSimilair<StdMap>(dictPath[i], outPath + "_map_" + to_string(i) + ".txt");
			}
			{
				map2Similair += dictionary.findSimilair<StdMap2>(dictPath[i], outPath + "_map2_" + to_string(i) + ".txt");
			}
			{
				map3Similair += dictionary.findSimilair<StdMap3>(dictPath[i], outPath + "_map3_" + to_string(i) + ".txt");
			}
		}
		// using PrefixTree
		{
			Dictionary<PrefixTree> dictionary(dictPath[i]);
			{
				map1Similair += dictionary.findSimilair<StdMap>(dictPath[i], outPath + "_map_" + to_string(i) + ".txt");
			}
			{
				map2Similair += dictionary.findSimilair<StdMap2>(dictPath[i], outPath + "_map2_" + to_string(i) + ".txt");
			}
			{
				map3Similair += dictionary.findSimilair<StdMap3>(dictPath[i], outPath + "_map3_" + to_string(i) + ".txt");
			}
		}
		// using StdSet
		{
			Dictionary<StdSet> dictionary(dictPath[i]);
			{
				map1Similair += dictionary.findSimilair<StdMap>(dictPath[i], outPath + "_map_" + to_string(i) + ".txt");
			}
			{
				map2Similair += dictionary.findSimilair<StdMap2>(dictPath[i], outPath + "_map2_" + to_string(i) + ".txt");
			}
			{
				map3Similair += dictionary.findSimilair<StdMap3>(dictPath[i], outPath + "_map3_" + to_string(i) + ".txt");
			}
		}


		map1Similair /= n_attempts, map2Similair /= n_attempts, map3Similair /= n_attempts;
		cout << i << endl;
		cout << "map<string,set<string>>: " << map1Similair << endl;
		cout << "map<int,map>: " << map2Similair << endl;
		cout << "map<char,map<int,map>>: " << map3Similair << endl;
		fout << i << endl;
		fout << "map<string,set<string>>: " << map1Similair << endl;
		fout << "map<int,map>: " << map2Similair << endl;
		fout << "map<char,map<int,map>>: " << map3Similair << endl;
	}
}

void task3() {
	make_dict("dictSil/dictionary5");
	string dictPath[dictN];
	dictPath[0] = "dictSil/dictionary5.txt";
	for (int i = 1; i < dictN; i++) {
		dictPath[i] = "dictSil/dictionary5" + to_string(i) + ".txt";
	}
	const string outPath = "output/task3/output";
	const string bigDict = "dictSjsu/dictionary.txt";
	ofstream fout(outPath + ".txt");

	for (int i = 0; i < dictN; i++) {
		int64_t hashTableCompare = 0, patriciaTreeCompare = 0, prefixTreeCompare = 0, stdSetCompare = 0;
		int n_attempts = 4;
		for (int j = 0; j < n_attempts; j++) {
			// using HashTable
			{
				Dictionary<HashTable> dictionary(bigDict);
				hashTableCompare += dictionary.compareDict(dictPath[i],
														   outPath + "_hashTable_" + to_string(i) + ".txt");
			}

			// using PatriciaTree
			{
				Dictionary<PatriciaTree> dictionary(bigDict);
				patriciaTreeCompare += dictionary.compareDict(dictPath[i],
															  outPath + "_patriciaTree_" + to_string(i) + ".txt");
			}
			// using PrefixTree
			{
				Dictionary<PrefixTree> dictionary(bigDict);
				prefixTreeCompare += dictionary.compareDict(dictPath[i],
															outPath + "_prefixTree_" + to_string(i) + ".txt");
			}
			// using StdSet
			{
				Dictionary<StdSet> dictionary(bigDict);
				stdSetCompare += dictionary.compareDict(dictPath[i], outPath + "_stdSet_" + to_string(i) + ".txt");
			}
		}

		hashTableCompare /= n_attempts, patriciaTreeCompare /= n_attempts, prefixTreeCompare /= n_attempts, stdSetCompare /= n_attempts;
		cout << i << endl;
		cout << "HashTable Compare: " << hashTableCompare << endl;
		cout << "Patricia Compare: " << patriciaTreeCompare << endl;
		cout << "Prefix Compare: " << prefixTreeCompare << endl;
		cout << "StdSet Compare: " << stdSetCompare << endl;
		fout << "HashTable Compare: " << hashTableCompare << endl;
		fout << "Patricia Compare: " << patriciaTreeCompare << endl;
		fout << "Prefix Compare: " << prefixTreeCompare << endl;
		fout << "StdSet Search: " << stdSetCompare << endl;
	}
}

void task4() {
	const string text1 = "text/Alice.txt";
	const string text2 = "text/Island.txt";
	const string textBroken = "text/broken.txt";
	const string output = "output/task4/output.txt";
	SpellChecker spellChecker;
	spellChecker.load_words(text1);
	spellChecker.load_words(text2);
	spellChecker.spell_check(textBroken, output);
}

int main() {
	// make_dict();
	using namespace std;
	chdir("C:\\Users\\Computer\\ClionProjects\\Homework\\KDZ");
	//task1();
	//task2();
	task3();
	//task4();
	cin.get();
}
