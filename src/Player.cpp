#include "../header/Player.h"
#include <iostream>
//prototype implementation
Player::Player(Vector center, int radius, const char * file, SDL_Renderer * renderer, int i)
{
	this->index = i;
	this->bounder = Circle(center, radius);
	this->main_player = false;
	this->next = false;
	this->mass = 100;

	SDL_Surface * surface = IMG_Load(file);
	this->texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	surface = IMG_Load("./image/Player/white_circle.png");
	this->m = SDL_CreateTextureFromSurface(renderer, surface);
	this->kick_fx = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	surface = IMG_Load("./image/Player/black_circle.png");
	this->n = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	this->velocity = Vector(0, 0);
	this->force = Vector(0, 0);
	this->acceleration = Vector(0, 0);
	back = false;

}

void Player::Display(SDL_Renderer * renderer, Uint32 time)
{
	SDL_FRect rect = this->bounder.get_rect();
	if(time - this->kick_time < this->kich_delay)
	{
		SDL_FRect r = this->bounder.get_rect();
		r.h += 40;
		r.w += 40;
		r.x -= 20;
		r.y -= 20;
		SDL_RenderCopyF(renderer, this->kick_fx, NULL, &r);
	}

	SDL_RenderCopyF(renderer, this->texture, NULL, &rect);

	

	if(this->main_player)
	{
		rect.x = rect.x + rect.w / 4;
		rect.y = rect.y + rect.h / 4;
		rect.w = rect.w / 2;
		rect.h = rect.h / 2;
		SDL_RenderCopyF(renderer, this->m, NULL, &rect);
	}
	else if(this->next)
	{
		rect.x = rect.x + rect.w / 4;
		rect.y = rect.y + rect.h / 4;
		rect.w = rect.w / 2;
		rect.h = rect.h / 2;
		SDL_RenderCopyF(renderer, this->n, NULL, &rect);
	}
}

void Player::CalSubVelocity(Ball * ball, Player * opposite[3], Player * team[3])
{


}

Player::~Player()
{
	SDL_DestroyTexture(this->texture);
}