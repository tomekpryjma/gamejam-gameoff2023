// gamejam-gameoff2023.cpp : Defines the entry point for the application.
//

#include "core/core.h"
#include <stdbool.h>
#include "game/globals.h"
#include "game/player.h"
#include "game/world.h"
#include "core/maths/vector2.h"
#include "core/maths/maths.h"
#include "game/view.h"
#include "core/clock.h"

#ifdef DEBUG

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#endif // DEBUG

int main()
{
	bool isRunning = true;
	App app;
	Player player;
	player.heading = 0;
	World world;
	world.player = &player;
	Clock clock;

	Core_Setup(&app);
	Clock_Init(&clock);

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
			g_worldGameMap[randomRow][randomCol] = 1;
		}
	}

	// place player
	bool playerPlaced = false;
	for (int r = 0; r < MAP_ROWS; r++) {
		for (int c = 0; c < MAP_COLUMNS; c++) {
			if (g_worldGameMap[r][c] == 0) {
				player.position = Vector2_Create(200, 200);
				playerPlaced = true;
				break;
			}
		}
		if (playerPlaced) {
			break;
		}
	}
#endif // DEBUG
	
	SDL_Event e;
	while (isRunning) {
		Clock_Tick(&clock);

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				isRunning = false;
			}
		}

		//====================
		// Update
		//====================
		Player_Update(&player, &clock);
		World_Raycast(&world, &player);

		//====================
		// Draw
		//====================
		SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);
		SDL_RenderClear(app.renderer);

		View_Render3D(&app, &world);
#ifdef SHOW2D
		View_Render2D(&app, &world);
#endif // SHOW2D
		SDL_RenderPresent(app.renderer);
	}

	Core_Shutdown(&app);
	return 0;
}
