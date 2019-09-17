#include <glew.h>	
#include <freeglut.h>
#include <iostream>
#include <glm.hpp>


int screenWidth = 800;
int screenHeight = 600;
unsigned char pressedKeys[256];
unsigned char initialPressedKeys[256];

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
	if (pressedKeys[27])//esc
		glutLeaveMainLoop();
}

void update()
{
	handleKeys();

	glutPostRedisplay();
}

void init()
{
	glewInit();
	glEnable(GL_DEPTH_TEST);
}



void main(int argc, char* argv[])
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
}