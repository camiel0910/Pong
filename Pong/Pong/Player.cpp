#pragma once
#include "Player.h"


Player::Player(bool leftPlayer, PLAYERTYPE playerType)
{
	Player::playerId = nextPlayerId;
	nextPlayerId++;
	Player::controlledBy = playerType;


	Player::leftPlayer = leftPlayer;
	if (Player::leftPlayer)
		pos.x = 50;
	else
		pos.x = gameBoard.width - 50;

	pos.y = gameBoard.height/2;
}


void Player::moveUp(float deltaTime)
{
	float newPosY = pos.y + gameBoard.playerSpeed * deltaTime;
	if (newPosY + playerHeight / 2 > gameBoard.height)
		pos.y = gameBoard.height - playerHeight / 2;
	else
		pos.y = newPosY;
}

void Player::moveDown(float deltaTime)
{
	float newPosY = pos.y - gameBoard.playerSpeed * deltaTime;
	if (newPosY - playerHeight / 2 < 0)
		pos.y = playerHeight / 2;
	else
		pos.y = newPosY;
}

