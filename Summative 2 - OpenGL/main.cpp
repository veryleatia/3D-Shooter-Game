#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\soil\SOIL.h"
#include "glm\glm.hpp"
#include "ShaderLoader.h"
#include "utils.h"
#include "camera.h"
#include "shape.h"

#include "iostream"
#include "time.h"
#include <string>

using namespace std;

GLuint program, vao, vbo;

#define BUTTON_UP 0	
#define BUTTON_DOWN 1
unsigned char keyState[255];


float Time;

int window;

CCamera* Camera = new CCamera;

//object here 
CShape* sparklefish = new CShape;
CShape* fish = new CShape;
CShape* cube = new CShape;


void keyboard(unsigned char key, int x, int y)
{
	keyState[key] = BUTTON_DOWN;
}

void keyboard_up(unsigned char key, int x, int y) 
{
	keyState[key] = BUTTON_UP;
}

void init()
{

	srand(static_cast<unsigned int> (time(NULL)));

	ShaderLoader shaderLoader;
	program = shaderLoader.CreateProgram("VAO_Triangle.vs", "VAO_Triangle.fs");

	Camera->CreateCamera(800.0, 600.0);

	sparklefish->init(program, "Assets/images/pyramid.jpg", Camera, 0.8, 0.8, Pyramid, 0.8);
	sparklefish->TranslateAbsolute(glm::vec3(0.5f, -0.8f, 1.0f));

	fish->init(program, "Assets/images/test.jpg", Camera, 1.5, 1.5, Square, 0);
	fish->TranslateAbsolute(glm::vec3(-0.9f, -0.9f, 0.0f));

	cube->init(program, "Assets/images/cube.jpg", Camera, 0.8, 0.8, Cube, 0.8);
	cube->TranslateAbsolute(glm::vec3(0.5f, 0.5f, 0.5f));
}

float fTime = 0;

void update()
{
	glUseProgram(program);
	GLint currentTimeLocation = glGetUniformLocation(program, "currentTime");

	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	float deltatime = (currentTime - Time) / 1000;
	Time = float(currentTime);

	glUseProgram(0);
	glutPostRedisplay();
}


void render(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.3f, 0.0f);

	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;

	sparklefish->render(Time);
	fish->render(Time);
	cube->render(Time);

	glutSwapBuffers();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 250);
	glutInitWindowSize(800, 600);

	window = glutCreateWindow("Summative 2 - OpenGL");
	glewInit();

	glEnable(GL_DEPTH_TEST);

	init();

	glutDisplayFunc(render);
	glutIdleFunc(update);
	glutMainLoop();

	return 0;
}