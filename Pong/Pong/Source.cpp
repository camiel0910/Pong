#include <glew.h>	
#include <freeglut.h>
#include <iostream>
#include <glm.hpp>
#include "Shader.h"
#include "Player.h"
#include "GameInstance.h"
#include <vector>


//opengl
int screenWidth = 800;
int screenHeight = 600;
unsigned char pressedKeys[256];
unsigned char initialPressedKeys[256];

//shader
Shader* basicShader;
unsigned int basicShaderVAO;
unsigned int basicShaderVBO;


//pong
std::vector<Player> players;
std::vector<Ball> balls;
std::vector<GameInstance> games;


void setupGames()
{
	players.push_back(Player(true, PLAYERTYPE::HUMAN));
	players.push_back(Player(false, PLAYERTYPE::NONE));
	balls.push_back(Ball());
	games.push_back(GameInstance(&players[players.size() - 2], &players[players.size() - 1], &balls[balls.size()-1]));
}

void initShader()
{
	basicShader = new Shader("BasicShader.vs", "BasicShader.fs");
	basicShader->use();

	glGenVertexArrays(1, &basicShaderVAO);
	glBindVertexArray(basicShaderVAO);


	glGenBuffers(1, &basicShaderVBO);	
	glBindBuffer(GL_ARRAY_BUFFER, basicShaderVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(playerDrawData.vertices), &playerDrawData.vertices[0], GL_STATIC_DRAW);

	//location 0: position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(0);

	////location 1: color
	//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

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
	//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	//basicShader->setUniformMatrix4fv("view", view);

	//set projection
	glm::mat4 projection(1.0f);
	//projection = glm::ortho(0.0f, 1000.0f, 0.0f, 1000.0f, -1.0f, 1.0f);
	//basicShader->setUniformMatrix4fv("projection", projection);

	


	glm::mat4 model;
	for(int i = 0; i < 1; i++)
	{
		Player* currentPlayer = &players[i];

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(currentPlayer->pos.x,currentPlayer->pos.y,0));
		//basicShader->setUniformMatrix4fv("model", model);

		glBindVertexArray(basicShaderVAO);
		glDrawArrays(GL_TRIANGLES, 0, playerDrawData.vertices.size());
		glBindVertexArray(0);
	}

	glutSwapBuffers();
}

void reshape(int newScreenWidth, int newScreenHeight)
{
	screenWidth = newScreenWidth;
	screenHeight = newScreenHeight;
}

void keyboard(unsigned char key, int mouseX, int mouseY)
{
	if (!pressedKeys[key])
		initialPressedKeys[key] = true;
	else
		initialPressedKeys[key] = false;

	pressedKeys[key] = true;
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

	/*if (pressedKeys['w'])
	{
		testPlayer->moveUp(0.1f);
		std::cout << testPlayer->pos.y << std::endl;
	}
	if (pressedKeys['s'])
	{
		testPlayer->moveDown(0.1f);
		std::cout << testPlayer->pos.y << std::endl;
	}*/


}

void update()
{
	handleKeys();

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
	glutIdleFunc(update);



	glutMainLoop();

	return 1;
}