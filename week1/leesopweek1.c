// #include<stdio.h>
// #include "module.h"

// int main(void){

//     // short i = 16;
//     // printf("%i",i);

//     float f = maxf(4.1, 4.044444444);
//     printf("de gerotste is %f", f);
//     return 0;
// }

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void displayArray(int array[], int size);

int main(){

    int someIntArray[] = {8, 5, 9, 2, 14};
    int someIntArraysSize = sizeof(someIntArray) / sizeof(int);

    displayArray(someIntArray, someIntArraysSize);

    return 0;
}

void displayArray(int array[], int size){

    int i;
    for ( i = 0; i < size; i++)
    {
        printf("the value at place %d is: %d", i, array[i]);
        printf("\n");
    }
    

}