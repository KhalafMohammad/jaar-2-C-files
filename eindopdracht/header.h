#ifndef HEADER_H
#define HEADER_H

#include <SDL2/SDL.h> //sdl lib voor sdl_color

#define SC_MULTIPLIER 1 // screen multiplier change to 2 for 4k or (1.5 for 1080p ,1.3333 for 1440p if you want)

#define Point_mover_PLAIN_WIDTH 1260 * SC_MULTIPLIER  // 1260 ,1900 for small screen and 2540(2k) or 3820(4k) for bigger screen	(for move_point_rand() function)
#define Point_mover_PLAIN_HEIGHT 700 * SC_MULTIPLIER // 700, 1060 for small screen and 1420(2K) or 2120(4k) for bigger screen (for move_point_rand() function)

// kleiner plain in de fullscreen
#define SCREEN_WIDTH_PLAIN 1241 * SC_MULTIPLIER	 // 1241, 1881 (small) and 2521 or 3762 (bigger)  (for randomaizer)
#define SCREEN_HEIGHT_PLAIN 681 * SC_MULTIPLIER // 681, 1041 (small) and 1401 or 2082 (bigger)  (for randomaizer)

// fullscreen
#define SCREEN_WIDTH 1280 * SC_MULTIPLIER  //  1280, 1920 or 2560 for bigger screens
#define SCREEN_HEIGHT 720 * SC_MULTIPLIER // 720, 1080 or 1440 for bigger screens
#define fps     33                          // how groot is fps hoe langzaam de punten bewegen.

//defenities relatie die relatie heeft met de punten.
#define points_index 200  // punten hoeveelheid
#define PI 3.14159265358979323846		 // pi voor de cirkel
#define point_plain 50					 // hoever wil je de punten bewegen. ideaal is 30 of 40
#define MAX_LIJNEN 4 * SC_MULTIPLIER	 // hoeveel lijnen een punt kan hebben. 4 of 5 zijn ideaal
#define MAX_DISTANCE 150                 // onder hoever moeten andere puneten om lijn temaken naar die punt
//#define PLAIN //tester preprocessor

typedef struct _point_
{
	int x, y;				// x en y coordinaten van elk punt
	int targetX1, targetX2; // target puntx om het punt te bewegen
	int targetY1, targetY2; // targt punty
	int direction_LR;		// direction Left-right
	int direction_UD;		// direction Up_Down
	int lijnen;				// lijnen die connected
	SDL_Color color_state;  // RGB color voor elk punt

} point;

void process_input(point *rand_punten);					// buttons en mouse input
void proper_shutdown(void);								// shutdown
void draw_lines(point *rand_point);						// draw lijnen tussen punten
void cirkel_plot(int x, int y);							// cirkel plot
void move_point_rand(point *points, int index);			// laat de punten random binnen de plain(vlak) bewegen.
int bereken_afstend(int x1, int x2, int y1, int y2); // afstand berekenen tussen twee coordinatiess


SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int pressed = 0;

#endif 