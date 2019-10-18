#pragma once
#include <glm.hpp>
#include <vector>
#include "Vertex.h"


const float ballWidth = 15;
const float ballHeight = 15;

class Ball
{
public:

	glm::vec2 pos = glm::vec2();
	glm::vec2 forceDir = glm::vec2();
	float currentSpeed = 1;
	Ball() {};
};

const struct
{
	std::vector<Vertex> vertices
	{
		Vertex(glm::vec3(-ballWidth / 2.0f, ballHeight / 2.0f, 0),glm::vec4(0,0,0,1),glm::vec2(0,0),glm::vec3(0,0,1)),
		Vertex(glm::vec3(ballWidth / 2.0f, ballHeight / 2.0f, 0),glm::vec4(0,0,0,1),glm::vec2(0,0),glm::vec3(0,0,1)),
		Vertex(glm::vec3(ballWidth / 2.0f, -ballHeight / 2.0f, 0),glm::vec4(0,0,0,1),glm::vec2(0,0),glm::vec3(0,0,1)),
		Vertex(glm::vec3(-ballWidth / 2.0f, ballHeight / 2.0f, 0),glm::vec4(0,0,0,1),glm::vec2(0,0),glm::vec3(0,0,1)),
		Vertex(glm::vec3(ballWidth / 2.0f, -ballHeight / 2.0f, 0),glm::vec4(0,0,0,1),glm::vec2(0,0),glm::vec3(0,0,1)),
		Vertex(glm::vec3(-ballWidth / 2.0f, -ballHeight / 2.0f, 0),glm::vec4(0,0,0,1),glm::vec2(0,0),glm::vec3(0,0,1)),
	};
} ballDrawData;