#include "../header/Ball.h"

Ball::Ball(Vector center, float radius, const char * file, SDL_Renderer * renderer)
{
	this->bounder = Circle(center, radius);
	SDL_Surface * surface = IMG_Load(file);
	this->texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	this->velocity = Vector(0, 0);
	this->force = Vector(0, 0);
	this->mass = 30;
	this->moving = false;
}

void Ball::Display(SDL_Renderer * renderer)
{
	SDL_FRect rect = this->bounder.get_rect();
	SDL_RenderCopyF(renderer, this->texture, NULL, &rect);
}

Ball::~Ball()
{
	SDL_DestroyTexture(this->texture);
}

