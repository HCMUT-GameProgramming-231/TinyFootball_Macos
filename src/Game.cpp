#include "../header/Game.h"
#include <iostream>

//prototype implementation

Game::Game(int width, int height, SDL_Window * window, SDL_Renderer * renderer, status game_mode)
{
	this->fps = 60;
	this->frame = 0;
	this->change_delay = 500;

	this->player1_score = 0;
	this->player2_score = 0;

	this->push_force = 50000;
	this->force_coefficient = 30; //hệ số ma sát

	this->width = width;
	this->height = height;
	
	this->window = window;
	this->renderer = renderer;

	
	this->detector = CollisionDectector();

	this->font = TTF_OpenFont("./Font/font.ttf", 12);

	//init field
	this->field = new Field(width, height, renderer);
	this->bot = Bot(this->field);
	//set game mode
	this->game_mode = game_mode;

	//init ball
	this->ball = new Ball(Vector(width / 2 , height / 2 ), 25, "./image/Ball/puck.png", this->renderer);

	//init players
	int pos_x_1 = width / 3;
	int pos_x_2 = 2 * width / 3;
	int pos_y = height / 4;
	for(int i = 0; i < 3; i++)
	{
		this->player_1[i] = new Player(Vector(pos_x_1, pos_y), 30, "./image/Player/player_1.png", this->renderer, i);
		this->player_2[i] = new Player(Vector(pos_x_2, pos_y), 30, "./image/Player/player_2.png", this->renderer, i);
		pos_y += height / 4;
	}


	//current player
	this->player_1_index = 1;
	this->player_1[1]->main_player = true;
	this->player_1[2]->next = true;
	
	this->player_2_index = 1;
	this->player_2[1]->main_player = true;
	this->player_2[2]->next = true;

	this->last_change_player1 = this->last_change_player2 = 0;
	this->timeout = false;
}

status Game::Display()
{	
	this->reset = false;
	this->timeout = false;
	SDL_Color font_color = {255, 255, 255};
	SDL_ShowCursor(SDL_DISABLE);
	SDL_Event event;
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	Uint32 time = 0;
	Uint32 cal_fps_time = 0; //just for checking fps
	std::string score = "Score: " + std::to_string(this->player1_score) + "-" + std::to_string(this->player2_score);
	std::string countdown = "Time: " + std::to_string(30);
	int timeleft = 90;
	Uint32 t = 0;
	this->Reset();
	Uint32 timeout_time = 0;
	player1_score = player2_score = 0;
	float delta = (float)1/ this->fps; //define value 60 in constructor
	Player * current_player_1;

	Player * player_list1[3] = {this->player_1[0], this->player_1[1], this->player_1[2]};
	Player * player_list2[3] = {this->player_2[0], this->player_2[1], this->player_2[2]};

	bool kick_flag = false;
	while(this->game_mode == pvp || this->game_mode == pvc)
	{
		time = SDL_GetTicks();

		if(time - t >= 1000 && !timeout)
		{
			timeleft--;
			if(timeleft == 0) 
			{
				timeout = true;
				timeout_time = time;
				SDL_SetCursor(NULL);
				for(int i = 0; i < 3; i++)
				{
					player_1[i]->velocity = player_2[i]->velocity = Vector(0, 0);
				}
				ball->velocity = Vector(0, 0);
				SDL_ShowCursor(SDL_ENABLE);
			}
			t = time;
		}

		if(!timeout)
		{
			//process input------------------------------------------------------------------------------------
			//movement of player 1
			current_player_1 = this->player_1[this->player_1_index];

			if(keystate[SDL_SCANCODE_W])
			{

				current_player_1->velocity = current_player_1->velocity + Vector(0, -1) * 300;
			}

			if(keystate[SDL_SCANCODE_S]) 
			{


				current_player_1->velocity = current_player_1->velocity + Vector(0, 1) * 300;

			}

			if(keystate[SDL_SCANCODE_A]) 
			{


				current_player_1->velocity = current_player_1->velocity + Vector(-1, 0) * 300;

			}

			if(keystate[SDL_SCANCODE_D]) 
			{

					current_player_1->velocity = current_player_1->velocity + Vector(1, 0) * 300;

			}

			//change current controlled player of player 1
			if(keystate[SDL_SCANCODE_1]) 
			{
				this->SetMain(1, 1, time);
			}
		
			else if(keystate[SDL_SCANCODE_2])
			{
				this->SetMain(2, 1, time);
			}

			else if(keystate[SDL_SCANCODE_3])
			{
				this->SetMain(0, 1, time);
			}


			

			//handle kick

			//movement of player 2 
			if(game_mode == pvp)
			{
				Player * current_player_2 = this->player_2[player_2_index];
				

				if(keystate[SDL_SCANCODE_UP]) current_player_2->velocity = current_player_2->velocity + Vector(0, -1) * 300;
				if(keystate[SDL_SCANCODE_DOWN]) current_player_2->velocity = current_player_2->velocity + Vector(0, 1) * 300;
				if(keystate[SDL_SCANCODE_LEFT]) current_player_2->velocity = current_player_2->velocity + Vector(-1, 0) * 300;
				if(keystate[SDL_SCANCODE_RIGHT]) current_player_2->velocity = current_player_2->velocity + Vector(1, 0) * 300;

				//change current controlled player of player 2
				if(keystate[SDL_SCANCODE_LEFTBRACKET]) 
				{
					this->SetMain(1, 2, time);
				}


				else if(keystate[SDL_SCANCODE_RIGHTBRACKET])
				{
					this->SetMain(2, 2, time);
				}
			

				else if(keystate[SDL_SCANCODE_P])
				{
					this->SetMain(0, 2, time);
				}					

			//handle kick
			}

			if(keystate[SDL_SCANCODE_ESCAPE]) this->game_mode = end;


			while(SDL_PollEvent(&event))
			{
				switch (event.type)
				{
					case SDL_QUIT:
						this->game_mode = end;
						break;
					
					case SDL_KEYDOWN:
						if(keystate[SDL_SCANCODE_G]) 
						{
							int main_player;
							if(this->player_1_index == 2) main_player = 0;
							else main_player = 1 + this->player_1_index;
							this->SetMain(main_player, 1, time);
						}
						
						if(keystate[SDL_SCANCODE_F])
						{
							kick_flag = true;
							this->Kick(this->player_1[player_1_index], time);
						}
						

						if(this->game_mode == pvp)
						{
							if(keystate[SDL_SCANCODE_COMMA])
							{
								int main_player;
								if(this->player_2_index == 2) main_player = 0;
								else main_player = 1 + this->player_2_index;
								this->SetMain(main_player, 2, time);
							}

							if(keystate[SDL_SCANCODE_PERIOD])
							{
								kick_flag = true;
								this->Kick(this->player_2[player_2_index], time);
							}
						}

						break;
						
					default:
						break;
				}
			}

			//Update state------------------------------------------------------------------------------------
			//player
			

			this->bot.ChooseForm(player_list1, this->ball, this->field, player_1_index, 1);

			

			if(this->game_mode == pvp)
			{
				this->bot.ChooseForm(player_list2, this->ball, this->field, player_2_index, 2);
			}
			else
			{
				bot.FindMove(player_list2, ball);
			}
			

			this->CheckWind();

			//ball vs player
			if(!kick_flag) this->CheckCollision_Ball_Players();
			this->UpdateBallSpeed();

			//ball vs edge
			this->CheckCollision_Ball_Edge();

			//player vs player
			this->CheckCollision_Players_Players();

			

			//player pos
			this->UpdatePlayersPos(time);
			this->UpdateBallPos();

			this->CheckGoal();
			kick_flag = false;
		}
		//Display----------------------------------------------------------------------------------------

		SDL_RenderClear(renderer);
		//display component
		this->field->Display(this->renderer);
		this->ball->Display(this->renderer);
		for(int i = 0; i < 3; i++)
		{
			this->player_1[i]->Display(this->renderer, time);
			this->player_2[i]->Display(this->renderer, time);
		}

		score = "Score: " + std::to_string(this->player1_score) + "-" + std::to_string(this->player2_score);
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(this->font, score.c_str(), font_color); 
		SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
		SDL_FRect font_rect = {(float)this->width /2 + 100, 0, 200, 100};
		SDL_RenderCopyF(this->renderer, Message, NULL, &font_rect);
		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(Message);


		countdown = "Time: "+std::to_string(timeleft);
		surfaceMessage = TTF_RenderText_Solid(this->font, countdown.c_str(), font_color);
		Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
		font_rect = {(float)this->width /2 - 300, 0, 200, 100};
		SDL_RenderCopyF(this->renderer, Message, NULL, &font_rect);
		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(Message);

		if(timeout)
		{
			this->DisplayWinner();
			while(SDL_PollEvent(&event))
			{
				switch (event.type)
				{
					case SDL_QUIT:
						this->game_mode = end;
						break;

					case SDL_MOUSEBUTTONDOWN:
						game_mode = menu;
						break;
					
					default:
						break;
				}
			}
		} 
		if(timeout && time-timeout_time >= 5000) game_mode = menu;


		SDL_RenderPresent(this->renderer);
		
		Uint32 this_frame_time = SDL_GetTicks() - time;

		if(this_frame_time < 1000 / this->fps)
		{

			SDL_Delay((Uint32)1000/this->fps -  this_frame_time);
		}


	}

	return game_mode;
}

void Game::DisplayWinner()
{
	std::string result;
	if(game_mode == pvp)
	{
		if(this->player1_score == this->player2_score) result = "Draw!";
		else if (this->player1_score > this->player2_score) result = "Player 1 won!";
		else result = "Player 2 won";
	}
	else
	{
		if(this->player1_score == this->player2_score) result = "Draw!";
		else if (this->player1_score > this->player2_score) result = "You won!";
		else result = "Computer won";
	}
	SDL_Rect font_rect = {this->width / 2 - 100, this->height / 2 - 50 , 250, 100};


	SDL_Surface * surfaceMessage = TTF_RenderText_Solid(this->font, result.c_str(), {0, 0, 0});
	
	SDL_Texture * Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	
	SDL_RenderCopy(this->renderer, Message, NULL, &font_rect);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}

void Game::UpdatePlayersPos(Uint32 time)
{
	float delta = 1.0/fps;
	for(int i = 0; i < 3; i++)
	{

		player_1[i]->bounder.center = player_1[i]->bounder.center + player_1[i]->velocity * delta; 
 
		player_2[i]->bounder.center = player_2[i]->bounder.center + player_2[i]->velocity * delta; 

		player_1[i]->velocity = player_2[i]->velocity = Vector(0, 0);
		if(i != player_1_index && bot.KickOrNot(player_1[i], this->ball, 1)) this->Kick(player_1[i], time);	
		if(game_mode == pvp)
		{
			if(i != player_2_index && bot.KickOrNot(player_2[i], this->ball, 2)) this->Kick(player_2[i], time);	
		}
		
		else
		{
			if(bot.KickOrNot(player_2[i], this->ball, 2)) this->Kick(player_2[i], time);
		}
	}
}

bool Game::SetMain(int main_player, int player, Uint32 time)
{

	if (player == 1)
	{
		if(time - this->last_change_player1 < this->change_delay) return false;
		this->last_change_player1 = time;
		this->player_1[player_1_index]->main_player = false;
		this->player_1_index = main_player;
		this->player_1[player_1_index]->next = false;
		this->player_1[player_1_index]->main_player = true;
		if(main_player == 2) this->player_1[0]->next = true;
		else this->player_1[main_player + 1]->next = true;
	}
	else
	{
		if(game_mode == pvp)
		{
			if(time - this->last_change_player2 < this->change_delay) return false;
			this->last_change_player2 = time;
			this->player_2[player_2_index]->main_player = false;
			this->player_2_index = main_player;
			this->player_2[player_2_index]->next = false;
			this->player_2[player_2_index]->main_player = true;
			if(main_player == 2) this->player_2[0]->next = true;
			else this->player_2[main_player + 1]->next = true;
		}
		else
		{
			if(time - this->last_change_player2 < this->change_delay) return false;
			this->last_change_player2 = time;
			this->player_2[player_2_index]->main_player = false;
			this->player_2_index = main_player;
			this->player_2[player_2_index]->main_player = true;
		}
	}
	return true;
}


void Game::CheckCollision_Ball_Players()
{
	Circle ball_bounder = this->ball->bounder;
	//ball_bounder.radius -= 5;
	float delta = 1.0 / this->fps;
	Player * player1;
	Player * player2;
	for(int i = 0; i< 3; i++)
	{
		player1 = this->player_1[i];
		if(this->detector.CircleAndCircle(ball_bounder, player1->bounder))
		{
			this->CheckCollisionStatus(player1, this->ball);
		}


		player2 = this->player_2[i];
		if(this->detector.CircleAndCircle(ball_bounder, player2->bounder))
		{
			this->CheckCollisionStatus(player2, this->ball);
		}
	}
}


void Game::UpdateBallSpeed()
{
	if(this->ball->velocity == Vector(0, 0)) return;
	float delta = 1.0 / this->fps;
	float force = 10 * this->ball->mass * this->force_coefficient;
	Vector acceleration = this->ball->velocity.GetUnitVector() * force * -1 / this->ball->mass;
	Vector new_velocity = this->ball->velocity - ball->velocity / 100;

	if(new_velocity.GetLength() < 1) new_velocity = Vector(0, 0);
	this->ball->velocity = new_velocity;
}

void Game::UpdateBallPos()
{
	float delta = 1.0 / this->fps;
	this->ball->bounder.center = this->ball->bounder.center + this->ball->velocity * delta;
}

Vector Game::Reflex(Vector v, Vector n)
{
	Vector v1 = v * -1;
	Vector new_n = n * v1.DotProduct(n);
	Vector s = v + new_n;
	Vector new_v = new_n + s;
	return new_v;
}

void Game::Kick(Player * player, Uint32 time)
{
	if(time - player->kick_time < player->kich_delay) return;
	player->kick_time = time;
	player->velocity = player->velocity / 2;
	Circle kick_range = player->bounder;
	kick_range.radius += 40;
	if(!this->detector.CircleAndCircle(kick_range, this->ball->bounder)) return;
	Vector direction = this->ball->bounder.center - player->bounder.center;
	this->ball->velocity = this->ball->velocity + direction.GetUnitVector() * 800;
}

void Game::CheckCollision_Ball_Edge()
{
	Rectangle edge;
	Circle ball_bounder = this->ball->bounder;
	Vector ball_velocity = this->ball->velocity;
	Vector n = Vector(0, 0);

	//check collide with top edge
	edge = this->field->upper_edge;
	if(this->detector.CircleAndRect(edge, ball_bounder)) 
	{
		n = Vector(0, 1);
		ball->bounder.center.y += 1;
	}

	//bottom edge
	edge = this->field->lower_edge;
	if(this->detector.CircleAndRect(edge, ball_bounder)) 
	{
		n = Vector(0, -1);
		ball->bounder.center.y -= 1;
	}


	//right edge 1
	edge = this->field->right_edge_1;
	if(this->detector.CircleAndRect(edge, ball_bounder)) 
	{
		if(ball->bounder.center.x > edge.get_rect().x) n = Vector(0, 1);
		else n = Vector(1, 0);
		ball->bounder.center.x -= 1;
	}

	//right edge 2
	edge = this->field->right_edge_2;
	if(this->detector.CircleAndRect(edge, ball_bounder)) 
	{
		if(ball->bounder.center.x > edge.get_rect().x) n = Vector(0, -1);
		else n = Vector(1, 0);
		ball->bounder.center.x -= 1;
	}

	//left edge 1
	edge = this->field->left_edge_1;
	if(this->detector.CircleAndRect(edge, ball_bounder)) 
	{
		if(ball->bounder.center.x < edge.get_rect().x + edge.width) n = Vector(0, 1);
		else n = Vector(-1, 0);
		ball->bounder.center.x += 1;
	}

	//left edge 2
	edge = this->field->left_edge_2;
	if(this->detector.CircleAndRect(edge, ball_bounder)) 
	{
		if(ball->bounder.center.x < edge.get_rect().x + edge.width) n = Vector(0, -1);
		else n = Vector(-1, 0);
		ball->bounder.center.x += 1;
	}

	if(n == Vector(0, 0)) return ;
	ball->velocity = this->Reflex(ball->velocity, n);

}

void Game::Score(int side)
{
	if(side == 1)
	{
		this->player1_score += 1;
	}
	else
	{
		this->player2_score += 1;
	}
	this->reset = true;
	this->Reset();
}

void Game:: CheckGoal()
{
	float right_bound = this->field->right_edge_1.get_rect().x + ball->bounder.radius;
	if(this->ball->bounder.center.x > right_bound) this->Score(1);
	
	float left_bound = this->field->left_edge_1.get_rect().x + this->field->left_edge_1.get_rect().w - ball->bounder.radius;
	if(this->ball->bounder.center.x < left_bound) this->Score(2); 
}

void Game::Reset()
{
	if(reset) SDL_Delay(1000);
	this->ball->bounder.center = Vector(this->width / 2, this->height/2);
	this->ball->velocity = Vector(0, 0);
	int pos_x_1 = width / 3;
	int pos_x_2 = 2 * width / 3;
	int pos_y = height / 4;
	for(int i = 0; i < 3; i++)
	{
		this->player_1[i]->bounder.center = Vector(pos_x_1, pos_y);
		this->player_2[i]->bounder.center = Vector(pos_x_2, pos_y);
		this->player_1[i]->velocity = this->player_2[i]->velocity = Vector(0, 0);
		this->player_1[i]->force = this->player_2[i]->force = Vector(0 ,0);
		this->player_1[i]->main_player = this->player_2[i]->main_player = false;
		this->player_1[i]->next = this->player_2[i]->next = false;
		player_1[i]->kick_time = player_2[i]->kick_time = 0;
		player_1[i]->back = player_2[i]->back = false;
		player_1[i]->forward = player_2[i]->forward = false;
		pos_y += height / 4;
	}

	pos_y = player_2[0]->bounder.center.y;
	player_2[0]->bounder.center.y = player_2[2]->bounder.center.y;
	player_2[2]->bounder.center.y = pos_y;

	//current player
	this->player_1_index = 1;
	this->player_1[1]->main_player = true;
	this->player_1[2]->next = true;
	
	this->player_2_index = 1;
	this->player_2[1]->main_player = true;
	if(this->game_mode == pvp) this->player_2[2]->next = true;

	this->last_change_player1 = this->last_change_player2 = 0;
}

void Game::CheckCollisionStatus(Player * player, Ball * ball)
{
	float real_distance = (ball->bounder.center - player->bounder.center ).GetLength();
	Vector direction = (ball->bounder.center - player->bounder.center).GetUnitVector();

	//ball movement
	if(ball->velocity == Vector(0, 0))
	{
		ball->velocity = direction * 300;
	}
	else
	{
		if (!(player->velocity == Vector(0 , 0)))
		{
			Vector v_ball = ball->velocity;
			Vector v_player = player->velocity;
			float cos = v_ball.GetCosAngle(v_player);
			
			if(cos < 0)
			{	
				this->ball->velocity = this->Reflex(this->ball->velocity, direction);
				player->bounder.center = player->bounder.center + direction * -1;
			}
			else
			{
				if(ball->velocity.GetLength() < player->velocity.GetLength())
				{
					ball->velocity = direction * 300;
				}
				else 
				{

					this->ball->velocity = this->ball->velocity.GetUnitVector() * 70;

				}
			}
		}
		else
		{
			ball->velocity = this->Reflex(ball->velocity, direction);

		}
		

		
	}

	if(real_distance < ball->bounder.radius + player->bounder.radius)
	{
		player->bounder.center = player->bounder.center + (ball->bounder.center - player->bounder.center).GetUnitVector() * -1 ;
		player->velocity = Vector(0, 0);
	}
}

void Game::CheckCollision_Players_Players()
{
	for(int i = 0 ; i < 3; i++)
	{
		Player * player1 = this->player_1[i];
		for(int x = 0; x < 3; x++)
		{
			Player * player2 = this->player_2[x];
			
			float real_distance = (player1->bounder.center - player2->bounder.center).GetLength();
			if(real_distance < player1->bounder.radius + player2->bounder.radius)
			{
				Vector direction =  (player1->bounder.center - player2->bounder.center).GetUnitVector();
				player1->bounder.center = player1->bounder.center + direction ;
				player2->bounder.center = player2->bounder.center + direction * -1;
			}

			if(this->detector.CircleAndCircle(player1->bounder, player2->bounder))
			{			
				if(player2->velocity == Vector(0, 0) && !(player1->velocity == Vector(0, 0)))
				{
					Vector direction = player2->bounder.center - player1->bounder.center;
					Vector direction_unit = direction.GetUnitVector();
					Vector v1_old_direction = player1->velocity.GetUnitVector();
					float cos_alpha = v1_old_direction.GetCosAngle(direction_unit);
					float sin_alpha = sqrt(1 - pow(cos_alpha, 2));
					float v1_length = player1->velocity.GetLength();

					if(cos_alpha <0.8 && cos_alpha > -0.8) //va chạm không xuyên tâm
					{
						
						float v1_new_length = (v1_length * sin_alpha) / (sin_alpha * cos_alpha * 2);
						
						float v2_new_length = v1_new_length;

						Vector new_v1_direction = v1_old_direction + (direction_unit * -1 + v1_old_direction);
						player1->velocity = new_v1_direction * v1_new_length;

						Vector new_v2_direction = direction_unit;
						player2->velocity =  new_v2_direction * v2_new_length;
					}
					else //va chạm xuyên tâm
					{
						player2->velocity = player1->velocity;
						player1->velocity = Vector(0, 0);
					}	
				}
				else if(player1->velocity == Vector(0, 0) && !(player2->velocity == Vector(0, 0)))
				{
					Vector direction = player1->bounder.center - player2->bounder.center;
					Vector direction_unit = direction.GetUnitVector();
					Vector v2_old_direction = player2->velocity.GetUnitVector();
					float cos_alpha = v2_old_direction.GetCosAngle(direction_unit);
					float sin_alpha = sqrt(1 - pow(cos_alpha, 2));
					float v2_length = player2->velocity.GetLength();


					if(cos_alpha < 0.8 && cos_alpha > -0.8) //va chạm không xuyên tâm
					{
						
						float v2_new_length = (v2_length * sin_alpha) / (sin_alpha * cos_alpha * 2);
						
						float v1_new_length = v2_new_length;

						Vector new_v2_direction = v2_old_direction + (direction_unit * -1 + v2_old_direction);
						player2->velocity = new_v2_direction * v2_new_length;

						Vector new_v1_direction = direction_unit;
						player1->velocity =  new_v1_direction * v1_new_length;
					}
					else //va chạm xuyên tâm
					{
						player1->velocity = player2->velocity;
						player2->velocity = Vector(0, 0);
					}	
				}
				else if( !(player1->velocity == Vector(0, 0)) && !(player2->velocity == Vector(0, 0)) )
				{
					float cos = player1->velocity.GetCosAngle(player2->velocity);

					if(cos < 0)
					{
						Vector direction = player1->bounder.center - player2->bounder.center;
						player1->velocity = this->Reflex(player1->velocity, direction.GetUnitVector());
						player2->velocity = this->Reflex(player2->velocity, (direction * -1).GetUnitVector());
					}
					else if(cos < 0.8)
					{
						
						if(player2->velocity.GetLength() > player1->velocity.GetLength())
						{
							Vector direction = player1->bounder.center - player2->bounder.center;
							Vector v1_direction_unit = player1->velocity.GetUnitVector();
							Vector scale_direction = v1_direction_unit * (direction.DotProduct(v1_direction_unit));
							Vector s = (direction * -1) + scale_direction;
							Vector v1_n = (scale_direction + s).GetUnitVector();
							Vector v2_n = direction.GetUnitVector();
							player1->velocity = this->Reflex(player1->velocity, v1_n);
							player2->velocity = this->Reflex(player2->velocity, v2_n);
						}
						else
						{
							Vector direction = player1->bounder.center - player2->bounder.center;
							Vector v1_direction_unit = player1->velocity.GetUnitVector();
							Vector scale_direction = v1_direction_unit * (direction.DotProduct(v1_direction_unit));
							Vector s = (direction * -1) + scale_direction;
							Vector v2_n = (scale_direction + s).GetUnitVector();
							Vector v1_n = direction.GetUnitVector();
							player1->velocity = this->Reflex(player1->velocity, v1_n);
							player2->velocity = this->Reflex(player2->velocity, v2_n);
						}			
					}
					else
					{
						Vector direction = player1->bounder.center - player2->bounder.center;
						if(player1->velocity.GetLength() > player2->velocity.GetLength())
						{
							player2->velocity = player1->velocity;
							player2->velocity = Vector(0, 0);
						}
						else
						{
							player1->velocity = Vector(0, 0);
							player1->velocity = player2->velocity;
						}
					}

				}
			}		
		}
	}
}

void Game::CheckWind()
{
	SDL_FRect frect;
	Rectangle rect;	
	Vector center;
	Wind wind;
	//upper wind
	wind = this->field->upper_wind;
	frect = wind.range;
	if(ball->bounder.center.y < frect.y + frect.h)
	{
		float distance_y = ball->bounder.center.y - frect.y;
		Vector wind_velocity = wind.direction * (wind.max - distance_y * (wind.max / frect.h));
		ball->velocity = ball->velocity + wind_velocity; 
	}
	//lower wind
	wind = this->field->lower_wind;
	frect = wind.range;
	if(ball->bounder.center.y > frect.y)
	{
		float distance_y = frect.y + frect.h - ball->bounder.center.y;
		Vector wind_velocity = wind.direction * (wind.max - distance_y * (wind.max / frect.h));
		ball->velocity = ball->velocity + wind_velocity; 
	}


}

Game::~Game()
{
	delete this->ball;
	delete this->field;
}