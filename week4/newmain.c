#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PI 3.14159265358979323846

int main(int argc, char* argv[]) {

    (void)argc;
	(void)argv;
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Partial Circle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Event event;
    int quit = 0;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // Clear the renderer
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Define the circle's center, radius, and angle range
        int circleX = WINDOW_WIDTH / 2;
        int circleY = WINDOW_HEIGHT / 2;
        int circleRadius = 50;
        double startAngle = 0.25 * PI; // 45 degrees in radians
        double endAngle = 1.75 * PI;   // 315 degrees in radians
        int numPoints = 100;

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

        // Present the renderer
        SDL_RenderPresent(renderer);
    }

    // Cleanup and quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
