#include <iostream>
#include "edge_searcher.h"

using namespace std;

//
// �������� ������ ���143
// CLion 1.1.1 MinGW 3.21
std::vector<int> *edge_substring_searcher::find_substrings(string &source, string &substring) {
    // ������ ������
    vector<int> edges;

    // ����� � ����� ������
    int substringLength = substring.length();
    int sourceLength = source.length();
    string s = substring + char(1) + source;
    int sLength = substringLength + sourceLength;

    // ���������� ������� ���� ������
    // ��������� �����
    edges.reserve(sLength);
    // � ������� �������� �������� ���� ������ �� ������� 1 ��� ����������
    // -1 : ������ ���
    edges.push_back(-1);
    for (int edgeStart = 0; edgeStart < sLength; edgeStart++) {
        int b = edges[edgeStart];
        while (b >= 0 && (s[edgeStart + 1] != s[b + 1])) {
            // ���� ���������� ���������� �����
            b = edges[b];
        }
        if (s[edgeStart + 1] == s[b + 1]) {
            // ������� ����� �� 1 ������ ������ ���������� �������
            edges.push_back(b + 1);
        }
        else {
            // ������ �� �������: �� �������� ��������� ������
            edges.push_back(-1);
        }
    }

    // ����������� � ������ ��������
    // ���� ����� ����� ����� ���������: ��������� ������ ���������
    // ����� -1
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
    // ������� �������� ������ -1
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
