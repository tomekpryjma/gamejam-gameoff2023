#include "world.h"
#include "../core/maths/maths.h"
#include <math.h>
#include <stdbool.h>

void World_Raycast(World* world, const Player* player) {
	float rayAngle = -FOV / 2.f;
	rayAngle *= DEG2RAD;
	float rayAngleIncrement = FOV / (float)WINDOW_WIDTH;
	rayAngleIncrement *= DEG2RAD;

	for (int rayIndex = 0; rayIndex < WINDOW_WIDTH; rayIndex++) {
		int mapX = 0;
		int mapY = 0;
		Vector2 rayDirection = { cos((double)player->heading + rayAngle), sin((double)player->heading + rayAngle) };
		Vector2 rayEndpoint = { player->position.x, player->position.y };

		for (int step = 0; step < RAY_LENGTH; step++) {
			rayEndpoint.x += rayDirection.x;
			rayEndpoint.y += rayDirection.y;
			mapX = rayEndpoint.x / CELL_SIZE;
			mapY = rayEndpoint.y / CELL_SIZE;

			if (mapX < 0) mapX = 0;
			if (mapX > MAP_COLUMNS) mapX = MAP_COLUMNS - 1;
			if (mapY < 0) mapY = 0;
			if (mapY > MAP_ROWS) mapY = MAP_ROWS - 1;

			if (g_worldGameMap[mapY][mapX] == 1) {
				break;
			}
		}

		rayAngle += rayAngleIncrement;

		/*
		* Add ray hit regardless of whether hit occured or not, when 3D view
		* is rendered a check is made to see if the ray endpoint's coords exist within the
		* g_worldGameMap array.
		*/
		World_SetHitDistance(world, player, &rayEndpoint, rayIndex, rayAngle);
	}
}

void World_SetHitDistance(World* world, const Player* player, const Vector2* rayEndpoint, int rayIndex, float rayAngle) {
	Vector2 diff = Vector2_GetDistances(&player->position, rayEndpoint);
	float magnitude = Vector2_Magnitude(&diff);
	world->distances[rayIndex] = cos(rayAngle) * magnitude;
}