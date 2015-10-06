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

int main(){
   cout << get_digit(143,10,1);
    cout << get_digit(8,3,0);
}

void sort_at_digit(int *arr, int n, int base, int digit_index) {

}
