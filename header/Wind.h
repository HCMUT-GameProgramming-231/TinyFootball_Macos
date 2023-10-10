#ifndef Wind_H
#define Wind_H

#include "./Vector.h"
#include <SDL2/SDL.h>

class Wind
{
	public:
	Vector direction;
	float min;
	float max;
	SDL_FRect range;
	Wind(){}
	Wind(Vector d, float min, float max, SDL_FRect range);
};

#endif