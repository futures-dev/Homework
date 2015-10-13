/**
 * Андрей Коломиец БПИ143
 * CLion 1.1.1 MinGW 3.21
 */
#include <string.h>
#include <iostream>

using namespace std;

void merge(int *arr, int start_first, int start_second, int end) {
    int i = start_first;
    int j = start_second;
    int *out = new int[end - start_first];
    int k = 0;
    while (i < start_second && j < end)
        if (arr[i] < arr[j])
            out[k++] = arr[i++];
        else
            out[k++] = arr[j++];
    while (i < start_second)
        out[k++] = arr[i++];
    while (j < end)
        out[k++] = arr[j++];
    memcpy(&arr[start_first], out, sizeof(int) * (end - start_first));
}

int main() {
    int *a = new int[9]{7, 1, 3, 5, 7, 2, 4, 6, 1};
    merge(a, 1, 5, 8);
    for (int i = 0; i < 9; i++)
        cout << a[i] << ' ';
}
