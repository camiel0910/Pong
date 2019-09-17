#pragma once
#include <glm.hpp>
#include "GameBoard.h"

class Player
{
public:
	float height = 80;
	float widht = 15;
	glm::vec2 pos;
	float speed = 2;
	bool leftPlayer;

	Player(bool leftPlayer);
	void moveUp(float deltaTime);
	void moveDown(float deltaTime);
};