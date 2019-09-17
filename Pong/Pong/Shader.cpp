#include "Shader.h"

Shader::Shader(const char vertexName[], const char fragmentName[])
{
	//get vertex data
	std::ifstream vertexFile(vertexName);
	if (vertexFile.is_open())
	{
		std::string vertexData((std::istreambuf_iterator<char>(vertexFile)), std::istreambuf_iterator<char>());
		vertexDataLenght = vertexData.length();

		//parse to c string because .c_str() didn't add a \0 at the end for some reason.
		cVertexData = new char[vertexDataLenght + 1];
		for (int i = 0; i < vertexDataLenght; i++)
		{
			cVertexData[i] = vertexData[i];
		}
		cVertexData[vertexDataLenght + 1] = '\0';
	}
	else
	{
		std::cout << "Can't open: " << vertexName << std::endl;
	}


	//get fragment shader data
	std::ifstream fragmentFile(fragmentName);
	if (fragmentFile.is_open())
	{
		std::string fragmentData((std::istreambuf_iterator<char>(fragmentFile)), std::istreambuf_iterator<char>());
		fragmentDataLenght = fragmentData.length();

		//parse to c string because .c_str() didn't add a \0 at the end for some reason.
		cFragmentData = new char[fragmentDataLenght + 1];
		for (int i = 0; i < fragmentDataLenght; i++)
		{
			cFragmentData[i] = fragmentData[i];
		}
		cFragmentData[fragmentDataLenght + 1] = '\0';
	}
	else
	{
		std::cout << "Can't open: " << fragmentName << std::endl;
	}

	//compile vertex shader
	Shader::vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &cVertexData, &vertexDataLenght);
	glCompileShader(vertexShaderId);

	int vertexSucces;
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &vertexSucces);
	if (!vertexSucces)
	{
		char infoLog[1080];
		glGetShaderInfoLog(vertexShaderId, 1080, NULL, infoLog);
		std::cout << "Error compiling: " << vertexName << '\n' << infoLog << std::endl;
	}
	else
	{
		std::cout << "Succesfully compiled: " << vertexName << std::endl;
	}

	//compile fragment shader
	Shader::fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &cFragmentData, &fragmentDataLenght);
	glCompileShader(fragmentShaderId);

	int fragmentSucces;
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &fragmentSucces);
	if (!fragmentSucces)
	{
		char infoLog[1080];
		glGetShaderInfoLog(fragmentShaderId, 1080, NULL, infoLog);
		std::cout << "Error compiling: " << fragmentName << '\n' << infoLog << std::endl;
	}
	else
	{
		std::cout << "Succesfully compiled: " << fragmentName << std::endl;
	}

	//link shader to program
	Shader::programShaderId = glCreateProgram();
	glAttachShader(programShaderId, vertexShaderId);
	glAttachShader(programShaderId, fragmentShaderId);
	glLinkProgram(programShaderId);

	int programSucces;
	glGetProgramiv(programShaderId, GL_LINK_STATUS, &programSucces);
	if (!programSucces)
	{
		char infoLog[1080];
		glGetShaderInfoLog(programShaderId, 1080, NULL, infoLog);
		std::cout << "Error linking program between: " << vertexName << " and " << fragmentName << '\n' << infoLog << std::endl;
	}
	else
	{
		std::cout << "Succesfully linked: " << vertexName << " and " << fragmentName << std::endl;
	}

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
}

void Shader::use()
{
	glUseProgram(programShaderId);
}

void Shader::setUniformMatrix4fv(const char* uniformName, glm::mat4 value)
{
	use();
	int uniformLocation = glGetUniformLocation(programShaderId, uniformName);
	if (uniformLocation == -1)
	{
		std::cout << "Can't find location for: " << uniformName << std::endl;
		return;
	}
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
}