#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\soil\SOIL.h"
//#include "Dependencies\freetype2\freetype\freetype.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "Dependencies\FMOD\fmod.hpp"
#include "sceneManager.h"

#include <ctime>

cSceneManager* game = new cSceneManager();

GLfloat prevTime = 0;

FMOD::System* audioMgr;
FMOD::Sound* bgMusic;
FMOD::Sound* hitSound;
FMOD::Channel* channel;
FMOD::Channel* channel2;

//TextLabel* label;

bool InitFmod() {
	FMOD_RESULT result;

	result = FMOD::System_Create(&audioMgr);
	if (result != FMOD_OK) return false;

	result = audioMgr->init(50, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK) return false;

	return true;
}

const bool LoadAudio() {
	FMOD_RESULT result;

	result = audioMgr->createSound("assets/audio/hitsound.mp3", FMOD_DEFAULT, 0, &hitSound);
	result = audioMgr->createSound("assets/audio/bgMusic.mp3", FMOD_DEFAULT, 0, &bgMusic);

	bgMusic->setMode(FMOD_LOOP_NORMAL);

	return true;
}

void keyboard(unsigned char key, int x, int y)
{
	game->keyboard(key);
}

void keyboard_up(unsigned char key, int x, int y)
{
	game->keyboard_up(key);
}

void init()
{

	game->init();

	InitFmod();
	LoadAudio();
	audioMgr->playSound(bgMusic, 0, false, &channel);


}

void render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	game->render();

	//label->Render();

	glutSwapBuffers();
}

void update()
{
	GLfloat currentTime = glutGet(GLUT_ELAPSED_TIME);

	GLfloat deltaTime = (currentTime - prevTime) * 0.08f;
	prevTime = currentTime;

	game->update(deltaTime);

	if (game->getIsDeleted())
	{
		delete game;
		game = new cSceneManager();
		game->init();
	}
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(560, 240);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Hamish's Graphics Game");

	glClearColor(0.0, 0.0, 0.0, 1.0);

	glewInit();
	init();


	glEnable(GL_DEPTH_TEST);


	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboard_up);

	// register callbacks
	glutDisplayFunc(render);
	glutIdleFunc(update);
	glutMainLoop();

	return(0);
}