#pragma once

#include <SDL.h>

typedef struct Clock {
	double deltaTime;
	Uint32 last;
} Clock;

void Clock_Init(Clock* clock);
void Clock_Tick(Clock* clock);