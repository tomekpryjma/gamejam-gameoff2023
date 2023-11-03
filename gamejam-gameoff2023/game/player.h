#pragma once

#include "../core/maths/vector2.h"

typedef struct Player {
	Vector2 position;
	Vector2 mousePosition;
	float heading;
} Player;

void Player_Update(Player* player);