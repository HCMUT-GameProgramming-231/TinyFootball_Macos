#include "../header/Bot.h"
#include <iostream>


Bot::Bot(Field * f)
{
	this->field = f;
}

void Bot::ChooseForm(Player * player[3], Ball * ball, Field * field, int main_index, int player_number)
{
		switch (main_index)
		{
		case 0:
			this->Defend(player[1], ball, field, player_number);
			this->SupportAttack(player[2], ball, player_number, field->width);
			break;
		
		case 1:
			this->Defend(player[0], ball, field, player_number);
			this->SupportAttack(player[2], ball, player_number, field->width);
			break;
		
		case 2:
			this->Defend(player[0], ball, field, player_number);
			this->SupportAttack(player[1], ball, player_number, field->width);
			break;

		default:
			break;
		}
}

void Bot::Defend(Player * player, Ball * ball, Field * field, int player_number)
{
	int width = field->width;
	int height = field->height;	

	if(player_number == 1)
	{
		Vector direction_to_ball = ball->bounder.center - player->bounder.center;
		if(direction_to_ball.x > 0)
		{
			if(ball->bounder.center.x >= width / 2 - 400 && player->bounder.center.x > width / 5)
			{
				Vector destination = Vector (width / 5 , height / 2);
				Vector direction = destination - player->bounder.center;
				if(direction == Vector(0, 0)) return;
				player->velocity = direction.GetUnitVector() * 150;
			}
			else if(ball->bounder.center.x < width / 2 - 400)
			{
				Vector destination = Vector(ball->bounder.center.x - ball->bounder.radius, ball->bounder.center.y);
				this->FindPath(player, destination, 1, ball, 1);
			} 
		}
		else
		{
			Vector destination = Vector(ball->bounder.center.x - ball->bounder.radius, ball->bounder.center.y);
			this->FindPath(player, destination, 1, ball, 1);
		}
	}
	else
	{
		Vector direction_to_ball = ball->bounder.center - player->bounder.center;
		if(direction_to_ball.x < 0)
		{

			if(ball->bounder.center.x <= width / 2 + 400 && player->bounder.center.x < width / 1.25)
			{
				
				Vector destination = Vector (width / 1.25 , height / 2);
				Vector direction = destination - player->bounder.center;
				if(direction == Vector(0, 0)) return;
				player->velocity = direction.GetUnitVector() * 150;
			}
			else if(ball->bounder.center.x > width / 2 + 400)
			{
				Vector destination = Vector(ball->bounder.center.x + ball->bounder.radius, ball->bounder.center.y);
				this->FindPath(player, destination, 2, ball, 1);
			} 
		}
		else
		{
			Vector destination = Vector(ball->bounder.center.x - ball->bounder.radius, ball->bounder.center.y);
			this->FindPath(player, destination, 2, ball, 1);
		}
	}
}

void Bot::SupportAttack(Player * player, Ball * ball, int player_number, float width)
{
	if(this->checkCorner(ball) && (player->bounder.center - ball->bounder.center).GetLength() < 150) return;
	if(player_number == 1)
	{
		if(player->forward)
		{
			if(player->bounder.center.x > width / 2 - 400) player->forward = false;
			else player->velocity = Vector(1, 0) * 200;
		}
		else 
		{
			
			if(player->bounder.center.x < width / 2  - 450)
			{
				player->forward = true;
				player->velocity = Vector(1, 0) * 200;
			}
			else
			{
				Vector destination = Vector(ball->bounder.center.x - ball->bounder.radius, ball->bounder.center.y);
				Vector direction = destination - player->bounder.center;
				if(direction.x > 0) this->FindPath(player, destination, 1, ball, 2);
				else if(player->bounder.center.x > width / 2  - 450) player->velocity = Vector(-1, 0) * 200;
			}
		}
		
	}
	else
	{
		
		if(player->forward)
		{
			if(player->bounder.center.x < width / 2 + 400) player->forward = false;
			else player->velocity = Vector(-1, 0) * 200;
		}
		else 
		{
			Vector direction_to_ball = ball->bounder.center - player->bounder.center;
			if(player->bounder.center.x > width / 2 + 450)
			{
				player->forward = true;
				player->velocity = Vector(-1, 0) * 200;
			}
			else
			{
				Vector destination = Vector(ball->bounder.center.x - ball->bounder.radius, ball->bounder.center.y);
				Vector direction = destination - player->bounder.center;
				if(direction.x < 0) this->FindPath(player, destination, 2, ball, 2 );
				else if(player->bounder.center.x < width / 2 + 450) player->velocity = Vector(1, 0) * 200;
			}
		}
	}
}

bool Bot::checkCorner(Ball * ball)
{
	Vector center = ball->bounder.center;
	SDL_FRect left_1 = field->left_edge_1.get_rect();
	SDL_FRect left_2 = field->left_edge_2.get_rect();
	SDL_FRect up = field->upper_edge.get_rect();
	SDL_FRect down = field->lower_edge.get_rect();
	SDL_FRect right_1 = field->right_edge_1.get_rect();
	SDL_FRect right_2 = field->right_edge_2.get_rect();
	//top left
	Vector top_left_corner = Vector(left_1.x + left_1.w, up.y + up.h);
	if(center.x - top_left_corner.x < 100 && center.y - top_left_corner.y < 100) return true;

	//bottom left 
	Vector bottom_left = Vector(left_2.x + left_2.w, down.y);
	if(center.x - bottom_left.x < 100 && center.y - bottom_left.y > -100) return true;

	//top right
	Vector top_right = Vector(right_1.x, up.y + up.h);
	if(center.x - top_right.x > -100 && center.y - top_right.y < 100) return true;

	//bottom right
	Vector bottom_right = Vector(right_2.x, down.y);
	if(center.x - bottom_right.x > -100 && center.y - bottom_right.y > -100) return true;

	//check luôn edge
	//top edge
	if(center.y - up.y < 100) return true;
	
	//bottom
	if(center.y - down.y > -100) return true;

	//left
	if(center.x - left_1.x < 50) return true;

	if(center.x - right_1.x > -50) return true;
	return false;

}

void Bot::FindPath(Player * player, Vector destination, int player_number, Ball * ball, int mode)
{
	if(this->checkCorner(ball) && (player->bounder.center - ball->bounder.center).GetLength() < 150) return;
	Vector direction = destination - player->bounder.center;
	float velocity ;
	if(mode == 1) velocity = 200;
	else if(mode == 2) velocity = 200;
	float cos_alpha = direction.GetCosAngle(Vector(1, 0));

	if(player_number == 1)
	{	
		if(player->back)
		{
			if(cos_alpha > 0.25) player->back = false;
			player->velocity = Vector(-1, 0) * velocity;
		}
		else
		{
			if(direction.x > 0) 
			{
				if(cos_alpha > 0.2 ) player->velocity = direction.GetUnitVector() * velocity;
				else
				{
					player->velocity = Vector(-1, 0) * velocity;
					player->back = true;
				}
			}
			else
			{
				player->velocity = Vector(-1, 0) * velocity;
				player->back = true;
			}
		}
	}
	else
	{
		if(player->back)
		{
			if(cos_alpha < -0.25) player->back = false;
			player->velocity = Vector(1, 0) * velocity;
		}
		else
		{
			if(direction.x < 0) 
			{
				if(cos_alpha < -0.2 ) player->velocity = direction.GetUnitVector() * velocity;
				else
				{
					player->velocity = Vector(1, 0) * velocity;
					player->back = true;
				}
			}
			else
			{
				player->velocity = Vector(1, 0) * velocity;
				player->back = true;
			}
		}
	}
}


void Bot::FindMove(Player * player[3], Ball * ball)
{
	this->Defend(player[1], ball, this->field, 2);
	this->AttackTop(player[2], ball);
	this->AttackBot(player[0], ball);
}

void Bot::AttackTop(Player * player, Ball * ball)
{
	float width = this->field->width;
	float height = this->field->height;
	if(ball->bounder.center.y > height / 2 || ball->bounder.center.x > width / 2 + 400)
	{
		if(player->bounder.center.x <  2 * width / 3 ) 
		{
			Vector des = Vector(2 * width / 3, height / 4 );
			Vector direction = des - player->bounder.center;
			player->velocity = direction.GetUnitVector() * 200;
		}
	}
	else
	{
		this->SupportAttack(player, ball, 2, width);
	}
}

void Bot::AttackBot(Player * player, Ball * ball)
{
	float width = this->field->width;
	float height = this->field->height;
	if(ball->bounder.center.y < height / 2 || ball->bounder.center.x > width / 2 + 400)
	{
		
		if(player->bounder.center.x <  2 * width / 3 ) 
		{
			Vector des = Vector(2 * width / 3, 3 * height / 4 );
			Vector direction = des - player->bounder.center;
			player->velocity = direction.GetUnitVector() * 200;
		}
	}
	else
	{
		this->SupportAttack(player, ball, 2, width);
	}
}

bool Bot::KickOrNot(Player * player, Ball * ball, int player_number)
{
	CollisionDectector detector;

	Circle kick_range = player->bounder;
	kick_range.radius += 40;
	Vector direction = ball->bounder.center - kick_range.center;
	float cos = direction.GetCosAngle(Vector(1, 0));

	if(player_number == 1)
	{
		if(detector.CircleAndCircle(kick_range, ball->bounder) && cos > 0.5) return true;
	}
	else
	{
		if(detector.CircleAndCircle(kick_range, ball->bounder) && cos < -0.5) return true;
	}
	
	return false;

}