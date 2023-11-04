#include "clock.h"

void Clock_Init(Clock* clock) {
	clock->deltaTime = 0;
	clock->last = SDL_GetTicks();
}
void Clock_Tick(Clock* clock) {
	Uint32 now = SDL_GetTicks();
	clock->deltaTime = (now - clock->last) / 1000.f;
	clock->last = now;
}