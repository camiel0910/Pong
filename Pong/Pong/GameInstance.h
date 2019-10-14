#pragma once
#include "Player.h"
#include "Ball.h"
#include "GameBoard.h"


class GameInstance
{
	Player* leftPlayer;
	Player* rightPlayer;
	Ball* ball;


public:
	GameInstance(Player* leftPlayer, Player* rightPlayer, Ball* ball);




};
