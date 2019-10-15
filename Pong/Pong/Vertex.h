#pragma once
#include <glm.hpp>

class Vertex
{
public:
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 texCoord;
	glm::vec3 normal;
	Vertex(glm::vec3 position, glm::vec4 color, glm::vec2 texCoord, glm::vec3 normal) : position(position), color(color), texCoord(texCoord), normal(normal) {};
};

