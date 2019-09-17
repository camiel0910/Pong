#pragma once
#include "Player.h"


Player::Player(bool leftPlayer)
{
	Player::leftPlayer = leftPlayer;
	if (Player::leftPlayer)
		pos.x = -gameBoardLeftEdge + 50;
	else
		pos.x = gameBoardRightEdge - 50;

	pos.y = 0;
}


void Player::moveUp(float deltaTime)
{
	float newPosY = pos.y + speed * deltaTime;
	if (newPosY + Player::height / 2 > gameBoardTopEdge)
		pos.y = gameBoardTopEdge - Player::height / 2;
	else
		pos.y = newPosY;
}

void Player::moveDown(float deltaTime)
{
	float newPosY = pos.y - speed * deltaTime;
	if (newPosY - Player::height / 2 < gameBoardBottomEdge)
		pos.y = gameBoardBottomEdge + Player::height / 2;
	else
		pos.y = newPosY;
}

