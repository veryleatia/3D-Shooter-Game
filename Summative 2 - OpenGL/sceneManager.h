#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\soil\SOIL.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "camera.h"
#include "player.h"

#include <vector>
#include "bullet.h"
#include "Enemies.h"
#include "Powerup.h"

#define BUTTON_UP 0
#define BUTTON_DOWN 1;

class cSceneManager
{
private:
	unsigned char keyState[255];
	bool playerAlive;
	bool playerWin;
	bool playerLose;
	bool enemy3MoveUp;
	bool isDeleted;
	int numOfEnemies;
	float cooldown;
	int score;
	int lives;
	int level;
	int rendernumber;
	float playerSpeed;

	cEnemies* enemy;
	cPlayer* player;
	cSprite* gameover;
	cSprite* mainmenu;
	cSprite* background;
	cSprite* win;
	cSprite* lose;
	cCamera* camera;
	std::vector<cPowerup*> VectorPowerups;
	std::vector<cBullet*> VectorBullets;
	std::vector<cEnemies*> VectorEnemies;

public:
	void init()
	{
		//change to a level system

		background->setNewPosition(glm::vec3(-1.0f, 0.0f, 0.0f));
		background->setScale(glm::vec3(15.0f, 30.0f, 1.0f));
		background->setImage("assets/sprites/floor.png");

		mainmenu->setNewPosition(glm::vec3(-0.4f, -2.0f, 1.5f));
		mainmenu->setScale(glm::vec3(15.0f, 30.0f, 1.0f));
		mainmenu->rotateX(45.0f);

		mainmenu->setImage("assets/sprites/mainmenu.png");
		gameover->setNewPosition(glm::vec3(-0.65f, -1.5f, 1.5f));
		gameover->setScale(glm::vec3(15.0f, 30.0f, 1.0f));
		gameover->rotateX(45.0f);
		gameover->setImage("assets/sprites/gameover.png");

		mainmenu->init();
		background->init();
		gameover->init();
		player->init();

		for (int i = 0; i < VectorEnemies.size(); ++i)
		{
			VectorEnemies[i]->init();
		}

		for (int i = 0; i < VectorPowerups.size(); ++i)
		{
			VectorPowerups[i]->init();
		}

		// was -4 10
		camera->setEye(-1.0f, -6.0f, 4.0f);
		camera->setCenter(0.0f, 0.5f, -1.0f);
		camera->setUp(0.0f, 0.0f, 1.0f);

		camera->setProjectionMatrix(45.0f, 800, 600, 0.5f, 100.0f);
		camera->setViewMatrix(camera->getEye(), camera->getEye() + camera->getCenter(), camera->getUp());
		win->setNewPosition(camera->getCenter());
		win->setScale(glm::vec3(4.0f, 4.0f, 1.0f));
		win->setImage("assets/sprites/win.png");
		win->init();
		lose->setNewPosition(camera->getCenter());
		lose->setScale(glm::vec3(4.0f, 4.0f, 1.0f));
		lose->setImage("assets/sprites/lose.png");
		lose->init();
	}

	bool getIsDeleted()
	{
		return isDeleted;
	}

	void render()
	{
		if (rendernumber == 0)
		{
			mainmenu->render(camera->getViewMatrix(), camera->getProjectionMatrix());
		}
		else if (rendernumber == 1)
		{

		}
	}
};