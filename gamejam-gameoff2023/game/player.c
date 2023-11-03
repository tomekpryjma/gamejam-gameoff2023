#include "player.h"
#include "../core/maths/maths.h"
#include "globals.h"
#include "SDL.h"


void Player_Update(Player* player) {
	int mx, my;
	SDL_GetMouseState(&mx, &my);
	player->mousePosition.x = mx;
	player->mousePosition.y = my;

	Uint8* keyStates = SDL_GetKeyboardState(NULL);
	if (keyStates[SDL_SCANCODE_W]) {
		player->position.y -= 1;
	}
	if (keyStates[SDL_SCANCODE_S]) {
		player->position.y += 1;
	}
	if (keyStates[SDL_SCANCODE_A]) {
		player->position.x -= 1;
	}
	if (keyStates[SDL_SCANCODE_D]) {
		player->position.x += 1;
	}

	Vector2 playerToMouseDist = Vector2_GetDistances(&player->position, &player->mousePosition);
	Vector2 playerToMouseHeading = Vector2_Normalize(&playerToMouseDist);
	player->heading = atan2f(playerToMouseHeading.y, playerToMouseHeading.x);
}