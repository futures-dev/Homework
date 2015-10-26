#include <stdexcept>
#include "heap_sort.h"

void swap(int *arr, int a, int b) {
    int t = arr[a];
    arr[a] = arr[b];
    arr[b] = t;
}

heap::heap(const int *source, int n) {
    capacity = n;
    current_size = 0;
    storage = new int[n];
    for (int i = 0; i < n; i++) {
        insert(source[i]);
    }
}

void heap::insert(const int value) {
    if (current_size == capacity)
        throw std::length_error("Insertion into full heap.");
    storage[current_size] = value;
    heapify_up(current_size++);
}

int heap::get_min() {
    return storage[0];
}

int heap::extract_min() {
    if (current_size == 0)
        throw std::length_error("Extraction from empty heap.");
    int t = storage[0];
    storage[0] = storage[current_size - 1];
    heapify_down(0);
    return t;
}

void heap::heapify_up(int index) {
    int i = index;
    int p = (i - 1) / 2;
    while (i > 0 && storage[i] < storage[p]) {
        swap(storage, i, p);
        i = p;
        p = (i - 1) / 2;
    }
}

void heap::heapify_down(int index) {
    int cl;
    int cr;
    int cm;
    while (true) {
        cl = index * 2 + 1;
        cr = cl + 1;
        cm = index;
        if (cl < current_size && storage[cl] < storage[cm])
            cm = cl;
        if (cr < current_size && storage[cr] < storage[cm])
            cm = cr;
        if (index == cm)
            break;
        swap(storage, index, cm);
        index = cm;
    }
}

heap::~heap() {
    delete[] storage;
}

void heapsort::heap_sort(int *arr, int n) {
    heap *h = new heap(arr, n);
    for (int i = 0; i < n; i++)
        arr[i] = h->extract_min();
}