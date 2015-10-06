/**
 * Андрей Коломиец БПИ143
 * CLion 1.1.1 MinGW 3.21
 */
#include <string.h>
#include <iostream>
using namespace std;

void copy_array(int* from, int* to, int size){
    memcpy(to,from,size*sizeof(int));
}

int get_digit(int number, int base, int digit_index) {
    while (digit_index-->0)
        number/=base;
    return number%base;
}


void sort_at_digit(int *arr, int n, int base, int digit_index) {
    int digitCount[base]; // initialize to zeros
    memset(digitCount,0,base*sizeof(int));
    int digits[n];
    for (int i = 0;i<n;i++)
        digitCount[digits[n]  = get_digit(arr[i],base,digit_index)]++; // ADD COMMENT
    int count = 0;
    for (int i = 0;i<base;i++){
        int tmp = digitCount[i];
        digitCount[i] = count;
        count += tmp;
    }
    int outArray[n];
    for (int i = 0;i<n;i++){
        int d = get_digit(arr[i],base,digit_index);
        outArray[digitCount[d]++] = arr[i];
    }
    delete[] arr;
    arr = outArray;
    delete[] (outArray,digitCount,digits);
}

int main(){
   int* b = new int[7] {33,45,21,43,26,73,25};
    sort_at_digit(b,7,10,0);
    for (int i = 0;i<7;i++)
        cout<<b[i]<<'\n';
    delete[] b;
}
