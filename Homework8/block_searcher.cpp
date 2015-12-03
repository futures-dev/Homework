//
// Коломиец Андрей БПИ143
// CLion 1.1.1 MinGW 3.21
//

#include "block_searcher.h"
#include <algorithm>

using namespace std;

std::vector<int> *block_substring_searcher::find_substrings(
        string &source, string &substring) {
    // Массив блоков
    vector<int> *blocks = new vector<int>();

    // Длины и новая строка
    int substringLength = substring.length();
    int sourceLength = source.length();
    if (substringLength > sourceLength)
        return blocks;
    string s = substring + "\1" + source;
    int sLength = substringLength + sourceLength;

    // Вычисление массива длин блоков
    // Выделение места
    blocks->reserve(sLength);
    blocks->push_back(0);
    int left = 0;
    int right = 0;
    for (int i = 1; i < sLength; i++) {
        // Ищем максимальный подходящий блок
        int temp = ((i >= left) && (left > 0)) ? (*blocks)[i - left] : 0;
        blocks->push_back(max(0, min(right - i, temp)));
        while ((i + (*blocks)[i] <= sLength) && (s[(*blocks)[i]] == s[i + (*blocks)[i]])) {
            (*blocks)[i]++;
        }
        // Если блок подходит, обновляем left и right
        if (i + (*blocks)[i] >= right) {
            left = i;
            right = i + (*blocks)[i];
        }
    }

    // Конвертация в массив подстрок
    // Удаляем элементы до \1
    blocks->erase(blocks->begin(), blocks->begin() + substringLength + 1);
    // Если длина равна длине подстроки: вычисляем индекс вхождения
    // Иначе -1
    int i = 0;
    while (i < sLength) {
        if ((*blocks)[i] == substringLength) {
            (*blocks)[i] = i;
        }
        else {
            (*blocks)[i] = -1;
        }
        i++;
    }
    // Удаляем элементы равные -1
    i = 0;
    while (i < blocks->size()) {
        if ((*blocks)[i] == -1) {
            blocks->erase(blocks->begin() + i);
        }
        else {
            i++;
        }
    }
    return blocks;
}
