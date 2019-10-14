#include "GameInstance.h"

GameInstance::GameInstance(Player* leftPlayer, Player* rightPlayer, Ball* ball)
{
	GameInstance::leftPlayer = leftPlayer;
	GameInstance::rightPlayer = rightPlayer;
	GameInstance::ball = ball;
	GameInstance::ball = new Ball();
}