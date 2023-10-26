#include <stdio.h>
#include <time.h> //include for random nums
#include <stdlib.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH   1024
#define SCREEN_HEIGHT  576

// Define the mighty cow as something drawable @ some x,y-coordinate:
typedef struct _koe_ {
	int x;
	int y;
} koe;

void process_input(koe *koetje);
void proper_shutdown(void);
void koe_offset(koe *array);//spawn 10 more cows
void onze_greta(koe array);//spawn greta


SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;


//offsets fast geleged voor greta

#define lijf_offset (SDL_Rect) {array.x, array.y, 32, 32}
#define kop_offset (SDL_Rect) {array.x + 8, array.y - 16, 16, 16}
#define staart_offset (SDL_Rect) {array.x + 14, array.y + 32, 4, 4}
#define linkervoorpoot_offset (SDL_Rect) {array.x - 6, array.y + 4, 6, 6}
#define rechtervoorpoot_offset (SDL_Rect) {array.x + 32, array.y + 4, 6, 6}
#define linkerachterpoot_offset (SDL_Rect) {array.x - 6, array.y + 24, 6, 6}
#define rechterachterpoot_offset (SDL_Rect) {array.x + 32, array.y + 24, 6, 6}



int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	srand((unsigned int)time(NULL));

	
	// Spawn Greta in the middle of the window:
	koe greta = {(SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2)};

	//een array van andere 10 nbc koeien.
	koe koeien[10];
	//create a random position for every koe.
	for (int i = 0; i < 10; i++)
	{
		koeien[i].x = rand()% SCREEN_WIDTH;
		koeien[i].y = rand() % SCREEN_HEIGHT;
	}
	
	
	
	unsigned int window_flags = 0;
	unsigned int renderer_flags = SDL_RENDERER_ACCELERATED;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	window = SDL_CreateWindow("All your grass are belong to Greta", SDL_WINDOWPOS_UNDEFINED, 
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
		SDL_SetRenderDrawColor(renderer, 39, 174, 96, 255);
		SDL_RenderClear(renderer);
		// Process selected inputs and pay close attention to moving
		// our freshly spawned cow:
		process_input(&greta);

		//spawn the rest of the cows:
		koe_offset(koeien);
		//spawn greta the great
		onze_greta(greta);

		
		// Render redrawn scene to front buffer, showing it in the 
		// actual window:
		SDL_RenderPresent(renderer);
		// Remember ~ 60 FPS of smooth Greta movements - PC Master Race!
		SDL_Delay(16);
	}

	return 0;
}

void process_input(koe *koetje)
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
					case SDL_SCANCODE_RIGHT:
						koetje->x += 4;
						break;
					case SDL_SCANCODE_LEFT:
						koetje->x -= 4;
						break;
					case SDL_SCANCODE_UP:
						koetje->y -= 4;
						break;
					case SDL_SCANCODE_DOWN:
						koetje->y += 4;
						break;
					default:
						break;
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

//function die neemt de array van de 10 koeien als argument en spawned ze op de scherm:
void koe_offset(koe *array){

	int r = rand() % 255;  // Random value tussen 0 and 255 voor Red
    int g = rand() % 255;  // Random value tussen 0 and 255 for Green
    int b = rand() % 255;  // Random value tussen 0 and 255 for Blue


	for (int i = 0; i < 10; i++)
	{
		SDL_Rect lijf1 = {array[i].x, array[i].y, 32, 32};
		SDL_Rect kop1 = {array[i].x + 8, array[i].y - 16, 16, 16};
		SDL_Rect staart1 = {array[i].x + 14, array[i].y + 32, 4, 4};
		SDL_Rect linkervoorpoot1 = {array[i].x - 6, array[i].y + 4, 6, 6};
		SDL_Rect rechtervoorpoot1 = {array[i].x + 32, array[i].y + 4, 6, 6};
		SDL_Rect linkerachterpoot1 = {array[i].x - 6, array[i].y + 24, 6, 6};
		SDL_Rect rechterachterpoot1 = {array[i].x + 32, array[i].y + 24, 6, 6};

		// hier maak ik alle koeien RGB BECAUSE - PC Master Race!
		SDL_SetRenderDrawColor(renderer, (Uint8)r, (Uint8)g, (Uint8)b, 255);
		// Redraw alle 10 koeien in de backbuffer naar hun updated location:
		SDL_RenderFillRect(renderer, &lijf1);
		SDL_RenderFillRect(renderer, &kop1);
		SDL_RenderFillRect(renderer, &staart1);
		SDL_RenderFillRect(renderer, &linkervoorpoot1);
		SDL_RenderFillRect(renderer, &rechtervoorpoot1);
		SDL_RenderFillRect(renderer, &linkerachterpoot1);
		SDL_RenderFillRect(renderer, &rechterachterpoot1);
	}

}

void onze_greta(koe array){


	SDL_Rect lijf = lijf_offset;
	SDL_Rect kop = kop_offset;
	SDL_Rect staart = staart_offset;
	SDL_Rect linkervoorpoot = linkervoorpoot_offset;
	SDL_Rect rechtervoorpoot = rechtervoorpoot_offset;
	SDL_Rect linkerachterpoot = linkerachterpoot_offset;
	SDL_Rect rechterachterpoot = rechterachterpoot_offset;


				
	// RGB (135, 54, 0) should be a brown fur color for Greta
	SDL_SetRenderDrawColor(renderer, 135, 54, 0, 255);
	// Redraw Grata in the backbuffer to her updated location:
	SDL_RenderFillRect(renderer, &lijf);
	SDL_RenderFillRect(renderer, &kop);
	SDL_RenderFillRect(renderer, &staart);
	SDL_RenderFillRect(renderer, &linkervoorpoot);
	SDL_RenderFillRect(renderer, &rechtervoorpoot);
	SDL_RenderFillRect(renderer, &linkerachterpoot);
	SDL_RenderFillRect(renderer, &rechterachterpoot);

}