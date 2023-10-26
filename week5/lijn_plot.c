#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//voor een grote window
// const int MIN_X = -139;
// const int MAX_X = 139;
// const int MIN_Y = -31;
// const int MAX_Y = 31;


// voor een kliene window
const int MIN_X = -60;
const int MAX_X = 60;
const int MIN_Y = -20;
const int MAX_Y = 20;



//points structure
typedef struct _points_
{
    double x;
    double y;
}point;

//line structure
typedef struct _line_{

    point P;
    point Q;

}line;

//functions
void plot_grid();
void plot_line(line *k);

int main()
{
    line l = {{13, 5},{-23,20}}; //points {P},{Q};

    //plot_grid();

    plot_line(&l);

    return 0; 
}




// plot de grid in de terminal door de x en y as de plotten.
void plot_grid(){

    // point test[4] = {{20,12},{21,13},{22,14},{23,15}}; //test

    for (int j = MAX_Y; j >= 0; j--)//  van af de max_y "positeif" tot 0 (decrementing)
    {
        for (int i = MIN_X; i <= MAX_X; i++){// vanaf min_x nigatief tot de max_x positief (encremnting)
            if(i == 0){
                putchar('|');// print | als x is gelijk aan 0
            }else
                putchar(' ');//anders print spatie

            // for (int m = 0; m < 4; m++) //test
            // {
            //     if (test[m].x == i && test[m].y == j)
            //     {
            //         printf("*");
            //     }
            // }
            
            
            
        }
    putchar('\n');
    }

    for (int i = MIN_X; i <= MAX_X; i++)// vanaf min_x nigatief tot de max_x positief (encremnting)
    {
        if(i == 0){
            putchar('+');//print + als de x is gelijk aan 0
        }else
        putchar('-');//voor de rest print -
    }
    putchar('\n');
    
    for (int j = -1; j >= MIN_Y; j--)//  van af de -1 tot min_y (decrementing)
    {
        for (int i = MIN_X; i <= MAX_X; i++)// vanaf min_x nigatief tot de max_x positief (encremnting)
    {
        if(i == 0){
            putchar('|');// print | als x is gelijk aan 0
        }else
            putchar(' ');//anders print spatie

        // for (int q = 0; q < 4; q++) //test
        //     {
        //         if (test[q].x == i && test[q].y == j)
        //         {
        //             printf("*");
        //         }
        //     }
    }
    putchar('\n');
    }

    
}


//plot de lijn tussen twee gegeven puneten in main, dooe eerst de richtingscoëfficient te berekenen en b met de y as.
void plot_line(line *k){

    int arr_indx; //bereken de grotte van de lijn
    if (k->P.x < 0 && k->Q.x > 0) // als Q.x niet nigatief an P.x nigatief
    {
        arr_indx = abs((int)k->P.x);//abs om nigatieve nummer positief te maken
        arr_indx += (int)k->Q.x; //arr_index + de positief nummer
        printf("============================= %d\n", arr_indx);
    }else if (k->P.x > 0 && k->Q.x < 0) // als P.x niet nigatief an Q.x nigatief
    {
        arr_indx = abs((int)k->Q.x);
        arr_indx += (int)k->P.x;
        printf("============================= %d\n", arr_indx);
    }else if (k->P.x < 0 && k->Q.x < 0)// als Q.x nigatief an P.x nigatief
    {
        arr_indx = abs((int)k->Q.x) + abs((int)k->P.x); 
        printf("============================= %d\n", arr_indx);
    }
    

    double R = (k->P.y - k->Q.y) / (k->P.x - k->Q.x);                                       //het berkenen van de richtingscoëfficient.
    
    double b = (k->P.y) - (R * k->P.x);                                                     //het berkenen met de b.

    printf("point p: x = %.1f, y = %.1f\n", k->P.x, k->P.y);
    printf("point p: x = %.1f, y = %.1f, R= %.2f, b = %.1f\n", k->Q.x, k->Q.y, R, b);           
    printf("y = %.1fx + %.1f", R,b);                                                        // y = ax + b


                                                                                            // double round (double x); //round a number 
                                                                                            //if x, the range is from min_x to max_x (encremnting).
                                                                                            //if y, the range is from max_y to min_y (decremnting).


    double x , y;
    point line_punten[arr_indx];
    int m = 0;

    if (k->Q.x < k->P.x) //als P is positief dan begin by Q en encrement tot Q
    {
        for (x = k->Q.x - 1; x <= k->P.x; x++) //het berekenen van alle punten tussen de punten P en Q
        {
            y = round((x * R) + b); // bereken Y coordinaten
                if (m < arr_indx) { //gooi alle punten in de array
                    line_punten[m].x = x;
                    line_punten[m].y = y;
                    m++;
                }  
        }
        for (int i = 0; i < arr_indx; i++) //print alle puneten
        {
            printf("x = %.1f , y = %.1f\n", line_punten[i].x, line_punten[i].y);
        }
    }else                                           // als Q is groter dan P
            for (x = k->P.x - 1; x <= k->Q.x; x++) //het berekenen van alle punten tussen de punten P en Q
        {
            y = round((x * R) + b);// bereken Y coordinaten
                if (m < 28) {//gooi alle punten in de array
                    line_punten[m].x = x;
                    line_punten[m].y = y;
                    m++;
                }
        }
        for (int i = 0; i < 28; i++)
        {
            printf("x = %.1f , y = %.1f\n", line_punten[i].x, line_punten[i].y);//print alle puneten
        }
    
    
    
    //printen van de top y as.
    for (int j = MAX_Y; j >= 0; j--) //  van af de max_y "positeif" tot 0 (decrementing)
    {
        for (int i = MIN_X; i <= MAX_X; i++){ // vanaf min_x nigatief tot de max_x positief (encremnting)
            if(i == 0){
                putchar('|'); // print | als x is gelijk aan 0
            }else
                putchar(' '); //anders print spatie

            for (int m = 0; m < arr_indx; m++) //hier print alle punten van de lijn op de grid
            {
                if (line_punten[m].x == i && line_punten[m].y == j) //als de x coordinaat en de y coordinaat is gelijk aan de coordianaat van een punt
                {
                    putchar('*'); //print een ster bij alle punten van de lijn op de grid
                }
            }    
        }
    putchar('\n');
    }
    //printen van x as.
    for (int i = MIN_X; i <= MAX_X; i++) // vanaf min_x nigatief tot de max_x positief (encremnting)
    {
        if(i == 0){
            putchar('+');//print + als de x is gelijk aan 0
        }else
        putchar('-'); //voor de rest print -
    }
    putchar('\n');


    //printen van de y as onder de x as.
    for (int j = -1; j >= MIN_Y; j--)//  van af de -1 tot min_y (decrementing)
    {
        for (int i = MIN_X; i <= MAX_X; i++)// vanaf min_x nigatief tot de max_x positief (encremnting)
    {
        if(i == 0){
            putchar('|');// print | als x is gelijk aan 0
        }else
            putchar(' ');//anders print spatie

        for (int q = 0; q < arr_indx; q++)//hier print alle punten van de lijn op de grid
            {
                if (line_punten[q].x == i && line_punten[q].y == j)//als de x coordinaat en de y coordinaat is gelijk aan de coordianaat van een punt
                {
                    putchar('*');//print een ster bij alle punten van de lijn op de grid
                }
            }
    }
    putchar('\n');
    }
}

//==========================================================================================================