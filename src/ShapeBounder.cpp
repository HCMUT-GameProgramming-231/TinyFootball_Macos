#include "../header/ShapeBounder.h"

Circle::Circle(Vector center, int radius)
{
	this->center = center;
	this->radius = radius;
}

Rectangle::Rectangle(Vector center_pos, float width, float height)
{
	this->center = center_pos;
	this->width = width;
	this->height = height;
}

SDL_FRect Rectangle::get_rect()
{
	float x = this->center.x - this->width / 2;
	float y = this->center.y - this->height / 2;
	SDL_FRect res = {x, y, this->width, this->height};
	return res;
}


SDL_FRect Circle::get_rect()
{
	float x = this->center.x - this->radius ;
	float y = this->center.y - this->radius ;
	SDL_FRect res = {x, y, this->radius * 2, this->radius * 2};
	return res;
}
