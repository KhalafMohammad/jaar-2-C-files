// #include <stdio.h>


//     // union u_tag (
//     //     int ival; /* integer */
//     //     float fval; /* float */
//     //     char *sval; /* string */
//     // } u;


// /*

//     1.a. Wat is het verschil tussen een struct en een union?

//         Op unions mogen dezelfde bewerkingen
//         worden toegepast als op structures: aan een union mag een waarde worden
//         toegekend, een union mag als geheel worden gekopieerd, het adres van een
//         union mag worden bepaald en union-leden kunnen afzonderlijk worden
//         bereikt en gemanipuleerd.
        
//         Een union mag alleen geïnitieerd worden met een waarde die het type heeft
//         van het eerste lid van die union; de union u hierboven mag dus alleen
//         worden geïnitieerd met een integerwaarde.

//     2.a. Welk statement zorgt ervoor dat hetgeen in de backbuffer wordt voorbereid, 
//          daadwerkelijk in het window wordt getoond?

//             de SDL_RenderClear() functie.
//     2.b. 1- de datatype of even is een struct in de union SDL_Event.
//          2- event.key is een event type en zet in typedef struct SDL_KeyBoardEvent struct die zet in de typedef union SDL_Event.
//          3- event.key.keysym is een typedef struct die heeft informatie over key events.
//          4- event.key.keysym.scancode is typedef enum.
    
//     2.c. de SDL_keycode waar SDLK_ESCAPE zet defineert de key op de keyboard en zijn modificatoren.
//          de SDL_SCANCODE waar SDL_SCANCODE_ESCAPE zet, dit difineert de scancode.
          

// */




// // Schrijf een stukje voorbeeldcode waarin je dezelfde structure MET en ZONDER typedef declareert en gebruikt.

// struct Huiswerken{ //hier is de struct zonder typedef

//     char *name;
//     int c_fils;
// };


// typedef struct{//hier de struct is typedef    

//     char *name;
//     int c_fils;
        
// }Huiswerken;


// int main(void){

//     Huiswerken Opdrachten[3] = {{"week1", 2}, //array die gebruikt de typedef struct.
//                              {"week2", 3},
//                              {"week3", 1}
//     };
//     int grotte = sizeof(Opdrachten) / sizeof(Opdrachten[0]); //calculeert de size van Opdrachten array.

//     struct Huiswerken Opdrachten3[] = {{"Week4",2}, //array die gebruikt de normale struct
//                                      {"week5", 5},
//                                      {"week6",4}
//     };
//     int grotte1 = sizeof(Opdrachten3) / sizeof(Opdrachten3[0]);    //calculeert de size van Opdrachten3 array.

    

//     for (int i = 0; i < grotte; i++) // for loop die print array Opdrachten
//     {
//         printf("periode 1 in %s had ik %d C files gemaakt.\n", Opdrachten[i].name, Opdrachten[i].c_fils);
//     }

//     printf("\n");
//     for (int i = 0; i < grotte1; i++)// for loop die print array Opdrachten3
//     {
//         printf("periode 1 in %s had ik %d C files gemaakt.\n", Opdrachten3[i].name, Opdrachten3[i].c_fils);
//     }

    
//     return 0;
// }




#include <stdio.h>
#include <stdlib.h>
// #include <time.h>

int main() {
    // Seed the random number generator with the current time
    srand(time(NULL));

    // Generate a random number between 1 and 10
    int randomNum = (rand() % 10) + 1;

    // Print the random number
    printf("Random number between 1 and 10: %d\n", randomNum);

    return 0;
}