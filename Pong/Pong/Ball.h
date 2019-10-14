#pragma once
#include <glm.hpp>


class Ball
{
public:
	float height = 15;
	float width = 15;
	glm::vec2 pos = glm::vec2();
	glm::vec2 forceDir = glm::vec2();
	float force = 1;
	Ball() {};
};