#pragma once

#include "SDL.h"

typedef struct App {
	SDL_Window* window;
	SDL_Renderer* renderer;
} App;

void Core_Setup(App* app);
void Core_Shutdown(App* app);