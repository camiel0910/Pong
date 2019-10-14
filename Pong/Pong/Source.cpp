#include <glew.h>	
#include <freeglut.h>
#include <iostream>
#include <glm.hpp>
#include "Shader.h"
#include "Player.h"


int screenWidth = 800;
int screenHeight = 600;
unsigned char pressedKeys[256];
unsigned char initialPressedKeys[256];
Shader* basicShader;
Player* testPlayer;

void display()
{
	
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

	if (pressedKeys['w'])
	{
		testPlayer->moveUp(0.1f);
		std::cout << testPlayer->pos.y << std::endl;
	}
	if (pressedKeys['s'])
	{
		testPlayer->moveDown(0.1f);
		std::cout << testPlayer->pos.y << std::endl;
	}


}

void update()
{
	handleKeys();

	glutPostRedisplay();
}

void init()
{
	glewInit();

	basicShader = new Shader("BasicShader.vs", "BasicShader.fs");
	basicShader->use();

	testPlayer = new Player(true);
}



int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("Pong");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutIdleFunc(update);

	init();

	glutMainLoop();

	return 1;
}