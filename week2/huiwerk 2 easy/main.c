#include <stdio.h>
#include <stdlib.h>


// opdracht nummer 4

// #define test
#define array_size 4 // defined array size

struct opdrachtnemer_info{ //struct met daarin zet alle datatypen

    char voornaam[50];
    char achternaam[50];
    int age;
    float uurtrief;
    int gewerkturen;
    
};

void raporteerbeloningen(struct opdrachtnemer_info opdrNemers[], int n);

int main()
{
    struct opdrachtnemer_info opdrNemers[array_size] = { //array met info over de opdrachtnemers
        {"koos", "korswagen", 32, 135.75f, 89},
        {"Bolus","Bonkpok", 44, 162.25f, 24},
        {"Mohammad","Khalaf", 23, 89.45f, 46},
        {"Jansen","dejong", 51, 50.45f, 10}};

    // int s = sizeof(opdrNemers)/ sizeof(opdrachtnemer_info);

#ifdef test
    printf("print opdrnemer naam %s\n:", opdrNemers[0].voornaam);
    printf("print opdrnemer naam %s\n:", opdrNemers[1].voornaam);
    
#endif 

    raporteerbeloningen(opdrNemers, array_size); //function call 

    return 0;
}

void printinfo(struct opdrachtnemer_info opdrNemer){ //func die de money calculeert voor elk opdrachtnemer 
    
    float totaaluren = (float)opdrNemer.uurtrief * (float)opdrNemer.gewerkturen; // uuren * uurtrief
    printf("%s %s, %d, heeft recht op:$%.2f\n", opdrNemer.voornaam, opdrNemer.achternaam, opdrNemer.age, totaaluren);
}


void raporteerbeloningen(struct opdrachtnemer_info opdrNemers[], int n){ //func roept func printinfo() geeft elk opdrNemers[0 tot 3] als argument
    int i;
    for( i = 0; i < n; i++)
    {
        printinfo(opdrNemers[i]);
    }
}

//===============================================================================

// opdracht nummer 2 en 1

// #define test

// void dectobinary(int dec);
// void xortobinary(int dec);

// int main(){

//     int decimal1;
//     int decimal2;
//     printf("enter a number to turn it binarrry: \n"); //eerst nummer vragen
//     scanf("%d: ", &decimal1);
//     printf("enter a second number to turn it binarrry: \n"); //tweede nummer vragen
//     scanf("%d: ", &decimal2);

// #ifdef test
//     printf("first %d second %d\n", decimal1, decimal2);
// #endif

//     printf("Getal 1 <%d> is binair: ",decimal1); //print eerst nummer als binair
//     dectobinary(decimal1);
//     printf("\n");

//     printf("Getal 2 < %d> is binair: ",decimal2); //print tweede nummer als binair
//     dectobinary(decimal2);
//     printf("\n                        ---------------------------------------\n");

    

//     unsigned int xor = decimal1 ^ decimal2; //xor calculatie met ^ xor operator

//     printf("XOR van beide getallen: "); //xor binair uitprinten
//     xortobinary(xor);
//     printf("\n");

//     int zeroCounter = 0;
//     for (int i = 0; i < 32; i++) { // calculeert hoeveel nullen in de xor binair zetten
//         if (((xor >> i) & 1) == 0){
//             zeroCounter++;
//         }
//     }

//     printf("\nbeide getallen komen op %d overeen!", zeroCounter);

//     return 0;
// }


// void dectobinary(int dec){ //func om decimal naar binair te maken

//     for(int i = 31; i >= 0; i--){

//         int bi = dec >> i;
//         if(bi& 1){
//             printf("1");

//         }else
//         printf("0");
//             if (i % 4 == 0) //elk nibble space printen
//             printf(" ");

//     }

// }

// void xortobinary(int dec){ //xor binair calculeren **geen eenen uitprinten. alleen nullen

//     for(int i = 31; i >= 0; i--){

//         int bi = dec >> i;
//         if(bi& 1){
//             printf(" ");

//         }else
//         printf("0");
//             if (i % 4 == 0)
//             printf(" ");

//     }

// }

//===============================================================================

// opdracht nummer 3

// enum Bool{ //  enum heeft twee waarden 1 of 0
//     False = 0,
//     True = 1

// };


// #define equal(x,y) ((x) == (y) ? True : False) // macro is equal en x en y zijn argumenten. is x en y equl dat geeft True terug, als Niet dan False.

// int main(){
//     int num1 = 1;
//     int num2 = 1;

//     enum Bool is_aqual =  equal(num1, num2);

//     if (is_aqual == True){
//         printf("both nums are equal");
//     }else{
//         printf("both nums are NOT-equal");
//     }

//     return 0;
// }

