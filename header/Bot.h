#ifndef Bot_H
#define Bot_H

#include "./Player.h"
#include "./Ball.h"
#include "./Vector.h"
#include "./Field.h"
#include "./CollisionDetector.h"

class Bot
{
	public:
	Field * field;
	Bot(){}
	Bot(Field * f);
	bool checkCorner(Ball * ball);
	void ChooseForm(Player * player[3], Ball * ball, Field * field, int main_index, int player_number);
	void Defend(Player * player, Ball * Ball, Field * field, int player_number);
	void SupportAttack(Player * player, Ball* ball, int player_number, float width);
	void FindPath(Player * player, Vector destination, int player_number, Ball * ball, int mode);
	void FindMove(Player * player[3], Ball * ball);
	void AttackTop(Player * player, Ball * ball);
	void AttackBot(Player * player, Ball * ball);
	bool KickOrNot(Player * player, Ball * ball, int player_number);
};

#endif