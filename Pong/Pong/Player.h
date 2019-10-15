#pragma once
#include <glm.hpp>
#include "GameBoard.h"
#include "Vertex.h"
#include <vector>

static int nextPlayerId = 0;
const float playerHeight = 80;
const float playerWidth = 15;
enum PLAYERTYPE { HUMAN, AI, UNSTOPPABLE, NONE};

class Player
{
public:

	glm::vec2 pos;
	float speed = 2;
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
		Vertex(glm::vec3(-0.5f,-0.5f,0.0f),glm::vec4(1,0,0,1),glm::vec2(1.0f,0.0f),glm::vec3(0.0f,0.0f,1.0f)),
		Vertex(glm::vec3(0.5f,-0.5f,0.0f),glm::vec4(0,1,0,1),glm::vec2(1.0f,0.0f),glm::vec3(0.0f,0.0f,1.0f)),
		Vertex(glm::vec3(0.0f,0.5f,0.0f),glm::vec4(0,0,1,1),glm::vec2(1.0f,0.0f),glm::vec3(0.0f,0.0f,1.0f))
		//Vertex(glm::vec3(-playerWidth / 2.0f,playerHeight / 2.0f,0),glm::vec4(1,0,0,1),glm::vec2(0,1),glm::vec3(0,0,1)),
		//Vertex(glm::vec3(playerWidth / 2.0f,playerHeight / 2.0f,0),glm::vec4(1,0,0,1),glm::vec2(0,1),glm::vec3(0,0,1)),
		//Vertex(glm::vec3(playerWidth / 2.0f, -playerHeight / 2.0f,0),glm::vec4(1,0,0,1),glm::vec2(0,1),glm::vec3(0,0,1)),
		//Vertex(glm::vec3(-playerWidth / 2.0f,playerHeight / 2.0f,0),glm::vec4(1,0,0,1),glm::vec2(0,1),glm::vec3(0,0,1)),
		//Vertex(glm::vec3(playerWidth / 2.0f,-playerHeight / 2.0f,0),glm::vec4(1,0,0,1),glm::vec2(0,1),glm::vec3(0,0,1)),
		//Vertex(glm::vec3(-playerWidth / 2.0f, -playerHeight / 2.0f,0),glm::vec4(1,0,0,1),glm::vec2(0,1),glm::vec3(0,0,1))	
	};

} playerDrawData;