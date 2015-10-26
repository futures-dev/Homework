#include <iostream>
#include "heap_sort.h"

int main() {
    int n = 2;
    int *b = new int[n]{2, 3};//4,6,2,4,7,3,2,5,3,4};
    heapsort::heap_sort(b, n);
    for (int i = 0; i < n; i++)
        std::cout << b[i] << ' ';
}