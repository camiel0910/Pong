#pragma once
#include <glm.hpp>
#include "GameBoard.h"
#include "Vertex.h"
#include <vector>

static int nextPlayerId = 0;
const float playerHeight = 70;
const float playerWidth = 15;
enum PLAYERTYPE { HUMAN, AI, UNSTOPPABLE, NONE};

class Player
{
public:

	glm::vec2 pos;
	bool leftPlayer;
	int playerId;
	PLAYERTYPE controlledBy = NONE;

	Player(bool leftPlayer, PLAYERTYPE playerType);
	void moveUp(float deltaTime);
	void moveDown(float deltaTime);
};

const struct 
{
	std::vector<Vertex> vertices{
		Vertex(glm::vec3(-playerWidth / 2.0f,playerHeight / 2.0f,0),glm::vec4(1,0,0,1),glm::vec2(0,1),glm::vec3(0,0,1)),
		Vertex(glm::vec3(playerWidth / 2.0f,playerHeight / 2.0f,0),glm::vec4(1,0,0,1),glm::vec2(0,1),glm::vec3(0,0,1)),
		Vertex(glm::vec3(playerWidth / 2.0f, -playerHeight / 2.0f,0),glm::vec4(1,0,0,1),glm::vec2(0,1),glm::vec3(0,0,1)),
		Vertex(glm::vec3(-playerWidth / 2.0f,playerHeight / 2.0f,0),glm::vec4(1,0,0,1),glm::vec2(0,1),glm::vec3(0,0,1)),
		Vertex(glm::vec3(playerWidth / 2.0f,-playerHeight / 2.0f,0),glm::vec4(1,0,0,1),glm::vec2(0,1),glm::vec3(0,0,1)),
		Vertex(glm::vec3(-playerWidth / 2.0f, -playerHeight / 2.0f,0),glm::vec4(1,0,0,1),glm::vec2(0,1),glm::vec3(0,0,1))	
	};

} playerDrawData;