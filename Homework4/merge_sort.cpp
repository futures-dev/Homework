/**
 * Àíäðåé Êîëîìèåö ÁÏÈ143
 * CLion 1.1.1 MinGW 3.21
 */
#include <string.h>
#include <iostream>

using namespace std;

// inclusive starts, exclusive end
void merge(int *arr, int start_first, int start_second, int end) {
    int i = start_first;
    int j = start_second;
    int *out = new int[end - start_first]; // temp array for sorted merged elements
    int k = 0;
    while (i < start_second && j < end)
        if (arr[i] < arr[j])
            out[k++] = arr[i++];
        else
            out[k++] = arr[j++];
    while (i < start_second) // if second part ended quicker
        out[k++] = arr[i++];
    while (j < end) // if first part ended quicker
        out[k++] = arr[j++];
    memcpy(&arr[start_first], out, sizeof(int) * (end - start_first)); // copy elements back
    delete [] out; // clean up
}

// inclusive left, exclusive right
void divide_and_merge(int *arr, int left, int right){
    if (left + 1<right){
        int m = right - (right - left) / 2; // Prevent overflow
        divide_and_merge(arr,left,m); // process left part
        divide_and_merge(arr,m,right); // process right part
        merge(arr,left,m,right); // merge
    }
}

void merge_sort(int *arr, int n){
    divide_and_merge(arr,0,n);
}
