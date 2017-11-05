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
#define BUTTON_DOWN 1
unsigned char keyState[255];

class cSceneManager
{
public:
	cSceneManager()
	{
	}

	void init()
	{
		std::cout << "WASD To move the character" << std::endl;
		std::cout << "jilk to make the player shoot" << std::endl;
		std::cout << "The player box is blue" << std::endl;
		std::cout << "Red blocks are enemies, pink are powerups" << std::endl;
		std::cout << "Walk over the powerup to pick it up, it will grant a small speed boost" << std::endl;

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

	void render()
	{
		if (rendernumber == 0)
		{
			mainmenu->render(camera->getViewMatrix(), camera->getProjectionMatrix());

		}
		else if (rendernumber == 1)
		{
			background->render(camera->getViewMatrix(), camera->getProjectionMatrix());

			if (!VectorBullets.empty())
			{
				for (int i = 0; i < VectorBullets.size(); ++i)
				{
					VectorBullets[i]->render(camera->getViewMatrix(), camera->getProjectionMatrix());
				}
			}
			if (!VectorEnemies.empty())
			{
				for (int i = 0; i < VectorEnemies.size(); ++i)
				{
					VectorEnemies[i]->render(camera->getViewMatrix(), camera->getProjectionMatrix());
				}
			}
			if (!VectorPowerups.empty())
			{
				for (int i = 0; i < VectorPowerups.size(); ++i)
				{
					VectorPowerups[i]->render(camera->getViewMatrix(), camera->getProjectionMatrix());
				}
			}

			player->render(camera->getViewMatrix(), camera->getProjectionMatrix());

			if (playerWin)
			{
				win->render(camera->getViewMatrix(), camera->getProjectionMatrix());
			}
			if (playerLose)
			{
				lose->render(camera->getViewMatrix(), camera->getProjectionMatrix());
			}
		}
		else if (rendernumber == 2)
		{
			gameover->render(camera->getViewMatrix(), camera->getProjectionMatrix());
		}
	}

	void update(GLfloat _deltaTime)
	{
		// enemies/camera wont move if in mainmenu or gameover screens
		if (rendernumber == 0)
		{
			_deltaTime = 0;
		}
		else if (rendernumber == 1)
		{

		}
		else if (rendernumber == 2)
		{
			camera->setEye(-1.0f, -6.0f, 4.0f);
			camera->setCenter(0.0f, 0.5f, -1.0f);
			camera->setUp(0.0f, 0.0f, 1.0f);
			_deltaTime = 0;
		}
		if (lives == 0)
		{
			// Game over screen
			rendernumber = 2;

			// R to restart
			if (keyState[(unsigned char)'r'] == BUTTON_DOWN)
			{
				isDeleted = true;
			}
			for (int i = 0; i < VectorBullets.size(); ++i)
			{
				for (int j = 0; j < VectorEnemies.size(); ++j)
				{
					std::swap(VectorBullets[i], VectorBullets.back());
					VectorBullets.pop_back();
					std::swap(VectorEnemies[j], VectorEnemies.back());
					VectorEnemies.pop_back();
				}
			}

		}
		// If all enemies are dead
		else if (VectorEnemies.size() == 0)
		{
			// When no enemies are on the screen, delete all bullets
			for (int i = 0; i < VectorBullets.size(); ++i)
			{
				std::swap(VectorBullets[i], VectorBullets.back());
				VectorBullets.pop_back();
			}

			level += 1;
			std::cout << "Level: " << level << std::endl << std::endl << std::endl;

			player->getPlayer()->setNewPosition(glm::vec3(-0.5f, -0.5f, 0.25f));

			numOfEnemies += 1;
			playerSpeed = 0.0275f;

			for (int i = 0; i < VectorPowerups.size(); ++i)
			{
				VectorPowerups.pop_back();
			}

			VectorPowerups.push_back(new cPowerup());
			VectorPowerups.back()->init();

			for (int i = 0; i < numOfEnemies; ++i)
			{
				VectorEnemies.push_back(new cEnemies(0.015f));
				VectorEnemies[i]->init();
			}
		}
		for (int i = 0; i < VectorBullets.size(); ++i)
		{
			VectorBullets[i]->update(_deltaTime);
		}
		for (int i = 0; i < VectorEnemies.size(); ++i)
		{
			VectorEnemies[i]->update(_deltaTime, player->getPlayer()->getNewPositionX(), player->getPlayer()->getNewPositionY());
		}
		if (keyState[(unsigned char)'g'] == BUTTON_DOWN && rendernumber == 0)
		{
			rendernumber = 1;
		}
		if (keyState[(unsigned char)'w'] == BUTTON_DOWN && keyState[(unsigned char)'a'] == BUTTON_DOWN && playerAlive)
		{
			player->setSpeed(playerSpeed);
		}
		else if (keyState[(unsigned char)'w'] == BUTTON_DOWN && keyState[(unsigned char)'d'] == BUTTON_DOWN && playerAlive)
		{
			player->setSpeed(playerSpeed);
		}
		else if (keyState[(unsigned char)'s'] == BUTTON_DOWN && keyState[(unsigned char)'a'] == BUTTON_DOWN && playerAlive)
		{
			player->setSpeed(playerSpeed);
		}
		else if (keyState[(unsigned char)'s'] == BUTTON_DOWN && keyState[(unsigned char)'d'] == BUTTON_DOWN && playerAlive)
		{
			player->setSpeed(playerSpeed);
		}
		else if (keyState[(unsigned char)'w'] == BUTTON_DOWN && playerAlive)
		{
			player->setSpeed(playerSpeed + 0.0125);
		}
		else if (keyState[(unsigned char)'a'] == BUTTON_DOWN && playerAlive)
		{
			player->setSpeed(playerSpeed + 0.0125);
		}
		else if (keyState[(unsigned char)'s'] == BUTTON_DOWN && playerAlive)
		{
			player->setSpeed(playerSpeed + 0.0125);
		}
		else if (keyState[(unsigned char)'d'] == BUTTON_DOWN && playerAlive)
		{
			player->setSpeed(playerSpeed + 0.0125);
		}
		// R to restart
		if (keyState[(unsigned char)'r'] == BUTTON_DOWN)
		{
			isDeleted = true;
		}
		// collisions
		if (keyState[(unsigned char)'w'] == BUTTON_DOWN && playerAlive)
		{
			if (player->getPlayer()->getNewPositionY() > 3.6f)
			{

			}
			else
			{
				player->getPlayer()->setNewPositionY(player->getPlayer()->getNewPositionY() + player->getSpeed() * _deltaTime);
			}
		}

		if (keyState[(unsigned char)'a'] == BUTTON_DOWN && playerAlive)
		{
			if (player->getPlayer()->getNewPositionX() < -4.35f)
			{

			}
			else
			{
				player->getPlayer()->setNewPositionX(player->getPlayer()->getNewPositionX() - player->getSpeed() * _deltaTime);
			}
		}

		if (keyState[(unsigned char)'s'] == BUTTON_DOWN && playerAlive)
		{
			if (player->getPlayer()->getNewPositionY() < -3.45f)
			{

			}
			else
			{
				player->getPlayer()->setNewPositionY(player->getPlayer()->getNewPositionY() - player->getSpeed() * _deltaTime);
			}
		}

		if (keyState[(unsigned char)'d'] == BUTTON_DOWN && playerAlive)
		{
			if (player->getPlayer()->getNewPositionX() > 2.3f)
			{

			}
			else
			{
				player->getPlayer()->setNewPositionX(player->getPlayer()->getNewPositionX() + player->getSpeed() * _deltaTime);
			}
		}
		// Press to shoot
		if (keyState[(unsigned char)'i'] == BUTTON_DOWN && playerAlive && cooldown < 0.0f)
		{
			cooldown = 25.0f;
			VectorBullets.push_back(new cBullet(0, 1, player->getPlayer()->getNewPositionX(), player->getPlayer()->getNewPositionY()));
			VectorBullets.back()->init();
		}
		if (keyState[(unsigned char)'k'] == BUTTON_DOWN && playerAlive && cooldown < 0.0f)
		{
			cooldown = 25.0f;
			VectorBullets.push_back(new cBullet(0, -1, player->getPlayer()->getNewPositionX(), player->getPlayer()->getNewPositionY()));
			VectorBullets.back()->init();
		}
		if (keyState[(unsigned char)'l'] == BUTTON_DOWN && playerAlive && cooldown < 0.0f)
		{
			cooldown = 25.0f;
			VectorBullets.push_back(new cBullet(1, 0, player->getPlayer()->getNewPositionX(), player->getPlayer()->getNewPositionY()));
			VectorBullets.back()->init();
		}
		if (keyState[(unsigned char)'j'] == BUTTON_DOWN && playerAlive && cooldown < 0.0f)
		{
			cooldown = 25.0f;
			VectorBullets.push_back(new cBullet(-1, 0, player->getPlayer()->getNewPositionX(), player->getPlayer()->getNewPositionY()));
			VectorBullets.back()->init();
		}
		cooldown -= _deltaTime;
		// Bullets deleting on collision with wall
		for (int i = 0; i < VectorBullets.size(); ++i)
		{
			if (VectorBullets[i]->getBullet()->getNewPositionX() > 5.0f || VectorBullets[i]->getBullet()->getNewPositionX() < -5.0f || VectorBullets[i]->getBullet()->getNewPositionY() > 5.0f || VectorBullets[i]->getBullet()->getNewPositionY() < -5.0f)
			{
				std::swap(VectorBullets[i], VectorBullets.back());
				VectorBullets.pop_back();
			}
		}
		// Bullet Enemy Collision
		for (int i = 0; i < VectorBullets.size(); ++i)
		{
			for (int j = 0; j < VectorEnemies.size(); ++j)
			{
				if (((VectorBullets[i]->getBullet()->getNewPositionX() <= (VectorEnemies[j]->getEnemy()->getNewPositionX() + 0.35f)) && (VectorBullets[i]->getBullet()->getNewPositionX() >= (VectorEnemies[j]->getEnemy()->getNewPositionX() - 0.35f))) &&
					((VectorBullets[i]->getBullet()->getNewPositionY() <= (VectorEnemies[j]->getEnemy()->getNewPositionY() + 0.35f)) && (VectorBullets[i]->getBullet()->getNewPositionY() >= (VectorEnemies[j]->getEnemy()->getNewPositionY() - 0.35f))))
				{
					std::swap(VectorBullets[i], VectorBullets.back());
					VectorBullets.pop_back();
					std::swap(VectorEnemies[j], VectorEnemies.back());
					VectorEnemies.pop_back();
					score += 30;
					std::cout << "Score: " << score << std::endl;
					break;
				}
			}
		}
		// Player Powerup Collision
		for (int i = 0; i < VectorPowerups.size(); ++i)
		{
			if (player->getPlayer()->getNewPositionX() <= (VectorPowerups[i]->getPowerup()->getNewPositionX() + 0.35f) && player->getPlayer()->getNewPositionX() >= (VectorPowerups[i]->getPowerup()->getNewPositionX() - 0.35f) &&
				player->getPlayer()->getNewPositionY() <= (VectorPowerups[i]->getPowerup()->getNewPositionY() + 0.35f) && player->getPlayer()->getNewPositionY() >= (VectorPowerups[i]->getPowerup()->getNewPositionY() - 0.35f))
			{
				std::cout << "WASD To move the character" << std::endl;
				std::cout << "jilk to make the player shoot" << std::endl;
				std::cout << "The player box is blue" << std::endl;
				std::cout << "Red blocks are enemies, pink are powerups" << std::endl;
				std::cout << "Walk over the powerup to pick it up, it will grant a small speed boost" << std::endl;

				playerSpeed = 0.05;
				std::swap(VectorPowerups[i], VectorPowerups.back());
				VectorPowerups.pop_back();
			}
		}


		// Enemy Player Collision
		for (int i = 0; i < VectorEnemies.size(); ++i)
		{
			if (player->getPlayer()->getNewPositionX() <= (VectorEnemies[i]->getEnemy()->getNewPositionX() + 0.35f) && player->getPlayer()->getNewPositionX() >= (VectorEnemies[i]->getEnemy()->getNewPositionX() - 0.35f) &&
				player->getPlayer()->getNewPositionY() <= (VectorEnemies[i]->getEnemy()->getNewPositionY() + 0.35f) && player->getPlayer()->getNewPositionY() >= (VectorEnemies[i]->getEnemy()->getNewPositionY() - 0.35f))
			{
				lives -= 1;
				std::cout << "You have been hit by an enemy! Lives: " << lives << std::endl;
				std::swap(VectorEnemies[i], VectorEnemies.back());
				VectorEnemies.pop_back();
			}
		}

		if (player->getPlayer()->getNewPositionX() >= -2.5f && player->getPlayer()->getNewPositionX() <= 0.5f)
		{
			camera->setCenterX(player->getPlayer()->getNewPositionX());
		}

		if (player->getPlayer()->getNewPositionY() > -1.0f && player->getPlayer()->getNewPositionY() <= 1.0f)
		{
			camera->setCenterY(player->getPlayer()->getNewPositionY());
		}
		camera->update();
	}

	bool getIsDeleted()
	{
		return isDeleted;
	}

	void keyboard(unsigned char key)
	{
		keyState[key] = BUTTON_DOWN;
	}

	void keyboard_up(unsigned char key) 
	{
		keyState[key] = BUTTON_UP;
	}

private:
	
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


};