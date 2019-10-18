#include <glew.h>	
#include <freeglut.h>
#include <iostream>
#include <glm.hpp>
#include "Shader.h"
#include "Player.h"
#include "GameInstance.h"
#include <vector>


//opengl
float screenWidth = 800;
float screenHeight = 600;
const float gameEdgeRight = 600;
const float gameEdgeLeft = 0.0f;
const float gameEdgeTop = 0.0;
const float gameEdgeBottom = 600.0f;
const float gameEdgeFar = 1.0f;
const float gameEdgeNear = -1.0f;

float currentFrameTime = 0;
float gameTime = 0;

unsigned char pressedKeys[256];
unsigned char initialPressedKeys[256];
bool arrowUp = false;
bool initialArrowUp = false;
bool arrowDown = false;
bool initialArrowDown = false;


//shader
Shader* basicShader;
unsigned int playerVAO;
unsigned int playerVBO;
unsigned int ballVAO;
unsigned int ballVBO;


//pong
std::vector<Player> players;
std::vector<Ball> balls;
std::vector<GameInstance> games;


void setupGames()
{
	players.push_back(Player(true, PLAYERTYPE::HUMAN));
	players.push_back(Player(false, PLAYERTYPE::HUMAN));
	balls.push_back(Ball());
	games.push_back(GameInstance(&players[players.size() - 2], &players[players.size() - 1], &balls[balls.size()-1]));
}

void initShader()
{
	basicShader = new Shader("BasicShader.vs", "BasicShader.fs");
	basicShader->use();

	//init player vao
	glGenVertexArrays(1, &playerVAO);
	glBindVertexArray(playerVAO);


	glGenBuffers(1, &playerVBO);	
	glBindBuffer(GL_ARRAY_BUFFER, playerVBO);
	glBufferData(GL_ARRAY_BUFFER, playerDrawData.vertices.size() * sizeof(Vertex), &playerDrawData.vertices[0], GL_STATIC_DRAW);

	//location 0: position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(0);

	////location 1: color
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	//init ball vao
	glGenVertexArrays(1, &ballVAO);
	glBindVertexArray(ballVAO);


	glGenBuffers(1, &ballVBO);
	glBindBuffer(GL_ARRAY_BUFFER, ballVBO);
	glBufferData(GL_ARRAY_BUFFER, ballDrawData.vertices.size() * sizeof(Vertex), &ballDrawData.vertices[0], GL_STATIC_DRAW);

	//location 0: position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(0);

	////location 1: color
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.8, 0.8, 0.8, 1);
	glEnable(GL_DEPTH_TEST);


	basicShader->use();


	//set view
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));
	basicShader->setUniformMatrix4fv("view", view);

	//set projection
	glm::mat4 orthoProjection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 10.0f);
	basicShader->setUniformMatrix4fv("projection", orthoProjection);


	glm::mat4 model;

	for(int i = 0; i < players.size(); i++)
	{
		Player* currentPlayer = &players[i];

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(currentPlayer->pos.x,currentPlayer->pos.y,0));
		basicShader->setUniformMatrix4fv("model", model);

		glBindVertexArray(playerVAO);
		glDrawArrays(GL_TRIANGLES, 0, playerDrawData.vertices.size());
		glBindVertexArray(0);
	}
	for (int i = 0; i < balls.size(); i++)
	{
		Ball* currentBall = &balls[i];

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(currentBall->pos.x, currentBall->pos.y, 0));
		basicShader->setUniformMatrix4fv("model", model);

		glBindVertexArray(ballVAO);
		glDrawArrays(GL_TRIANGLES, 0, ballDrawData.vertices.size());
		glBindVertexArray(0);	
	}



	glutSwapBuffers();
}

void reshape(int newScreenWidth, int newScreenHeight)
{
	glutReshapeWindow(screenWidth, screenHeight);
}

void keyboard(unsigned char key, int mouseX, int mouseY)
{
	if(!pressedKeys[key])
		initialPressedKeys[key] = true;
	else
		initialPressedKeys[key] = false;

	pressedKeys[key] = true;
}

void keyboardSpecial(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_UP: 
		{
			if (!initialArrowUp && !arrowUp)
				initialArrowUp = true;
			else
				initialArrowUp = false;

			arrowUp = true;
		}	break;
		case GLUT_KEY_DOWN:
		{
			if (!initialArrowDown && !arrowDown)
				initialArrowDown = true;
			else
				initialArrowDown = false;

			arrowDown = true;
		}break;
	}
}

void keyboardSpecialUp(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_UP:
		{
			initialArrowUp = false;
			arrowUp = false;
		}
		case GLUT_KEY_DOWN:
		{
			initialArrowDown = false;
			arrowDown = false;
		}
	}
}

void keyboardUp(unsigned char key, int mouseX, int mouseY)
{
	pressedKeys[key] = false;
	initialPressedKeys[key] = false;
}

void handleKeys()
{
	if(pressedKeys[27])//esc
		glutLeaveMainLoop();

	if (pressedKeys['w'])
	{
		players[0].moveUp(currentFrameTime);
	}
	if (pressedKeys['s'])
	{
		players[0].moveDown(currentFrameTime);
	}
	if(arrowUp)
	{
		players[1].moveUp(currentFrameTime);
	}
	if(arrowDown)
	{
		players[1].moveDown(currentFrameTime);
	}

	if (initialPressedKeys['r'])
	{
		for (int i = 0; i < games.size(); i++)
		{
			games[i].StartRound();
		}
		initialPressedKeys['r'] = false;
	}
}

void frameTime()
{
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	currentFrameTime = currentTime - gameTime;
	gameTime = currentTime;
	
}

void update()
{
	frameTime();
	handleKeys();

	for (int i = 0; i < games.size(); i++)
	{
		games[i].gameStep(currentFrameTime);
	}

	glutPostRedisplay();
}

void init()
{
	glewInit();

	initShader();
	setupGames();

}

int main(int argc, char* argv[])
{
	glewInit();

	glutInit(&argc, argv);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("Pong");


	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(keyboardSpecial);
	glutSpecialUpFunc(keyboardSpecialUp);
	glutIdleFunc(update);



	glutMainLoop();

	return 1;
}