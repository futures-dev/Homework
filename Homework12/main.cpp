//
// �������� ������ ��� 143
// 15.12.2015
// MinGW 3.20 CLion 1.2.2
// �� 12, KMP, AMB
//

#include <iostream>
#include <vector>

using namespace std;

std::vector<int> *morris(string &source, string &substring) {
    // ������ ������
    vector<int> *edges = new vector<int>();

    // ����� � ����� ������
    int substringLength = substring.length();
    int sourceLength = source.length();

    // ���������� ������� ���� ������
    // ��������� �����
    edges->reserve(substringLength);
    // � ������� �������� �������� ���� ������ �� ������� 1 ��� ����������
    // -1 : ������ ���
    edges->push_back(-1);
    for (int edgeStart = 0; edgeStart < substringLength; edgeStart++) {
        int b = (*edges)[edgeStart];
        while (b >= 0 && (substring[edgeStart + 1] != substring[b + 1])) {
            // ���� ���������� ���������� �����
            b = (*edges)[b];
        }
        if (substring[edgeStart + 1] == substring[b + 1]) {
            // ������� ����� �� 1 ������ ������ ���������� �������
            edges->push_back(b + 1);
        }
        else {
            // ������ �� �������: �� �������� ��������� ������
            edges->push_back(-1);
        }
    }
    cout << "Edges: " << endl;
    for (int i = 0; i < edges->size(); i++) {
        cout << ++((*edges)[i]) << " ";
    }
    cout << endl;
    edges->erase(edges->begin(), edges->begin());
    // brs
    vector<int> *brs = new vector<int>(edges->size());
    (*brs)[0] = 0;
    for (int i = 1; i < substringLength; i++) {
        if (substring[(*edges)[i]] != substring[i + 1]) {
            // ���������� �����
            (*brs)[i] = (*edges)[i];
        }
        else {
            // �� ���������� �����
            (*brs)[i] = (*brs)[(*edges)[i]];
        }

    }

    delete edges;
    edges = brs;

    cout << "BRS: " << endl;
    for (int i = 0; i < edges->size(); i++) {
        cout << ((*edges)[i])-- << " ";
    }
    cout << endl;

    // KMP
    vector<int> *output = new vector<int>(); // ������ �������� ��������
    int q = -1;
    for (int i = 0; i < sourceLength; i++) {
        while (q >= 0 && (substring[q + 1] != source[i])) {
            q = (*edges)[q];
        }
        if (substring[q + 1] == source[i]) {
            q++;
        }
        if (q == substringLength - 1) {
            output->push_back(i - substringLength + 1);
            q = (*edges)[substringLength];
        }
    }
    cout << "Substring indices:" << endl;
    for (int i = 0; i < output->size(); i++) {
        cout << (*output)[i] << " ";
    }
    cout << endl;
    delete edges;
    return output;
}

vector<int> *BM(string &source, string &sub) {
    int n = source.length();
    int m = sub.length();
    vector<int> *output = new vector<int>(); // ������ �������� ��������
    int *bs = new int['z' - 'a' + 1];
    for (int i = 'a'; i <= 'z'; i++) {
        bs[i - 'a'] = -1; // ��������� �� �������� ����� i
        for (int k = m - 1; k >= 0; k--) { // ������ ������ ���������
            if (sub[k] == i) {
                bs[i - 'a'] = k;
                break;
            }
        }
    }
    cout << "BS" << endl;
    for (int i = 'a'; i <= 'z'; i++)
        cout << bs[i - 'a'] << " ";
    cout << endl;
    int i = 0;
    while (i <= (n - m)) { // ������������ T
        int j = m - 1;
        // ��������� ����-�������
        while (j >= 0 && (sub[j] == source[i + j - 1])) {
            j--;
        }
        if (j == -1) {
            output->push_back(i - 1);
            i++;
        }
            // ����� ������
        else {
            i = i + max(0, j - bs[source[i + j - 1]] - 1);
        }
    }
    return output;
}

int main() {
    cout << "Source: " << endl;
    string source; // kbabcklabcabckaabdaabckabcab
    cin >> source;
    cout << "Search: " << endl;
    string sub;
    cin >> sub; // abc

    cout << endl << "KMP" << endl;
    vector<int> *s = morris(source, sub);
    cout << "Output: (0-based)" << endl;
    for (int i = 0; i < s->size(); i++) {
        cout << (*s)[i] << " ";
    }
    delete s;
    cout << endl;

    cout << endl << "ABM" << endl;
    s = BM(source, sub);
    cout << "Output: (0-based)" << endl;
    for (int i = 0; i < s->size(); i++) {
        cout << (*s)[i] << " ";
    }
    delete s;
    cout << endl;
    cout << "Press enter to exit...";
    cin.get();
    cin.get();

    return 0;
}