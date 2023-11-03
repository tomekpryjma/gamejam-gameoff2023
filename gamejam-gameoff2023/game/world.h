#pragma once

#include "globals.h"
#include "player.h"
#include "../core/maths/vector2.h"

int g_worldGameMap[MAP_ROWS][MAP_COLUMNS];

typedef struct World {
	float distances[WINDOW_WIDTH];
	const Player* player;
} World;

void World_Raycast(World* world, const Player* player);
void World_SetHitDistance(World* world, const Player* player, const Vector2* rayEndpoint, int rayIndex, float rayAngle);