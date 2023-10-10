#include "../header/Wind.h"

Wind::Wind(Vector d, float min, float max, SDL_FRect range)
{
	this->direction = d;
	this->min = min;
	this->max = max;
	this->range = range;
}