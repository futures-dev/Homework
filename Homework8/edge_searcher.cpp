#include <iostream>
#include "edge_searcher.h"

using namespace std;

//
// Коломиец Андрей БПИ143
// CLion 1.1.1 MinGW 3.21
std::vector<int> *edge_substring_searcher::find_substrings(string &source, string &substring) {
    // Массив граней
    vector<int> edges;

    // Длины и новая строка
    int substringLength = substring.length();
    int sourceLength = source.length();
    string s = substring + char(1) + source;
    int sLength = substringLength + sourceLength;

    // Вычисление массива длин граней
    // Выделение места
    edges.reserve(sLength);
    // В массиве хранятся значения длин граней за вычетом 1 для индексации
    // -1 : Граней нет
    edges.push_back(-1);
    for (int edgeStart = 0; edgeStart < sLength; edgeStart++) {
        int b = edges[edgeStart];
        while (b >= 0 && (s[edgeStart + 1] != s[b + 1])) {
            // Ищем наибольшую подходящую грань
            b = edges[b];
        }
        if (s[edgeStart + 1] == s[b + 1]) {
            // Найдена грань на 1 больше засчет последнего символа
            edges.push_back(b + 1);
        }
        else {
            // Граней не найдено: не подходит последний символ
            edges.push_back(-1);
        }
    }

    // Конвертация в массив подстрок
    // Если длина равна длине подстроки: вычисляем индекс вхождения
    // Иначе -1
    int i = 0;
    while (i < edges.size()) {
        if (edges[i] == substringLength - 1) {
            edges[i] = i - substringLength - 1;
        }
        else {
            edges[i] = -1;
        }
        i++;
    }
    // Удаляем элементы равные -1
    i = 0;
    while (i < edges.size()) {
        if (edges[i] == -1) {
            edges.erase(edges.begin() + i);
        }
        else {
            i++;
        }
    }
    return &edges;
}
