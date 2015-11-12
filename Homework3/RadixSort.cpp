/**
 * Андрей Коломиец БПИ143
 * CLion 1.1.1 MinGW 3.21
 */
#include <string.h>

void copy_array(int* from, int* to, int size){
    memcpy(to, from, size * sizeof(int)); // No need to make a separate function...
}

int get_digit(int number, int base, int digit_index) {
    while (digit_index-- > 0)
        number/=base;
    return number%base;
}


void sort_at_digit(int *arr, int n, int base, int digit_index) {
    int digitCount[base]; // Array to store sums in
    memset(digitCount, 0, base * sizeof(int)); // initialize to zeros
    int original[n]; // Original array elementsS
    copy_array(arr, original, n);
    int digits[n]; // Array to cache digits in. obviously, we can recalculate digit each time we need it.
    for (int i = 0;i<n;i++)
        digitCount[digits[i] = get_digit(arr[i], base, digit_index)]++; // Count numbers of each digit and cache digit
    int count = 0;
    for (int i = 0;i<base;i++){
        if (digitCount[i] > 0) {
            int tmp = digitCount[i];
            digitCount[i] = count; // Amount of numbers with digit < i
            count += tmp;
        }
        else
            digitCount[i] = -1; // There are no numbers with this digit, although it is in [0;base)
    }
    for (int i = 0; i < n; i++)
        if (digitCount[digits[i]] >= 0) // Not trying process elements with digits that never occurred
            arr[digitCount[digits[i]]++] = original[i];
    delete[] (original, digits, digitCount); // Clean up
}

// In RadixSort.h it is not mentioned that array elements are positive.
// So I sort negative and positive parts of array and then merge them.
void radix_sort(int *arr, int n, int base) {
    if (n <= 1)
        return;
    int maxN = arr[0]; // Max number to find out when to stop radix sort
    int minN = arr[0]; // Min number for negative integers
    int *negArr = new int[n];
    int negI = 0;
    int *posArr = new int[n];
    int posI = 0;
    for (int i = 0;i<n;i++){
        if (arr[i] < 0) {
            negArr[negI++] = arr[i]; // Sign does not matter.
            if (minN > arr[i])
                minN = arr[i];
        }
        else {
            posArr[posI++] = arr[i];
            if (maxN < arr[i])
                maxN = arr[i];
        }
    }

    // While maxN has significant digits
    for (int i = 0; maxN > 0; maxN /= base) {
        sort_at_digit(posArr, posI, base, i); // Sort at digit #i
    }
    for (int i = 0; minN > 0; minN /= base) {
        sort_at_digit(negArr, negI, base, i);
    }
    // Absolutely biggest negative int is the least.
    for (int i = negI - 1; i >= 0; i--)
        arr[i] = negArr[i];
    for (int i = 0; i < posI; i++)
        arr[negI + i] = posArr[i];
    delete[] (posArr, negArr); // Clean up
}
