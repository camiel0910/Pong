#pragma once
#include "Player.h"
#include "Ball.h"
#include "GameBoard.h"
#include <cstdlib>
#include <ctime>
#include <iostream>


class GameInstance
{
	Player* leftPlayer;
	Player* rightPlayer;
	Ball* ball;
	float scoreLeft = 0;
	float scoreRight = 0;
	bool leftScoredLast = true;
	bool playing = false;
	bool autoRestart = false;
	   
public:
	GameInstance(Player* leftPlayer, Player* rightPlayer, Ball* ball);
	void StartRound();
	void gameStep(float deltaTime);



};
