#pragma once
#include <fstream>
#include <iostream>
#include <glew.h>
#include "glm.hpp"
#include <gtc/type_ptr.hpp>

class Shader
{
public:
	Shader(const char vertexNamep[], const char fragementName[]);
	void use();
	void setUniformMatrix4fv(const char* uniformName, glm::mat4 value);

private:
	char* cVertexData;
	char* cFragmentData;

	int vertexDataLenght;
	int fragmentDataLenght;

	unsigned int vertexShaderId;
	unsigned int fragmentShaderId;
	unsigned int programShaderId;

};