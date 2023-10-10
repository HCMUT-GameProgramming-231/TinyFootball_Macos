#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "./Status.h"
#include "./Sprite.h"
#include "./ShapeBounder.h"
#include "./CollisionDetector.h"
#include <SDL2/SDL_mixer.h>

#include <string>
//Hiện thực MainMenu

class MainMenu
{
	//method and attribute prototype
	public:
		SDL_Window *  window;
		SDL_Renderer * renderer;
		Sprite<Rectangle> * bg_sprite;
		Sprite<Rectangle> * buttons[3];
		SDL_Cursor * default_cursor;
		SDL_Cursor * hovering_cursor;
		int window_width;
		int window_height;
		MainMenu(){}
		MainMenu(int width, int height, SDL_Window * window, SDL_Renderer * renderer);
		~MainMenu();
		status Display();
};
