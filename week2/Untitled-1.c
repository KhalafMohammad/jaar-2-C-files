#include <stdio.h>

int main(){

    auto long a = 500000;
    auto long *pntr = &a;
    auto char *cptr;
    printf("adres van a is 0x%p\n", (void *)pntr);
    printf("adres van pntr is 0x%p\n", (void *)pntr);
    printf("adres van pntr is 0x%p\n", (void *)&pntr);
    cptr = (char *)pntr;
    cptr++;
    printf("adres van cptr is 0x%p\n", (void *)cptr);
    return 0;
}