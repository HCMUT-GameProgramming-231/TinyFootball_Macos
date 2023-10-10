#ifndef ShapeCollider_H

#define ShapeCollider_H

#include "./Vector.h"
#include <SDL2/SDL.h>

//Các bouding box 

class Circle 
{
	public:
		Vector center;
		float radius;
		Circle(){}
		Circle(Vector center, int radius);
		SDL_FRect get_rect();
};


class Rectangle 
{
	public:
	Vector center;
	float width;
	float height;
	Rectangle(){}
	Rectangle(Vector center_pos, float width, float height);
	SDL_FRect get_rect();
};

#endif