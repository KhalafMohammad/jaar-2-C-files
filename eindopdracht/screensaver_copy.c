#include <stdio.h>
#include <time.h> //include for random nums
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>
// #include "header.h"

#define SC_MULTIPLIER 1 // screen multiplier change to 2 for 4k or (1.5 for 1080p ,1.3333 for 1440p if you want)

#define Point_mover_PLAIN_WIDTH 1260 * SC_MULTIPLIER  // 1260 ,1900 for small screen and 2540(2k) or 3820(4k) for bigger screen	(for move_point_rand() function)
#define Point_mover_PLAIN_HEIGHT 700 * SC_MULTIPLIER // 700, 1060 for small screen and 1420(2K) or 2120(4k) for bigger screen (for move_point_rand() function)

// smaller plain within the full screen
#define SCREEN_WIDTH_PLAIN 1241 * SC_MULTIPLIER	 // 1241, 1881 (small) and 2521 or 3762 (bigger)  (for randomaizer)
#define SCREEN_HEIGHT_PLAIN 681 * SC_MULTIPLIER // 681, 1041 (small) and 1401 or 2082 (bigger)  (for randomaizer)

// fullscreen
#define SCREEN_WIDTH 1280 * SC_MULTIPLIER  //  1280, 1920 or 2560 for bigger screens
#define SCREEN_HEIGHT 720 * SC_MULTIPLIER // 720, 1080 or 1440 for bigger screens

#define points_index 200  // punten hoeveelheid
#define PI 3.14159265358979323846		 // pi voor de cirkel
#define point_plain 50					 // hoever wil je de punten bewegen. ideaal is 30 of 40
#define MAX_LIJNEN 4 //* SC_MULTIPLIER	 // hoeveel lijnen een punt kan hebben. 4 of 5 zijn ideaal
#define MAX_DISTANCE 150
// #define PLAIN //tester preprocessor

typedef struct _point_
{
	int x, y;				// x en y coordinaten van elk punt
	int targetX1, targetX2; // target puntx om het punt te bewegen
	int targetY1, targetY2; // targt punty
	int direction_LR;		// direction Left-right
	int direction_UD;		// direction Up_Down
	int lijnen;				// lijnen die connected
	SDL_Color color_state;

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

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	srand((unsigned int)time(NULL));

	point rand_point[points_index];

	for (int i = 0; i < points_index; i++)
	{
		rand_point[i].x = (rand() % SCREEN_WIDTH_PLAIN) + 20; // maak de coordinatie vand de punt random binnen de vlak(plain)
		rand_point[i].y = (rand() % SCREEN_HEIGHT_PLAIN) + 20;
		rand_point[i].targetX1 = rand_point[i].x + rand() % point_plain; // Random X target
		rand_point[i].targetX2 = rand_point[i].x - rand() % point_plain; // Random X target
		rand_point[i].targetY1 = rand_point[i].y + rand() % point_plain; // Random Y target
		rand_point[i].targetY2 = rand_point[i].y - rand() % point_plain; // Random Y target
		rand_point[i].direction_LR = 1;
		rand_point[i].direction_UD = 1;
		rand_point[i].color_state.r = 255; //rest point color to white before the mouse click to white
		rand_point[i].color_state.g = 255;
		rand_point[i].color_state.b = 255;
		rand_point[i].color_state.a = 255;
	}

	//=========================================== V SDL related V ====================================================

	unsigned int window_flags = 0;
	unsigned int renderer_flags = SDL_RENDERER_ACCELERATED;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	window = SDL_CreateWindow("screensaver", SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
							  window_flags);
	if (window == NULL)
	{
		printf("Failed to create window -- Error: %s\n",
			   SDL_GetError());
		exit(1);
	}

	renderer = SDL_CreateRenderer(window, -1, renderer_flags);
	if (renderer == NULL) // error handling:
	{
		printf("Failed to create renderer -- Error: %s\n",
			   SDL_GetError());
		exit(1);
	}

	//============================================= ^ SDL RELATED ^ =====================================================
	while (1)
	{
		// Refresh the backbuffer to its original state:
		// RGB (39, 174, 96) should be a green grass color
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// Process selected inputs and pay close attention to moving				//
		process_input(rand_point); //

#ifdef PLAIN
		// de vlak (plain) vastleggen(dit is een kliene-plain binnen de fullscreen) waar de punten gaan bewegen
		//  								  R	  G  B    A
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red is x1900 by y1060
		SDL_RenderDrawPoint(renderer, 1900, 1060);
		cirkel_plot(1900, 1060);

		SDL_RenderDrawLine(renderer, 1900, 1060, 20, 1060);

		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green is x20 by y1060
		SDL_RenderDrawPoint(renderer, 20, 1060);
		cirkel_plot(20, 1060);

		SDL_RenderDrawLine(renderer, 20, 1060, 20, 20);

		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // blue is x1900 by y20
		SDL_RenderDrawPoint(renderer, 1900, 20);
		cirkel_plot(1900, 20);

		SDL_RenderDrawLine(renderer, 1900, 20, 1900, 1060);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white is x20 by y20
		SDL_RenderDrawPoint(renderer, 20, 20);
		cirkel_plot(20, 20);

		SDL_RenderDrawLine(renderer, 1900, 20, 20, 20);
#endif

		// laat de punten gaan bewegen
		move_point_rand(rand_point, points_index);

		// lijnen renderen tussen puneten.
		draw_lines(rand_point);

		// Render redrawn scene to front buffer, showing it in the
		// actual window:
		SDL_RenderPresent(renderer);
		// Remember ~ 60 FPS of smooth Greta movements - PC Master Race!
		SDL_Delay(33);
	}

	return 0;
}

void process_input(point *rand_point)
{
	int punt_afstand;

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			proper_shutdown();
			exit(0);
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.scancode)
			{
			case SDL_SCANCODE_ESCAPE:
				proper_shutdown();
				exit(0);
				break;
			default:
				break;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) //als de linkse mouse button is geclicked
			{
				pressed = 1; //dan hij is geklicked maak pressed 1
			}

			break;
		case SDL_MOUSEMOTION:
			if (pressed == 1)
			{

				for (int i = 0; i < points_index; i++)
				{
					punt_afstand = bereken_afstend(rand_point[i].x, event.motion.x, rand_point[i].y, event.motion.y);
					if (punt_afstand < 100)
					{

						rand_point[i].color_state.r = 255;
						rand_point[i].color_state.g = 255;
						rand_point[i].color_state.b = 255;
						rand_point[i].color_state.a = 255;
					}
					else if (punt_afstand > 100 && punt_afstand < 175){

						rand_point[i].color_state.r = 100;
						rand_point[i].color_state.g = 100;
						rand_point[i].color_state.b = 100;
						rand_point[i].color_state.a = 255;

					}
					else if(punt_afstand > 175 && punt_afstand < 250){

						rand_point[i].color_state.r = 25;
						rand_point[i].color_state.g = 25;
						rand_point[i].color_state.b = 25;
						rand_point[i].color_state.a = 255;
					}
					else{

						rand_point[i].color_state.r = 0;
						rand_point[i].color_state.g = 0;
						rand_point[i].color_state.b = 0;
						rand_point[i].color_state.a = 255;
						
					}
				}
			}

			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)//als de linkse mouse button is niet geclicked of mouse linkse button is up..
			{
				pressed = 0; //dan hij is niet meer geklicked maak pressed 0
				for (int i = 0; i < points_index; i++) // en reset alle punten naar wit.
				{
					rand_point[i].color_state.r = 255;
					rand_point[i].color_state.g = 255;
					rand_point[i].color_state.b = 255;
					rand_point[i].color_state.a = 255;
				}
			}

			break;
		default:
			break;
		}
	}
}

void proper_shutdown(void)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// de lijnen maken tussen een punt en een andere die dichtbij is.
void draw_lines(point *rand_point)
{

	//het begin van punten plotten op de screen.
	for (int i = 0; i < points_index; i++)
	{
		//kleur geven (wit)
		SDL_SetRenderDrawColor(renderer, rand_point[i].color_state.r, rand_point[i].color_state.g, rand_point[i].color_state.b, rand_point[i].color_state.a);
		SDL_RenderDrawPoint(renderer, rand_point[i].x, rand_point[i].y);//render de punten in de array
		cirkel_plot(rand_point[i].x, rand_point[i].y);//plot een cirkel om de puntheen
	}
	// elk lijn lengte berekenen door de x en y coordinaten van twee punten aan het begin en einde van de lijn.
	double lijn_lengte;

	for (int i = 0; i < points_index; i++)//iterate door de array
	{
		rand_point[i].lijnen = 0; // lijnen eerst reset naar 0

		for (int j = i + 1; j < points_index; j++) // check met de volgende punt die aan de beurt
		{
			if (rand_point[i].lijnen < MAX_LIJNEN) // is lijnen van die punt minder dan 5 dan...
			{

				lijn_lengte = bereken_afstend(rand_point[i].x, rand_point[j].x, rand_point[i].y, rand_point[j].y);//afstand berkenen
				if (round(lijn_lengte) < MAX_DISTANCE) // is distance minder dan MAX_DISTANCE pixels dan plot een lijn
				{
					SDL_SetRenderDrawColor(renderer, rand_point[i].color_state.r, rand_point[i].color_state.g, rand_point[i].color_state.b, rand_point[i].color_state.a);
					SDL_RenderDrawLine(renderer, rand_point[i].x, rand_point[i].y, rand_point[j].x, rand_point[j].y);
					rand_point[i].lijnen++; // en encrement de lijnen van die punt
				}
			}
		}
	}
}

// plot een cirkel heeft x en y coordinaten nodig voor de center van de circel
void cirkel_plot(int x, int y)
{
	// SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	// geef eerst de middle van de cirkel
	int cirkel_X = x;
	int cirkel_Y = y;

	int cirkel_Radius = 4;				   // de grotte van de cirkel
	int numPoints = 20;					   // hoeveel punten langs de radius van de cirkel, 1000 is veel 100 is ok.
	double angleStep = 2 * PI / numPoints; // radiaal berkenen tussen elk punt rond de cirkel

	for (int i = 0; i < numPoints; i++)
	{ // coordinaten berkenen voor elk punt rond de cirkel
		int x = cirkel_X + (int)(cirkel_Radius * cos(angleStep * i));
		int y = cirkel_Y + (int)(cirkel_Radius * sin(angleStep * i));
		SDL_RenderDrawPoint(renderer, x, y); // alle puneten berkenen
	}
}

/*i heb twee extra punten gemaakt met hun x en y, (X1,Y1) en (X2,Y2)
de punt eerst beweegt naar de coordianten van de punten die boven gecreëerd
daarna als de coordianten van de punt is gelijk aan de random punt keertterug en nieuwe
punt daarna wordt gerandomiseerd */
void move_point_rand(point *points, int index)
{

	for (int q = 0; q < index; q++)
	{
		points[q].x += points[q].direction_LR; // Move the point in the current direction
		points[q].y += points[q].direction_UD;

		// Check if the point has reached a target, and reverse direction
		if (points[q].x >= points[q].targetX1 || points[q].x <= points[q].targetX2 || points[q].x >= Point_mover_PLAIN_WIDTH || points[q].x <= 20)
		{
			points[q].direction_LR *= -1;							 // reverse direction back
			points[q].targetX1 = points[q].x + rand() % point_plain; // recreate first target X coordinate
			points[q].targetX2 = points[q].x - rand() % point_plain; // recreate second target X coordinate
		}

		if (points[q].y >= points[q].targetY1 || points[q].y <= points[q].targetY2 || points[q].y >= Point_mover_PLAIN_HEIGHT || points[q].y <= 20)
		{
			points[q].direction_UD *= -1;
			points[q].targetY1 = points[q].y + rand() % point_plain; // recreate first target Y coordinate
			points[q].targetY2 = points[q].y - rand() % point_plain; // recreate second target Y coordinate
		}
	}
}

int bereken_afstend(int x1, int x2, int y1, int y2)//bereken_afstend
{

	double lengte = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
	return (int)round(lengte);
}