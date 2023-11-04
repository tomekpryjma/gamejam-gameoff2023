#include "player.h"
#include "../core/maths/maths.h"
#include "globals.h"
#include "SDL.h"


void Player_Update(Player* player, const Clock* clock) {
	int moveDirectionFB = 0;
	int moveDirectionLR = 0;
	int mRelX;
	const double dT = clock->deltaTime;

	SDL_GetRelativeMouseState(&mRelX, NULL);
	player->heading += mRelX * DEG2RAD * PLAYER_LOOK_SPEED * dT;

	Uint8* keyStates = SDL_GetKeyboardState(NULL);
	if (keyStates[SDL_SCANCODE_W]) {
		moveDirectionFB = 1;
	}
	if (keyStates[SDL_SCANCODE_S]) {
		moveDirectionFB = -1;
	}
	if (keyStates[SDL_SCANCODE_A]) {
		moveDirectionLR = -1;
	}
	if (keyStates[SDL_SCANCODE_D]) {
		moveDirectionLR = 1;
	}

	if (moveDirectionFB != 0) {
		player->position.x += cos(player->heading) * moveDirectionFB * PLAYER_MOVE_SPEED * dT;
		player->position.y += sin(player->heading) * moveDirectionFB * PLAYER_MOVE_SPEED * dT;
	}
	if (moveDirectionLR != 0) {
		player->position.x += cos(player->heading + M_PI_2) * moveDirectionLR * PLAYER_MOVE_SPEED * dT;
		player->position.y += sin(player->heading + M_PI_2) * moveDirectionLR * PLAYER_MOVE_SPEED * dT;
	}
}