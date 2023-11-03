// gamejam-gameoff2023.cpp : Defines the entry point for the application.
//

#include "core/core.h"
#include <stdbool.h>
#include "game/globals.h"
#include "core/maths/vector2.h"
#include "core/maths/maths.h"

#ifdef DEBUG

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#endif // DEBUG


int gameMap[MAP_ROWS][MAP_COLUMNS];
float distances[WINDOW_WIDTH];

int main()
{
	bool isRunning = true;
	App app;
	Vector2 playerMapPos;
	Vector2 playerPos;
	Vector2 playerHeading;
	Vector2 mousePos = {0, 0};

	Core_Setup(&app);

#ifdef DEBUG
	time_t t;
	srand((unsigned) time(&t));

	// map build
	int activeRows = MAP_ROWS / 2;
	int activeColsPerRow = 20;

	for (int i = 0; i < activeRows; i++) {
		int randomRow = rand() % MAP_ROWS - 1;
		for (int j = 0; j < activeColsPerRow; j++) {
			int randomCol = rand() % MAP_COLUMNS - 1;
			gameMap[randomRow][randomCol] = 1;
		}
	}

	// place player
	bool playerPlaced = false;
	for (int r = 0; r < MAP_ROWS; r++) {
		for (int c = 0; c < MAP_COLUMNS; c++) {
			if (gameMap[r][c] == 0) {
				playerPos = Vector2_Create(200, 200);
				playerPlaced = true;
				break;
			}
		}
		if (playerPlaced) break;
	}
#endif // DEBUG
	
	// Loop
	SDL_Event e;
	while (isRunning) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				isRunning = false;
			}
		}
		// Update mouse
		int mx, my;
		SDL_GetMouseState(&mx, &my);
		mousePos.x = mx;
		mousePos.y = my;
		// End update mouse

		// Keyboard state
		Uint8* keyStates = SDL_GetKeyboardState(NULL);
		if (keyStates[SDL_SCANCODE_W]) {
			playerPos.y -= 1;
		}
		if (keyStates[SDL_SCANCODE_S]) {
			playerPos.y += 1;
		}
		if (keyStates[SDL_SCANCODE_A]) {
			playerPos.x -= 1;
		}
		if (keyStates[SDL_SCANCODE_D]) {
			playerPos.x += 1;
		}
		// end Keyboard state

		float rayAngleIncrement = FOV / (float)WINDOW_WIDTH;
		rayAngleIncrement *= DEG2RAD;

		// update player heading
		Vector2 playerToMouseDist = Vector2_GetDistances(&playerPos, &mousePos);
		Vector2 playerToMouseHeading = Vector2_Normalize(&playerToMouseDist);
		float playerHeading = atan2f(playerToMouseHeading.y, playerToMouseHeading.x);
		// end update player heading
		
		SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);
		SDL_RenderClear(app.renderer);

		// Raycasting
		float rayAngle = -FOV / 2.f;
		rayAngle *= DEG2RAD;
		for (int rayIndex = 0; rayIndex < WINDOW_WIDTH; rayIndex++) {
			bool hit = false;
			// offset by playerheading
			Vector2 rayDirection = {
				cos((double)playerHeading + rayAngle),
				sin((double)playerHeading + rayAngle)
			};
			SDL_SetRenderDrawColor(app.renderer, 0, 0, 255, 255);
			SDL_RenderDrawLine(
				app.renderer,
				playerPos.x,
				playerPos.y,
				playerPos.x + rayDirection.x * 20,
				playerPos.y + rayDirection.y * 20
			);

			Vector2 rayEndpoint = {playerPos.x, playerPos.y};
			int mapX = 0;
			int mapY = 0;

			// Extend ray
			for (int step = 0; step < RAY_LENGTH; step++) {
				if (hit) break;
				rayEndpoint.x += rayDirection.x;
				rayEndpoint.y += rayDirection.y;
				mapX = rayEndpoint.x / CELL_SIZE;
				mapY = rayEndpoint.y / CELL_SIZE;

				if (mapX < 0) mapX = 0;
				if (mapX > MAP_COLUMNS) mapX = MAP_COLUMNS - 1;
				if (mapY < 0) mapY = 0;
				if (mapY > MAP_ROWS) mapY = MAP_ROWS - 1;

				if (gameMap[mapY][mapX] == 1) {
					hit = true;
				}
			}
			// end extend ray
			rayAngle += rayAngleIncrement;
			if (hit) {
				SDL_RenderDrawRect(app.renderer, &(SDL_Rect){rayEndpoint.x, rayEndpoint.y});
				Vector2 diff = Vector2_GetDistances(&playerPos, &rayEndpoint);
				float magnitude = Vector2_Magnitude(&diff);
				distances[rayIndex] = cos(rayAngle) * magnitude;
			}
		}
		// End Raycasting

		// Render 3d view
		for (int rayIndex = 0; rayIndex < WINDOW_WIDTH; rayIndex++) {
			float distance = distances[rayIndex];
			if (distance == 0) distance = 1e30;
			float wallHeight = (CELL_SIZE / distance) * 500;
			SDL_Rect wallSlice = {rayIndex, (WINDOW_HEIGHT / 2) - (wallHeight / 2), 1, wallHeight };
			float wallColour = (distance / RAY_LENGTH) * 255;
			SDL_SetRenderDrawColor(app.renderer, wallColour, wallColour, wallColour, 255);
			SDL_RenderDrawRect(app.renderer, &wallSlice);
		}
		// end Render 3d view

#ifdef SHOW2D
		// render 2d map
		for (int r = 0; r < MAP_ROWS; r++) {
			for (int c = 0; c < MAP_COLUMNS; c++) {
				if (gameMap[r][c] != 1) continue;
				SDL_Rect cell = { c * CELL_SIZE, r * CELL_SIZE, CELL_SIZE, CELL_SIZE };
				SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
				SDL_RenderDrawRect(app.renderer, &cell);
			}
		}
		// end render 2d map

		// render player
		SDL_SetRenderDrawColor(app.renderer, 255, 0, 0, 255);
		SDL_Rect playerRect = { playerPos.x, playerPos.y, CELL_SIZE, CELL_SIZE };
		SDL_RenderDrawRect(app.renderer, &playerRect);
		// end render player
#endif // SHOW2D

		SDL_RenderPresent(app.renderer);
	}

	Core_Shutdown(&app);
	return 0;
}
