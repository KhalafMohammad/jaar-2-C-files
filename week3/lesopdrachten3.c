#include <stdio.h>
#include <stdlib.h>



// int main(){

//     unsigned getal = 0xE13A2CD5;
//     unsigned char abyte = 0;
//     abyte = *(((unsigned char *)(&getal))+ 1);
        //eerste haackje zoekt de adress bij &getal
        //tweede haakje converteert van unsigned int naar unsigned char
        //derde haakje zoekt de plaats in de ineger waar je zoekt zoals 0x2c

    
//     printf("%d", abyte);

//     return 0;
// }

//=========================================================

int main(){

    //char str[1024] = "dit is een string";
    int *str = malloc((size_t)(10000000000 * sizeof(char)));
    for (int i = 0; i < 10000000000; i++)
    {
        str[i] = 'a';
    }
    str[10000000000 - 1] = '\0';

    printf("C-string is : %c\n", str[0]);
    printf("programma is bij het einde gekomen\n");
    while(1);
    free(str);
    return 0;
}