#pragma once
#include "Player.h"


Player::Player(bool leftPlayer, PLAYERTYPE playerType)
{
	Player::playerId = nextPlayerId;
	nextPlayerId++;
	Player::controlledBy = playerType;


	Player::leftPlayer = leftPlayer;
	if (Player::leftPlayer)
		pos.x = -gameBoard.leftEdge + 50;
	else
		pos.x = gameBoard.rightEdge - 50;

	pos.y = 0;
}


void Player::moveUp(float deltaTime)
{
	float newPosY = pos.y + speed * deltaTime;
	if (newPosY + playerHeight / 2 > gameBoard.topEdge)
		pos.y = gameBoard.topEdge - playerHeight / 2;
	else
		pos.y = newPosY;
}

void Player::moveDown(float deltaTime)
{
	float newPosY = pos.y - speed * deltaTime;
	if (newPosY - playerHeight / 2 < gameBoard.bottomEdge)
		pos.y = gameBoard.bottomEdge + playerHeight / 2;
	else
		pos.y = newPosY;
}

