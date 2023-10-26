#include <stdio.h>

void tidy_significands(int *data_array, int size);


int main(){

    int data1[8] = {0,0,0,0,8,12,14,0}; //array maken
    int data_size = sizeof(data1) / sizeof(data1[0]); //size calculeeren
    printf("array 1 input:      {%d, %d, %d, %d, %d, %d, %d, %d}\n", data1[0], data1[1], data1[2], data1[3], data1[4], data1[5], data1[6], data1[7]); //array printen

    tidy_significands(data1, data_size); //function call
    printf("array 1 output:     {%d, %d, %d, %d, %d, %d, %d, %d}\n\n", data1[0], data1[1], data1[2], data1[3], data1[4], data1[5], data1[6], data1[7]); //array printen


    int data2[8] = {0,0,0,1,123,65,8,0}; //array maken
    data_size = sizeof(data2) / sizeof(data2[0]); //size calculeeren
    printf("array 2 input:      {%d, %d, %d, %d, %d, %d, %d, %d}\n", data2[0], data2[1], data2[2], data2[3], data2[4], data2[5], data2[6], data2[7]); //array printen
    tidy_significands(data2, data_size); //function call
    printf("array 2 output:     {%d, %d, %d, %d, %d, %d, %d, %d}\n\n", data2[0], data2[1], data2[2], data2[3], data2[4], data2[5], data2[6], data2[7]); //array printen

    int data3[5] = {0,0,0,0,0}; //array maken
    printf("array 3 input:      {%d, %d, %d, %d, %d}\n", data3[0], data3[1], data3[2], data3[3], data3[4]); //array printen
    data_size = sizeof(data3) / sizeof(data3[0]); //size calculeeren
    tidy_significands(data3, data_size); //function call
    printf("array 3 output:     {%d, %d, %d, %d, %d}\n\n", data3[0], data3[1], data3[2], data3[3], data3[4]); //array printen

    int data4[9] = {1,2,3,4,5,6,7,8,9}; //array maken
    data_size = sizeof(data4) / sizeof(data4[0]); //size calculeeren
    printf("array 4 input:      {%d, %d, %d, %d, %d, %d, %d, %d, %d}\n", data4[0], data4[1], data4[2], data4[3], data4[4], data4[5], data4[6], data4[7], data4[8]); //array printen
    tidy_significands(data4, data_size); //function call
    printf("array 4 output:     {%d, %d, %d, %d, %d, %d, %d, %d, %d}\n\n", data4[0], data4[1], data4[2], data4[3], data4[4], data4[5], data4[6], data4[7], data4[8]); //array printen

    return 0;
}


void tidy_significands(int *data_array, int size){
    int counter = 0;

    while(counter < size && data_array[counter] == 0){ //zoeken naar de waarde die niet null is en encrement de counter zolang er 0 is.

        counter++;
    }

    if(counter < size){     // zolang de counter kliener is dan de de size van de data_array
        int *significands = data_array + counter;   // stel significands pointer in op het adres van het eerste significante waarde
        int *naar_voren = data_array;               // de naarvoeren pointer naar het begin adres van de array.
        int elemnten_copy = size - counter;         // hoeveel elementen zullen we copieren, dus vanaf de eerste significante waarde

        for (int i = 0; i < elemnten_copy; i++)
        {
                naar_voren[i] = significands[i];    /*kopier vanaf de eerse significante waarde adres in naar_voeren naar de
                                                     significands adressen dus vanaf adres 4 naar adres 0.*/
        }
        for (int i = elemnten_copy; i < size; i++)
        {
            naar_voren[i] = 0;                      // de rest van de array met nullen.
        }
            
    }
}