#include "view.h"

void View_Render2D(const App* app, const World* world) {
	for (int r = 0; r < MAP_ROWS; r++) {
		for (int c = 0; c < MAP_COLUMNS; c++) {
			if (g_worldGameMap[r][c] != 1) {
				continue;
			}

			SDL_Rect cell = {
				c * CELL_SIZE, r * CELL_SIZE,
				CELL_SIZE, CELL_SIZE
			};
			SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
			SDL_RenderDrawRect(app->renderer, &cell);
		}
	}
	SDL_Rect playerRect = {
		(*world->player).position.x, (*world->player).position.y,
		CELL_SIZE, CELL_SIZE
	};
	SDL_SetRenderDrawColor(app->renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(app->renderer, &playerRect);
}
void View_Render3D(const App* app, const World* world) {
	for (int rayIndex = 0; rayIndex < WINDOW_WIDTH; rayIndex++) {
		float distance = world->distances[rayIndex];
		
		if (distance == 0) {
			distance = 1e30;
		}
		
		float wallHeight = (CELL_SIZE / distance) * 500;
		float wallColour = (distance / RAY_LENGTH) * 255;
		int wallY = (WINDOW_HEIGHT / 2) - (wallHeight / 2);
		SDL_Rect wallSlice = {
			rayIndex, wallY,
			1, wallHeight
		};
		
		SDL_SetRenderDrawColor(app->renderer, wallColour, wallColour, wallColour, 255);
		SDL_RenderDrawRect(app->renderer, &wallSlice);
	}
}