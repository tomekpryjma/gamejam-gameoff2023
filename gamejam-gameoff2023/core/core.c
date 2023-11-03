#include "core.h"
#include "../game/globals.h"
#include <stdio.h>

void Core_Setup(App* app) {
	int result = SDL_Init(SDL_INIT_VIDEO);
	if (result != 0) {
		printf(SDL_GetError());
		exit(result);
	}

	app->window = SDL_CreateWindow("Game Jam - Game Off 2023", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if (app->window == NULL) {
		printf(SDL_GetError());
		exit(1);
	}

	app->renderer = SDL_CreateRenderer(app->window, 0, 0);
	if (app->renderer == NULL) {
		printf(SDL_GetError());
		exit(1);
	}
}

void Core_Shutdown(App* app) {
	SDL_DestroyRenderer(app->renderer);
	SDL_DestroyWindow(app->window);
	SDL_Quit();
}