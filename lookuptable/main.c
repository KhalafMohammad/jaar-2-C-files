#include <stdio.h>
#include <math.h>

#define tabel_index 256

int main(){

    int lookup_tabel[tabel_index] = {0};
    printf("const int lookup_tabel[256] = {");
    for (int i = 1; i <= tabel_index; i++)
    {
        //8-bit resolutie geeft 256 discrete duty cycles.
        lookup_tabel[i] = (int)pow(i,2) / tabel_index; //so x = (n^2) / 256;
        printf(" %d,", lookup_tabel[i]);
    }
    printf("};");
    return 0;
}