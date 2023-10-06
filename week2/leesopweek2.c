#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #define test

void dectobinary(int dec1, int dec2);
void displayArray(int array[], int size);

int main(){

    int decimal1;
    int decimal2;
    printf("enter a number to turn it binarrry: \n");
    scanf("%d: ", &decimal1);
    printf("enter a second number to turn it binarrry: \n");
    scanf("%d: ", &decimal2);

#ifdef test
    printf("first %d second %d\n", decimal1, decimal2);
#endif

    dectobinary(decimal1, decimal2);


    return 0;
}

void dectobinary(int dec1, int dec2){
    int derdebit[32];

    for(int i = 0; i < 31; i++){

        int bi = dec1 >> i;
        if(bi& 1){
            printf("1");
            // derdebit[i]= 1;

        }else
            printf("0");
            // derdebit[i]= 0;
    // bi = derdebit[i];
    }
    printf("\n");
        int someIntArraysSize = sizeof(derdebit) / sizeof(int);
        displayArray(derdebit,someIntArraysSize);

    // printf("derde bit van het getal %d is: %d",dec1,derdebit[29]);
    printf("\n");
    for(int i = 31; i >= 0; i--){

        int bi = dec2 >> i;
        if(bi& 1){
            printf("1");

        }else
        printf("0");
        
    }

} 

void displayArray(int array[], int size){

    int i;
    for ( i = 0; i < size; i++)
    {
        printf("the value at place %d is: %d", i, array[i]);
        printf("\n");
    }
    

}