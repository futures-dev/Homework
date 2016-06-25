/**
 * ������ �������� ���143
 * Andrei Kolomiets BPI143
 * CLion 1.1.1 MinGW 3.21
 */

#include "quick_sort.h"
#include "random"

/*
 * Swaps arr[a] and arr[b]
 */
void swap(int* arr, int a, int b) {
    int t = arr[a];
    arr[a] = arr[b];
    arr[b] = t;
}

/*
 * Sorts an array using quick_sort. Pivot is chosen as the middle element.
 */
void q_sort::quick_sort_middle(int *arr, int n) {
    quick_sort(arr, 0, n, get_middle_pivot);
}

/*
 * Sorts an array using quick_sort. Pivot is chosen as the last element.
 */
void q_sort::quick_sort_last(int *arr, int n) {
    quick_sort(arr, 0, n, get_last_pivot);
}

/*
 * Sorts an array using quick_sort. Pivot is chosen as a random element.
 */
void q_sort::quick_sort_rand(int *arr, int n) {
    quick_sort(arr, 0, n, get_rand_pivot);
}

/*
 * Returns a pivot as the middle element.
 */
int q_sort::get_middle_pivot(int from, int to) {
    return (to - from - 1) / 2 + from;
}

/*
 * Returns a pivot as the last element.
 */
int q_sort::get_last_pivot(int from, int to) {
    return to - 1;
}

/*
 * Returns a pivot as a random element.
 */
int q_sort::get_rand_pivot(int from, int to) {
    return rand() % (to - from) + from;
}

/*
 * Iterative without rearrange function
 */


    void q_sort::quick_sort(int* arr, int from, int to, pivot_chooser a_pivot_chooser){
        int l = from;
        int r = to - 1;
        int t = 0;
        int pivot_index = a_pivot_chooser(from,to);
        int pivot = arr[pivot_index];
        do {
            while (arr[l] < pivot)
                l++;
            while (arr[r] > pivot)
                r--;
            if (l <= r) {
                if (arr[l] > arr[r]) {
                    swap(arr,l,r);
                }
                l++;
                r--;
            }
        }
        while (l<=r);
        if (l<to-1)
            quick_sort(arr,l,to,a_pivot_chooser);
        if (r>from)
            quick_sort(arr,from,r+1,a_pivot_chooser);
    }

    // Don't need this
    int q_sort::rearrange_array_with_pivot(int* arr, int from, int to, int pivot_index){
    }


/*
 * Implements quick sort using the correspondent pivot_chooser
 */
void q_sort::quick_sort(int *arr, int from, int to, pivot_chooser a_pivot_chooser) {
    if (from < to - 1) // Array of 1 element is sorted
    {
        int pivot_index = a_pivot_chooser(from, to); // Get the pivot index
        pivot_index = rearrange_array_with_pivot(arr, from, to, pivot_index); // Rearrange array and get new pivot index
        quick_sort(arr, from, pivot_index, a_pivot_chooser); // Sort left part of the array
        quick_sort(arr, pivot_index + 1, to, a_pivot_chooser); // Sort right part
    }
}

/*
 * Shuffles the array so that elements <= pivot are to the left, and >= are to the right.
 * Returns new pivot_index.
 */
int q_sort::rearrange_array_with_pivot(int *arr, int from, int to, int pivot_index) {
    int pivot = arr[pivot_index]; // Get pivot value
    swap(arr, pivot_index, to - 1); // Move pivot to the end
    int j = from - 1; // Index of the last element of the left part of the array
    for (int i = from; i < to - 1; i++) // Index of the first element of the right part of the array
    {
        if (arr[i] <= pivot) // This element is from the left part, not the right one
        {
            j++;
            swap(arr, i, j);
        }
    }
    swap(arr, j + 1, to - 1); // Swap first element of the right part and the very last which is pivot
    return j + 1; // New pivot index, correctly between left and right parts
}