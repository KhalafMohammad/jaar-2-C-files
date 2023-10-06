#include <stdio.h>

struct punt {
    int X;
    int y;
};

int main (void){

    struct punt pt;
    struct punt maxpt = { 320, 200 };
    printf ("%d,%d", pt.X, pt.y);

    return 0;
}