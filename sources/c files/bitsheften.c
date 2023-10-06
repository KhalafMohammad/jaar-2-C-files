#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// typedef struct _point
// {
//     double x;
//     double y;
// }point;


// double straight_distance(point pt1, point pt2);
void dectobinary(int n);

int main(){
    // point punt1 = {0.5, 2.5};
    // point punt2 = {3.5,6.5};

    // double afstand =  straight_distance(punt1, punt2);
    // printf("AFSTAND TUSSEN PUNT1 EN PUNT2 IS %f\n", sqrt(afstand));
    int n = 17;
    dectobinary(n);


    return 0;
}


// double straight_distance(point pt1, point pt2){
//     double gdistance =0.0;


//     // gdistance = pow((pow ((pt2.x - pt1.x), 2) + (pow (pt2.y - pt1.y), 2)), 0,5);
//     gdistance = ((pt2.x- pt1.x)*(pt2.x-pt1.x))+((pt2.y-pt1.y)*(pt2.y-pt1.y));
//     return gdistance;
// }

void dectobinary(int n){

    int binarylist[32];

    int i = 0;
    while (n > 0)
    {
        binarylist[i] = n % 2;
        n = n / 2;
        i++;
    }

    int j;
    
    for(j =i - 1 ; j>=0; j--){
        printf("%d", binarylist[j]);
    }
    printf("\n");
    printf("%d", binarylist[2]);

}