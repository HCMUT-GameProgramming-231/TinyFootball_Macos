#ifndef Player_H

#define Player_H

#include "./ShapeBounder.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "./Vector.h"
#include "./Ball.h"

//Cầu thủ
class Player
{
	//methods + attribute
	public:
	SDL_Texture * texture;
	SDL_Texture * kick_fx;
	SDL_Texture * m ;
	SDL_Texture * n ;
	Circle bounder;
	Vector force; //hợp lực tác dụng lên vật
	Vector velocity; //vector vận tốc
	Vector sub_velocity;
	Vector acceleration;
	bool main_player;
	Uint32 kick_time;
	bool back;
	bool forward;
	bool next;
	float mass;
	bool up, down, right, left;
 	static const Uint32 kich_delay = 500; //thời gian delay giữa 2 lần đá
	Player(Vector center, int radius, const char * file, SDL_Renderer * renderer, int i);
	void Display(SDL_Renderer * renderer, Uint32 time);
	int index;
	void CalSubVelocity(Ball * ball, Player * opposite[3], Player * team[3]);
	~Player();
};

#endif