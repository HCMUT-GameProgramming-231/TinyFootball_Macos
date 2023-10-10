#ifndef Sprite_H

#define Sprite_H

#include "./ShapeBounder.h"
#include <SDL2/SDL.h>
#include <string>
#include "./Status.h"

template<typename T>
class Sprite
{
	public:
		T shape;
		SDL_Surface * surface;
		SDL_Texture * texture;
		int width;
		int height;
		std::string name;
		Sprite(){}
		Sprite(const char * img_path, SDL_Renderer * renderer, T shape, std::string name="")
		{
			this->name = name;
			this->surface = IMG_Load(img_path);
			this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
			this->shape = shape;
		}
		~Sprite()
		{
			SDL_FreeSurface(this->surface);
			SDL_DestroyTexture(this->texture);
		}
};

#endif