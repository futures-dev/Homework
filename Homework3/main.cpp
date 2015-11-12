#include <iostream>
#include "RadixSort.h"

int main() {
    int n = 10;
    int *b = new int[n]{50, 1, 400, 20, 3000, 70, 800, 90, 1000, 60};
    radix_sort(b, n, 7);
    for (int i = 0; i < n; i++)
        std::cout << b[i] << ' ';
}