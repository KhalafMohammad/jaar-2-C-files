#include <stdio.h>
#include <time.h> //include for random nums
// #include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>

#define SCREEN_WIDTH   1200
#define SCREEN_HEIGHT  800
#define pointscount 3
#define hoekencount 3
#define PI 3.14159265358979323846


typedef struct _punt_ {
    int x;
    int y;
}punt;

typedef struct _hoek_ {
    double cos_hoek;
    double rad_hoek;
	double graden_hoek;
}hoek;


void process_input(punt *punten);
void proper_shutdown(void);
void calc_hoeken(punt *punten);
void cirkel_plot(int x , int y);
void plot_recht_rect(int x , int y);
void plot_half_cirkel(int x, int y, double rad);


SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int isDragging = 0;


int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	
    srand((unsigned int)time(NULL));

	punt punten[pointscount];
	//create a random position for every point.
	for (int i = 0; i < pointscount; i++)
	{
		punten[i].x = rand()% SCREEN_WIDTH;
		punten[i].y = rand() % SCREEN_HEIGHT;
	}
	
	
	
	
	unsigned int window_flags = 0;
	unsigned int renderer_flags = SDL_RENDERER_ACCELERATED;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	window = SDL_CreateWindow("Interactive DrieHoek", SDL_WINDOWPOS_UNDEFINED, 
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
	
	while (1)
	{
		// Refresh the backbuffer to its original state:
		// RGB (39, 174, 96) should be a green grass color
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
        process_input(punten);
		// Process selected inputs and pay close attention to moving
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);//green triangle
        for (int i = 0; i < pointscount; i++)
        {
            SDL_RenderDrawPoint(renderer, punten[i].x, punten[i].y);//render every point in punten array 
			
			SDL_Rect rect_to_grab = {punten[i].x, punten[i].y, 10,10}; // render een rectangle bij elk punt
			//SDL_RenderFillRect(renderer, &rect_to_grab);
			SDL_RenderDrawRect(renderer, &rect_to_grab);
        }
		

        //lijnen renderen tussen puneten.
        SDL_RenderDrawLine(renderer, punten[0].x, punten[0].y, punten[1].x, punten[1].y);
		SDL_RenderDrawLine(renderer, punten[1].x, punten[1].y, punten[2].x, punten[2].y);
        SDL_RenderDrawLine(renderer, punten[2].x, punten[2].y, punten[0].x, punten[0].y);

		calc_hoeken(punten);//lijnen tussen punten berekenen
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            
		// Render redrawn scene to front buffer, showing it in the 
		// actual window:
		SDL_RenderPresent(renderer);
		// Remember ~ 60 FPS of smooth Greta movements - PC Master Race!
		SDL_Delay(16);
	}

	return 0;
}

void process_input(punt *punten)
{
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
				
					if (event.button.button == SDL_BUTTON_LEFT) {
						
						for (int i = 0; i < pointscount; i++)
						{	//als de plaats van de mouse toen de linker button is klicked op de plaats van 
							//een van de punten dan verandert de draging naar 1 voor punt A, 2 voor B en 3 voor C
							if (event.button.x >= punten[i].x && event.button.x <= punten[i].x + 10 &&
                    			event.button.y >= punten[i].y && event.button.y <= punten[i].y + 10) {
									if(i == 0){
										isDragging = 1; // Start dragging
									}else if(i == 1){
										isDragging = 2;
									}else if(i == 2){
										isDragging = 3;
									}
							}
						}
					}
				break;
			case SDL_MOUSEMOTION:
				
				if (isDragging == 1) {
					//als draging is 1 dan de mouse is op punt A en heeft de coordinaten van de mouse als het beweegt
					punten[0].x = event.motion.x;
            		punten[0].y = event.motion.y;
					printf("punt A is grabbed\n");
					

            	}else if (isDragging == 2){
					//als draging is 2 dan de mouse is op punt B en heeft de coordinaten van de mouse als het beweegt
					punten[1].x = event.motion.x;
            		punten[1].y = event.motion.y;
					printf("punt B is grabbed\n");

				}else if (isDragging == 3){
					//als draging is 3 dan de mouse is op punt C en heeft de coordinaten van de mouse als het beweegt
					punten[2].x = event.motion.x;
            		punten[2].y = event.motion.y;
					printf("punt C is grabbed\n");
				}
				
            	break;
            case SDL_MOUSEBUTTONUP:
            	if (event.button.button == SDL_BUTTON_LEFT) {
                	isDragging = 0; // Stop dragging
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

// functie calculeert de hoeken door eerst de lengte van de lijnen de berekenen.
void calc_hoeken(punt *punten)
{
	//elk lijn lengte berekenen door de x en y coordinaten van twee punten aan het begin en einde van de lijn.
	double lengte_b = sqrt(pow(punten[0].x - punten[2].x, 2) + pow(punten[0].y - punten[2].y, 2));
	double lengte_a = sqrt(pow(punten[2].x - punten[1].x, 2) + pow(punten[2].y - punten[1].y, 2));
	double lengte_c = sqrt(pow(punten[1].x - punten[0].x, 2) + pow(punten[1].y - punten[0].y, 2));

	hoek hoeken[hoekencount];

	//door de lengte van de lijn die tegen over de hoek A is (a) bereknt dit hoeveel graden is die hoek door eerst
	//cos van de hoek te bereknen, daarne radiaal berkenen en dan van radiaal naar graden.
	hoeken[0].cos_hoek = (pow(lengte_b, 2) + pow(lengte_c, 2) - pow(lengte_a, 2)) / (2.0 * lengte_b * lengte_c);
	//naar radialen berkenen dooe acos() functie.
	hoeken[0].rad_hoek = acos(hoeken[0].cos_hoek);
	//naar graden berkenen door graden = rad * (180 / pi)
	hoeken[0].graden_hoek = hoeken[0].rad_hoek * (180.0 / PI);
	//==========================================================
	//hetzelfde voor hoek B
	hoeken[1].cos_hoek = (pow(lengte_a, 2) + pow(lengte_c, 2) - pow(lengte_b, 2)) / (2.0 * lengte_a * lengte_c);
	hoeken[1].rad_hoek = acos(hoeken[1].cos_hoek);

	hoeken[1].graden_hoek = hoeken[1].rad_hoek * (180.0 / PI);
	//===========================================================
	//en ook voor Hoek C
	hoeken[2].cos_hoek = (pow(lengte_a, 2) + pow(lengte_b, 2) - pow(lengte_c, 2)) / (2.0 * lengte_a * lengte_b);
	hoeken[2].rad_hoek = acos(hoeken[2].cos_hoek);

	hoeken[2].graden_hoek = hoeken[2].rad_hoek * (180.0 / PI);
	//printen van graden met een nummer achter de komma.
	printf("hoek A heeft %.1f graden\n", hoeken[0].graden_hoek);
	printf("hoek B heeft %.1f graden\n", hoeken[1].graden_hoek);
	printf("hoek C heeft %.1f graden\n", hoeken[2].graden_hoek);
	printf("\n");
	printf("\n");

	//als hoek A groter of gelijk aan 89.2 EN kliener of gelijk aan 90.2 dan maakt hij een witte rectangle 
	if(hoeken[0].graden_hoek >= 89.9 && hoeken[0].graden_hoek <= 90.1){

		plot_recht_rect(punten[0].x , punten[0].y);//rect plotten

	}else{
		cirkel_plot(punten[0].x, punten[0].y);	//cirkel plotten
		//plot_half_cirkel(punten[0].x, punten[0].y, radiaal_A);
	}
	
	if(hoeken[1].graden_hoek >= 89.9 && hoeken[1].graden_hoek <= 90.1){

		plot_recht_rect(punten[1].x , punten[1].y);//rect plotten

	}else{
        cirkel_plot(punten[1].x, punten[1].y); //cirkel plotten
	}
	
	if(hoeken[2].graden_hoek >= 89.9 && hoeken[2].graden_hoek <= 90.1){

		plot_recht_rect(punten[2].x , punten[2].y); //rect plotten
		
	}else{
		
		cirkel_plot(punten[2].x, punten[2].y); //cirkel plotten
	}
}

//plot een cirkel heeft x en y coordinaten nodig voor de center van de circel
void cirkel_plot(int x , int y){
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	//geef eerst de middle van de cirkel
	int cirkel_X = x;
    int cirkel_Y = y;
	
    int cirkel_Radius = 35; // de grotte van de cirkel
    int numPoints = 500; // hoeveel punten langs de radius van de cirkel, 1000 is veel 100 is ok. 
    double angleStep = 2 * PI / numPoints;//radiaal berkenen tussen elk punt rond de cirkel 

    for (int i = 0; i < numPoints; i++) { // coordinaten berkenen voor elk punt rond de cirkel
        int x = cirkel_X + (int)(cirkel_Radius * cos(angleStep * i));
        int y = cirkel_Y + (int)(cirkel_Radius * sin(angleStep * i));
        SDL_RenderDrawPoint(renderer, x, y);//alle puneten berkenen 
    }
}
//plot een rectangle op de hoek als het 90.0 graden is, heeft x en y coordinaten nodig voor de center van de rectangel.
void plot_recht_rect(int x , int y){


	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //witte kleur
	int rectx_a = x - (30 / 2); //offsset geven zodat de punt in de middle van de recangle is
	int recty_a = y - (30 / 2); //offsset geven zodat de punt in de middle van de recangle is
	SDL_Rect rect_recht = {rectx_a, recty_a , 30 ,30}; //begin punt en grotte geven
	SDL_RenderDrawRect(renderer, &rect_recht); //renderen
}

void plot_half_cirkel(int x, int y, double rad){


	int circleX = x;
    int circleY = y;
    int circleRadius = 35;
    double startAngle = 0 * PI; // o degrees in radians
    double endAngle = rad * PI;   // the corner's degrees in radians
    int numPoints = 1000;

    // Calculate the angular increment
    double angleStep = (endAngle - startAngle) / numPoints;

    // Render points within the specified angle range
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
    for (int i = 0; i <= numPoints; i++) {
        double angle = startAngle + angleStep * i;
        int x = circleX + (int)(circleRadius * cos(angle));
        int y = circleY + (int)(circleRadius * sin(angle));
        SDL_RenderDrawPoint(renderer, x, y);
    }

}