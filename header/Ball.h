#ifndef Ball_H

#define Ball_H

#include "./ShapeBounder.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//Hiện thực trái bóng
class Ball
{
	public:
	Circle bounder;
	SDL_Texture * texture;
	Ball(){};
	Ball(Vector center, float radius, const char * file, SDL_Renderer * renderer);
	Vector velocity;
	Vector force;
	bool moving;
	float mass;
	void Display(SDL_Renderer * renderer);
	~Ball();
};

#endif