#include "./Player.h"
#include "./Ball.h"
#include "./Field.h"
#include "./Status.h"
#include "./CollisionDetector.h"
#include "./Bot.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <string>

//Hiện thực game
class Game
{
	//Methods and attribute prototype
	public:
		int fps ;
		int frame;
		int player1_score;
		int player2_score;
		bool reset;
		SDL_Window * window;
		SDL_Renderer * renderer;
		CollisionDectector detector;
		Field * field;
		status game_mode;
		Player * player_1[3];
		Player * player_2[3];
		int player_1_index;
		int player_2_index;
		Bot bot;
		Ball * ball;
		float force_coefficient; //hệ số ma sát
		float push_force; // độ lớn lực đấy
		int width;
		int height;
		TTF_Font * font;
		Uint32 change_delay;
		Uint32 last_change_player1;
		Uint32 last_change_player2;
		Game(int width, int height, SDL_Window * window, SDL_Renderer * renderer, status game_mode);
		bool SetMain(int main_player, int player, Uint32 time);
		status Display();
		void Kick(Player * player, Uint32 time);
		void DisplayWinner();
		bool timeout ;
		void CheckCollision_Ball_Edge();
		void CheckCollision_Ball_Players();
		void CheckCollision_Players_Edge();
		void CheckCollision_Players_Players();

		void UpdatePlayersForce();
		void UpdatePlayersSpeed();
		void UpdatePlayersPos(Uint32 time);
		
		void UpdateBallSpeed();
		void UpdateBallPos();

		void CheckWind();

		Vector Reflex(Vector v, Vector n); //phản xạ giữa vector tới v và vector pháp tuyến n

		void Score(int side);
		void CheckGoal();
		void CheckCollisionStatus(Player * player, Ball * ball);
		void Reset();
		~Game();
};

