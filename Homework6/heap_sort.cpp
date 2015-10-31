#include <stdexcept>
#include "heap_sort.h"

/*
 * Swaps arr[a] and arr[b]
 */
void swap(int *arr, int a, int b) {
    int t = arr[a];
    arr[a] = arr[b];
    arr[b] = t;
}

/*
 * Min Heap constructor.
 * Sets capacity to n,
 * current size to 0,
 * initializes storage as an int[n],
 * inserts source values to the heap.
 */
heap::heap(const int *source, int n) : capacity(n) {
    current_size = 0;
    storage = new int[n];
    for (int i = 0; i < n; i++) {
        insert(source[i]);
    }
}

/*
 * Inserts a value in the heap.
 * Throws std::length_error if the heap is full.
 */
void heap::insert(const int value) {
    if (current_size == capacity)
        throw std::length_error("Insertion into full heap.");
    storage[current_size] = value;
    heapify_up(current_size++);
}

/*
 * Returns the minimum element in the heap.
 */
int heap::get_min() {
    return storage[0];
}

/*
 * Returns the minimum element and removes it from the heap.
 * Throws std::length_error if the heap is empty.
 */
int heap::extract_min() {
    if (current_size == 0)
        throw std::length_error("Extraction from empty heap.");
    int t = storage[0];
    storage[0] = storage[current_size - 1];
    heapify_down(0);
    return t;
}

/*
 * Pushes a heap element with specified index up the heap
 * until it is in the correct place.
 */
void heap::heapify_up(int index) {
    int i = index;
    int p = (i - 1) / 2; // parent index
    // while parent is bigger than child
    while (i > 0 && storage[i] < storage[p]) {
        swap(storage, i, p);
        i = p;
        p = (i - 1) / 2;
    }
}

/*
 * Pushes a heap element with the specified undex down the heap
 * until it is in the correct place.
 */
void heap::heapify_down(int index) {
    int cl; // left child index
    int cr; // right child index
    int cm; // least child index
    while (true) {
        cl = index * 2 + 1;
        cr = cl + 1;
        cm = index;
        if (cl < current_size && storage[cl] < storage[cm])
            cm = cl;
        // no else: if both are less than parent, choose right
        if (cr < current_size && storage[cr] < storage[cm])
            cm = cr;
        if (index == cm)
            break;
        swap(storage, index, cm);
        index = cm;
    }
}

/*
 * Destroys the heap.
 * Deletes the storage array.
 */
heap::~heap() {
    delete[] storage;
}

/*
 * Sorts an array using heap sort.
 * Creates a heap and
 * consequently calls extract_min method.
 */
void heapsort::heap_sort(int *arr, int n) {
    heap *h = new heap(arr, n);
    for (int i = 0; i < n; i++)
        arr[i] = h->extract_min();
}