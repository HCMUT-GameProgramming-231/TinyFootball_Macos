#ifndef Field_H

#define Field_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "./Sprite.h"
#include "./ShapeBounder.h"
#include "./Wind.h"

class Field
{
	public:
		int width;
		int height;
		Sprite<Rectangle> * field;
		SDL_Texture * grass;
		Rectangle upper_edge;
		Rectangle lower_edge;
		SDL_Texture * upper_lower_edge_texture;
		SDL_Texture * left_right_edge_texture;
		Rectangle right_edge_1;
		Rectangle right_edge_2;
		Rectangle left_edge_1;
		Rectangle left_edge_2;
		Wind upper_wind;
		Wind lower_wind;

		Field(){}
		Field(int width, int height, SDL_Renderer * renderer);
		void Display(SDL_Renderer * renderer);
		~Field();
};

#endif